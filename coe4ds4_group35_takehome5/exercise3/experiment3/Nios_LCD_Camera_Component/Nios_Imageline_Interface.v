// Copyright by Adam Kinsman, Henry Ko and Nicola Nicolici
// Developed for the Embedded Systems course (COE4DS4)
// Department of Electrical and Computer Engineering
// McMaster University
// Ontario, Canada

`timescale 1ns/100ps
`default_nettype none

// This module interfaces to the image slave
module Nios_Imageline_Interface (
	input logic Clock,
	input logic Resetn,
	
	output logic [31:0] Filter_config,

	output logic [2:0] State_reload,
	input logic [2:0] State_read,
	
	output logic SDRAM_wr_src,
	output logic SDRAM_rd_src,
	output logic SDRAM_wren,
	output logic SDRAM_rden,
	output logic [15:0] SDRAM_wr_data_1,
	output logic [15:0] SDRAM_wr_data_2,
	input logic [15:0] SDRAM_rd_data_1,
	input logic [15:0] SDRAM_rd_data_2,
	
	input logic [10:0] address,
	input logic chipselect,
	input logic read,
	input logic write,
	output logic [31:0] readdata,
	input logic [31:0] writedata,
	output logic waitrequest
);

// ra 0 - SDRAM read data
// wa 0 - SDRAM write data
// ra 1 - status
//		bit 4:2 - state
// 		bit 1 - wr source
//		bit 0 - rd source
// wa 1 - 
//		bit 4:2 - state reload
//		bit 1 - wr source
//		bit 0 - rd source
// wa 2 - write address load (not used anymore)
// wa 3 - read address load  (not used anymore)
// wa 4 - filter config
// ra 5 - state read		(not used anymore)
// wa 5 - state reload		(not used anymore)


logic waitrequest_buf, waitrequest_buf_1;
logic chipselect_buf;

// drive waitrequest at negedge to make sure it is activated before the next rising edge of the clock as soon as the chipselect is activated
always_ff @(negedge Clock or negedge Resetn) begin
	if (~Resetn) begin
		waitrequest <= 1'b0;
	end else begin
		if (chipselect) begin
			if (!chipselect_buf) begin
				// activate waitrequest on posedge of chipselect
				waitrequest <= 1'b1;
			end else begin
				if (waitrequest_buf_1) waitrequest <= 1'b0;
			end
		end else waitrequest <= 1'b0;
	end
end

always_ff @(posedge Clock or negedge Resetn) begin
	if (~Resetn) begin
		waitrequest_buf <= 1'b0;
		waitrequest_buf_1 <= 1'b0;
		chipselect_buf <= 1'b0;
	end else begin
		waitrequest_buf <= waitrequest;
		waitrequest_buf_1 <= waitrequest_buf;
		
		chipselect_buf <= chipselect;
	end
end

// activate SDRAM_rden for one clock cycle only upon read request to get one data from SDRAM
always_ff @(posedge Clock or negedge Resetn) begin
	if (~Resetn) begin
		SDRAM_rden <= 1'b0;
	end else begin
		if (chipselect & read & (address == 11'd0) & (waitrequest & !waitrequest_buf))
			SDRAM_rden <= 1'b1;
		else
			SDRAM_rden <= 1'b0;		
	end
end

//assign SDRAM_rden = chipselect & read & (address == 11'd0) & (waitrequest & !waitrequest_buf);

always_ff @(posedge Clock or negedge Resetn) begin
	if (~Resetn) begin
		readdata <= 32'd0;
	end else if (chipselect & read & waitrequest_buf_1) begin
		case (address)
			11'd0 : readdata <= {SDRAM_rd_data_1,SDRAM_rd_data_2};
			11'd1 : readdata <= {27'd0, 
				State_read, SDRAM_wr_src, SDRAM_rd_src };
			default : readdata <= 32'd0;
		endcase
	end
end

always_ff @(posedge Clock or negedge Resetn) begin
	if (~Resetn) begin
		SDRAM_wren <= 1'b0;
		SDRAM_wr_data_1 <= 16'h0000;
		SDRAM_wr_data_2 <= 16'h0000;
	end else begin
		if (chipselect & write & (address == 11'd0) & (waitrequest & !waitrequest_buf)) begin
			SDRAM_wren <= 1'b1;
			SDRAM_wr_data_1 <= writedata[31:16];
			SDRAM_wr_data_2 <= writedata[15:0];
		end else SDRAM_wren <= 1'b0;
	end
end

always_ff @(posedge Clock or negedge Resetn) begin
	if (~Resetn) begin
		State_reload <= 3'd0;
		SDRAM_wr_src <= 1'b0;
		SDRAM_rd_src <= 1'b0;
	end else begin
		if (chipselect & write & 
			(address == 11'd1) & 
			(waitrequest & !waitrequest_buf)
		) begin
			State_reload <= writedata[4:2];
			SDRAM_wr_src <= writedata[1];
			SDRAM_rd_src <= writedata[0];
		end
	end
end

always_ff @(posedge Clock or negedge Resetn) begin
	if (~Resetn) Filter_config <= 32'd0;
	else if (chipselect & write & (address == 11'd4) & (waitrequest & !waitrequest_buf))
		Filter_config <= writedata;
end

endmodule
