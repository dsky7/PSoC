/*******************************************************************************
* File Name:  CyControlReg_v1_0.v
*
* Description:
*  Verilog file for the control register. Assigns values to nets.
*
* Note:
*  
********************************************************************************
* Copyright 2008-2009, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

`include "cypress.v"

module CyControlReg_v1_0 (
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
	
	cy_psoc3_control
    	#(.cy_force_order(1))
    ctrl_reg(
        /*  output	[07:00]	 */  .control(control)
    );
endmodule

