// Copyright by Adam Kinsman, Henry Ko and Nicola Nicolici
// Developed for the Embedded Systems course (COE4DS4)
// Department of Electrical and Computer Engineering
// McMaster University
// Ontario, Canada

`timescale 1ns/100ps
`default_nettype none

// This module provides master control of a 
// three wire interface
module I2C_M16_Controller (
	input logic Clock,
	input logic Resetn,
	
	output logic I2C_sclk,
 	inout wire I2C_sdat,
	output logic I2C_scen,

	input logic Start,
	input logic [15:0] Data_I,
	output logic Acknowledge,
	output logic Done
);

logic 			clock_div, clock_div_prev;
logic 	[11:0] 	clock_div_count;

always_ff @(posedge Clock or negedge Resetn) begin
	if (~Resetn) begin
		clock_div <= 1'b0;
		clock_div_prev <= 1'b0;
		clock_div_count <= 12'h000;
	end else begin
		clock_div <= clock_div_count[11];
		clock_div_prev <= clock_div;
		clock_div_count <= clock_div_count + 12'h1;
	end
end

logic 			sdat_en;
logic 	[15:0]	sdat;
logic 	[4:0] 	state_counter;

assign Done = (state_counter == 5'd0);
assign I2C_sclk = ( clock_div & ~I2C_scen );
assign I2C_sdat = (sdat_en) ? sdat[15] : 1'bz;

always_ff @(posedge Clock or negedge Resetn) begin
	if (~Resetn) begin
		state_counter <= 5'd0;
		Acknowledge <= 1'b1;
	end else begin
		if (state_counter == 5'd0) begin
			if (Start) begin
				state_counter <= 5'd1;
				Acknowledge <= 1'b1;
			end
		end else if (clock_div & ~clock_div_prev) begin
			if (state_counter == 5'd18) 
				state_counter <= 5'd0;
			else state_counter <= state_counter + 5'd1;
			if (state_counter == 5'd9)
				Acknowledge <= Acknowledge & I2C_sdat; 
		end
	end
end

always_ff @(posedge Clock or negedge Resetn) begin
	if (~Resetn) begin
		sdat <= {16{1'b1}};
		I2C_scen <= 1'b1;
		sdat_en <= 1'b0;
	end else if (~clock_div & clock_div_prev) begin
		if (state_counter == 5'd2) sdat <= Data_I[15:0];
		else sdat <= { sdat[14:0], 1'b1 };
		
		if (state_counter == 5'd2) sdat_en <= 1'b1; 
		if (state_counter == 5'd9) sdat_en <= 1'b0;
		if (state_counter == 5'd10) sdat_en <= 1'b1;
		if (state_counter == 5'd18) sdat_en <= 1'b0;
		
		if (state_counter == 5'd2) I2C_scen <= 1'b0; 
		if (state_counter == 5'd18) I2C_scen <= 1'b1; 
	end
end

endmodule
