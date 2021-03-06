/******************************************************************************* 
* File Name:  B_I2CS_UDB_v1_20.v 
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*  
* Description: 
*  This file provides a top level model of the I2C Slave componnent
*  defining and all of the necessary interconnect.
* 
* Note: 
*
********************************************************************************
*                 Control and Status Register definitions
******************************************************************************** 
*
* TBD
******************************************************************************** 
*               Data Path register definitions   
******************************************************************************** 
*  INSTANCE NAME:  DatapathName 
*  DESCRIPTION: 
*  REGISTER USAGE: 
*   F0 => na 
*   F1 => na 
*   D0 => na  
*   D1 => na 
*   A0 => na 
*   A1 => na
*   TBD
* 
******************************************************************************** 
*               I*O Signals:   
******************************************************************************** 
*  IO SIGNALS: 
*  TBD
* 
********************************************************************************
* Copyright 2008-2009, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/



`include "cypress.v"
`ifdef B_I2CS_UDB_V_v1_10_ALREADY_INCLUDED
`else
`define B_I2CS_UDB_V_v1_10_ALREADY_INCLUDED

module B_I2CS_UDB_v1_20(
    input wire clk,
    input wire scl_in,
    input wire sda_in,
    output reg sda_out,
    output reg scl_out,
    output wire irq
);

    /* The clock is generated by a COUNT7 prescaler */
 //   wire clk;
  
    localparam I2C_IDLE      = 3'h0;
    localparam I2C_RX_DATA   = 3'h1;
    localparam I2C_RX_STALL  = 3'h2;
    localparam I2C_RX_ACK    = 3'h3;
    localparam I2C_TX_DATA   = 3'h4;
    localparam I2C_TX_ACK    = 3'h5;
    localparam I2C_TX_STALL  = 3'h6;

    localparam I2C_OWN_ADDR  = 7'h05;

    reg[2:0] state;
    reg byte_complete;
    reg address;
    reg start_sample;
    reg sda_in_dly;
    reg scl_in_dly;
    reg lrb;

    wire sda_negedge_detect;
    wire sda_posedge_detect;
    wire scl_negedge_detect;
    wire scl_posedge_detect;
    wire load_dummy;
    wire tx_reg_empty;
    wire address_match;
    wire count_eq_zero;
    wire shift_data_out;
    wire start_detect;
    wire stop_detect;
    wire shift_enable;
    wire counter_load;
    wire counter_enable;
    wire i2c_reset;
    
   
    wire [2:0] cs_addr_shifter;
    
       
    /**************************************************************************/
    /* Control Register Implementation                                        */
    /**************************************************************************/
	localparam I2C_CTRL_UNUSED7			= 8'h7;
	localparam I2C_CTRL_UNUSED6  		= 8'h6;	  
    localparam I2C_CTRL_UNUSED5       	= 8'h5;  /* interrupt on stop */
    localparam I2C_CTRL_ANY_ADDRESS  	= 8'h4;  /* interrupt on any address */
    localparam I2C_CTRL_TRANSMIT  		= 8'h3;  /* 1=transmit 0=receive */
    localparam I2C_CTRL_NACK     		= 8'h2;  /* 1=nack on read, 0=another byte */
    localparam I2C_CTRL_UNUSED1   		= 8'h1;  /* reserved for enable master */
	localparam I2C_CTRL_EN_SLAVE		= 8'h0;	 /* disable and reset the block */
	wire	[7:0]	control;		    

	/* Instantiate the control register */
    cy_psoc3_control #(.cy_force_order(1))	
    ctrlreg(
        /* output[07:00] */ .control(control)
    );

	wire ctrl_en_slave = control[I2C_CTRL_EN_SLAVE];
	wire ctrl_nack = control[I2C_CTRL_NACK];
	wire ctrl_transmit = control[I2C_CTRL_TRANSMIT];
	wire ctrl_any_address = control[I2C_CTRL_ANY_ADDRESS];
	
    /**************************************************************************/
    /* Status Register Implementation                                        */
    /**************************************************************************/
	localparam I2C_STS_UNUSED6			= 8'h6;	
	localparam I2C_STS_UNUSED5			= 8'h5;	
	localparam I2C_STS_STOP				= 8'h4;	
	localparam I2C_STS_ADDR				= 8'h3;	
	localparam I2C_STS_UNUSED2			= 8'h2;	
    localparam I2C_STS_LRB			    = 8'h1;
	localparam I2C_STS_BYTE_COMPLETE	= 8'h0;	 /* inton each matched address and data byte */


	/* all status set to transparent mode */

	wire	[6:0]	status;			        	/* Status Register Input */
	assign status[6:5] = 2'h0;				
    assign status[I2C_STS_STOP] = stop_detect; 			// sticky
    assign status[I2C_STS_ADDR] = address; 				// transparent
	assign status[I2C_STS_UNUSED2] = 1'b0;
	assign status[I2C_STS_LRB] = lrb;                   // transparent
	assign status[I2C_STS_BYTE_COMPLETE]  = byte_complete;  // sticky

    /* Instantiate the status register and interrupt hook*/
    cy_psoc3_statusi #(.cy_force_order(1), .cy_md_select(7'h11), .cy_int_mask(7'h00)) 
    stsreg(
        /* input          */ .clock(clk),
        /* input  [06:00] */ .status(status),
        /* output         */ .interrupt(irq)
    );
	
