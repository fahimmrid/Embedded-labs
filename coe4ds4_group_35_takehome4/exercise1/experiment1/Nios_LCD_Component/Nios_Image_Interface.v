// Copyright by Adam Kinsman, Henry Ko and Nicola Nicolici
// Developed for the Embedded Systems course (COE4DS4)
// Department of Electrical and Computer Engineering
// McMaster University
// Ontario, Canada

`timescale 1ns/100ps
`default_nettype none

// This module interfaces to the image slave
module Nios_Image_Interface (
	input logic Clock,
	input logic Resetn,
	
	output logic [15:0] SRAM_writedata_1,
	output logic [15:0] SRAM_writedata_2,
	output logic SRAM_write_en,
	output logic SRAM_load_en,
	
	input logic [3:0] address,
	input logic chipselect,
	input logic read,
	input logic write,
	output logic [31:0] readdata,
	input logic [31:0] writedata	
);

logic [1:0] wen_reg, load_reg;
logic [9:0] X_fill_count;
logic [8:0] Y_fill_count;

always @(posedge Clock or negedge Resetn) begin
	if (~Resetn) begin
		wen_reg <= 2'b00;
		SRAM_write_en <= 1'b0;
		SRAM_writedata_1 <= 16'h0000;
		SRAM_writedata_2 <= 16'h0000;
		X_fill_count <= 10'd0;
		Y_fill_count <= 9'd0;
	end else if (SRAM_load_en) begin
		wen_reg <= 2'b00;
		SRAM_write_en <= 1'b0;
		SRAM_writedata_1 <= 16'h0000;
		SRAM_writedata_2 <= 16'h0000;
		X_fill_count <= 10'd0;
		Y_fill_count <= 9'd0;		
	end else begin
		wen_reg[1] <= wen_reg[0];
		wen_reg[0] <= (
			chipselect & write & 
			(address == 4'd0));
		if (wen_reg == 2'b01) begin
			SRAM_writedata_1 <= writedata[31:16];
			SRAM_writedata_2 <= writedata[15:0];
//		end
//		if (wen_reg == 2'b10) begin
			SRAM_write_en <= 1'b1;
			if (X_fill_count == 10'd639) begin
				X_fill_count <= 10'd0;
				if (Y_fill_count == 9'd511) Y_fill_count <= 9'd0;
				else Y_fill_count <= Y_fill_count + 9'd1;
			end else X_fill_count <= X_fill_count + 10'd1;
		end else SRAM_write_en <= 1'b0;					
	end
end
				
always_ff @(posedge Clock or negedge Resetn) begin
	if (~Resetn) begin
		readdata <= 32'd0;
	end else begin
		if (read & chipselect & 
			(address == 4'd1)
		) begin
			readdata <= {
				7'd0, Y_fill_count,
				6'd0, X_fill_count };
		end
	end
end

//assign SRAM_load_en = ~Resetn;
always_ff @(posedge Clock or negedge Resetn) begin
	if (~Resetn) begin
		SRAM_load_en <= 1'b1;
		load_reg <= 2'b00;
	end else begin
		load_reg[1] <= load_reg[0];
		load_reg[0] <= (
			chipselect & write & 
			(address == 4'd2));
		SRAM_load_en <= (load_reg == 2'b01);
	end
end

// wa 0 - pixel write 
// ra 1 - location
// wa 2 - sync

endmodule
