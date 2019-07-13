// Copyright by Adam Kinsman, Henry Ko and Nicola Nicolici
// Developed for the Embedded Systems course (COE4DS4)
// Department of Electrical and Computer Engineering
// McMaster University
// Ontario, Canada

`timescale 1ns/100ps
`default_nettype none

// This module interfaces to the Touch panel slave
module Nios_Touch_Panel_Interface (
	input logic Clock,
	input logic Resetn,	
	input logic Touch_En,
	input logic Coord_En,
	input logic [11:0] X_Coord,
	input logic [11:0] Y_Coord,	

	input  logic [3:0] address,
	input  logic chipselect,
	input  logic read,
	input  logic write,
	output logic [31:0] readdata,
	input  logic [31:0] writedata,
	output logic irq
);

// ra 0 - touch_en + coords
// r/wa 1 - touch limit
// r/wa 2 - touch_en info, irq clear
// info: touch, coord, counter, touch neg, touch pos, irq

logic [1:0] Touch_en_edge;
logic [5:0] Touch_en_info;
logic [31:0] Touch_en_counter, Touch_en_limit;
logic [11:0] x_coord_reg, y_coord_reg;
logic [5:0] LCD_keypad;

always_ff @(posedge Clock or negedge Resetn) begin
	if (~Resetn) begin
		x_coord_reg <= 12'h000;
		y_coord_reg <= 12'h000;
	end else begin
		if (Coord_En) begin
			x_coord_reg <= X_Coord;
			y_coord_reg <= Y_Coord;
		end
	end
end

always_ff @(posedge Clock or negedge Resetn) begin
	if (~Resetn) readdata <= 32'd0;
	else begin
		case (address[1:0])
			2'd0 : readdata <= { Touch_En,
				3'h0, x_coord_reg, 4'h0, y_coord_reg };
			2'd1 : readdata <= Touch_en_limit;
			2'd2 : readdata <= { 26'd0, Touch_en_info };
			default : readdata <= 32'd0;
		endcase
	end
end

always_ff @(posedge Clock or negedge Resetn) begin
	if (~Resetn) Touch_en_limit <= 32'hFFFFFFFF;
	else if (chipselect & write &
		(address == 32'd1)) Touch_en_limit <= writedata;
end

logic active_flag;
always_ff @(posedge Clock or negedge Resetn) begin
	if (~Resetn) begin
		Touch_en_info <= 6'd0;
		active_flag <= 1'b0;
	end else begin
		if (~Touch_en_info[5]) active_flag <= 1'b0;
		else if (Coord_En) active_flag <= 1'b1;
	
		if (chipselect & write &
			(address == 32'd2)
		) begin
			Touch_en_info <= writedata[5:0];
		end else begin
			Touch_en_info[5] <= Touch_En;
			if (Coord_En) Touch_en_info[4] <= 1'b1;
			if (Touch_en_counter == 32'd0) Touch_en_info[3] <= 1'b1;
			if (Touch_en_edge == 2'b10) Touch_en_info[2] <= 1'b1;
			if (Touch_en_edge == 2'b01) Touch_en_info[1] <= 1'b1;
 
			if (active_flag & (Touch_en_counter == 32'd0))
				Touch_en_info[0] <= 1'b1; 
		end 
	end
end

assign irq = Touch_en_info[0];

always_ff @(posedge Clock or negedge Resetn) begin
	if (~Resetn) begin
		Touch_en_counter <= 32'd0;
		Touch_en_edge <= 2'b00;
	end else begin
		Touch_en_edge <= { Touch_en_edge[0], Touch_En };
		if (~Touch_En) Touch_en_counter <= 32'd0;
		else if (active_flag) begin
			if (Touch_en_counter == 32'd0)
				Touch_en_counter <= Touch_en_limit;
			else Touch_en_counter <= Touch_en_counter - 32'd1;
		end
	end
end

endmodule
