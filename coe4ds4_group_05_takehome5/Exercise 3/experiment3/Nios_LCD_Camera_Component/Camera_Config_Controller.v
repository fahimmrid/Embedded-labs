// Copyright by Adam Kinsman, Henry Ko and Nicola Nicolici
// Developed for the Embedded Systems course (COE4DS4)
// Department of Electrical and Computer Engineering
// McMaster University
// Ontario, Canada

`timescale 1ns/100ps
`default_nettype none

// This module controls the configuration 
// interface of the Digital Camera
module Camera_Config_Controller (
	input logic Clock,
	input logic Resetn,
	
	input logic Start,
	output logic Done,
	input logic [15:0] iExposure,
	
	output logic Camera_I2C_sclk,
	inout wire Camera_I2C_sdat
);

logic I2C_start, I2C_done, I2C_error;

logic 	[23:0] 	I2C_data;
logic 	[15:0] 	Lookup_data;
logic 	[4:0] 	I2C_state;

always_comb begin case (I2C_state)
	5'd00 : Lookup_data = 16'h0000;
	5'd01 : Lookup_data = 16'h2000;		// Row/Column Mirroring
	5'd02 : Lookup_data = 16'hF103;		
	5'd03 : Lookup_data = 
		{ 8'h09 , iExposure[15:8] };	// Exposure
	5'd04 : Lookup_data = 
		{ 8'hF1 , iExposure[7:0] }; 	
	5'd05 : Lookup_data = 16'h2B00;		// Green 1 Gain
	5'd06 : Lookup_data = 16'hF1B0;
	5'd07 : Lookup_data = 16'h2C00;		// Blue Gain
	5'd08 : Lookup_data = 16'hF1CF;
	5'd09 : Lookup_data = 16'h2D00;		// Red Gain
	5'd10 : Lookup_data = 16'hF1CF;
	5'd11 : Lookup_data = 16'h2E00;		// Green 2 Gain
	5'd12 : Lookup_data = 16'hF1B0;
	5'd13 : Lookup_data = 16'h0500;		// H_Blanking
	5'd14 : Lookup_data = 16'hF188;
	5'd15 : Lookup_data = 16'h0600;		// V_Blanking
	5'd16 : Lookup_data = 16'hF119;
	default : Lookup_data = 16'h0000;
endcase end

// I2C control state machine
always_ff @(posedge Clock or negedge Resetn) begin
	if (~Resetn) begin
		I2C_start <= 1'b0;
		I2C_state <= 5'd0;
		I2C_data <= 24'h000000;
		Done <= 1'b1;
	end else begin
		if (I2C_state == 5'd0) begin
			if (Start) begin 
				Done <= 1'b0;
				I2C_state <= 5'd01; 
				I2C_start <= 1'b1; 
				I2C_data <= { 8'hBA , Lookup_data };
			end
		end else begin
			I2C_start <= 1'b0; 
			if (I2C_done & ~I2C_start) begin
				if (~I2C_error & (I2C_state == 5'd17)) begin
					Done <= 1'b1;
					I2C_state <= 5'd00; 
				end else begin
					I2C_start <= 1'b1; 
					if (~I2C_error) begin
						I2C_state <= I2C_state + 5'd1; 
						I2C_data <= { 8'hBA , Lookup_data};
					end	
				end
			end	
		end
	end
end

// I2C master unit
I2C_M24_Controller u0 (
	.Clock(Clock),
	.Resetn(Resetn),	
	.I2C_sclk(Camera_I2C_sclk),
 	.I2C_sdat(Camera_I2C_sdat),
 	.I2C_scen(),
	.Start(I2C_start),
	.Data_I(I2C_data),
	.Error(I2C_error),
	.Done(I2C_done)
);

endmodule
