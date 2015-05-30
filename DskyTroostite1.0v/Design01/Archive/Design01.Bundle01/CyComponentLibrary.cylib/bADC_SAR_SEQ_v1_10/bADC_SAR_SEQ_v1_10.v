/*******************************************************************************
* File Name: bADC_SAR_SEQ_v1_10.v
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
* This file provides the Verilog implementation of the bADC_SAR_SEQ component.
*
*------------------------------------------------------------------------------
*                 Control Register definition
*------------------------------------------------------------------------------
*
*  Control Register Definition
*  +=====+-------+-------+-------+--------+--------+-------+--------+--------+
*  | Bit |   7   |   6   |   5   |   4    |   3    |   2   |   1    |   0    |
*  +=====+-------+-------+-------+--------+--------+-------+--------+--------+
*  |Desc |                  UNUSED                 |SW_SOC |LOAD_PER|   EN   |
*  +=====+-------+-------+-------+--------+--------+-------+--------+--------+
*
*    EN          =>   Enable Base component
*
*    LOAD PERIOD =>   Generate pulse to load period to the Counter7
*
*    SW_SOC      =>   Software Start of Conversion (SOC) Pulse
*
********************************************************************************
* I*O Signals:
********************************************************************************
*    name              direction       Description
*
*    eoc               output          sampling is done (eoc)
*    ch_addr           output          channel address
*    soc_out           output          SOC output to the ADC SAR
*    soc               input           soc input
*    eos               input           end of sampling
*    nrq               input           DMA next request input
*    clock             input           component clock
*    bus_clock         input           bus clock
*
********************************************************************************
* Copyright 2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

`include "cypress.v"

module bADC_SAR_SEQ_v1_10 (
    output eoc,
    output soc_out,
    output [5:0] ch_addr,

    input soc,
    input eos,
    input nrq,
    input clock,
    input sar_eoc,
    input bus_clock
);

parameter SampleMode  = 0;
parameter NumChannels = 0;

localparam CyclePeriod = (NumChannels - 1);

/* Sample Mode local parameters */
localparam ADC_SAR_SEQ_SAMPLE_MODE_FREE_RUNNING = 1'h0;
localparam ADC_SAR_SEQ_SAMPLE_MODE_HW_TRIGGERED = 2'h2;

/* Local parameters for the Control Register bits */
localparam ADC_SAR_SEQ_CTRL_ENABLE      = 1'b0;
localparam ADC_SAR_SEQ_CTRL_LOAD_PERIOD = 1'b1;
localparam ADC_SAR_SEQ_CTRL_SW_SOC      = 2'h2;

/* Local parameters for the Status Register bits */
localparam ADC_SAR_SEQ_STS_END_OF_CONVERSION = 1'b0;

wire [6:0] count;
wire [7:0] control;
wire [7:0] status;

wire enable      = control[ADC_SAR_SEQ_CTRL_ENABLE];
wire load_period = control[ADC_SAR_SEQ_CTRL_LOAD_PERIOD];
wire sw_soc      = control[ADC_SAR_SEQ_CTRL_SW_SOC];
wire cnt_enable;
wire clk_fin;
wire comb_logic;
wire reset_fsm;
wire soc_in;
wire soc_edge_detect;
reg bus_clk_reg;
reg comp_clk_reg;
reg soc_reg;
reg eoc_reg;
reg eoc_dbl_reg;
reg soc_src_select;
reg reset_fsm_reg;
reg is_soc_set;
reg soc_edge_detect_reg;

/* Clock Enable primitive instantiation */
cy_psoc3_udb_clock_enable_v1_0 #(.sync_mode(`TRUE))
ClkEn (
    .clock_in(clock),
    .enable(1'b1),
    .clock_out(clk_fin)
);

/* Output to address input of the AMUXHw component */
assign ch_addr = count[5:0];

assign status[7:1] = 6'h0;
assign status[ADC_SAR_SEQ_STS_END_OF_CONVERSION] = comp_clk_reg;

/* The last channel address is loaded at the startup and changes in the
*  decrementing fashion each time after the SAR data sampling is complete
*/
assign cnt_enable = ((enable & eos) | load_period);

/* Clock domain crossing for nrq to generate eoc */
always@(posedge bus_clock)
begin
    bus_clk_reg <= comb_logic;
end

always@(posedge clk_fin)
begin
    comp_clk_reg <= comb_logic;
end

assign eoc        = comp_clk_reg;
assign comb_logic = (~comp_clk_reg & bus_clk_reg) | nrq;

/* SW & HW Triggered Mode logic */
if(SampleMode != ADC_SAR_SEQ_SAMPLE_MODE_FREE_RUNNING)
begin
    assign reset_fsm = (((count[6:0] == CyclePeriod) & eoc) & enable);

    assign soc_edge_detect = (enable == 1'b1) ? (~soc_reg & soc) : 1'b0;

    /* HW or SW SOC selection */
    assign soc_in  = (SampleMode == ADC_SAR_SEQ_SAMPLE_MODE_HW_TRIGGERED) ? soc_edge_detect_reg : sw_soc;

    /* React to SOC input only ones and switch to SAR ADC registered EOC */
    assign soc_out = (soc_src_select == 1'b1) ? eoc_dbl_reg : soc_in;


    always@(posedge clk_fin)
    begin
        soc_reg             <= soc;
        eoc_reg             <= sar_eoc;
        eoc_dbl_reg         <= eoc_reg;
        reset_fsm_reg       <= reset_fsm;
        soc_edge_detect_reg <= soc_edge_detect;
    end

    always@(posedge clk_fin)
    begin
        if(enable)
        begin
            if(soc_in)
            begin
                is_soc_set <= 1'b1;
            end
            else
            if(reset_fsm_reg)
            begin
                is_soc_set <= 1'b0;
            end
            else
            begin
                is_soc_set <= is_soc_set;
            end
        end
        else
        begin
            is_soc_set <= 1'b0;
        end
    end

    /* Logic to control SOC-EOC MUX */
    always@(posedge clk_fin)
    begin
        if(enable)
        begin
            if(NumChannels != 1)
            begin
                if(is_soc_set & eoc_reg)
                begin
                    soc_src_select <= 1'b1;
                end
                else
                if(reset_fsm_reg)
                begin
                    soc_src_select <= 1'b0;
                end
                else
                begin
                    soc_src_select <= soc_src_select;
                end
            end
            else
            begin
                soc_src_select <= 1'b0;
            end
        end
        else
        begin
            soc_src_select <= 1'b0;
        end
    end
end
else
begin
    assign soc_out = 1'b0;
end

/* Control Register instantiation */
cy_psoc3_control #(.cy_force_order(1), .cy_ctrl_mode_1(8'h06), .cy_ctrl_mode_0(8'h07))
CtrlReg(
    /* input          */ .clock(clk_fin),
    /* output [07:00] */ .control(control)
);

/* Channel Selection Counter instantiation */
cy_psoc3_count7 #(.cy_period(CyclePeriod),.cy_route_ld(0),.cy_route_en(1), .cy_alt_mode(0))
ChannelCounter(
    /* input          */ .clock(clk_fin),
    /* input          */ .reset(1'b0),
    /* input          */ .load(1'b0),
    /* input          */ .enable(cnt_enable),
    /* output [06:00] */ .count(count),
    /* output         */ .tc()
);

cy_psoc3_status #(.cy_force_order(1), .cy_md_select(8'h01))
EOCSts(
    /* input            */ .clock(clk_fin),
    /* output   [07:00] */ .status(status)
);

endmodule

/* [] END OF FILE */
