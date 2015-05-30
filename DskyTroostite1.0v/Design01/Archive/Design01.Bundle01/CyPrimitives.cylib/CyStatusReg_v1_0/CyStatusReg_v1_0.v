/*******************************************************************************
* File Name:  CyStatusReg_v1_0.v
*
* Description:
*  Sets the value of a status register to match that of nets.
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

module CyStatusReg_v1_0 (
	input wire status_0,
	input wire status_1,
	input wire status_2,
	input wire status_3,
	input wire status_4,
	input wire status_5,
	input wire status_6,
	input wire status_7,
	input wire clock
);

	parameter [0:0] Bit0Mode = 0;
	parameter [0:0] Bit1Mode = 0;
	parameter [0:0] Bit2Mode = 0;
	parameter [0:0] Bit3Mode = 0;
	parameter [0:0] Bit4Mode = 0;
	parameter [0:0] Bit5Mode = 0;
	parameter [0:0] Bit6Mode = 0;
	parameter [0:0] Bit7Mode = 0;

	parameter NumInputs = 8;
	localparam ModeMask = {Bit7Mode, Bit6Mode, Bit5Mode, Bit4Mode, Bit3Mode, Bit2Mode, Bit1Mode, Bit0Mode};
    
    cy_psoc3_status #(.cy_force_order(1), .cy_md_select(ModeMask))
    sts_reg(
        /* input            */  .clock(clock),
        /* input    [07:00] */  .status({status_7,status_6,status_5,status_4,status_3,status_2,status_1,status_0})
    );
	
endmodule

