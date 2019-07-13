// Copyright by Adam Kinsman, Henry Ko and Nicola Nicolici
// Developed for the Embedded Systems course (COE4DS4)
// Department of Electrical and Computer Engineering
// McMaster University
// Ontario, Canada

`timescale 1ns/100ps
`default_nettype none

// This module provides master control of a 
// three wire interface
module I2C_M24_Controller (
	input logic Clock,
	input logic Resetn,
	
	output logic I2C_sclk,
 	inout wire I2C_sdat,
 	output logic I2C_scen,

	input logic Start,
	input logic [23:0] Data_I,
	output logic Error,
	output logic Done
);

assign I2C_scen = 1'b0;

logic  			clock_div, clock_div_prev;
logic  	[10:0] 	clock_div_count;

always_ff @(posedge Clock or negedge Resetn) begin
	if (~Resetn) begin
		clock_div <= 1'b0;
		clock_div_prev <= 1'b0;
		clock_div_count <= 11'h000;
	end else begin
		clock_div <= clock_div_count[10];
		clock_div_prev <= clock_div;
		clock_div_count <= clock_div_count + 11'h1;
	end
end

logic 			clk_OR_msk, clk_AND_msk;
logic 	[30:0]	sdat;
logic 	[5:0] 	state_counter;

assign Done = (state_counter == 6'h00);
assign I2C_sclk = (( clock_div & clk_AND_msk ) | clk_OR_msk );
assign I2C_sdat = (sdat[30]) ? 1'bz : 1'b0;

always_ff @(posedge Clock or negedge Resetn) begin
	if (~Resetn) begin
		state_counter <= 6'd0;
		Error <= 1'b0;
	end else begin
		if (state_counter == 6'd0) begin
			if (Start) begin
				state_counter <= 6'd1;
				Error <= 1'b0;
			end
		end else if (clock_div & ~clock_div_prev) begin
			if (state_counter == 6'd33)
				state_counter <= 6'd0;
			else state_counter <= state_counter + 6'h1;
			if (
				(state_counter == 6'd12) | 
				(state_counter == 6'd21) | 
				(state_counter == 6'd30)
			) Error <= Error | I2C_sdat; 
		end
	end
end

always_ff @(posedge Clock or negedge Resetn) begin
	if (~Resetn) begin
		sdat <= {31{1'b1}};
		clk_OR_msk <= 1'b1;
		clk_AND_msk <= 1'b1;
	end else if (~clock_div & clock_div_prev) begin
		if (state_counter == 6'd2) sdat <= { 1'b0, 1'b0, 
			Data_I[23:16], 1'b1, Data_I[15:8], 
			1'b1, Data_I[7:0], 1'b1, 1'b0, 1'b0 };
		else sdat <= { sdat[29:0],1'b1 };
		if (state_counter == 6'd3) clk_OR_msk <= 1'b0;
		if (state_counter == 6'd32) clk_OR_msk <= 1'b1;
		if (
			(state_counter == 6'd3) | 
			(state_counter == 6'd31)
		) clk_AND_msk <= 1'b0;
		else clk_AND_msk <= 1'b1;
	end
end

endmodule
