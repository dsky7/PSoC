/*******************************************************************************
* File Name:  CyControlReg_v1_50.v
*
* Description:
*  Verilog file for the control register. Assigns values to nets.
*
* Note:
*  
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

`include "cypress.v"

module CyControlReg_v1_50 (
        input wire clock,
		input wire reset,
        output wire control_0,
        output wire control_1,
        output wire control_2,
        output wire control_3,
        output wire control_4,
        output wire control_5,
        output wire control_6,
        output wire control_7		
);

    parameter NumOutputs = 8;
    
    wire [7:0] control;
    assign control_0 = control[0];
    assign control_1 = control[1];
    assign control_2 = control[2];
    assign control_3 = control[3];
    assign control_4 = control[4];
    assign control_5 = control[5];
    assign control_6 = control[6];
    assign control_7 = control[7];
    
	localparam PSOC3 = 8'd1;
    localparam PSOC5 = 8'd2;
    localparam PSOC5_ES0 = 8'd0;
    localparam PSOC5_ES1 = 8'd1;
    localparam PSOC3_ES1 = 8'd0;
    localparam PSOC3_ES2 = 8'd1;
    localparam PSOC3_ES3 = 8'd2;

    parameter DeviceFamily = PSOC3; /* Device family */
    parameter SiliconRevision = 1; /* Silicon revision */

    localparam SEL_MODE_DIRECT  = 2'd0;
    localparam SEL_MODE_SYNC    = 2'd1;
    localparam SEL_MODE_PULSE   = 2'd3;
    parameter [1:0] Bit0Mode    = SEL_MODE_DIRECT;
    parameter [1:0] Bit1Mode    = SEL_MODE_DIRECT;
    parameter [1:0] Bit2Mode    = SEL_MODE_DIRECT;
    parameter [1:0] Bit3Mode    = SEL_MODE_DIRECT;
    parameter [1:0] Bit4Mode    = SEL_MODE_DIRECT;
    parameter [1:0] Bit5Mode    = SEL_MODE_DIRECT;
    parameter [1:0] Bit6Mode    = SEL_MODE_DIRECT;
    parameter [1:0] Bit7Mode    = SEL_MODE_DIRECT;
	
	localparam DEFAULT_BITVALUE = 8'b0;
	parameter [7:0] BitValue = DEFAULT_BITVALUE;
	
    localparam DEFALUT_RESET  = 1'b0;
	parameter  ExternalReset = DEFALUT_RESET;
    
    localparam ModeMask0 = {Bit7Mode[0], Bit6Mode[0], Bit5Mode[0], Bit4Mode[0], Bit3Mode[0], Bit2Mode[0], Bit1Mode[0], Bit0Mode[0]};
    localparam ModeMask1 = {Bit7Mode[1], Bit6Mode[1], Bit5Mode[1], Bit4Mode[1], Bit3Mode[1], Bit2Mode[1], Bit1Mode[1], Bit0Mode[1]};
    localparam ExtReset = ExternalReset;
	wire clk = (ModeMask0 == 8'd0 && ModeMask1 == 8'd0) ? 1'b0 : clock;   
	wire rst = (DeviceFamily != "PSOC3" && SiliconRevision <= "2") ? 1'b0 : reset;

    localparam [7:0] bitval = (NumOutputs == 8) ? (BitValue & 8'b11111111) :
							  (NumOutputs == 7) ? (BitValue & 8'b01111111) : 
							  (NumOutputs == 6) ? (BitValue & 8'b00111111) : 
							  (NumOutputs == 5) ? (BitValue & 8'b00011111) : 
							  (NumOutputs == 4) ? (BitValue & 8'b00001111) :
							  (NumOutputs == 3) ? (BitValue & 8'b00000111) : 
						      (NumOutputs == 2) ? (BitValue & 8'b00000011) : 
							  (BitValue & 8'b00000001);                    
    
    cy_psoc3_control
        #(.cy_init_value(bitval), .cy_force_order(1), .cy_ctrl_mode_0(ModeMask0), .cy_ctrl_mode_1(ModeMask1), .cy_ext_reset(ExtReset))
        ctrl_reg(
            /* input            */  .clock(clk),				
			/* input            */  .reset(rst),
            /*  output	[07:00]	 */ .control(control)
        );

endmodule