// start detect resets all state in the block, this excepted
always @(posedge clk)
begin
	sda_in_dly <= sda_in;
end

// start detect resets all state in the block, this excepted
always @(posedge clk)
begin
  	scl_in_dly <= scl_in;
end
    
assign sda_negedge_detect = ~sda_in & sda_in_dly;
assign sda_posedge_detect = sda_in & ~sda_in_dly;
assign scl_negedge_detect = ~scl_in & scl_in_dly;
assign scl_posedge_detect = scl_in & ~scl_in_dly;

// Compute start and stop
assign start_detect = scl_in & sda_negedge_detect;
assign stop_detect = scl_in & sda_posedge_detect;


// The start detect resets all state in the block, this excepted
always @(posedge clk)
begin
	start_sample <= start_detect;
end

//////////////////////////////////////////////////////////////////////////////
// COMBINATIONAL SIGNALS
//////////////////////////////////////////////////////////////////////////////

// Compute when to enable shifting
//
assign shift_enable = scl_posedge_detect & (state == I2C_RX_DATA | state == I2C_TX_DATA);

// Compute when to reload bit counter
//
assign counter_load = (state == I2C_RX_ACK) | (state == I2C_TX_ACK);

// Compute when to count
//
assign counter_enable = start_sample | shift_enable;

// Compute asynchronous reset
//
assign i2c_reset = ~ctrl_en_slave | start_detect;

// Compute when to continue transfer, CPU signals this with a write to FIFO F1
// this is dummy data, it isn't used, its loaded into A1
//
assign load_dummy = scl_in == 1'b0 & ~tx_reg_empty 
				& (state == I2C_RX_STALL | state == I2C_TX_STALL);

//////////////////////////////////////////////////////////////////////////////
// REGISTERED SIGNALS
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// LRB (last received bit, which is ACK/NACK from the master on WRITE command !!!!!
//////////////////////////////////////////////////////////////////////////////
//
always @(posedge clk or posedge i2c_reset)
begin
	if (i2c_reset) lrb <= 1'b0;
	else
	begin
		if (scl_posedge_detect  & state == I2C_TX_ACK )
			lrb <= sda_in;
	end
end



// Address bit distinguishs the address reception from data reception
// This is sticky until the user writes to continue the transfer
// 
always @(posedge clk or posedge i2c_reset)
begin
  if (i2c_reset) 	address <= 1'b0;
  else    	 		address <= (start_sample | address) & tx_reg_empty;
end



