// Copyright by Adam Kinsman, Henry Ko and Nicola Nicolici
// Developed for the Embedded Systems course (COE4DS4)
// Department of Electrical and Computer Engineering
// McMaster University
// Ontario, Canada

`timescale 1ns/100ps
`default_nettype none

// This module interfaces to the console slave
module Nios_Console_Interface (
	input logic Clock,
	input logic Resetn,

	output logic [5:0] Button_Invert,

	output logic [9:0] CharMap_address,
	output logic [15:0] CharMap_data,
	output logic CharMap_wren,
	input logic [15:0] CharMap_q,
	
	output logic [7:0] Label_address,
	output logic [7:0] Label_data,
	output logic Label_wren,
	input logic [7:0] Label_q,
	
	input logic [10:0] address,
	input logic chipselect,
	input logic read,
	input logic write,
	output logic [31:0] readdata,
	input logic [31:0] writedata
);

// wa 0x0 - button invert
// wa 0x1 - filter config
// wa 0x300 - Label
// wa 0x400 - CharMap

assign CharMap_address = address[9:0];
assign Label_address = address[7:0];

assign CharMap_wren = chipselect & write &
	(address[10] == 1'b1);
assign Label_wren = chipselect & write &
	(address[10:8] == 3'd3);

assign CharMap_data = writedata[15:0];
assign Label_data = writedata[7:0];

logic [10:0] address_reg;

always_ff @(posedge Clock or negedge Resetn) begin
	if (~Resetn) address_reg <= 11'd0;
	else address_reg <= address;
end

assign readdata = 
	(address_reg[10] == 1'b1) ? { 16'h0000, CharMap_q } : 
	(address_reg[10:8] == 3'd3) ? { 24'h000000, Label_q } : 
	(address_reg == 11'd0) ? { 26'd0, Button_Invert } :
		32'h00000000;

always_ff @(posedge Clock or negedge Resetn) begin
	if (~Resetn) Button_Invert <= 6'd0;
	else if (chipselect & write &
		(address == 11'd0)) Button_Invert <= writedata[5:0];
end

endmodule
