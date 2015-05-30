/*******************************************************************************
* File Name:  CyStatusReg_v0_5.v
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

module CyStatusReg_v0_5 (
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

	parameter NumInputs = 8;
	parameter ModeMask = 0;
    
    cy_psoc3_status #(.cy_force_order(1), .cy_md_select(ModeMask))
    sts_reg(
        /* input            */  .clock(clock),
        /* input    [07:00] */  .status({status_7,status_6,status_5,status_4,status_3,status_2,status_1,status_0})
    );
	
endmodule