// Compute SCL out for stalling
// once scl_out goes low it's "latched" because the master stops
// released when we change state because of a FIFO write
//
always @(posedge clk or posedge i2c_reset)
begin
	if (i2c_reset) scl_out <= 1'b1;
	else
	begin
		if (state == I2C_RX_STALL & scl_in == 1'b0)
			scl_out <= 1'b0;
		else
		if (state == I2C_TX_STALL & scl_in == 1'b0)
			scl_out <= 1'b0;
		else
			scl_out <= 1'b1;
	end
end

// Compute SDA out
// change only on the negative edge of SCL
//
always @(posedge clk or posedge i2c_reset)
begin
	if (i2c_reset) sda_out <= 1'b1;
	else
	begin
		// Output data only on the negative edge or if the clock is low
		begin
			if (scl_negedge_detect | scl_out == 1'b0)
			begin
				if (state == I2C_TX_STALL | state == I2C_TX_DATA)	
					sda_out <= shift_data_out;
				else
				if (state == I2C_RX_STALL | state == I2C_RX_ACK) 	
					sda_out <= 1'b0;
				else						
					sda_out <= 1'b1;
			end
		end
	end
end
		

//////////////////////////////////////////////////////////////////////////////
// PROTOCOL STATE MACHINE
//////////////////////////////////////////////////////////////////////////////
// Includes states and byte complete computation
// State changes are aligned with input shifting which is on the positive edge of SCL
// There are two flows: RX data/address, and TX data, and the address state bit
// distinguishes between RX data and address

always @(posedge clk or posedge i2c_reset)
begin
	if (i2c_reset) 
	begin
  		state <= I2C_IDLE;
  		byte_complete <= 1'b0;
	end
	else
	begin

	byte_complete <= 1'b0;
	
    case (state)

      // Stay in IDLE state until start signal is detected
      
    I2C_IDLE: 
	begin
        if (start_sample) 	state <= I2C_RX_DATA;
        else       			state <= I2C_IDLE;
	end

	// WRITE (address or data)
	// The address state bit is used to distinguish
	// If an address and a match (or any address), stall, otherwise idle

    I2C_RX_DATA: 
	begin
        if (scl_posedge_detect && count_eq_zero) 
		begin
            if (!address | (address & (address_match | ctrl_any_address))) 
			begin
				byte_complete <= 1'b1;
				state <= I2C_RX_STALL;
			end
            else               					  
				state <= I2C_IDLE;
        end
        else
            state <= I2C_RX_DATA;
    end
    
	// Local CPU is reading address and deciding what to do, tx or rx, etc
    // Wait for a dummy write to the tx registe to start either read or write
	// If a write, local CPU can NACK... better not do this on address state

    I2C_RX_STALL: 
	begin
        if (scl_in == 1'b0 & ~tx_reg_empty) 
		begin
		// foo - go to ACK then idle? to be compatible wiht master
		// would need to also change sda_out computation if this changes (ctrl_nack)
			if (ctrl_nack) 	state <= I2C_IDLE;
			else			state <= I2C_RX_ACK;
		end
		else
			state <= I2C_RX_STALL;
    end 

    // ACK the received address or data

    I2C_RX_ACK: 
	begin
		if (scl_posedge_detect)
		begin
			if (ctrl_transmit) 	state <= I2C_TX_DATA; 
			else				state <= I2C_RX_DATA;
		end
        else         			
			state <= I2C_RX_ACK;
    end 

	// READ
    // 8-bits of data is shifting out

    I2C_TX_DATA: 
	begin
        if (scl_posedge_detect & count_eq_zero) 
			state <= I2C_TX_ACK;
        else
            state <= I2C_TX_DATA;
 	end	

	// Check for the ACK from the external master
	// If it's a NACK, then idle

    I2C_TX_ACK: 
	begin
        /*
        if (scl_posedge_detect) 
		begin
        	if (~sda_in)
			begin
				byte_complete <= 1'b1;
				state <= I2C_TX_STALL;
			end
			else             
				state <= I2C_IDLE; 
		end
	    else
            state <= I2C_TX_ACK;
        */
        
        if (scl_posedge_detect)  
		begin
			byte_complete <= 1'b1;
			state <= I2C_TX_STALL;
		end

    end

	// External master ACKed, so it wants more bytes

    I2C_TX_STALL: 
	begin
		if (scl_in == 1'b0  & ~tx_reg_empty)
			state <= I2C_TX_DATA;  
		else
            state <= I2C_TX_STALL;
	end

	endcase

  end
end

//////////////////////////////////////////////////////////////////////////////
// COUNT7 
//////////////////////////////////////////////////////////////////////////////
// Used for bit counting for address and data shift in and out

wire [2:0] count;
wire [3:0] foo;

    cy_psoc3_count7 #(.cy_period(7'd7),.cy_route_ld(1),.cy_route_en(1)) 
    counter(
        /*  input		     */  .clock(clk),
        /*  input		     */  .reset(i2c_reset),
        /*  input		     */  .load(counter_load),
        /*  input		     */  .enable(counter_enable),
        /*  output  [06:00]	 */  .count({foo,count}),
        /*  output		     */  .tc()
     );

assign count_eq_zero = (count == 3'b0);

//////////////////////////////////////////////////////////////////////////////
// DATAPATH 
//////////////////////////////////////////////////////////////////////////////
// Datapath is shifting into and out of A0
// User writes TX data to A0 and reads TX data from A0, always stalled
// F1 status is used to synchronize start of transmission

    assign cs_addr_shifter = {1'b0, load_dummy,  shift_enable };        
    
    cy_psoc3_dp8 #(.d0_init_a(8'h05),
    .cy_dpconfig_a(
    {
    	`CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_A0,
    	`CS_SHFT_OP___SL, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
    	`CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    	`CS_CMP_SEL_CFGA, /*CS_REG0 Comment:IDLE */
    	`CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_A0,
    	`CS_SHFT_OP___SL, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
    	`CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    	`CS_CMP_SEL_CFGA, /*CS_REG1 Comment:SHIFT A0 */
    	`CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_A0,
    	`CS_SHFT_OP___SL, `CS_A0_SRC_NONE, `CS_A1_SRC___F1,
    	`CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    	`CS_CMP_SEL_CFGA, /*CS_REG2 Comment:LOAD A1 from F1 */
    	`CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
    	`CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
    	`CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    	`CS_CMP_SEL_CFGA, /*CS_REG3 Comment: */
    	`CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
    	`CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
    	`CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    	`CS_CMP_SEL_CFGA, /*CS_REG4 Comment: */
    	`CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
    	`CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
    	`CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    	`CS_CMP_SEL_CFGA, /*CS_REG5 Comment: */
    	`CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
    	`CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
    	`CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    	`CS_CMP_SEL_CFGA, /*CS_REG6 Comment: */
    	`CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
    	`CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
    	`CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    	`CS_CMP_SEL_CFGA, /*CS_REG7 Comment: */
    	  8'hFF, 8'h00,	/*SC_REG4	Comment: */
    	  8'hFF, 8'h7F,	/*SC_REG5	Comment:Address Mask */
    	`SC_CMPB_A0_D1, `SC_CMPA_A0_D1, `SC_CI_B_ARITH,
    	`SC_CI_A_ARITH, `SC_C1_MASK_DSBL, `SC_C0_MASK_ENBL,
    	`SC_A_MASK_DSBL, `SC_DEF_SI_0, `SC_SI_B_DEFSI,
    	`SC_SI_A_ROUTE, /*SC_REG6 Comment: */
    	`SC_A0_SRC_ACC, `SC_SHIFT_SL, 1'b0,
    	1'b0, `SC_FIFO1_BUS, `SC_FIFO0_BUS,
    	`SC_MSB_DSBL, `SC_MSB_BIT7, `SC_MSB_NOCHN,
    	`SC_FB_NOCHN, `SC_CMP1_NOCHN,
    	`SC_CMP0_NOCHN, /*SC_REG7 Comment: */
    	 10'h0, `SC_FIFO_CLK__DP,`SC_FIFO_CAP_AX,
    	`SC_FIFO__EDGE,`SC_FIFO__SYNC,`SC_EXTCRC_DSBL,
    	`SC_WRK16CAT_DSBL /*SC_REG8 Comment: */
    })) shifter(
    /*  input                   */  .clk(clk),
    /*  input   [02:00]         */  .cs_addr(cs_addr_shifter),
    /*  input                   */  .route_si(sda_in),
    /*  input                   */  .route_ci(1'b0),
    /*  input                   */  .f0_load(1'b0),
    /*  input                   */  .f1_load(1'b0),
    /*  input                   */  .d0_load(1'b0),
    /*  input                   */  .d1_load(1'b0),
    /*  output                  */  .ce0(address_match),
    /*  output                  */  .cl0(),
    /*  output                  */  .z0(),
    /*  output                  */  .ff0(),
    /*  output                  */  .ce1(),
    /*  output                  */  .cl1(),
    /*  output                  */  .z1(),
    /*  output                  */  .ff1(),
    /*  output                  */  .ov_msb(),
    /*  output                  */  .co_msb(),
    /*  output                  */  .cmsb(),
    /*  output                  */  .so(shift_data_out),
    /*  output                  */  .f0_bus_stat(), 
    /*  output                  */  .f0_blk_stat(),
    /*  output                  */  .f1_bus_stat(), 
    /*  output                  */  .f1_blk_stat(tx_reg_empty)
    );

  

    
    
endmodule //B_I2CS_UDB_v1_20
`endif /* B_I2CS_UDB_V_v1_0_ALREADY_INCLUDED */

