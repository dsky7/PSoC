/*******************************************************************************
* File Name:  B_SPI_Slave_v2_60.v
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides a base level model of the SPI Slave component
*
* Note:
*  None
********************************************************************************
*                 Control and Status Register definitions
********************************************************************************
*
*  Control Register Definition
*  +=======+--------+--------+--------+--------+--------+--------+--------+--------+
*  |  Bit  |   7    |   6    |   5    |   4    |   3    |   2    |   1    |   0    |
*  +=======+--------+--------+--------+--------+--------+--------+--------+--------+
*  | Desc  | unused | unused | unused | unused |unused  |unused  |unused  | tx_en  |
*  +=======+--------+--------+--------+--------+--------+--------+--------+--------+
*
*      tx_en        =>   0 = disable tx (for Bidirectional Mode only)
*                        1 = enable  tx (fof Bidirectional Mode only)
*
*  Tx interrupt Status Register Definition
*  +=======+--------+--------+--------+--------+--------+--------+--------+--------+
*  |  Bit  |   7    |   6    |   5    |   4    |   3    |   2    |   1    |   0    |
*  +=======+--------+--------+--------+--------+--------+--------+--------+--------+
*  | Desc |interrupt|bt_cplt |unused  |unused  |unused  |tx_empty |tx_n_f |spi_done|
*  +=======+--------+--------+--------+--------+--------+--------+--------+--------+

*  Rx interrupt Status Register Definition
*  +=======+--------+--------+--------+--------+--------+--------+--------+--------+
*  |  Bit  |   7    |   6    |   5    |   4    |   3    |   2    |   1    |   0    |
*  +=======+--------+--------+--------+--------+--------+--------+--------+--------+
*  | Desc |interrupt|rx_full |rx_f_ovr|rx_f_e  |rx_n_e  | unused |unused  | unused |
*  +=======+--------+--------+--------+--------+--------+--------+--------+--------+
*    spi_done  =>  0 = spi transmission not done
*                  1 = spi transmission done
*
*    tx_n_f    =>  0 = TX FIFO full
*                  1 = TX not full
*
*    tx_empty  =>  0 = TX_FIFO not empty
*                  1 = TX FIFO empty
*
*    rx_n_e    =>  0 =  RX FIFO empty
*                  1 =  RX FIFO not empty
*
*    rx_f_e    =>  0 = RX FIFO not empty
*                  1 = RX FIFO empty
*
*    rx_f_ovr  =>  0 = RX FIFO not overrun
*                  1 = RX FIFO overrun
*
*    rx_full   =>  0 = RX FIFO not full
*                  1 = RX FIFO full
*
*    bt_cplt   =>  0 = byte/word transfer is not complete
*                  1 = byte/word transfer complete
*
********************************************************************************
*                 Data Path register definitions
********************************************************************************
*  INSTANCE NAME:  DatapathName
*  DESCRIPTION:
*  REGISTER USAGE:
*    F0 => TX FIFO buffer
*    F1 => RX FIFO buffer
*    D0 => na
*    D1 => na
*    A0 => Current SPI Value(MISO data is shifted out, MOSI data is shifted in)
*    A1 => na
*
********************************************************************************
*               I*O Signals:
********************************************************************************
*  IO SIGNALS:
*
*     reset       input     component reset input
*    clock        input     component clock input
*    mosi         input     SPI MOSI input
*    sclk         input     SPI SCLK input
*    ss           input     SPI SS input
*    tx_enable    output    tx enable output(is used for Bidirectional Mode only)
*    miso         output    SPI MISO output
*    interrupt    output    interrupt output
*
********************************************************************************
********************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

`include "cypress.v"
`ifdef B_SPI_Slave_v2_60_V_ALREADY_INCLUDED
`else
`define B_SPI_Slave_v2_60_V_ALREADY_INCLUDED

module B_SPI_Slave_v2_60(
    input  wire  reset,     /* System Reset             */
    input  wire  clock,     /* System Clk - 2x Bit rate */
    input  wire  mosi,      /* SPI MOSI input           */
    input  wire  sclk,      /* SPI SCLK input           */
    input  wire  ss,        /* SPI SS input             */

    output  wire tx_enable, /* tx enable control output         */
    output  wire miso,      /* SPI MISO output                  */
    output  wire tx_interpt,/* Status Register Interrupt output */
    output  wire rx_interpt /* Status Register Interrupt output */
);
    localparam SPIS_MSB_FIRST = 1'b0;
    localparam SPIS_LSB_FIRST = 1'b1;

    /**************************************************************************
    * UDB revisions
    **************************************************************************/

    localparam CY_UDB_V0 = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_5A);
    localparam CY_UDB_V1 = (!CY_UDB_V0);

    /* Default is rising edge mode */
    parameter ModeCPHA               = 1'b0;
    parameter ModePOL                = 1'b0; /* Default is rising edge mode */
    parameter [0:0] ShiftDir         = SPIS_MSB_FIRST;
    parameter [5:0] NumberOfDataBits = 7'd8;
    parameter BidirectMode = 0;

    generate
    if(CY_UDB_V0)
    begin:es2

        B_SPI_Slave_ES2_v2_60 #(.ModePOL(ModePOL), .ModeCPHA(ModeCPHA),.ShiftDir(ShiftDir),
                          .NumberOfDataBits(NumberOfDataBits), .BidirectMode(BidirectMode))
        SPISlave(
            .reset(reset),
            .clock(clock),
            .mosi(mosi),
            .sclk(sclk),
            .ss(ss),
            .tx_enable(tx_enable),
            .miso(miso),
            .tx_interpt(tx_interpt),
            .rx_interpt(rx_interpt)
        );

    end
    else begin:es3

        B_SPI_Slave_ES3_v2_60 #(.ModePOL(ModePOL), .ModeCPHA(ModeCPHA),.ShiftDir(ShiftDir),
                          .NumberOfDataBits(NumberOfDataBits),.BidirectMode(BidirectMode))
        SPISlave(
            .reset(reset),
            .clock(clock),
            .mosi(mosi),
            .sclk(sclk),
            .ss(ss),
            .tx_enable(tx_enable),
            .miso(miso),
            .tx_interpt(tx_interpt),
            .rx_interpt(rx_interpt)
        );
    end

    endgenerate
    endmodule

    `ifdef B_SPI_Slave_ES3_v2_60_V_ALREADY_INCLUDED
    `else
    `define B_SPI_Slave_ES3_v2_60_V_ALREADY_INCLUDED

    module B_SPI_Slave_ES3_v2_60(
        input  wire reset,     /* System Reset             */
        input  wire clock,     /* System Clk - 2x Bit rate */
        input  wire mosi,      /* SPI MOSI input           */
        input  wire sclk,      /* SPI SCLK input           */
        input  wire ss,        /* SPI SS input             */

        output wire tx_enable, /* tx enable control output         */
        output wire miso,      /* SPI MISO output                  */
        output wire tx_interpt,/* Status Register Interrupt output */
        output wire rx_interpt /* Status Register Interrupt output */
);

    /* bit order: default is MSb first (i.e Shift Left and ShiftLeft in static configuration is = 0) */
    /* DO NOT CHANGE these two parameters.  They define constants */
    localparam SPIS_MSB_FIRST = 1'b0;
    localparam SPIS_LSB_FIRST = 1'b1;

    /* Status register bits */
    localparam SPIS_STS_SPI_DONE_BIT            = 3'd0;
    localparam SPIS_STS_TX_BUFFER_NOT_FULL_BIT  = 3'd1;
    localparam SPIS_STS_TX_BUFFER_EMPTY_BIT     = 3'd2;
    localparam SPIS_STS_BYTE_COMPLETE_BIT       = 3'd6;
    localparam SPIS_STS_RX_BUFFER_NOT_EMPTY_BIT = 3'd3;
    localparam SPIS_STS_RX_BUFFER_EMPTY_BIT     = 3'd4;
    localparam SPIS_STS_RX_FIFO_OVERRUN_BIT     = 3'd5;
    localparam SPIS_STS_RX_FIFO_FULL_BIT        = 3'd6;

    /* Index for Bidirectional Mode Control Register bit */
    localparam CTRL_TX_PERMISSION = 1'b0;

    /* Counter initialization bit */
    localparam CTRL_CNT_INIT      = 1'b1;

    parameter [0:0] ShiftDir =  SPIS_MSB_FIRST;
    parameter BidirectMode   = 0;

    /* set to 2-8 bits only. Default is 8 bits */
    parameter [6:0] NumberOfDataBits = 7'd8;

    /* Default is rising edge mode */
    parameter [0:0] ModeCPHA         = 1'b0;
    parameter [0:0] ModePOL          = 1'b0;

    localparam [2:0] dp8MsbVal = (NumberOfDataBits % 8) - 3'd1;

    localparam [7:0] dpMask    =(NumberOfDataBits == 8) ? 8'd255:
                                (NumberOfDataBits == 7) ? 8'd127:
                                (NumberOfDataBits == 6) ? 8'd63 :
                                (NumberOfDataBits == 5) ? 8'd31 :
                                (NumberOfDataBits == 4) ? 8'd15 :
                                (NumberOfDataBits == 3) ? 8'd7  :
                                (NumberOfDataBits == 2) ? 8'd3  : 8'd0;

    /* This value get's truncated to 3 bits */
    localparam [2:0] dp16MsbVal = (NumberOfDataBits % 8) - 4'd9;
    /* Index for Bidirectional Mode Control Register bit */
    localparam CTRL_TX_ENABLE = 1'b0;

    localparam [7:0] dp16MOSIMask = (NumberOfDataBits == 16) ? 8'd255 :
                                    (NumberOfDataBits == 15) ? 8'd127 :
                                    (NumberOfDataBits == 14) ? 8'd63 :
                                    (NumberOfDataBits == 13) ? 8'd31 :
                                    (NumberOfDataBits == 12) ? 8'd15 :
                                    (NumberOfDataBits == 11) ? 8'd7 :
                                    (NumberOfDataBits == 10) ? 8'd3 :
                                    /*(NumberOfDataBits == 9)  ? */ 8'd1 ;

    localparam [1:0] dynShiftDir     =  (ShiftDir == SPIS_MSB_FIRST) ? 2'd1 : 2'd2;
    localparam [1:0] dp16MSBSIChoice = (ShiftDir == SPIS_MSB_FIRST) ? `SC_SI_A_CHAIN : `SC_SI_A_ROUTE;
    localparam [1:0] dp16LSBSIChoice = (ShiftDir == SPIS_MSB_FIRST) ? `SC_SI_A_ROUTE : `SC_SI_A_CHAIN;

    /* RX FIFO is loaded on the negedge of SCLK */
    localparam f1_edge = `SC_FIFO_CLK1_NEG;

    /* Datapath selection local parameters */
    localparam SR8  = 8'd8;
    localparam SR16 = 8'd16;

    /* datapath configurations  */
    localparam dp8_config = {
            `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM0:      */
            `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM1:      */
            `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM2:      */
            `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM3:      */
            `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
            dynShiftDir, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM4:      */
            `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
            dynShiftDir, `CS_A0_SRC___F0, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM5:      */
            `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM6:      */
            `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM7:      */
            dpMask, 8'hFF, /*CFG9:      */
            8'hFF, 8'hFF, /*CFG11-10:      */
            `SC_CMPB_A1_D1, `SC_CMPA_A1_D1, `SC_CI_B_ARITH,
            `SC_CI_A_ARITH, `SC_C1_MASK_DSBL, `SC_C0_MASK_DSBL,
            `SC_A_MASK_ENBL, `SC_DEF_SI_0, `SC_SI_B_DEFSI,
            `SC_SI_A_ROUTE, /*CFG13-12:      */
            `SC_A0_SRC_ACC, ShiftDir, 1'h0,
            1'h0, `SC_FIFO1_ALU, `SC_FIFO0_BUS,
            `SC_MSB_ENBL, dp8MsbVal, `SC_MSB_NOCHN,
            `SC_FB_NOCHN, `SC_CMP1_NOCHN,
            `SC_CMP0_NOCHN, /*CFG15-14:      */
            3'h00, `SC_FIFO_SYNC__ADD, 4'h00,f1_edge,`SC_FIFO_CLK0_POS,
            `SC_FIFO_CLK__DP,`SC_FIFO_CAP_AX,`SC_FIFO__EDGE,
            `SC_FIFO_ASYNC,`SC_EXTCRC_DSBL,`SC_WRK16CAT_DSBL  /*CFG17-16:      */
        };

    localparam dp16_config_msb = {
            `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM0:      */
            `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM1:      */
            `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM2:      */
            `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM3:      */
            `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
            dynShiftDir, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM4:      */
            `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
            dynShiftDir, `CS_A0_SRC___F0, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM5:      */
            `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM6:      */
            `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM7:      */
            dp16MOSIMask, 8'h00, /*CFG9:      */
            8'hFF, 8'hFF, /*CFG11-10:      */
            `SC_CMPB_A1_D1, `SC_CMPA_A1_D1, `SC_CI_B_ARITH,
            `SC_CI_A_ARITH, `SC_C1_MASK_DSBL, `SC_C0_MASK_DSBL,
            `SC_A_MASK_ENBL, `SC_DEF_SI_0, `SC_SI_B_DEFSI,
            dp16MSBSIChoice, /*CFG13-12:      */
            `SC_A0_SRC_ACC, ShiftDir, 1'h0,
            1'h0, `SC_FIFO1_ALU, `SC_FIFO0_BUS,
            `SC_MSB_ENBL, dp16MsbVal, `SC_MSB_NOCHN,
            `SC_FB_NOCHN, `SC_CMP1_NOCHN,
            `SC_CMP0_NOCHN, /*CFG15-14:      */
            3'h00, `SC_FIFO_SYNC__ADD, 4'h00,f1_edge, `SC_FIFO_CLK0_POS,
            `SC_FIFO_CLK__DP,`SC_FIFO_CAP_AX,
            `SC_FIFO__EDGE,`SC_FIFO_ASYNC,`SC_EXTCRC_DSBL,
            `SC_WRK16CAT_DSBL  /*CFG17-16:      */
        };

    localparam dp16_config_lsb = {
            `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM0:      */
            `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM1:      */
            `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM2:      */
            `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM3:      */
            `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
            dynShiftDir, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM4:      */
            `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
            dynShiftDir, `CS_A0_SRC___F0, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM5:      */
            `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM6:      */
            `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
            `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
            `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
            `CS_CMP_SEL_CFGA, /*CFGRAM7:      */
            8'hFF, 8'h00, /*CFG9:      */
            8'hFF, 8'hFF, /*CFG11-10:      */
            `SC_CMPB_A1_D1, `SC_CMPA_A1_D1, `SC_CI_B_ARITH,
            `SC_CI_A_ARITH, `SC_C1_MASK_DSBL, `SC_C0_MASK_DSBL,
            `SC_A_MASK_DSBL, `SC_DEF_SI_0, `SC_SI_B_DEFSI,
            dp16LSBSIChoice, /*CFG13-12:      */
            `SC_A0_SRC_ACC, ShiftDir, 1'h0,
            1'h0, `SC_FIFO1_ALU, `SC_FIFO0_BUS,
            `SC_MSB_DSBL, `SC_MSB_BIT7, `SC_MSB_NOCHN,
            `SC_FB_NOCHN, `SC_CMP1_NOCHN,
            `SC_CMP0_NOCHN, /*CFG15-14:      */
            3'h00, `SC_FIFO_SYNC__ADD, 4'h00,f1_edge, `SC_FIFO_CLK0_POS,
            `SC_FIFO_CLK__DP,`SC_FIFO_CAP_AX,
            `SC_FIFO__EDGE,`SC_FIFO_ASYNC,`SC_EXTCRC_DSBL,
            `SC_WRK16CAT_DSBL  /*CFG17-16:      */
            };

    /* Status Register inputs from the PLD/DP's */
    wire    [6:0]   tx_status;
    wire    [6:0]   rx_status;

    /* Master Out Slave In from the Datapath.
    Selects between mosi_dp8 and mosi_dp16 based on NUM_BITS */
    wire            miso_from_dp;
    /* One compare output of the counter which signals
    when to load received data into the FIFO */
    wire dpcounter_zero;
    /* "Counter is equal to '1' condition" output
    is used as "byte complete" condition*/
    wire dpcounter_one;
    /* counter output */
    wire [6:0] count;

    /* control register output*/
    wire [7:0] control;
    /* datapath si input*/
    wire mosi_to_dp;
    /* non-connected wires, used for connection convenience */
    wire nc1,nc2,nc3,nc4;
    /* TX and RX FIFO status outputs */
    wire dpMISO_fifo_not_empty;
    wire dpMISO_fifo_not_full;
    wire dpMISO_fifo_empty;
    wire dpMOSI_fifo_not_empty;
    wire dpMOSI_fifo_full;
    wire dpMOSI_fifo_empty;

    /* "clear on read" status input sources */
    wire mosi_buf_overrun;
    /* load RX FIFO (from counter) */
    wire load;

    /* Datapath and Counter7 clock */
    wire dp_clock;
    /* conditional 'shift out' wires for 16-bit datapath */
    wire mosi_from_dpL;
    wire mosi_from_dpR;
    wire mosi_fin;
    wire cnt_reset = reset | ss;
    wire inv_ss    = ~ss;
    /*registered MOSI value*/
    reg mosi_tmp;
    reg dpcounter_one_reg;
    reg mosi_buf_overrun_fin;
    wire clock_fin;
    wire  dpcounter_one_fin;
    wire  miso_tx_empty_reg_fin;
    wire mosi_buf_overrun_reg;
    wire dpMOSI_fifo_full_reg;

    wire tx_load        = (ModeCPHA == 1'b0) ? load : dpcounter_zero;
    wire byte_complete  = dpcounter_one_fin & (~dpcounter_one_reg);
    wire rx_buf_overrun = mosi_buf_overrun_reg &(~mosi_buf_overrun_fin);
    wire prc_clk_src    = (((ModeCPHA == 0) && (ModePOL == 0)) || ((ModeCPHA == 1) && (ModePOL == 1))) ? sclk : ~sclk;
    wire dp_clk_src     = (((ModeCPHA == 0) && (ModePOL == 1)) || ((ModeCPHA == 1) && (ModePOL == 0))) ? sclk : ~sclk;

    cy_psoc3_udb_clock_enable_v1_0 #(.sync_mode(`TRUE))
    ClkEn (
        .clock_in(clock),
        .enable(1'b1),
        .clock_out(clock_fin)
    );

    cy_psoc3_udb_clock_enable_v1_0 #(.sync_mode(`FALSE))
    PrcClkEn (
        .clock_in(prc_clk_src),
        .enable(1'b1),
        .clock_out(prc_clk)
    );

    cy_psoc3_udb_clock_enable_v1_0 #(.sync_mode(`FALSE))
    DpClkEn (
        .clock_in(dp_clk_src),
        .enable(1'b1),
        .clock_out(dp_clock)
    );

    cy_psoc3_sync sync_1(
        .sc_out(dpcounter_one_fin),
        .sc_in(dpcounter_one),
        .clock(clock_fin)
    );

    cy_psoc3_sync sync_2(
        .sc_out(miso_tx_empty_reg_fin),
        .sc_in(dpMISO_fifo_empty),
        .clock(clock_fin)
    );

    cy_psoc3_sync sync_3(
        .sc_out(mosi_buf_overrun_reg),
        .sc_in(mosi_buf_overrun),
        .clock(clock_fin)
    );

    cy_psoc3_sync sync_4(
        .sc_out(dpMOSI_fifo_full_reg),
        .sc_in(dpMOSI_fifo_full),
        .clock(clock_fin)
    );

    assign miso                  = (ss == 1'b0) ? miso_from_dp : 1'b0;
    assign dpMISO_fifo_not_empty = ~dpMISO_fifo_empty;
    assign mosi_buf_overrun      = load & dpMOSI_fifo_full;

    /* status register connections */
    assign tx_status[SPIS_STS_SPI_DONE_BIT]            = (byte_complete & miso_tx_empty_reg_fin);
    assign tx_status[SPIS_STS_TX_BUFFER_EMPTY_BIT]     = miso_tx_empty_reg_fin;
    assign tx_status[SPIS_STS_TX_BUFFER_NOT_FULL_BIT]  = dpMISO_fifo_not_full;
    assign tx_status[SPIS_STS_BYTE_COMPLETE_BIT]       = byte_complete;

    assign rx_status[SPIS_STS_RX_BUFFER_EMPTY_BIT]     = ~dpMOSI_fifo_not_empty;
    assign rx_status[SPIS_STS_RX_BUFFER_NOT_EMPTY_BIT] = dpMOSI_fifo_not_empty;
    assign rx_status[SPIS_STS_RX_FIFO_OVERRUN_BIT]     = rx_buf_overrun;
    assign rx_status[SPIS_STS_RX_FIFO_FULL_BIT]        = dpMOSI_fifo_full_reg;

    assign tx_status[5:3] = 3'h0;
    assign rx_status[2:0] = 3'h0;

    /* Determination of 'sclk_fin' polarity
    according to the ModePOL parameter value.
    If 'SS' is 'high' SCLK should be blocked */

    generate
        if(BidirectMode)
        begin: SyncCtl
            /* 'TX enable' control wire (for Bidirectional mode) */
            /* Control register instantiation */
            cy_psoc3_control #(.cy_force_order(1),.cy_ctrl_mode_1(8'h00),.cy_ctrl_mode_0(8'h01))
            CtrlReg(
                /* input          */ .clock(clock_fin),
                /* output [07:00] */ .control(control)
            );

            assign mosi_fin  = mosi;
            assign tx_enable = control[CTRL_TX_PERMISSION];
        end else
        begin
            assign mosi_fin  = mosi;
            assign  control  = 7'h0;
            assign tx_enable = 1'b0;
        end
    endgenerate

    cy_psoc3_count7 #(.cy_period(NumberOfDataBits-7'h1),.cy_route_ld(0),.cy_route_en(1))
    BitCounter(
        /* input          */ .clock(dp_clock),
        /* input          */ .reset(cnt_reset),
        /* input          */ .load(1'b0),
        /* input          */ .enable(inv_ss),
        /* output [06:00] */ .count(count),
        /* output         */ .tc()
        );

    assign dpcounter_zero = (count[3:0] == 4'h0);
    assign dpcounter_one  = (count[3:0] == 4'h1);
    assign load = (ModeCPHA == 1'b0) ? dpcounter_one : dpcounter_zero;

    cy_psoc3_statusi #(.cy_force_order(1), .cy_md_select(7'h41), .cy_int_mask(7'h7F))
    TxStsReg(
        /* input         */  .clock(clock_fin),
        /* input [06:00] */  .status(tx_status),
        /* output        */  .interrupt(tx_interpt)
        );

    cy_psoc3_statusi #(.cy_force_order(1), .cy_md_select(7'h20), .cy_int_mask(7'h7F))
    RxStsReg(
        /* input         */  .clock(clock_fin),
        /* input [06:00] */  .status(rx_status),
        /* output        */  .interrupt(rx_interpt)
        );


    always@(posedge clock_fin)
    begin
        dpcounter_one_reg    <= dpcounter_one_fin;
        mosi_buf_overrun_fin <= mosi_buf_overrun_reg;
    end

    always@(posedge prc_clk)
    begin
        mosi_tmp <= mosi_fin;
    end

    /* Bypass input flip-flop on last received bit */
    assign mosi_to_dp = (load == 1'b1) ? mosi_fin : mosi_tmp;

    generate

        if(NumberOfDataBits <= SR8) begin: sR8
            cy_psoc3_dp8 #(.cy_dpconfig_a(dp8_config))
            Dp(
                /*  input           */ .clk(dp_clock),
                /*  input           */ .reset(reset),
                /*  input   [02:00] */ .cs_addr({inv_ss, 1'b0,tx_load}),
                /*  input           */ .route_si(mosi_to_dp),
                /*  input           */ .route_ci(1'b0),
                /*  input           */ .f0_load(1'b0),
                /*  input           */ .f1_load(load),
                /*  input           */ .d0_load(1'b0),
                /*  input           */ .d1_load(1'b0),
                /*  output          */ .ce0(),
                /*  output          */ .cl0(),
                /*  output          */ .z0(),
                /*  output          */ .ff0(),
                /*  output          */ .ce1(),
                /*  output          */ .cl1(),
                /*  output          */ .z1(),
                /*  output          */ .ff1(),
                /*  output          */ .ov_msb(),
                /*  output          */ .co_msb(),
                /*  output          */ .cmsb(),
                /*  output          */ .so(miso_from_dp),
                /*  output          */ .f0_bus_stat(dpMISO_fifo_not_full),
                /*  output          */ .f0_blk_stat(dpMISO_fifo_empty),
                /*  output          */ .f1_bus_stat(dpMOSI_fifo_not_empty),
                /*  output          */ .f1_blk_stat(dpMOSI_fifo_full)
                );

        end /* NumberOfDataBits <= 8 */
        else if (NumberOfDataBits <= SR16) begin : sR16 /* NumberOfDataBits > 8 */

            cy_psoc3_dp16 #(.cy_dpconfig_a(dp16_config_lsb), .cy_dpconfig_b(dp16_config_msb))
            Dp(
                /*  input         */  .clk(dp_clock),
                /*  input         */  .reset(reset),
                /*  input [02:00] */  .cs_addr({inv_ss, 1'b0, tx_load}),
                /*  input         */  .route_si(mosi_to_dp),
                /*  input         */  .route_ci(1'b0),
                /*  input         */  .f0_load(1'b0),
                /*  input         */  .f1_load(load),
                /*  input         */  .d0_load(1'b0),
                /*  input         */  .d1_load(1'b0),
                /*  output        */  .ce0(),
                /*  output        */  .cl0(),
                /*  output        */  .z0(),
                /*  output        */  .ff0(),
                /*  output        */  .ce1(),
                /*  output        */  .cl1(),
                /*  output        */  .z1(),
                /*  output        */  .ff1(),
                /*  output        */  .ov_msb(),
                /*  output        */  .co_msb(),
                /*  output        */  .cmsb(),
                /*  output        */  .so({mosi_from_dpL,mosi_from_dpR}),
                /*  output        */  .f0_bus_stat({dpMISO_fifo_not_full, nc1}),
                /*  output        */  .f0_blk_stat({dpMISO_fifo_empty, nc2}),
                /*  output        */  .f1_bus_stat({dpMOSI_fifo_not_empty, nc3}),
                /*  output        */  .f1_blk_stat({dpMOSI_fifo_full, nc4})
            );

            assign miso_from_dp      = (ShiftDir == SPIS_MSB_FIRST) ? mosi_from_dpL : mosi_from_dpR;

        end /* sR16 */

    endgenerate
    endmodule
    `endif /* B_SPI_Slave_ES3_v2_60__V_ALREADY_INCLUDED */

    `ifdef B_SPI_Slave_ES2_v2_60__V_ALREADY_INCLUDED
    `else
    `define B_SPI_Slave_ES2_v2_60__V_ALREADY_INCLUDED

    module B_SPI_Slave_ES2_v2_60(
        input  wire reset,     /*System Reset */
        input  wire clock,     /* System Clk - 2x Bit rate */
        input  wire mosi,      /* SPI MOSI input */
        input  wire sclk,      /* SPI SCLK input */
        input  wire ss,        /* SPI SS input */

        output wire tx_interpt,/* Status Register Interrupt output */
        output wire rx_interpt,/* Status Register Interrupt output */
        output wire tx_enable, /* tx enable */
        output wire miso       /* SPI MISO output */

);
    /* SPIS_MSB_FIRST is default */
    parameter [0:0] ShiftDir         = 1'b0;
    /* set to 2-16 bits only. Default is 8 bits */
    parameter [4:0] NumberOfDataBits = 5'd8;
    /* Default is rising edge mode */
    parameter ModeCPHA     = 1'b0;
    /* Default is rising edge mode */
    parameter ModePOL      = 1'b0;
    parameter BidirectMode = 0;

    localparam SPIS_MSB_FIRST = 1'b0;
    localparam SPIS_LSB_FIRST = 1'b1;

    /* Status register bits */
    localparam SPIS_STS_SPI_DONE_BIT            = 3'd0;
    localparam SPIS_STS_TX_BUFFER_NOT_FULL_BIT  = 3'd1;
    localparam SPIS_STS_TX_BUFFER_EMPTY_BIT     = 3'd2;
    localparam SPIS_STS_BYTE_COMPLETE_BIT       = 3'd6;
    localparam SPIS_STS_RX_BUFFER_NOT_EMPTY_BIT = 3'd3;
    localparam SPIS_STS_RX_BUFFER_EMPTY_BIT     = 3'd4;
    localparam SPIS_STS_RX_FIFO_OVERRUN_BIT     = 3'd5;
    localparam SPIS_STS_RX_FIFO_FULL_BIT        = 3'd6;

    localparam [2:0] dp8MsbVal   = (NumberOfDataBits % 8) - 3'd1;
    localparam [7:0] dp8MOSIMask = (NumberOfDataBits == 8) ? 8'd255:
                                   (NumberOfDataBits == 7) ? 8'd127:
                                   (NumberOfDataBits == 6) ? 8'd63 :
                                   (NumberOfDataBits == 5) ? 8'd31 :
                                   (NumberOfDataBits == 4) ? 8'd15 :
                                   (NumberOfDataBits == 3) ? 8'd7  :
                                   /*(NumberOfDataBits == 2) ? */ 8'd3;

    /* This value get's truncated to 3 bits */
    localparam [2:0] dp16MsbVal = (NumberOfDataBits % 8) - 4'd9;
    /* Index for Bidirectional Mode Control Register bit */
    localparam CTRL_TX_ENABLE   = 1'b0;

    localparam [7:0] dp16MOSIMask = (NumberOfDataBits == 16) ? 8'd255 :
                                    (NumberOfDataBits == 15) ? 8'd127 :
                                    (NumberOfDataBits == 14) ? 8'd63 :
                                    (NumberOfDataBits == 13) ? 8'd31 :
                                    (NumberOfDataBits == 12) ? 8'd15 :
                                    (NumberOfDataBits == 11) ? 8'd7 :
                                    (NumberOfDataBits == 10) ? 8'd3 :
                                    /*(NumberOfDataBits == 9)  ? */ 8'd1 ;

    localparam [1:0] dynShiftDir     = (ShiftDir == SPIS_MSB_FIRST) ? 2'd1 : 2'd2;
    localparam [1:0] dp16MSBSIChoice = (ShiftDir == SPIS_MSB_FIRST) ? `SC_SI_A_CHAIN : `SC_SI_A_ROUTE;
    localparam [1:0] dp16LSBSIChoice = (ShiftDir == SPIS_MSB_FIRST) ? `SC_SI_A_ROUTE : `SC_SI_A_CHAIN;

    localparam dp8_MISO_cfg = {
                `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
                dynShiftDir, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
                `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
                `CS_CMP_SEL_CFGA, /*CFGRAM0:      Shift */
                `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
                dynShiftDir, `CS_A0_SRC___F0, `CS_A1_SRC_NONE,
                `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
                `CS_CMP_SEL_CFGA, /*CFGRAM1:      Shift and Load New FIFO Data */
                `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
                `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
                `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
                `CS_CMP_SEL_CFGA, /*CFGRAM2:       */
                `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
                `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
                `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
                `CS_CMP_SEL_CFGA, /*CFGRAM3:       */
                `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
                `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
                `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
                `CS_CMP_SEL_CFGA, /*CFGRAM4:       */
                `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
                `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
                `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
                `CS_CMP_SEL_CFGA, /*CFGRAM5:       */
                `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
                `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
                `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
                `CS_CMP_SEL_CFGA, /*CFGRAM6:       */
                `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
                `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
                `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
                `CS_CMP_SEL_CFGA, /*CFGRAM7:       */
                8'hFF, 8'h00,    /*CFG9:       */
                8'hFF, 8'hFF,    /*CFG11-10:       */
                `SC_CMPB_A1_D1, `SC_CMPA_A1_D1, `SC_CI_B_ARITH,
                `SC_CI_A_ARITH, `SC_C1_MASK_DSBL, `SC_C0_MASK_DSBL,
                `SC_A_MASK_DSBL, `SC_DEF_SI_0, `SC_SI_B_DEFSI,
                `SC_SI_A_CHAIN, /*CFG13-12:       */
                `SC_A0_SRC_ACC, ShiftDir, 1'h0,
                1'h0, `SC_FIFO1__A0, `SC_FIFO0_BUS,
                `SC_MSB_ENBL, dp8MsbVal, `SC_MSB_NOCHN,
                `SC_FB_NOCHN, `SC_CMP1_NOCHN,
                `SC_CMP0_NOCHN, /*CFG15-14:       */
                10'h00, `SC_FIFO_CLK__DP,`SC_FIFO_CAP_AX,
                `SC_FIFO__EDGE,`SC_FIFO__SYNC,`SC_EXTCRC_DSBL,
                `SC_WRK16CAT_DSBL /*CFG17-16:       */
            };

    localparam dp8_MOSI_cfg = {
                `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
                dynShiftDir, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
                `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
                `CS_CMP_SEL_CFGA, /*CFGRAM0:      Shift Data In on SCLK always */
                `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
                `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
                `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
                `CS_CMP_SEL_CFGA, /*CFGRAM1:      Unused */
                `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
                `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
                `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
                `CS_CMP_SEL_CFGA, /*CFGRAM2:      Unused */
                `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
                `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
                `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
                `CS_CMP_SEL_CFGA, /*CFGRAM3:      Unused */
                `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
                `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
                `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
                `CS_CMP_SEL_CFGA, /*CFGRAM4:      Unused */
                `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
                `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
                `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
                `CS_CMP_SEL_CFGA, /*CFGRAM5:      Unused */
                `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
                `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
                `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
                `CS_CMP_SEL_CFGA, /*CFGRAM6:      Unused */
                `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
                `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
                `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
                `CS_CMP_SEL_CFGA, /*CFGRAM7:      Unused */
                dp8MOSIMask, 8'h00,    /*CFG9:       */
                8'hFF, 8'hFF,    /*CFG11-10:       */
                `SC_CMPB_A1_D1, `SC_CMPA_A1_D1, `SC_CI_B_ARITH,
                `SC_CI_A_ARITH, `SC_C1_MASK_DSBL, `SC_C0_MASK_DSBL,
                `SC_A_MASK_ENBL, `SC_DEF_SI_0, `SC_SI_B_DEFSI,
                `SC_SI_A_ROUTE, /*CFG13-12:       */
                `SC_A0_SRC_ACC, ShiftDir, 1'h0,
                1'h0, `SC_FIFO1_ALU, `SC_FIFO0_ALU,
                `SC_MSB_ENBL, dp8MsbVal, `SC_MSB_NOCHN,
                `SC_FB_NOCHN, `SC_CMP1_NOCHN,
                `SC_CMP0_NOCHN, /*CFG15-14:       */
                10'h00, `SC_FIFO_CLK__DP,`SC_FIFO_CAP_AX,
                `SC_FIFO__EDGE,`SC_FIFO__SYNC,`SC_EXTCRC_DSBL,
                `SC_WRK16CAT_DSBL /*CFG17-16:       */
            };

    localparam dp16_MISO_lsb_cfg = {
                `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
                dynShiftDir, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
                `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
                `CS_CMP_SEL_CFGA, /*CFGRAM0:      Shift */
                `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
                dynShiftDir, `CS_A0_SRC___F0, `CS_A1_SRC_NONE,
                `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
                `CS_CMP_SEL_CFGA, /*CFGRAM1:      Shift and Load New FIFO Data */
                `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
                `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
                `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
                `CS_CMP_SEL_CFGA, /*CFGRAM2:       */
                `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
                `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
                `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
                `CS_CMP_SEL_CFGA, /*CFGRAM3:       */
                `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
                `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
                `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
                `CS_CMP_SEL_CFGA, /*CFGRAM4:       */
                `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
                `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
                `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
                `CS_CMP_SEL_CFGA, /*CFGRAM5:       */
                `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
                `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
                `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
                `CS_CMP_SEL_CFGA, /*CFGRAM6:       */
                `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
                `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
                `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
                `CS_CMP_SEL_CFGA, /*CFGRAM7:       */
                8'hFF, 8'h00,    /*CFG9:       */
                8'hFF, 8'hFF,    /*CFG11-10:       */
                `SC_CMPB_A1_D1, `SC_CMPA_A1_D1, `SC_CI_B_ARITH,
                `SC_CI_A_ARITH, `SC_C1_MASK_DSBL, `SC_C0_MASK_DSBL,
                `SC_A_MASK_DSBL, `SC_DEF_SI_0, `SC_SI_B_DEFSI,
                dp16LSBSIChoice, /*CFG13-12:       */
                `SC_A0_SRC_ACC, ShiftDir, 1'h0,
                1'h0, `SC_FIFO1__A0, `SC_FIFO0_BUS,
                `SC_MSB_ENBL, `SC_MSB_BIT7, `SC_MSB_CHNED,
                `SC_FB_NOCHN, `SC_CMP1_NOCHN,
                `SC_CMP0_NOCHN, /*CFG15-14:       */
                10'h00, `SC_FIFO_CLK__DP,`SC_FIFO_CAP_AX,
                `SC_FIFO__EDGE,`SC_FIFO__SYNC,`SC_EXTCRC_DSBL,
                `SC_WRK16CAT_DSBL /*CFG17-16:       */
                };

    localparam dp16_MISO_msb_cfg = {
                `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
                dynShiftDir, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
                `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
                `CS_CMP_SEL_CFGA, /*CFGRAM0:      Shift */
                `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
                dynShiftDir, `CS_A0_SRC___F0, `CS_A1_SRC_NONE,
                `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
                `CS_CMP_SEL_CFGA, /*CFGRAM1:      Shift and Load New FIFO Data */
                `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
                `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
                `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
                `CS_CMP_SEL_CFGA, /*CFGRAM2:       */
                `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
                `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
                `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
                `CS_CMP_SEL_CFGA, /*CFGRAM3:       */
                `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
                `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
                `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
                `CS_CMP_SEL_CFGA, /*CFGRAM4:       */
                `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
                `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
                `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
                `CS_CMP_SEL_CFGA, /*CFGRAM5:       */
                `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
                `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
                `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
                `CS_CMP_SEL_CFGA, /*CFGRAM6:       */
                `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
                `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
                `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
                `CS_CMP_SEL_CFGA, /*CFGRAM7:       */
                8'hFF, 8'h00,    /*CFG9:       */
                8'hFF, 8'hFF,    /*CFG11-10:       */
                `SC_CMPB_A1_D1, `SC_CMPA_A1_D1, `SC_CI_B_ARITH,
                `SC_CI_A_ARITH, `SC_C1_MASK_DSBL, `SC_C0_MASK_DSBL,
                `SC_A_MASK_DSBL, `SC_DEF_SI_0, `SC_SI_B_DEFSI,
                dp16MSBSIChoice, /*CFG13-12:       */
                `SC_A0_SRC_ACC, ShiftDir, 1'h0,
                1'h0, `SC_FIFO1__A0, `SC_FIFO0_BUS,
                `SC_MSB_ENBL, dp16MsbVal, `SC_MSB_CHNED,
                `SC_FB_NOCHN, `SC_CMP1_NOCHN,
                `SC_CMP0_NOCHN, /*CFG15-14:       */
                10'h00, `SC_FIFO_CLK__DP,`SC_FIFO_CAP_AX,
                `SC_FIFO__EDGE,`SC_FIFO__SYNC,`SC_EXTCRC_DSBL,
                `SC_WRK16CAT_DSBL /*CFG17-16:       */
    };

    localparam dp16_MOSI_lsb_cfg = {
                `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
                dynShiftDir, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
                `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
                `CS_CMP_SEL_CFGA, /*CFGRAM0:      Shift Data In on SCLK always */
                `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
                `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
                `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
                `CS_CMP_SEL_CFGA, /*CFGRAM1:      Unused */
                `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
                `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
                `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
                `CS_CMP_SEL_CFGA, /*CFGRAM2:      Unused */
                `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
                `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
                `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
                `CS_CMP_SEL_CFGA, /*CFGRAM3:      Unused */
                `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
                `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
                `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
                `CS_CMP_SEL_CFGA, /*CFGRAM4:      Unused */
                `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
                `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
                `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
                `CS_CMP_SEL_CFGA, /*CFGRAM5:      Unused */
                `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
                `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
                `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
                `CS_CMP_SEL_CFGA, /*CFGRAM6:      Unused */
                `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
                `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
                `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
                `CS_CMP_SEL_CFGA, /*CFGRAM7:      Unused */
                8'hFF, 8'h00,    /*CFG9:       */
                8'hFF, 8'hFF,    /*CFG11-10:       */
                `SC_CMPB_A1_D1, `SC_CMPA_A1_D1, `SC_CI_B_ARITH,
                `SC_CI_A_ARITH, `SC_C1_MASK_DSBL, `SC_C0_MASK_DSBL,
                `SC_A_MASK_DSBL, `SC_DEF_SI_0, `SC_SI_B_DEFSI,
                dp16LSBSIChoice, /*CFG13-12:       */
                `SC_A0_SRC_ACC, ShiftDir, 1'h0,
                1'h0, `SC_FIFO1_ALU, `SC_FIFO0_ALU,
                `SC_MSB_ENBL, `SC_MSB_BIT7, `SC_MSB_CHNED,
                `SC_FB_NOCHN, `SC_CMP1_NOCHN,
                `SC_CMP0_NOCHN, /*CFG15-14:       */
                10'h00, `SC_FIFO_CLK__DP,`SC_FIFO_CAP_AX,
                `SC_FIFO__EDGE,`SC_FIFO__SYNC,`SC_EXTCRC_DSBL,
                `SC_WRK16CAT_DSBL /*CFG17-16:       */
    };

    localparam dp16_MOSI_msb_cfg = {
                `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
                dynShiftDir, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
                `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
                `CS_CMP_SEL_CFGA, /*CFGRAM0:      Shift Data In on SCLK always */
                `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
                `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
                `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
                `CS_CMP_SEL_CFGA, /*CFGRAM1:      Unused */
                `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
                `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
                `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
                `CS_CMP_SEL_CFGA, /*CFGRAM2:      Unused */
                `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
                `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
                `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
                `CS_CMP_SEL_CFGA, /*CFGRAM3:      Unused */
                `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
                `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
                `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
                `CS_CMP_SEL_CFGA, /*CFGRAM4:      Unused */
                `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
                `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
                `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
                `CS_CMP_SEL_CFGA, /*CFGRAM5:      Unused */
                `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
                `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
                `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
                `CS_CMP_SEL_CFGA, /*CFGRAM6:      Unused */
                `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
                `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
                `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
                `CS_CMP_SEL_CFGA, /*CFGRAM7:      Unused */
                dp16MOSIMask, 8'h00,    /*CFG9:       */
                8'hFF, 8'hFF,    /*CFG11-10:       */
                `SC_CMPB_A1_D1, `SC_CMPA_A1_D1, `SC_CI_B_ARITH,
                `SC_CI_A_ARITH, `SC_C1_MASK_DSBL, `SC_C0_MASK_DSBL,
                `SC_A_MASK_ENBL, `SC_DEF_SI_0, `SC_SI_B_DEFSI,
                dp16MSBSIChoice, /*CFG13-12:       */
                `SC_A0_SRC_ACC, ShiftDir, 1'h0,
                1'h0, `SC_FIFO1_ALU, `SC_FIFO0_ALU,
                `SC_MSB_ENBL, dp16MsbVal, `SC_MSB_CHNED,
                `SC_FB_NOCHN, `SC_CMP1_NOCHN,
                `SC_CMP0_NOCHN, /*CFG15-14:       */
                10'h00, `SC_FIFO_CLK__DP,`SC_FIFO_CAP_AX,
                `SC_FIFO__EDGE,`SC_FIFO__SYNC,`SC_EXTCRC_DSBL,
                `SC_WRK16CAT_DSBL /*CFG17-16:       */
    };

    wire dp8MISO_f0_not_full;
    wire dp16MISO_f0_not_full;
    wire dp8MISO_f0_empty;
    wire dp16MISO_f0_empty;
    wire dp8MOSI_f0_full;
    wire dp16MOSI_f0_full;
    wire dp8MOSI_f0_not_empty;
    wire dp16MOSI_f0_not_empty;
    wire miso_tx_full;
    wire miso_tx_empty;
    wire mosi_rx_full;
    wire mosi_rx_empty;
    wire miso_tx_not_full;
    wire mosi_rx_not_empty;
    wire nc0,nc1,nc2,nc3,nc4;
    wire miso_from_dp;

    /* Slave Status register input */
    wire [6:0]tx_status;
    wire [6:0]rx_status;
    wire cnt_enable = ~ss;
    /* Counter compare to zero use to notify when a transfer is complete */
    /* MISO from DP8 only used if NumberOfDataBits <= 8 */
    wire miso8;
    /* MISO from DP16 only used if NumberOfDataBits > 8 */
    wire [1:0]   miso16;

    wire mosi_to_dp = mosi;

    wire misoclk_src     = (((ModeCPHA == 1'b0) && (ModePOL == 1'b1))||
                            ((ModeCPHA == 1'b1) && (ModePOL == 1'b0))) ? sclk : ~sclk;

    wire counter_clk_src = (((ModeCPHA == 1'b0) && (ModePOL == 1'b0) ||
                             (ModeCPHA == 1'b1) && (ModePOL == 1'b1)))? sclk : ~sclk;
    wire mosiclk_src     = counter_clk_src;

    reg dpcounter_one_reg;
    reg mosi_rx_full_fin;
    wire inv_ss = ~ss;
    wire counter_clk_fin;
    wire misoclk_fin;
    wire mosiclk_fin;
    wire [6:0] count;
    wire [7:0] control;
    wire clock_fin;
    wire dpcounter_zero = (count[3:0] == 4'h0);
    wire dpcounter_one  = (count[3:0] == 4'h1);
    wire mosi_to_dp_fin;
    wire  dpcounter_one_fin;
    wire  miso_tx_empty_reg_fin;
    wire mosi_rx_full_dbl_reg;

    wire mosi_fifo_load      = dpcounter_one;
    wire byte_complete       = dpcounter_one_fin & (~dpcounter_one_reg);
    wire ff0_load            = dpcounter_zero;
    wire ff0_load_fin        = ff0_load;
    wire mosi_fifo_load_sync = dpcounter_one_fin;
    wire pre_tx_enable;

    cy_psoc3_udb_clock_enable_v1_0 #(.sync_mode(`TRUE))
    ClkEn (
        .clock_in(clock),
        .enable(1'b1),
        .clock_out(clock_fin)
    );

    cy_psoc3_udb_clock_enable_v1_0 #(.sync_mode(`FALSE))
    CntClkEn (
        .clock_in(counter_clk_src),
        .enable(1'b1),
        .clock_out(counter_clk_fin)
    );

    cy_psoc3_udb_clock_enable_v1_0 #(.sync_mode(`FALSE))
    MISOClkEn (
        .clock_in(misoclk_src),
        .enable(1'b1),
        .clock_out(misoclk_fin)
    );

    cy_psoc3_udb_clock_enable_v1_0 #(.sync_mode(`FALSE))
    MOSIClkEn (
        .clock_in(mosiclk_src),
        .enable(1'b1),
        .clock_out(mosiclk_fin)
    );

    assign miso_from_dp   = (NumberOfDataBits <= 8) ? miso8 :
                            (ShiftDir == SPIS_LSB_FIRST) ? miso16[0] : miso16[1];

    assign miso = (ss ==1'b0) ? miso_from_dp : 1'b0;

    assign miso_tx_full      = (NumberOfDataBits <= 8) ? ~dp8MISO_f0_not_full  : ~dp16MISO_f0_not_full;
    assign miso_tx_empty     = (NumberOfDataBits <= 8) ? dp8MISO_f0_empty      : dp16MISO_f0_empty;
    assign mosi_rx_full      = (NumberOfDataBits <= 8) ? dp8MOSI_f0_full       : dp16MOSI_f0_full;
    assign mosi_rx_empty     = (NumberOfDataBits <= 8) ? ~dp8MOSI_f0_not_empty : ~dp16MOSI_f0_not_empty;
    assign miso_tx_not_full  = (NumberOfDataBits <= 8) ? dp8MISO_f0_not_full   : dp16MISO_f0_not_full;
    assign mosi_rx_not_empty = (NumberOfDataBits <= 8) ? dp8MOSI_f0_not_empty  : dp16MOSI_f0_not_empty;

    generate
    if(BidirectMode) begin : AsyncCtl

        cy_psoc3_control #(.cy_force_order(1))
        CtrlReg(
            /* output [07:00] */ .control(control)
        );

        assign pre_tx_enable = control[CTRL_TX_ENABLE];

        cy_psoc3_sync sync_4(
        .sc_out(tx_enable),
        .sc_in(pre_tx_enable),
        .clock(clock_fin)
        );

        assign mosi_to_dp_fin = mosi_to_dp;

    end
    else begin
        assign control        = 8'h0;
        assign tx_enable      = 1'b0;
        assign mosi_to_dp_fin = mosi_to_dp;
    end
    endgenerate

    generate
        if(NumberOfDataBits <= 8)
        begin : sR8
            cy_psoc3_dp8 #(.cy_dpconfig_a(dp8_MISO_cfg))
            DpMISO(
                /* input           */ .clk(misoclk_fin),
                /* input   [02:00] */ .cs_addr({ss,1'b0,ff0_load_fin}),
                /* input           */ .route_si(1'b0),
                /* input           */ .route_ci(1'b0),
                /* input           */ .f0_load(1'b0),
                /* input           */ .f1_load(1'b0),
                /* input           */ .d0_load(1'b0),
                /* input           */ .d1_load(1'b0),
                /* output          */ .ce0(),
                /* output          */ .cl0(),
                /* output          */ .z0(),
                /* output          */ .ff0(),
                /* output          */ .ce1(),
                /* output          */ .cl1(),
                /* output          */ .z1(),
                /* output          */ .ff1(),
                /* output          */ .ov_msb(),
                /* output          */ .co_msb(),
                /* output          */ .cmsb(),
                /* output          */ .so(miso8),
                /* output          */ .f0_bus_stat(dp8MISO_f0_not_full),
                /* output          */ .f0_blk_stat(dp8MISO_f0_empty),
                /* output          */ .f1_bus_stat(),
                /* output          */ .f1_blk_stat()
            ); /* dp8MISO */

            cy_psoc3_dp8 #(.cy_dpconfig_a(dp8_MOSI_cfg))
            DpMOSI(
                /*  input           */ .clk(mosiclk_fin),
                /*  input   [02:00] */ .cs_addr({ss, 2'b0}),
                /*  input           */ .route_si(mosi_to_dp_fin),
                /*  input           */ .route_ci(1'b0),
                /*  input           */ .f0_load(mosi_fifo_load),
                /*  input           */ .f1_load(1'b0),
                /*  input           */ .d0_load(1'b0),
                /*  input           */ .d1_load(1'b0),
                /*  output          */ .ce0(),
                /*  output          */ .cl0(),
                /*  output          */ .z0(),
                /*  output          */ .ff0(),
                /*  output          */ .ce1(),
                /*  output          */ .cl1(),
                /*  output          */ .z1(),
                /*  output          */ .ff1(),
                /*  output          */ .ov_msb(),
                /*  output          */ .co_msb(),
                /*  output          */ .cmsb(),
                /*  output          */ .so(),
                /*  output          */ .f0_bus_stat(dp8MOSI_f0_not_empty),
                /*  output          */ .f0_blk_stat(dp8MOSI_f0_full),
                /*  output          */ .f1_bus_stat(),
                /*  output          */ .f1_blk_stat()
            ); /* dp8MOSI */
        end /* end of DP8_Section */
        else
        begin : sR16
            cy_psoc3_dp16 #(.cy_dpconfig_a(dp16_MISO_lsb_cfg), .cy_dpconfig_b(dp16_MISO_msb_cfg))
            DpMISO(
                /*  input           */ .clk(misoclk_fin),
                /*  input   [02:00] */ .cs_addr({ss,1'b0,ff0_load_fin}),
                /*  input           */ .route_si(1'b0),
                /*  input           */ .route_ci(1'b0),
                /*  input           */ .f0_load(1'b0),
                /*  input           */ .f1_load(1'b0),
                /*  input           */ .d0_load(1'b0),
                /*  input           */ .d1_load(1'b0),
                /*  output [01:00]  */ .ce0(),
                /*  output [01:00]  */ .cl0(),
                /*  output [01:00]  */ .z0(),
                /*  output [01:00]  */ .ff0(),
                /*  output [01:00]  */ .ce1(),
                /*  output [01:00]  */ .cl1(),
                /*  output [01:00]  */ .z1(),
                /*  output [01:00]  */ .ff1(),
                /*  output [01:00]  */ .ov_msb(),
                /*  output [01:00]  */ .co_msb(),
                /*  output [01:00]  */ .cmsb(),
                /*  output [01:00]  */ .so(miso16),
                /*  output [01:00]  */ .f0_bus_stat({dp16MISO_f0_not_full, nc1}),
                /*  output [01:00]  */ .f0_blk_stat({dp16MISO_f0_empty, nc2}),
                /*  output [01:00]  */ .f1_bus_stat(),
                /*  output [01:00]  */ .f1_blk_stat()
            );

            cy_psoc3_dp16 #(.cy_dpconfig_a(dp16_MOSI_lsb_cfg), .cy_dpconfig_b(dp16_MOSI_msb_cfg))
            DpMOSI(
                /*  input           */ .clk(mosiclk_fin),
                /*  input   [02:00] */ .cs_addr({ss, 2'b0}),
                /*  input           */ .route_si(mosi_to_dp_fin),
                /*  input           */ .route_ci(1'b0),
                /*  input           */ .f0_load(mosi_fifo_load),
                /*  input           */ .f1_load(1'b0),
                /*  input           */ .d0_load(1'b0),
                /*  input           */ .d1_load(1'b0),
                /*  output  [01:00] */ .ce0(),
                /*  output  [01:00] */ .cl0(),
                /*  output  [01:00] */ .z0(),
                /*  output  [01:00] */ .ff0(),
                /*  output  [01:00] */ .ce1(),
                /*  output  [01:00] */ .cl1(),
                /*  output  [01:00] */ .z1(),
                /*  output  [01:00] */ .ff1(),
                /*  output  [01:00] */ .ov_msb(),
                /*  output  [01:00] */ .co_msb(),
                /*  output  [01:00] */ .cmsb(),
                /*  output  [01:00] */ .so(),
                /*  output  [01:00] */ .f0_bus_stat({dp16MOSI_f0_not_empty, nc3}),
                /*  output  [01:00] */ .f0_blk_stat({dp16MOSI_f0_full, nc4}),
                /*  output  [01:00] */ .f1_bus_stat(),
                /*  output  [01:00] */ .f1_blk_stat()
            );
        end /* end of DP16_Section */

    endgenerate

    cy_psoc3_count7 #(.cy_period(NumberOfDataBits-7'd1),.cy_route_ld(0),.cy_route_en(1))
    BitCounter(
        /* input          */ .clock(counter_clk_fin),
        /* input          */ .reset(ss),
        /* input          */ .load(1'b0),
        /* input          */ .enable(inv_ss),
        /* output [06:00] */ .count(count),
        /* output          */ .tc()
    );

    cy_psoc3_sync sync_1(
        .sc_out(dpcounter_one_fin),
        .sc_in(dpcounter_one),
        .clock(clock_fin)
    );

    cy_psoc3_sync sync_2(
        .sc_out(miso_tx_empty_reg_fin),
        .sc_in(miso_tx_empty),
        .clock(clock_fin)
    );

    cy_psoc3_sync sync_3(
        .sc_out(mosi_rx_full_dbl_reg),
        .sc_in(mosi_rx_full),
        .clock(clock_fin)
    );

    always@(posedge clock_fin)
    begin
        dpcounter_one_reg <= dpcounter_one_fin;
        mosi_rx_full_fin  <= mosi_rx_full_dbl_reg;
    end

    /* Instantiate the status register and interrupt hook */
    cy_psoc3_statusi #(.cy_force_order(1), .cy_md_select(7'h41), .cy_int_mask(7'h00))
    TxStsReg(
        /* input         */  .clock(clock_fin),
        /* input [06:00] */  .status(tx_status),
        /* output        */  .interrupt(tx_interpt)
        );

    cy_psoc3_statusi #(.cy_force_order(1), .cy_md_select(7'h20), .cy_int_mask(7'h00))
    RxStsReg(
        /* input         */  .clock(clock_fin),
        /* input [06:00] */  .status(rx_status),
        /* output        */  .interrupt(rx_interpt)
        );

        /* ES2 status register connections */
    assign tx_status[SPIS_STS_SPI_DONE_BIT]            = (miso_tx_empty_reg_fin & byte_complete);
    assign tx_status[SPIS_STS_TX_BUFFER_EMPTY_BIT]     = miso_tx_empty_reg_fin;
    assign tx_status[SPIS_STS_TX_BUFFER_NOT_FULL_BIT]  = miso_tx_not_full;
    assign tx_status[SPIS_STS_BYTE_COMPLETE_BIT]       = byte_complete;

    assign rx_status[SPIS_STS_RX_BUFFER_EMPTY_BIT]     = mosi_rx_empty;
    assign rx_status[SPIS_STS_RX_BUFFER_NOT_EMPTY_BIT] = mosi_rx_not_empty;
    assign rx_status[SPIS_STS_RX_FIFO_OVERRUN_BIT]     = (mosi_rx_full_dbl_reg & mosi_fifo_load_sync);
    assign rx_status[SPIS_STS_RX_FIFO_FULL_BIT]        = mosi_rx_full_dbl_reg;

    assign tx_status[5:3] = 3'h0;
    assign rx_status[2:0] = 3'h0;

endmodule /* SPI_Slave */
`endif /* B_SPI_Slave_ES2_v2_60_V_ALREADY_INCLUDED */
`endif /* B_SPI_Slave_v2_60_V_ALREADY_INCLUDED */

