/*******************************************************************************
* File Name: bMDIO_Interface_v1_0.v
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  The bMDIO_Interface module implements the CFP MDIO interface.
*
*  In Basic mode the component receives MDIO frame, checks PHY and DEV
*  addresses and drives the MDIO line during data portion of the MDIO read
*  frame. It generates an interrupt signal at the end of each frame if the 
*  PHY/DEV address matches with the component PHY/DEV address.
*  In Advanced mode the component additionally checks whether the received 
*  register address belongs to the one of the allocated register spaces, maps
*  this address into the register memory address and generates all control
*  signals for the DMAs.
*
********************************************************************************
*                 Datapath Register Definitions (16-bit)
********************************************************************************
*
*  INSTANCE NAME: MdioDp
*
*  DESCRIPTION:
*    This datapath checks if the physical address coming from MDIO matches with 
*    the configured one in the component customizer. It shifts the received and
*    sent frames. 
*
*  REGISTER USAGE:
*    F0 => Loads the register data to be serialized.
*    F1 => Captures the controlling bits from MDIO master.
*    D0 => Stores the frame pattern + MDIO slave PHY address + DEV address.
*    D1 => Used in advanced mode only. Contains register writable bitmask.
*    A0 => Shift the bits to/from MDIO pin.
*    A1 => Used in advanced mode only for W/R bit masking.
*
********************************************************************************
*  INSTANCE NAME: AddrComp (Advanced Mode Only)
*
*  DESCRIPTION:
*    This datapath determines whether a received address belongs to one of the
*    allocated register spaces and if it does, calculates the register offset
*    within this register space. 
*
*  REGISTER USAGE:
*    F0 => Contains the start addresses of all register spaces.
*    F1 => Contains the end addresses of all register spaces.
*    D0 => Loads the start address of each register space for the comparison.
*    D1 => Loads the start address of each register space for the comparison.
*    A0 => Contains the current MDIO address/register offset.
*    A1 => Stores the last accessed MDIO address.
*
********************************************************************************
*  INSTANCE NAME: AddrCalc
*
*  DESCRIPTION:
*    This datapath is used to calculate physical memory address of the accessed
*    register and the address of its configuration data. 
*
*  REGISTER USAGE:
*    F0 => Contains the register space info (register start memory address and 
*          the address of configurations array associated with this space.
*    F1 => Not used.
*    D0 => Stores the base memory address of the register space info array.
*    D1 => Size of register space info. Constant = 8.
*    A0 => Used for the address calculation. Meaning depends on state.
*    A1 => Used for the address calculation. Meaning depends on state.
*
********************************************************************************
*  INSTANCE NAME: FwAlu
*
*  DESCRIPTION:
*    This datapath along with DMA is used from the SetBits API to perform atomic
*    OR write operation. 
*
*  REGISTER USAGE:
*    F0 => Not used.
*    F1 => Not used.
*    D0 => Not used.
*    D1 => Not used.
*    A0 => Register value from the memory/result of OR operation.
*    A1 => Bits to set.
*
********************************************************************************
*                 I*O Signals:
********************************************************************************
*    Name           Direction    Description
*    mdio_out       output       MD IO output pin
*    interrupt      output       Interrupt signal when frame finished
*    addr           output       Indicates an address frame
*    cor            output       Indicates clear-on-read register access
*    rs_dma0        output       Triggers StartAddrDMA
*    rs_dma1        output       Triggers EndAddrDMA
*    info_dma       output       Triggers InfoDMA
*    addr_dma       output       Triggers AddrDMA
*    cfg_dma        output       Triggers CfgDMA
*    wr_dma         output       Triggers WrDMA
*    rd_dma         output       Triggers RdDMA
*    fw_dma         output       Triggers FwDMA
*    info_nrq       input        Indicates that InfoDMA transfer complete
*    addr_nrq       input        Indicates that AddrDMA transfer complete
*    wr_nrq         input        Indicates that WrDMA transfer complete
*    fw_nrq         input        Indicates that FwDMA transfer complete
*    mdio_in        input        MD IO input pin
*    mdc            input        MD clock in
*    enable         input        Synchronous active high enable
*    phy_addr[4:0]  input        Physical port address bus
*    force_cor      input        Forces the register to be cleared on read
*    en_page[7:0]   input        Enables the correspondent page(s)
*    clock          input        Input clock - at least 8 x MDC
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

`include "cypress.v"
`ifdef  bMDIO_Interface_v1_0_V_ALREADY_INCLUDED
`else
`define bMDIO_Interface_v1_0_V_ALREADY_INCLUDED

module bMDIO_Interface_v1_0
(
    output reg        mdio_out,  /* MD IO output pin (Merged)               */
    output reg        interrupt, /* Interrupt signal when frame finished    */
    output reg        address,   /* Indicates an address frame is received  */
    output reg        cor,       /* Indicates clear-on-read register access */
    output reg        read,      /* Indicates a read frame is received      */
    output wire       rs_dma0,   /* Triggers StartAddrDMA                   */
    output wire       rs_dma1,   /* Triggers EndAddrDMA                     */
    output reg        info_dma,  /* Triggers InfoDMA                        */
    output reg        addr_dma,  /* Set when AddrDMA transfer is complete   */
    output reg        cfg_dma,   /* Triggers CfgDMA to move register config */    
    output wire       wr_dma,    /* Triggers WrDMA to write/clear register  */
    output wire       rd_dma,    /* Triggers RdDMA to read register         */
    output reg        fw_dma,    /* Triggers FwDMA used by APIs             */
    input  wire       info_nrq,  /* Set when InfoDMA transfer is complete   */
    input  wire       addr_nrq,  /* Set when AddrDMA transfer is complete   */
    input  wire       wr_nrq,    /* Set when WrDMA transfer is complete     */
    input  wire       fw_nrq,    /* Set when FwDMA transfer is complete     */
    input  wire       mdio_in,   /* MD IO input pin                         */
    input  wire       mdc,       /* MD clock in                             */
    input  wire       enable,    /* Synchronous active high enable          */ 
    input  wire [4:0] phy_addr,  /* Physical port address bus               */
    input  wire       force_cor, /* Forces register clearing on read frame  */
    input  wire [7:0] en_page,   /* Register space enable signals           */  
    input  wire       clock      /* Clock the component operates off        */
);

    /***************************************************************************
    *           Parameters
    ***************************************************************************/
    /* Physical address and operation mode parameters */
    localparam PHYADDR_FIRMWARE = 1'b0;
    localparam PHYADDR_HARDWARE = 1'b1;
    localparam OPMODE_BASIC     = 1'b0;
    localparam OPMODE_ADVANCED  = 1'b1;
    parameter PhyAddressMode    = PHYADDR_FIRMWARE; /* default = Firmware */
    parameter OperationMode     = OPMODE_BASIC;     /* default = Basic    */
    /* Number of register spaces */
    parameter NumRegSpaces = 4;
    /* MDIO frame bit counter period */
    localparam [7:0] BitCountPeriod = 7'd31;
    /* Register page definition */
    localparam [2:0] MDIO_PAGE1 = 3'd0;
    localparam [2:0] MDIO_PAGE2 = 3'd1;
    localparam [2:0] MDIO_PAGE3 = 3'd2;
    localparam [2:0] MDIO_PAGE4 = 3'd3;
    localparam [2:0] MDIO_PAGE5 = 3'd4;
    localparam [2:0] MDIO_PAGE6 = 3'd5;
    localparam [2:0] MDIO_PAGE7 = 3'd6;
    localparam [2:0] MDIO_PAGE8 = 3'd7;
    
    /***************************************************************************
    *            UDB array version definitions 
    ***************************************************************************/   
    
    localparam CY_UDB_V0 = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_5A);    
    localparam CY_UDB_V1 = (!CY_UDB_V0);

    /***************************************************************************
    *       MDIO FRAME PROCESSING
    ***************************************************************************/
    reg        mdc_dly;       /* One cycle delay MDC clock                    */
    reg        busy;          /* Busy condition when processing a frame       */
    wire [6:0] count;         /* MDIO frame bit count                         */
    wire       tc;            /* Terminal count output                        */
    wire       nc1, nc2, nc3; /* nc bits connected to unused datapath outputs */
    reg  [1:0] opcode;        /* MDIO operation bits                          */
    wire       rising_mdc;    /* MDC rising edge                              */
    wire       so;            /* Shift out                                    */
    wire [1:0] ce0;           /* A0 == D0 condition                           */
    reg        ta_bits;       /* Set when turning around bits drive the MDIO  */
    reg        addr_match;    /* PHYADDR/DEVADDR detect condition             */
    reg        capture;       /* Forces A0 capture to F1                      */
    reg        mdio_enable;   /* Final mdio enable signal                     */
    
    /***************************************************************************
    *         Instantiation of udb_clock_enable primitive 
    ****************************************************************************
    * The udb_clock_enable primitive component allows to support clock enable 
    * mechanism and specify the intended synchronization behavior for the clock 
    * result (operational clock).
    */
    cy_psoc3_udb_clock_enable_v1_0 #(.sync_mode(`TRUE)) ClkSync
    (
        /* input  */    .clock_in(clock),
        /* input  */    .enable(1'b1),
        /* output */    .clock_out(op_clock)
    );

    /***************************************************************************
    *       Control register implementation                                      
    ***************************************************************************/   
    wire [7:0] ctrl;
    /* Control Register bit location (bits 7-2 are unused) */
    localparam [2:0] MDIO_CTRL_ENABLE     = 3'd0;
    localparam [2:0] MDIO_CTRL_INT_ENABLE = 3'd1;
    localparam [2:0] MDIO_CTRL_FW_TRIG    = 2'd2;
    
    /* Control register mode */
    generate
    if(CY_UDB_V0)
    begin: Direct
        cy_psoc3_control #(.cy_force_order(1)) CtlReg
        (
            /* output [07:00] */  .control(ctrl)
        );        
    end /* Direct */
    else
    begin: Sync
        cy_psoc3_control #(.cy_force_order(1), .cy_ctrl_mode_1(8'h00), .cy_ctrl_mode_0(8'h01)) CtlReg
        (
            /*  input         */  .clock(op_clock),
            /* output [07:00] */  .control(ctrl)
        );
    end /* Sync */
    endgenerate
    
    always @(posedge op_clock)
    begin
        mdio_enable <= ctrl[MDIO_CTRL_ENABLE] & enable;
    end
    
    /***************************************************************************
    *       MDIO physical address capture
    ***************************************************************************/
    generate
    if(PhyAddressMode == PHYADDR_HARDWARE)
    begin: Hardware
        cy_psoc3_status #(.cy_force_order(1), .cy_md_select(8'h0)) PhyAddr
        (
            /* input         */  .clock(op_clock),
            /* input [07:00] */  .status({3'b0, phy_addr}) /* Bits 7-5 unused */  
        );
    end /* Hardware */
    endgenerate
    
    /***************************************************************************
    *       MDIO frame detection                                                    
    ***************************************************************************/
    always @(posedge op_clock)
    begin
        /* If disable or TC is detected, not busy */
        if (~mdio_enable | tc)
        begin
            busy <= 1'b0;
        end
        else
        begin
            /* If start bit detected, busy till the counter TC happens */
            busy <= ~mdio_in | busy;
        end
    end
        
    /***************************************************************************
    *       MDC bus clock edge detection
    ***************************************************************************/
    always @(posedge op_clock)
    begin
        mdc_dly <= mdc;                          /* Delay MDC */
    end
    
    assign rising_mdc  =  mdc & ~mdc_dly;       /* Detect rising edge of MDC  */

    /***************************************************************************
    *       Operation code sampling
    ***************************************************************************/    
    always @(posedge op_clock)
    begin
        /* Opcode[1] (bit 3) is sampled when counter equal 29 */
        if((count[4:0] == 5'd29) & rising_mdc)
        begin 
            opcode[1] <= mdio_in;
        end
    end
    always @(posedge op_clock)
    begin
        /* Opcode[0] (bit 4) is sampled when counter equal 28 */
        if((count[4:0] == 5'd28) & rising_mdc)
        begin
            opcode[0] <= mdio_in;
        end
    end
    
    /***************************************************************************
    *       Count7 block used to count bits on the MDIO frame                      
    ***************************************************************************/
    cy_psoc3_count7 #(.cy_period(BitCountPeriod),.cy_route_ld(`TRUE),.cy_route_en(`TRUE)) 
    BitCounter
    (
        /*  input          */  .clock(op_clock),
        /*  input          */  .reset(1'b0),
        /*  input          */  .load(ld_count),     /* Re-load the counter */
        /*  input          */  .enable(en_count),   /* Counter enabled on rising edges of MDC */
        /*  output [06:00] */  .count(count),
        /*  output         */  .tc(tc)
     );

    assign ld_count = ~busy;             /* Load the counter */
    assign en_count = rising_mdc;        /* Enable the counter */
        
    /***************************************************************************
    *       Datapath control signals
    ***************************************************************************/
    /* The turn around bits should happen when counter equal 0x10 */
    always @(posedge op_clock)
    begin
        ta_bits <= (count[4:0] == 5'h10);
    end

    /* Check if the PHYADDR/DEVADDR matches */
    always @(posedge op_clock)
    begin
        if(~mdio_enable | tc)
        begin
            /* Clear when disabled or not busy */
            addr_match <= 1'b0;
        end
        else
        begin
            /* Set when the PHYADDR/DEVADDR matches (ce0 is high) */
            addr_match <= ce0[1] & count[4] | addr_match;
        end
    end
    
    /* MDIO Frame processing state machine states */
    localparam [2:0] MDIO_SLAVE_STATE_IDLE      = 3'd0;
    localparam [2:0] MDIO_SLAVE_STATE_SHIFT     = 3'd1;
    localparam [2:0] MDIO_SLAVE_STATE_LOAD_MEM  = 3'd2;
    localparam [2:0] MDIO_SLAVE_STATE_LOAD_MSK  = 3'd3;
    localparam [2:0] MDIO_SLAVE_STATE_A1_XOR_A0 = 3'd4;
    localparam [2:0] MDIO_SLAVE_STATE_A1_AND_D1 = 3'd5;
    localparam [2:0] MDIO_SLAVE_STATE_A0_XOR_A1 = 3'd6;
    localparam [2:0] MDIO_SLAVE_STATE_COR       = 3'd7;
    
    reg  [2:0] fp_state;
    wire [2:0] mdio_cs_addr;

    generate
    if(OperationMode == OPMODE_BASIC)
    /***************************************************************************
    *                       BASIC MODE OF OPERATION
    ***************************************************************************/
    begin: Basic
        /***********************************************************************
        * Capture shift register data into the write FIFO (F1) two times per 
        * frame:
        *  - 1st time: device address ended
        *  - 2nd time: at the end of the frame (tc from the counter)
        ***********************************************************************/
        always @(posedge op_clock)
        begin
            capture <= (ce0[1] & count[4]) | (tc & addr_match);
        end

        /***********************************************************************
        *       MDIO bus drive logic
        ***********************************************************************/
        always @(posedge op_clock)
        begin
            /*******************************************************************
            * Drive logic low during turn around bits, drive MDIO out during 16 
            * lower bits of a read frame. Otherwise drive a logic high.
            *******************************************************************/
            mdio_out <= (so & ~ta_bits) | ~(opcode[1] & addr_match) | (count[4] & ~ta_bits);
        end
        
        /***********************************************************************
        *       Interrupt generation logic                                             
        ***********************************************************************/
        always @(posedge op_clock)
        begin
            /* Generate a pulse if a frame is received and interrupts enabled */
            interrupt <= tc & capture & ctrl[MDIO_CTRL_INT_ENABLE];
        end
        
        /***********************************************************************
        *   State machine for the MDIO frame processing datapath (Basic mode)
        ***********************************************************************/
        always @(posedge op_clock)
        begin
            if(mdio_enable & rising_mdc)
            begin
                case(fp_state)
                MDIO_SLAVE_STATE_IDLE:
                    /* PHYADDR/DEVADDR matches and OP is Read */
                    if(ta_bits & opcode[1] & addr_match)
                    begin
                        fp_state <= MDIO_SLAVE_STATE_LOAD_MEM;
                    end
                    else
                    begin
                        fp_state <= MDIO_SLAVE_STATE_SHIFT;
                    end
                default:
                    fp_state <= MDIO_SLAVE_STATE_IDLE;
                endcase
            end
            else
            begin
                fp_state <= MDIO_SLAVE_STATE_IDLE;
            end
        end
        /* Use fp_state[1:0] bits to drive MdioDp datapath control signals */
        assign mdio_cs_addr = {1'b0, fp_state[1:0]};
    end
    else
    /***************************************************************************
    *                    ADVANCED MODE OF OPERATION
    ***************************************************************************/
    begin: Advanced /* Advanced mode */
        /* Register config bitmap
        * Bit 3: Register is clear on read (COR)
        * Bit 2: Register is write only (WO)
        * Bit 1: Trigger interrupt on write
        * Bit 0: Trigger interrupt on read
        */
        localparam [2:0] MDIO_REG_IS_COR       = 3'd3;
        localparam [2:0] MDIO_REG_IS_WO        = 3'd2;
        localparam [2:0] MDIO_REG_INT_ON_WRITE = 3'd1;
        localparam [2:0] MDIO_REG_INT_ON_READ  = 3'd0;
        
        wire [7:0] reg_cfg; /* Register configuration */
        
        /*************************************************************************** 
        * Depending on user settings in customizer a register space can have data
        * width of 8 or 16 bits, and be located in Flash or SRAM. Two control 
        * registers are used to provide these settings to hardware.
        ***************************************************************************/
        wire [7:0] data_width;
        wire [7:0] mem_type;
        reg is_16bit;       /* Set when the data has 16 bit width */
        reg is_sram;        /* Set when the register page is located in SRAM */  
        reg is_page_en;     /* Enable page signal for the current page */
        reg addr_is_valid;  /* Indicates whether the current address is valid */
        
        if(CY_UDB_V0)
        begin: Direct
            /* Register config control register (Direct mode) */
            cy_psoc3_control #(.cy_force_order(1)) CfgReg
            (
                /* output [07:00] */  .control(reg_cfg)
            );

            /* Data width register settings (Direct mode) */
            cy_psoc3_control #(.cy_force_order(1)) DataWidthCfg
            (
                /* output [07:00] */  .control(data_width)
            );
            
            /* Register page memory type settings (Direct mode) */
            cy_psoc3_control #(.cy_force_order(1)) MemTypeCfg
            (
                /* output [07:00] */  .control(mem_type)
            );
            
        end /* Direct */
        else
        begin: Sync
            /* Register config control register (Sync mode) */
            cy_psoc3_control #(.cy_force_order(1), .cy_ctrl_mode_1(8'h00), .cy_ctrl_mode_0(8'h8F)) CfgReg
            (
                /* input          */  .clock(op_clock),
                /* output [07:00] */  .control(reg_cfg)
            );
            /* Data width register settings (Sync mode) */
            cy_psoc3_control #(.cy_force_order(1), .cy_ctrl_mode_1(8'h00), .cy_ctrl_mode_0(8'hFF)) DataWidthCfg
            (
                /*  input         */  .clock(op_clock),
                /* output [07:00] */  .control(data_width)
            );
            /* Register page memory type settings (Sync mode) */
            cy_psoc3_control #(.cy_force_order(1), .cy_ctrl_mode_1(8'h00), .cy_ctrl_mode_0(8'hFF)) MemTypeCfg
            (
                /*  input         */  .clock(op_clock),
                /* output [07:00] */  .control(mem_type)
            );
        end /* Sync */    
        
        /***********************************************************************
        *       Opcode detection based on the frame type
        ***********************************************************************/
        localparam MDIO_OP_ADDR       = 2'd0;
        localparam MDIO_OP_WRITE      = 2'd1;
        localparam MDIO_OP_READ       = 2'd3;
        localparam MDIO_OP_POS_READ   = 2'd2;
        
        reg addr_match_dly; /* One cycle delayed addr_match signal            */
        reg op_address;     /* A pulse at the end of an address frame         */
        reg op_pos_read;    /* A pulse at the end of a pos read frame         */
        reg op_read;        /* A pulse at the end of a read or pos read frame */
        reg op_write;       /* A pulse at the end of a write frame            */
        reg cor_reg;        /* A pulse if addr_match and a COR reg is read    */
         

        always @(posedge op_clock)
        begin
            addr_match_dly  <= addr_match;
            op_write        <= addr_match & tc & (opcode == MDIO_OP_WRITE);
            op_address      <= addr_match & tc & (opcode == MDIO_OP_ADDR);
            op_pos_read     <= addr_match & tc & (opcode == MDIO_OP_POS_READ);
            op_read         <= addr_match & tc & opcode[1];
            cor_reg         <= addr_match & ~addr_match_dly & opcode[1] & (reg_cfg[MDIO_REG_IS_COR] | force_cor);
        end

        /***********************************************************************
        * Capture register data into the write FIFO (F1) after masking or COR 
        * operation and if the register is not configured to be read only, 
        * the address is valid and the associated register page is enabled.
        * Check only 2 bits for fp_state due to the state encoding.
        ***********************************************************************/
        always @(posedge op_clock)
        begin
            capture <= (fp_state[2:1] == 2'b11) & is_sram & addr_is_valid & is_page_en;
        end

        /***********************************************************************
        * Generate the read interrupt if a read or post read frame is received,
        * the accessed register allows interrupt on read, the address is valid,
        * and the associated register page is enabled.
        ***********************************************************************/
        always @(posedge op_clock)
        begin
            read <= op_read & reg_cfg[MDIO_REG_INT_ON_READ] & addr_is_valid & is_page_en;
        end

        /***********************************************************************
        * Generate the cor interrupt when the WrDMA completes and op_code is
        * read or pos_read.
        ***********************************************************************/
        always @(posedge op_clock)
        begin
            cor <= wr_nrq & opcode[1];
        end

        /***********************************************************************
        *       Interrupt generation logic                                             
        ***********************************************************************/
        always @(posedge op_clock)
        begin
            /* Generate a pulse if a write frame is received, interrupts
            *  enabled and the corresponding register allows interrupt */
            interrupt <= wr_nrq & ~opcode[1] & ctrl[MDIO_CTRL_INT_ENABLE] & 
                         reg_cfg[MDIO_REG_INT_ON_WRITE];
        end
        
        /***********************************************************************
        * Trigger Read DMA at the begining of each frame to update the FIFO 0
        * of the Frame processing datapath in preparation for a Read frame.
        ***********************************************************************/
        assign rd_dma = busy;
        
        /***********************************************************************
        *       MDIO bus drive logic
        ***********************************************************************/
        reg cfp_addr; /* Set if address is between 0x8000 and 0xFFFF */
        reg keep_high;
        always @(posedge op_clock)
        begin
            /*******************************************************************
            * Drive logic high if not CFP address or register is WO or a frame
            * is not to this slave or OP is not read or disabled.
            *******************************************************************/
            keep_high <= ~cfp_addr | (reg_cfg[MDIO_REG_IS_WO] & is_page_en) |
                         ~(opcode[1] & addr_match) | ~mdio_enable;
        end
        
        always @(posedge op_clock)
        begin
            /*******************************************************************
            * Drive logic low during turn around bits, drive MDIO out during 16 
            * lower bits of a read frame. Otherwise drive a logic high.
            *******************************************************************/
            mdio_out <= (so & ~ta_bits & addr_is_valid & is_page_en) | (count[4] & ~ta_bits) | (keep_high);
        end
        
        /***********************************************************************
        * State machine for the MDIO frame processing datapath (Advanced mode)
        ***********************************************************************/
        always @(posedge op_clock)
        begin
            if(mdio_enable)
            begin
                case(fp_state)
                MDIO_SLAVE_STATE_IDLE:
                if(rising_mdc)
                begin
                    /* PHYADDR/DEVADDR matches and OP is Read (Pos Read) */
                    if(ta_bits & opcode[1] & addr_match)
                    begin
                        fp_state <= MDIO_SLAVE_STATE_LOAD_MEM;
                    end
                    else
                    begin
                        fp_state <= MDIO_SLAVE_STATE_SHIFT;
                    end
                end
                else
                begin
                    if(op_write) /* generated at the end of a write frame */
                    begin
                        /* If a write frame is received, the state machine goes to
                        *  the LOAD MASK state for masking preparation */
                        fp_state <= MDIO_SLAVE_STATE_LOAD_MSK;
                    end
                    else
                    begin
                        /* If a read frame is received and the associated register
                        *  is configured to be COR. */
                        if(cor_reg)
                        begin
                            fp_state <= MDIO_SLAVE_STATE_COR;
                        end
                        else
                        begin
                            fp_state <= MDIO_SLAVE_STATE_IDLE;
                        end
                    end
                end
                
                MDIO_SLAVE_STATE_COR:
                    /* Clear A1 and load register data from F0 to A0. */
                    fp_state <= MDIO_SLAVE_STATE_IDLE;
                    
                MDIO_SLAVE_STATE_LOAD_MSK:
                    /* Load register value from F0 to A0 and received data bits
                    *  from A0 to A1 */            
                    fp_state <= MDIO_SLAVE_STATE_A1_XOR_A0;
                
                MDIO_SLAVE_STATE_A1_XOR_A0:
                /* Received bits XOR register value stored in register memory */ 
                begin
                    fp_state <= MDIO_SLAVE_STATE_A1_AND_D1;
                end
                
                MDIO_SLAVE_STATE_A1_AND_D1:
                /* Mask read only bits and go to the next state, where the masking
                * bits are XORed with the register memory value */
                begin
                    fp_state <= MDIO_SLAVE_STATE_A0_XOR_A1;
                end
                /* Stay in IDLE otherwise */
                default:
                    fp_state <= MDIO_SLAVE_STATE_IDLE;
                endcase
            end
            else
            begin
                fp_state <= MDIO_SLAVE_STATE_IDLE;
            end
        end
        assign mdio_cs_addr = fp_state;
        
        /***********************************************************************
        *
        *           ADDRESS ANALYZER MODULE
        *
        ***********************************************************************/
    
        /* FIFO status signals */
        wire [1:0] ac_f0_not_full;
        wire [1:0] ac_f1_not_full;
        wire [1:0] ac_f0_empty;
        wire [1:0] ac_f1_empty;
    
        /***************************************************************************
        * DMA request signals to write the register space addresses into FIFOs.
        * The FIFO bus status is used only from LSB datapath since the DMA accesses
        * 16-bit UDB address space.
        ***************************************************************************/
        assign rs_dma0 = ac_f0_not_full[0];
        assign rs_dma1 = ac_f1_not_full[0];
        /* Start processing if an address or post read frame received */
        wire start_analysis = op_address | op_pos_read;
    
        /***************************************************************************
        * rs_addr_ready calculation is based on the register space start address 
        * FIFO (F0) and register space end address FIFO (F1). Both FIFOs are updated 
        * by individual DMA channels, therefore the data from FIFOs must be loaded
        * only if both FIFOs are not empty. 
        ***************************************************************************/
        reg rs_addr_ready;
        always @(posedge op_clock)
        begin
            rs_addr_ready <= ~ac_f0_empty[0] & ~ac_f1_empty[0];
        end
    
        /*************************************************************************** 
        * Datapath conditional outputs used to determine if an address is in range
        * and which register space is accessed. The A0 is compared to D0 and D1 at
        * the same time. The calculation is based on ce0, cl0, ce1 and cl1 datapath
        * outputs.
        ***************************************************************************/
        wire [1:0] rsce0;   /* high, if an address is equal to start address */
        wire [1:0] rsce1;   /* high, if an address is equal to end address   */
        wire [1:0] rscl0;   /* high, if an address is below start address    */
        wire [1:0] rscl1;   /* high, if an address is below end address      */
        
        /***********************************************************************
        * The address is considered in range if it belongs to one of the 
        * register space boundaries.
        * Conditionals are chained, so use the outputs from MSB datapath only
        ***********************************************************************/
        reg addr_in_range;
        always @(posedge op_clock)
        begin
            addr_in_range <= ((~rscl0[1] & rscl1[1]) | rsce0[1] | rsce1[1]);
        end
        
        reg [2:0] rs_count;     /* Register space (page) index */
        reg [2:0] current_page; /* Store the index of the current page */

        wire rs_tc = (rs_count == (NumRegSpaces-1));
    
        localparam [3:0] MDIO_AC_STATE_IDLE        = 4'b0000;
        localparam [3:0] MDIO_AC_STATE_SHIFT       = 4'b0001;
        localparam [3:0] MDIO_AC_STATE_INC_ADDR    = 4'b0010;
        localparam [3:0] MDIO_AC_STATE_MULT        = 4'b0011;
        localparam [3:0] MDIO_AC_STATE_STORE_ADDR  = 4'b0100;
        localparam [3:0] MDIO_AC_STATE_COMP        = 4'b0101;
        localparam [3:0] MDIO_AC_STATE_WAIT        = 4'b0110;
        localparam [3:0] MDIO_AC_STATE_CALC_IDX    = 4'b0111;
        localparam [3:0] MDIO_AC_STATE_LOAD_RS     = 4'b1000;
    
        reg [3:0] rs_state;
        
        /* Generate a pulse when the last received address is updated with the
        * new one, and the frame is not a post read frame. */
        always @(posedge op_clock)
        begin
            /* Check only 3 bits of the rs_state due to the state encoding */
            address <= (rs_state[2:0] == 3'b100) & ~opcode[1];
        end
        
        wire rs_load = rs_state[3];
        /* rs_wait is generated when the address comparison state machine
        *  is in the WAIT state. Check only 3 bits due to the state encoding. */ 
        wire rs_wait = (rs_state[2:0] == 3'b110);

        reg rs_update; /* Indicates when the rs_count needs update */
        always @(posedge op_clock)
        begin
            rs_update <= rs_wait;
        end
        
        /***********************************************************************
        * addr_is_valid is used to store whether the last accessed address
        * is valid. Set if address is in range and cleared when the address
        * analysis starts.
        ***********************************************************************/
        always @(posedge op_clock)
        begin
            addr_is_valid <= ((addr_in_range & rs_update) | addr_is_valid) & ~start_analysis;
        end
        
        /***********************************************************************
        * Any access to addresses between 0x0000 and 0x7FFF should be ignored 
        * (no activity in the MDIO bus). To determine if the address is in range
        * between 0x0000 and 0x7FFF the MSB address bit is checked when the
        * state machine is in the STORE_ADDR state.
        ***********************************************************************/
        wire address_msb;       /* so out of the AddrComp datapath */
        always @(posedge op_clock)
        begin
            /* Check only 3 bits due to the state encoding */
            if(rs_state[2:0] == 3'b100)
            begin
                cfp_addr <= address_msb;
            end
        end
        
        /***********************************************************************
        *       State machine for the address compare (AddrComp) datapath
        ***********************************************************************/
        always @(posedge op_clock)
        begin
            case(rs_state)
            MDIO_AC_STATE_IDLE:
                /* IDLE until enabled */
                if(start_analysis)
                /* Start processing if an address or post read frame received */
                begin
                    if(op_address)
                    begin
                        rs_state <= MDIO_AC_STATE_STORE_ADDR;
                    end
                    else
                    begin
                        rs_state <= MDIO_AC_STATE_INC_ADDR;
                    end
                end
                else
                /* If the component is enabled and not processing an address
                * frame, shift in MDIO data on rising edge of MDC. */ 
                begin
                    if(rising_mdc & busy)
                    begin
                        rs_state <= MDIO_AC_STATE_SHIFT;
                    end
                    else
                    begin
                        rs_state <= MDIO_AC_STATE_IDLE;
                    end
                end
            
            MDIO_AC_STATE_INC_ADDR:
                /* If a post read frame received, increment the address 
                *  previously stored in A1 and start analysis */
                rs_state <= MDIO_AC_STATE_STORE_ADDR;
                
            MDIO_AC_STATE_STORE_ADDR:
                /* If an address frame received, store the address in A1. 
                *  Move to the next state if register space address FIFOs
                *  are not empty. */
                if(rs_addr_ready)
                begin
                    rs_state <= MDIO_AC_STATE_LOAD_RS;
                end
                
            MDIO_AC_STATE_LOAD_RS:
                /* In this state d0_load and d1_load are generated to load 
                *  register space boundaries from F0 to D0 (start address)
                *  and F1 to D1 (end address). */
                rs_state <= MDIO_AC_STATE_WAIT;
                
            MDIO_AC_STATE_WAIT:
                /* One cycle delay due to addr_in_range pipelining */
                rs_state <= MDIO_AC_STATE_COMP;

           MDIO_AC_STATE_COMP:
                /* If the address belongs to the current register space, 
                *  go to the CALC IDX state and calculate the register 
                *  index within given register space. */
                if(~rs_update & rs_addr_ready)
                begin
                    if(addr_in_range)
                    begin
                        rs_state <= MDIO_AC_STATE_CALC_IDX;
                    end
                    else
                    begin
                        /* Move to IDLE if rs_count done, else load next reg space
                        *  boundary */
                        rs_state <= (rs_count == 3'd0) ? MDIO_AC_STATE_IDLE : MDIO_AC_STATE_LOAD_RS;
                    end
                end
                else
                begin
                    rs_state <= MDIO_AC_STATE_COMP;
                end
            
            MDIO_AC_STATE_CALC_IDX:
                /* In this state a register index within a register space is
                *  calculated, by substracting the register space start
                *  address from the current address. and DMA that moves it to the address calculation
                *  datapath is triggered */
                if(is_16bit)
                begin
                    rs_state <= MDIO_AC_STATE_MULT;
                end
                else
                begin
                    rs_state <= (rs_count == 3'd0) ? MDIO_AC_STATE_IDLE : MDIO_AC_STATE_LOAD_RS;
                end
            
            MDIO_AC_STATE_MULT:
                /* If a 16-bit register is accessed, multiply index by two.
                *  If all register spaces are processed, move to the IDLE
                *  state. Else go to the LOAD state. */
                rs_state <= (rs_count == 3'd0) ? MDIO_AC_STATE_IDLE : MDIO_AC_STATE_LOAD_RS;
                
            default:
                rs_state <= MDIO_AC_STATE_IDLE;
            endcase
        end

        /* Register page width config MUX (8 to 1) */
        always @(posedge op_clock)
        begin
            case(current_page)
                MDIO_PAGE1: is_16bit <= data_width[MDIO_PAGE1];
                MDIO_PAGE2: is_16bit <= data_width[MDIO_PAGE2];
                MDIO_PAGE3: is_16bit <= data_width[MDIO_PAGE3];
                MDIO_PAGE4: is_16bit <= data_width[MDIO_PAGE4];
                MDIO_PAGE5: is_16bit <= data_width[MDIO_PAGE5];
                MDIO_PAGE6: is_16bit <= data_width[MDIO_PAGE6];
                MDIO_PAGE7: is_16bit <= data_width[MDIO_PAGE7];
                MDIO_PAGE8: is_16bit <= data_width[MDIO_PAGE8];
            default:
                is_16bit <= data_width[MDIO_PAGE1];
            endcase
        end
        
        /* Register page memory type config MUX (8 to 1) */
        always @(posedge op_clock)
        begin
            case(current_page)
                MDIO_PAGE1: is_sram <= mem_type[MDIO_PAGE1];
                MDIO_PAGE2: is_sram <= mem_type[MDIO_PAGE2];
                MDIO_PAGE3: is_sram <= mem_type[MDIO_PAGE3];
                MDIO_PAGE4: is_sram <= mem_type[MDIO_PAGE4];
                MDIO_PAGE5: is_sram <= mem_type[MDIO_PAGE5];
                MDIO_PAGE6: is_sram <= mem_type[MDIO_PAGE6];
                MDIO_PAGE7: is_sram <= mem_type[MDIO_PAGE7];
                MDIO_PAGE8: is_sram <= mem_type[MDIO_PAGE8];
            default:
                is_sram <= mem_type[MDIO_PAGE1];
            endcase
        end
        
        /* Enable page signal MUX (8 to 1) */
        always @(posedge op_clock)
        begin
            case(current_page)
                MDIO_PAGE1: is_page_en <= en_page[MDIO_PAGE1];
                MDIO_PAGE2: is_page_en <= en_page[MDIO_PAGE2];
                MDIO_PAGE3: is_page_en <= en_page[MDIO_PAGE3];
                MDIO_PAGE4: is_page_en <= en_page[MDIO_PAGE4];
                MDIO_PAGE5: is_page_en <= en_page[MDIO_PAGE5];
                MDIO_PAGE6: is_page_en <= en_page[MDIO_PAGE6];
                MDIO_PAGE7: is_page_en <= en_page[MDIO_PAGE7];
                MDIO_PAGE8: is_page_en <= en_page[MDIO_PAGE8];
            default:
                is_page_en <= en_page[MDIO_PAGE1];
            endcase
        end
        
        /* Determine the index of accessed register page */
        always @(posedge op_clock)
        begin
            if(addr_in_range & rs_update)
            begin
                current_page <= rs_count;
            end
        end
        
        /************************************************************************** 
        * 3-bit counter is used to count register spaces when the state machine 
        * goes over all register spaces to determine which register space is 
        * accessed.
        ***************************************************************************/
        always @(posedge op_clock)
        begin
            if(~mdio_enable)
            begin
                rs_count <= 3'd0;
            end
            else
            begin
                if(rs_update)
                begin
                    /* Reload counter on period */
                    rs_count <= (rs_tc) ? 3'd0 : rs_count + 1'b1;
                end
                else
                begin
                    rs_count <= rs_count;
                end
            end
        end

        localparam [3:0] MDIO_BA_STATE_RESET            = 4'b0000;
        localparam [3:0] MDIO_BA_STATE_HOLD             = 4'b0001;
        localparam [3:0] MDIO_BA_STATE_INC_OFFSET       = 4'b0011;
        localparam [3:0] MDIO_BA_STATE_UPDATE_INFO      = 4'b1001;
        localparam [3:0] MDIO_BA_STATE_LOAD_LSB         = 4'b0101;
        localparam [3:0] MDIO_BA_STATE_CALC_LSB         = 4'b0100;
        localparam [3:0] MDIO_BA_STATE_UPDATE_LSB       = 4'b0110;
        localparam [3:0] MDIO_BA_STATE_LOAD_MSB         = 4'b1101;
        localparam [3:0] MDIO_BA_STATE_CALC_MSB         = 4'b1111;
        localparam [3:0] MDIO_BA_STATE_UPDATE_MSB       = 4'b1110;
        localparam [3:0] MDIO_BA_STATE_SHIFT_1X         = 4'b1010;
        localparam [3:0] MDIO_BA_STATE_SHIFT_2X         = 4'b0010;
    
        reg [3:0] ba_state;
        
        /* Carry is asserted if a register space cross 64K memory block */
        wire [1:0] co_reg; /* Carry out from AddrCalc datapath */
        reg carry;
        /* Sample carry out from the lower address bits computation one clock
        *  after the state machine transits from CALC_LSB to UPDATE_LSB */
        reg sample_carry;
        
        always @(posedge op_clock)
        begin
            /* Only 3 bits of register state need to be checked */
            sample_carry <= (ba_state[2:0] == 3'b100);
        end
        
        always @(posedge op_clock)
        begin
            if(sample_carry) 
            begin
                carry <= co_reg[1];
            end
        end

        /*********************************************************************** 
        * The procedure for determining of the register address into PSoC memory
        * is the same as the determining address for the register configuration.
        * Therefore the state machine can use the same states and some 
        * indication when exit from the address processing.
        * cfg_done indicates that the register configuration addresses is
        * processing. It is checked in MSB_UPDATE state to exit from the address
        * calculation procedure.
        ***********************************************************************/
        reg cfg_done;
        always @(posedge op_clock)
        /* Set in SHIFT_1X/SHIFT_2X and clear in RESET. Use only 3 bits of the
        *  state register to save logic resources. */
        begin
            cfg_done <= (cfg_done | (ba_state[2:0] == 3'b010)) & ~(ba_state[2:0] == 3'b000);
        end
        
        /* Trigger DMA to move physical (PSoC) addresses of the register space
        *  memory and config array for the associated register space to the 
        *  address calculation datapath FIFO. */
        always @(posedge op_clock)
        begin
            /* 3'b110 = (MDIO_BA_STATE_UPDATE_LSB | MDIO_BA_STATE_UPDATE_MSB)
            *  Check only 3 bits due to the state encoding */
            addr_dma <= (ba_state[2:0] == 3'b110) | (ba_state == MDIO_BA_STATE_UPDATE_INFO);
        end
        always @(posedge op_clock)
        begin
            info_dma <= addr_nrq & (ba_state == MDIO_BA_STATE_UPDATE_INFO);
        end
        /* Trigger DMA to update register configuration */
        always @(posedge op_clock)
        begin
            cfg_dma <= addr_nrq & cfg_done & (ba_state == MDIO_BA_STATE_UPDATE_MSB);
        end
        
        always @(posedge op_clock)
        begin
            case(ba_state)
            MDIO_BA_STATE_RESET:
                /* Load start address of the array that contains physical memory
                * and configuration addresses for all register spaces
                * from D0 to A0. Clear A1. */
                ba_state <= MDIO_BA_STATE_HOLD;

            MDIO_BA_STATE_HOLD:
                /* Hold state. Move to RESET when address analysis starts */
                if(start_analysis)
                begin
                    ba_state <= MDIO_BA_STATE_RESET;
                end
                else
                begin
                    /* Move to the next state if register space boundary is
                    * loaded in address comparison (AddrComp) datapath. */
                    if(rs_wait)
                    begin
                        ba_state <= MDIO_BA_STATE_INC_OFFSET;
                    end
                    else
                    begin
                        ba_state <= MDIO_BA_STATE_HOLD;
                    end
                end

            MDIO_BA_STATE_INC_OFFSET:
                /* Increment A0 by 8 to point to the next register space. */ 
                if(addr_in_range)
                /* If an address belongs to the current register space, trigger DMA
                *  to update physical (PSoC) addresses of the register space memory
                *  and config array for the associated register space. */
                begin
                    ba_state <= MDIO_BA_STATE_UPDATE_INFO;
                end
                else
                begin
                    ba_state <= MDIO_BA_STATE_HOLD;
                end

            MDIO_BA_STATE_UPDATE_INFO:
                /***************************************************************
                * In this state AddrDMA is triggered to transfer register index
                * within the current register space from A0 reg of the AddrComp
                * datapath to A1 reg of the AddrCalc datapath. Then InfoDMA 
                * transfers the physical (PSoC) addresses of the register space
                * memory and config array for the associated register space into
                * F0 of the AddrCalc datapath.
                ***************************************************************/
                if(info_nrq)
                begin
                    ba_state <= MDIO_BA_STATE_LOAD_LSB;
                end

            MDIO_BA_STATE_LOAD_LSB:
                /* Load the lower 16 bit of the physical memory for the given 
                *  register space (F0 -> A0) */
                ba_state <= MDIO_BA_STATE_CALC_LSB;

            MDIO_BA_STATE_CALC_LSB:
                /* Add register index to the lower 16 address bits */
                ba_state <= MDIO_BA_STATE_UPDATE_LSB;

            MDIO_BA_STATE_UPDATE_LSB:
                /* Trigger AddrDMA to update 16 lower address bits of the Write 
                * and Read DMAs. Wait until the transfer is complted and move to
                * the next state. */
                if(addr_nrq)
                begin
                    ba_state <= MDIO_BA_STATE_LOAD_MSB;
                end

            MDIO_BA_STATE_LOAD_MSB:
                /* Load the upper 16 bit of the physical memory for the given 
                *  register space (F0 -> A0) */
                if(carry)
                /* Check the carry from the addition of the lower address bits */
                begin
                    ba_state <= MDIO_BA_STATE_CALC_MSB;
                end
                else
                begin
                    ba_state <= MDIO_BA_STATE_UPDATE_MSB;
                end

            MDIO_BA_STATE_CALC_MSB:
                /* Increment the upper 16 address bits */
                ba_state <= MDIO_BA_STATE_UPDATE_MSB;

            MDIO_BA_STATE_UPDATE_MSB:
                /* Trigger AddrDMA to update 16 upper address bits of the Write
                * and Read DMAs. Wait until the transfer is complted and move to
                * the next state. */
                if(addr_nrq)
                begin
                    /* Check whether both register memory address and register
                    * configuration address were calculated. If yes, move to the 
                    * RESET state. Otherwise move to the SHIFT states and go through
                    * LOAD_LSB - UPDATE_MSB one more time to calculate the 
                    * register configuration address. */
                    if(cfg_done)
                    begin
                        ba_state <= MDIO_BA_STATE_RESET;
                    end
                    else
                    begin
                        ba_state <= MDIO_BA_STATE_SHIFT_1X;
                    end
                end
                else
                begin
                    ba_state <= MDIO_BA_STATE_UPDATE_MSB;
                end

            MDIO_BA_STATE_SHIFT_1X:
                /* Each register has 4 bytes of configuration data. Multiply the
                * index by two to determine the offset within configuration data
                * array. */
                if(is_16bit)
                begin
                    ba_state <= MDIO_BA_STATE_LOAD_LSB;
                end
                else
                begin
                    ba_state <= MDIO_BA_STATE_SHIFT_2X;
                end

            MDIO_BA_STATE_SHIFT_2X:
                /* Shift the index one more time if the 8-bit register space
                *  is accessed. */
                ba_state <= MDIO_BA_STATE_LOAD_LSB;

            default:
                ba_state <= MDIO_BA_STATE_RESET;
            endcase
        end   

        /***********************************************************************
        * FwAlu datapath control. This datapath along with DMA is used to 
        * implement atomic firmaware operations, especially SetBits API.
        ***********************************************************************/
        localparam [0:0] MDIO_FW_STATE_IDLE = 1'b0;
        localparam [0:0] MDIO_FW_STATE_OR   = 1'b1;
        
        reg fw_state;
        
        always @(posedge op_clock)
        begin
            case(fw_state)
            MDIO_FW_STATE_IDLE:
                if(fw_nrq)
                begin
                    fw_state <= MDIO_FW_STATE_OR;
                end
            MDIO_FW_STATE_OR:
                fw_state <= MDIO_FW_STATE_IDLE;
            default
                fw_state <= MDIO_FW_STATE_IDLE;
            endcase
        end
        
        /* Generate a DMA request only when the component is not busy */
        reg fw_req;
        reg fw_req_dly;
        always @(posedge op_clock)
        begin
            if(~busy)
            begin
                fw_req <= ctrl[MDIO_CTRL_FW_TRIG];
            end
            fw_req_dly <= fw_req; /* One cycle delay fw_req */
            fw_dma <= fw_req ^ fw_req_dly; /* A pulse when fw_req changes */
        end

        /***************************************************************************
        * 16-bit address comparator. Loads register space boundaries from FIFOs to
        * D registers. Compares A0 (address) to D registers and generates compare
        * conditions. 
        ***************************************************************************/
        cy_psoc3_dp16 #(.cy_dpconfig_a(
        {
            `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM0:  Idle*/
            `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP___SL, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM1:  Shift in MDIO*/
            `CS_ALU_OP__INC, `CS_SRCA_A1, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC__ALU,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM2:  Inc addr if post read*/
            `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP___SL, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGB,
            `CS_CMP_SEL_CFGA, /*CFGRAM3:  Multiply by two if 16-bit reg accessed*/
            `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC__ALU,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM4:  Store current address*/
            `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM5:  Idle*/
            `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM6:  Idle*/
            `CS_ALU_OP__SUB, `CS_SRCA_A1, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM7:  Calculate reg idx that is accessed*/
            8'hFF, 8'h00,  /*CFG9:  */
            8'hFF, 8'hFF,  /*CFG11-10:  */
            `SC_CMPB_A1_D1, `SC_CMPA_A0_D1, `SC_CI_B_ARITH,
            `SC_CI_A_ARITH, `SC_C1_MASK_DSBL, `SC_C0_MASK_DSBL,
            `SC_A_MASK_DSBL, `SC_DEF_SI_0, `SC_SI_B_DEFSI,
            `SC_SI_A_ROUTE, /*CFG13-12:  */
            `SC_A0_SRC_ACC, `SC_SHIFT_SL, 1'h0,
            1'h0, `SC_FIFO1_BUS, `SC_FIFO0_BUS,
            `SC_MSB_DSBL, `SC_MSB_BIT0, `SC_MSB_NOCHN,
            `SC_FB_NOCHN, `SC_CMP1_NOCHN,
            `SC_CMP0_NOCHN, /*CFG15-14:  */
            10'h00, `SC_FIFO_CLK__DP,`SC_FIFO_CAP_AX,
            `SC_FIFO_LEVEL,`SC_FIFO_ASYNC,`SC_EXTCRC_DSBL,
            `SC_WRK16CAT_DSBL /*CFG17-16:  */
        }
        ), .cy_dpconfig_b(
        {
            `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM0:  Idle*/
            `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP___SL, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM1:  Shift in MDIO*/
            `CS_ALU_OP__INC, `CS_SRCA_A1, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC__ALU,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM2:  Inc address if post read frame*/
            `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP___SL, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM3:  Multiply by two if 16-bit reg accessed*/
            `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC__ALU,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM4:  Store current address*/
            `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM5:  Idle*/
            `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM6:  Idle*/
            `CS_ALU_OP__SUB, `CS_SRCA_A1, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM7:  Calculate reg idx that is accessed*/
            8'hFF, 8'h00,  /*CFG9:  */
            8'hFF, 8'hFF,  /*CFG11-10:  */
            `SC_CMPB_A1_D1, `SC_CMPA_A0_D1, `SC_CI_B_ARITH,
            `SC_CI_A_CHAIN, `SC_C1_MASK_DSBL, `SC_C0_MASK_DSBL,
            `SC_A_MASK_DSBL, `SC_DEF_SI_0, `SC_SI_B_DEFSI,
            `SC_SI_A_CHAIN, /*CFG13-12:  */
            `SC_A0_SRC_ACC, `SC_SHIFT_SL, 1'h0,
            1'h0, `SC_FIFO1_BUS, `SC_FIFO0_BUS,
            `SC_MSB_DSBL, `SC_MSB_BIT0, `SC_MSB_NOCHN,
            `SC_FB_NOCHN, `SC_CMP1_CHNED,
            `SC_CMP0_CHNED, /*CFG15-14:  */
            10'h00, `SC_FIFO_CLK__DP,`SC_FIFO_CAP_AX,
            `SC_FIFO_LEVEL,`SC_FIFO_ASYNC,`SC_EXTCRC_DSBL,
            `SC_WRK16CAT_DSBL /*CFG17-16:  */
        }
        )) AddrComp
        (
            /*  input                   */  .reset(1'b0),
            /*  input                   */  .clk(op_clock),
            /*  input   [02:00]         */  .cs_addr(rs_state[2:0]),
            /*  input                   */  .route_si(mdio_in),
            /*  input                   */  .route_ci(1'b0),
            /*  input                   */  .f0_load(1'b0),
            /*  input                   */  .f1_load(1'b0),
            /*  input                   */  .d0_load(rs_load),
            /*  input                   */  .d1_load(rs_load),
            /*  output  [01:00]         */  .ce0(rsce0),
            /*  output  [01:00]         */  .cl0(rscl0),
            /*  output  [01:00]         */  .z0(),
            /*  output  [01:00]         */  .ff0(),
            /*  output  [01:00]         */  .ce1(rsce1),
            /*  output  [01:00]         */  .cl1(rscl1),
            /*  output  [01:00]         */  .z1(),
            /*  output  [01:00]         */  .ff1(),
            /*  output  [01:00]         */  .ov_msb(),
            /*  output  [01:00]         */  .co_msb(),
            /*  output  [01:00]         */  .cmsb(),
            /*  output  [01:00]         */  .so({address_msb, nc3}),
            /*  output  [01:00]         */  .f0_bus_stat(ac_f0_not_full),
            /*  output  [01:00]         */  .f0_blk_stat(ac_f0_empty),
            /*  output  [01:00]         */  .f1_bus_stat(ac_f1_not_full),
            /*  output  [01:00]         */  .f1_blk_stat(ac_f1_empty)
        );
    
        cy_psoc3_dp16 #(.cy_dpconfig_a(
        {
            `CS_ALU_OP__XOR, `CS_SRCA_A1, `CS_SRCB_A1,
            `CS_SHFT_OP_PASS, `CS_A0_SRC___D0, `CS_A1_SRC__ALU,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM0:  Load base addr from D0 to A0; Clear A1;*/
            `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM1:  Idle*/
            `CS_ALU_OP_PASS, `CS_SRCA_A1, `CS_SRCB_D0,
            `CS_SHFT_OP___SL, `CS_A0_SRC_NONE, `CS_A1_SRC__ALU,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM2:  Multiple reg index by 2 (A1 << 1)*/
            `CS_ALU_OP__ADD, `CS_SRCA_A0, `CS_SRCB_A1,
            `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC___D1,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM3:  A0 = A0 + A1; A1 = 8;*/
            `CS_ALU_OP__ADD, `CS_SRCA_A0, `CS_SRCB_A1,
            `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM4:  The lower 16 address bits + index*/
            `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC___F0, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM5:  Load 16-bit address from F0 to A0*/
            `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM6:  Idle (Wait for DMA to complete transfer)*/
            `CS_ALU_OP__INC, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM7:  Incerement the upper address if required*/
            8'hFF, 8'h00,  /*CFG9:   */
            8'hFF, 8'hFF,  /*CFG11-10:   */
            `SC_CMPB_A1_D1, `SC_CMPA_A1_D1, `SC_CI_B_ARITH,
            `SC_CI_A_ARITH, `SC_C1_MASK_DSBL, `SC_C0_MASK_DSBL,
            `SC_A_MASK_DSBL, `SC_DEF_SI_0, `SC_SI_B_DEFSI,
            `SC_SI_A_DEFSI, /*CFG13-12:   */
            `SC_A0_SRC_ACC, `SC_SHIFT_SL, 1'h0,
            1'h0, `SC_FIFO1_BUS, `SC_FIFO0_BUS,
            `SC_MSB_DSBL, `SC_MSB_BIT0, `SC_MSB_NOCHN,
            `SC_FB_NOCHN, `SC_CMP1_NOCHN,
            `SC_CMP0_NOCHN, /*CFG15-14:   */
            10'h00, `SC_FIFO_CLK__DP,`SC_FIFO_CAP_AX,
            `SC_FIFO_LEVEL,`SC_FIFO__SYNC,`SC_EXTCRC_DSBL,
            `SC_WRK16CAT_DSBL /*CFG17-16:   */
        }
        ), .cy_dpconfig_b(
        {
            `CS_ALU_OP__XOR, `CS_SRCA_A1, `CS_SRCB_A1,
            `CS_SHFT_OP_PASS, `CS_A0_SRC___D0, `CS_A1_SRC__ALU,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM0:  Load base address to A0; Clear A1;*/
            `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM1:  Idle*/
            `CS_ALU_OP_PASS, `CS_SRCA_A1, `CS_SRCB_D0,
            `CS_SHFT_OP___SL, `CS_A0_SRC_NONE, `CS_A1_SRC__ALU,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM2:  Multiple reg index by 2 (A1 << 1)*/
            `CS_ALU_OP__ADD, `CS_SRCA_A0, `CS_SRCB_A1,
            `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC___D1,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM3:  A0 = A0 + A1; A1 = 8;*/
            `CS_ALU_OP__ADD, `CS_SRCA_A0, `CS_SRCB_A1,
            `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM4:  The lower 16 address bits + index*/
            `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC___F0, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM5:  Load 16-bit address from F0 to A0*/
            `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM6:  Idle (Wait for DMA to complete transfer)*/
            `CS_ALU_OP__INC, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM7:  Incerement the upper address if required*/
            8'hFF, 8'h00,  /*CFG9:   */
            8'hFF, 8'hFF,  /*CFG11-10:   */
            `SC_CMPB_A1_D1, `SC_CMPA_A1_D1, `SC_CI_B_ARITH,
            `SC_CI_A_CHAIN, `SC_C1_MASK_DSBL, `SC_C0_MASK_DSBL,
            `SC_A_MASK_DSBL, `SC_DEF_SI_0, `SC_SI_B_DEFSI,
            `SC_SI_A_CHAIN, /*CFG13-12:  */
            `SC_A0_SRC_ACC, `SC_SHIFT_SL, 1'h0,
            1'h0, `SC_FIFO1_BUS, `SC_FIFO0_BUS,
            `SC_MSB_DSBL, `SC_MSB_BIT0, `SC_MSB_NOCHN,
            `SC_FB_NOCHN, `SC_CMP1_NOCHN,
            `SC_CMP0_NOCHN, /*CFG15-14:  */
            10'h00, `SC_FIFO_CLK__DP,`SC_FIFO_CAP_AX,
            `SC_FIFO_LEVEL,`SC_FIFO__SYNC,`SC_EXTCRC_DSBL,
            `SC_WRK16CAT_DSBL /*CFG17-16:  */
        }
        )) AddrCalc
        (
            /*  input                   */  .reset(1'b0),
            /*  input                   */  .clk(op_clock),
            /*  input   [02:00]         */  .cs_addr(ba_state[2:0]),
            /*  input                   */  .route_si(1'b0),
            /*  input                   */  .route_ci(1'b0),
            /*  input                   */  .f0_load(1'b0),
            /*  input                   */  .f1_load(1'b0),
            /*  input                   */  .d0_load(1'b0),
            /*  input                   */  .d1_load(1'b0),
            /*  output  [01:00]         */  .ce0(),
            /*  output  [01:00]         */  .cl0(),
            /*  output  [01:00]         */  .z0(),
            /*  output  [01:00]         */  .ff0(),
            /*  output  [01:00]         */  .ce1(),
            /*  output  [01:00]         */  .cl1(),
            /*  output  [01:00]         */  .z1(),
            /*  output  [01:00]         */  .ff1(),
            /*  output  [01:00]         */  .ov_msb(),
            /*  output  [01:00]         */  .co_msb_reg(co_reg),
            /*  output  [01:00]         */  .cmsb(),
            /*  output  [01:00]         */  .so(),
            /*  output  [01:00]         */  .f0_bus_stat(),
            /*  output  [01:00]         */  .f0_blk_stat(),
            /*  output  [01:00]         */  .f1_bus_stat(),
            /*  output  [01:00]         */  .f1_blk_stat()
        );

        cy_psoc3_dp16 #(.cy_dpconfig_a(
        {
            `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM0:  */
            `CS_ALU_OP___OR, `CS_SRCA_A0, `CS_SRCB_A1,
            `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM1:  A0 = A0 OR A1*/
            `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM2:  */
            `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM3:  */
            `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM4:  */
            `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM5:  */
            `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM6:  */
            `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM7:  */
            8'hFF, 8'h00,  /*CFG9:  */
            8'hFF, 8'hFF,  /*CFG11-10:  */
            `SC_CMPB_A1_D1, `SC_CMPA_A1_D1, `SC_CI_B_ARITH,
            `SC_CI_A_ARITH, `SC_C1_MASK_DSBL, `SC_C0_MASK_DSBL,
            `SC_A_MASK_DSBL, `SC_DEF_SI_0, `SC_SI_B_DEFSI,
            `SC_SI_A_DEFSI, /*CFG13-12:  */
            `SC_A0_SRC_ACC, `SC_SHIFT_SL, 1'h0,
            1'h0, `SC_FIFO1_BUS, `SC_FIFO0_BUS,
            `SC_MSB_DSBL, `SC_MSB_BIT0, `SC_MSB_NOCHN,
            `SC_FB_NOCHN, `SC_CMP1_NOCHN,
            `SC_CMP0_NOCHN, /*CFG15-14:  */
            10'h00, `SC_FIFO_CLK__DP,`SC_FIFO_CAP_AX,
            `SC_FIFO_LEVEL,`SC_FIFO__SYNC,`SC_EXTCRC_DSBL,
            `SC_WRK16CAT_DSBL /*CFG17-16:  */
        }
        ), .cy_dpconfig_b(
        {
            `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM0:  */
            `CS_ALU_OP___OR, `CS_SRCA_A0, `CS_SRCB_A1,
            `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM1:  A0 = A0 OR A1*/
            `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM2:  */
            `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM3:  */
            `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM4:  */
            `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM5:  */
            `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM6:  */
            `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM7:  */
            8'hFF, 8'h00,  /*CFG9:  */
            8'hFF, 8'hFF,  /*CFG11-10:  */
            `SC_CMPB_A1_D1, `SC_CMPA_A1_D1, `SC_CI_B_ARITH,
            `SC_CI_A_ARITH, `SC_C1_MASK_DSBL, `SC_C0_MASK_DSBL,
            `SC_A_MASK_DSBL, `SC_DEF_SI_0, `SC_SI_B_DEFSI,
            `SC_SI_A_DEFSI, /*CFG13-12:  */
            `SC_A0_SRC_ACC, `SC_SHIFT_SL, 1'h0,
            1'h0, `SC_FIFO1_BUS, `SC_FIFO0_BUS,
            `SC_MSB_DSBL, `SC_MSB_BIT0, `SC_MSB_NOCHN,
            `SC_FB_NOCHN, `SC_CMP1_NOCHN,
            `SC_CMP0_NOCHN, /*CFG15-14:  */
            10'h00, `SC_FIFO_CLK__DP,`SC_FIFO_CAP_AX,
            `SC_FIFO_LEVEL,`SC_FIFO__SYNC,`SC_EXTCRC_DSBL,
            `SC_WRK16CAT_DSBL /*CFG17-16:  */
        }
        )) FwAlu
        (
            /*  input                   */  .reset(1'b0),
            /*  input                   */  .clk(op_clock),
            /*  input   [02:00]         */  .cs_addr({2'b0, fw_state}),
            /*  input                   */  .route_si(1'b0),
            /*  input                   */  .route_ci(1'b0),
            /*  input                   */  .f0_load(1'b0),
            /*  input                   */  .f1_load(1'b0),
            /*  input                   */  .d0_load(1'b0),
            /*  input                   */  .d1_load(1'b0),
            /*  output  [01:00]         */  .ce0(),
            /*  output  [01:00]         */  .cl0(),
            /*  output  [01:00]         */  .z0(),
            /*  output  [01:00]         */  .ff0(),
            /*  output  [01:00]         */  .ce1(),
            /*  output  [01:00]         */  .cl1(),
            /*  output  [01:00]         */  .z1(),
            /*  output  [01:00]         */  .ff1(),
            /*  output  [01:00]         */  .ov_msb(),
            /*  output  [01:00]         */  .co_msb(),
            /*  output  [01:00]         */  .cmsb(),
            /*  output  [01:00]         */  .so(),
            /*  output  [01:00]         */  .f0_bus_stat(),
            /*  output  [01:00]         */  .f0_blk_stat(),
            /*  output  [01:00]         */  .f1_bus_stat(),
            /*  output  [01:00]         */  .f1_blk_stat()
        );    
    end
    endgenerate
    
    /***************************************************************************
    * 16-bit datapath configured as MDIO shift registers and parallel to
    * serial interface.
    ***************************************************************************/
    cy_psoc3_dp16 #(.cy_dpconfig_a(
    {
        `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
        `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
        `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
        `CS_CMP_SEL_CFGA, /*CFGRAM0:  Idle*/
        `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
        `CS_SHFT_OP___SL, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
        `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
        `CS_CMP_SEL_CFGA, /*CFGRAM1:  Shift the mdio input in A0*/
        `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
        `CS_SHFT_OP_PASS, `CS_A0_SRC___F0, `CS_A1_SRC_NONE,
        `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
        `CS_CMP_SEL_CFGA, /*CFGRAM2:  Load the data to be read from F0*/
        `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
        `CS_SHFT_OP_PASS, `CS_A0_SRC___F0, `CS_A1_SRC__ALU,
        `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
        `CS_CMP_SEL_CFGA, /*CFGRAM3:  Load A0 (VAL) to A1; F0 (MEM) to A0*/
        `CS_ALU_OP__XOR, `CS_SRCA_A0, `CS_SRCB_A1,
        `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC__ALU,
        `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
        `CS_CMP_SEL_CFGA, /*CFGRAM4:  A1 = A0 (MEM) xor A1 (VAL)*/
        `CS_ALU_OP__AND, `CS_SRCA_A1, `CS_SRCB_D1,
        `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC__ALU,
        `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
        `CS_CMP_SEL_CFGA, /*CFGRAM5:  A1 = A1 AND D1 (MASK)*/
        `CS_ALU_OP__XOR, `CS_SRCA_A0, `CS_SRCB_A1,
        `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
        `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
        `CS_CMP_SEL_CFGA, /*CFGRAM6:  A0 = A1 XOR A0 (MEM)*/
        `CS_ALU_OP__XOR, `CS_SRCA_A0, `CS_SRCB_A0,
        `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
        `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
        `CS_CMP_SEL_CFGA, /*CFGRAM7:  COR operation*/
        8'hFF, 8'h00,  /*CFG9:  */
        8'hFF, 8'hFF,  /*CFG11-10:  Phy Address Match*/
        `SC_CMPB_A1_D1, `SC_CMPA_A1_D1, `SC_CI_B_ARITH,
        `SC_CI_A_ARITH, `SC_C1_MASK_ENBL, `SC_C0_MASK_ENBL,
        `SC_A_MASK_DSBL, `SC_DEF_SI_0, `SC_SI_B_DEFSI,
        `SC_SI_A_ROUTE, /*CFG13-12:  */
        `SC_A0_SRC_ACC, `SC_SHIFT_SL, 1'h0,
        1'h0, `SC_FIFO1__A0, `SC_FIFO0_BUS,
        `SC_MSB_DSBL, `SC_MSB_BIT7, `SC_MSB_NOCHN,
        `SC_FB_NOCHN, `SC_CMP1_NOCHN,
        `SC_CMP0_NOCHN, /*CFG15-14:  */
        10'h00, `SC_FIFO_CLK__DP,`SC_FIFO_CAP_AX,
        `SC_FIFO__EDGE,`SC_FIFO__SYNC,`SC_EXTCRC_DSBL,
        `SC_WRK16CAT_DSBL /*CFG17-16:  */
    }
    ), .cy_dpconfig_b(
    {
        `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
        `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
        `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
        `CS_CMP_SEL_CFGA, /*CFGRAM0:  Idle*/
        `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
        `CS_SHFT_OP___SL, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
        `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
        `CS_CMP_SEL_CFGA, /*CFGRAM1:  Shift the mdio data in A0*/
        `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
        `CS_SHFT_OP_PASS, `CS_A0_SRC___F0, `CS_A1_SRC_NONE,
        `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
        `CS_CMP_SEL_CFGA, /*CFGRAM2:  Load the data to be read from F0*/
        `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
        `CS_SHFT_OP_PASS, `CS_A0_SRC___F0, `CS_A1_SRC__ALU,
        `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
        `CS_CMP_SEL_CFGA, /*CFGRAM3:  Load A0 (VAL) to A1; F0 (MEM) to A0*/
        `CS_ALU_OP__XOR, `CS_SRCA_A0, `CS_SRCB_A1,
        `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC__ALU,
        `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
        `CS_CMP_SEL_CFGA, /*CFGRAM4:  A1 = A0 (MEM) xor A1 (VAL)*/
        `CS_ALU_OP__AND, `CS_SRCA_A1, `CS_SRCB_D1,
        `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC__ALU,
        `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
        `CS_CMP_SEL_CFGA, /*CFGRAM5:  A1 = A1 AND D1 (MASK)*/
        `CS_ALU_OP__XOR, `CS_SRCA_A0, `CS_SRCB_A1,
        `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
        `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
        `CS_CMP_SEL_CFGA, /*CFGRAM6:  A0 = A1 XOR A0 (MEM)*/
        `CS_ALU_OP__XOR, `CS_SRCA_A0, `CS_SRCB_A0,
        `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
        `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
        `CS_CMP_SEL_CFGA, /*CFGRAM7: COR operation*/
        8'hFF, 8'h00,  /*CFG9:  */
        8'hFF, 8'hF3,  /*CFG11-10:  Phy Address Match */
        `SC_CMPB_A1_D1, `SC_CMPA_A1_D1, `SC_CI_B_ARITH,
        `SC_CI_A_ARITH, `SC_C1_MASK_DSBL, `SC_C0_MASK_ENBL,
        `SC_A_MASK_DSBL, `SC_DEF_SI_0, `SC_SI_B_DEFSI,
        `SC_SI_A_CHAIN, /*CFG13-12:  */
        `SC_A0_SRC_ACC, `SC_SHIFT_SL, 1'h0,
        1'h0, `SC_FIFO1__A0, `SC_FIFO0_BUS,
        `SC_MSB_DSBL, `SC_MSB_BIT7, `SC_MSB_NOCHN,
        `SC_FB_NOCHN, `SC_CMP1_CHNED,
        `SC_CMP0_CHNED, /*CFG15-14:  */
        10'h00, `SC_FIFO_CLK__DP,`SC_FIFO_CAP_AX,
        `SC_FIFO__EDGE,`SC_FIFO__SYNC,`SC_EXTCRC_DSBL,
        `SC_WRK16CAT_DSBL /*CFG17-16:  */
    }
    )) MdioDp
    (
        /*  input                   */  .reset(1'b0),
        /*  input                   */  .clk(op_clock),
        /*  input   [02:00]         */  .cs_addr(mdio_cs_addr),
        /*  input                   */  .route_si(mdio_in),
        /*  input                   */  .route_ci(1'b0),
        /*  input                   */  .f0_load(1'b0),
        /*  input                   */  .f1_load(capture),
        /*  input                   */  .d0_load(1'b0),
        /*  input                   */  .d1_load(1'b0),
        /*  output  [01:00]         */  .ce0(ce0), /* PHYADRR/DEVADDR detect */
        /*  output  [01:00]         */  .cl0(),
        /*  output  [01:00]         */  .z0(),
        /*  output  [01:00]         */  .ff0(),
        /*  output  [01:00]         */  .ce1(),
        /*  output  [01:00]         */  .cl1(),
        /*  output  [01:00]         */  .z1(),
        /*  output  [01:00]         */  .ff1(),
        /*  output  [01:00]         */  .ov_msb(),
        /*  output  [01:00]         */  .co_msb(),
        /*  output  [01:00]         */  .cmsb(),
        /*  output  [01:00]         */  .so({so,nc1}),
        /*  output  [01:00]         */  .f0_bus_stat(),
        /*  output  [01:00]         */  .f0_blk_stat(),
        /*  output  [01:00]         */  .f1_bus_stat({wr_dma, nc2}),
        /*  output  [01:00]         */  .f1_blk_stat()
    );    

endmodule

`endif /* bMDIO_Interface_v1_0_V_ALREADY_INCLUDED */
