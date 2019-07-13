// Copyright by Adam Kinsman, Henry Ko and Nicola Nicolici
// Developed for the Embedded Systems course (COE4DS4)
// Department of Electrical and Computer Engineering
// McMaster University
// Ontario, Canada

`timescale 1ns/100ps
`default_nettype none

// This module controls the LCD configuration 
// interface of the LTM
module LCD_Config_Controller (
	input logic Clock,
	input logic Resetn,

	input logic Start,
	output logic Done,
	
	output logic LCD_I2C_sclk,
 	inout wire LCD_I2C_sdat,
	output logic LCD_I2C_scen
);

logic I2C_start, I2C_done, I2C_Acknowledge;

logic 	[15:0] 	I2C_data, Lookup_data;
logic 	[4:0]	I2C_state;

logic [9:0] GAMMA_0,   GAMMA_8,   GAMMA_16,  GAMMA_32; 
logic [9:0] GAMMA_64,  GAMMA_96,  GAMMA_128, GAMMA_192; 
logic [9:0] GAMMA_224, GAMMA_240, GAMMA_248, GAMMA_256;

assign GAMMA_0	 = 10'd106;
assign GAMMA_8	 = 10'd200;
assign GAMMA_16	 = 10'd289;
assign GAMMA_32	 = 10'd375;
assign GAMMA_64	 = 10'd460;
assign GAMMA_96	 = 10'd543;
assign GAMMA_128 = 10'd625;
assign GAMMA_192 = 10'd705;
assign GAMMA_224 = 10'd785;
assign GAMMA_240 = 10'd864;
assign GAMMA_248 = 10'd942;
assign GAMMA_256 = 10'd1020;

logic vr, hr;
assign vr = 1'b0;
assign hr = 1'b0;

always_comb begin case (I2C_state)
	5'd00 : Lookup_data = { {6'h11,2'b01} , {GAMMA_0[9:8],GAMMA_8[9:8],GAMMA_16[9:8],GAMMA_32[9:8]} };
	5'd01 : Lookup_data = { {6'h12,2'b01} , {GAMMA_64[9:8],GAMMA_96[9:8],GAMMA_128[9:8],GAMMA_192[9:8]} };
	5'd02 : Lookup_data = { {6'h13,2'b01} , {GAMMA_224[9:8],GAMMA_240[9:8],GAMMA_248[9:8],GAMMA_256[9:8]} };
	5'd03 : Lookup_data = { {6'h14,2'b01} , GAMMA_0[7:0] };
	5'd04 : Lookup_data = { {6'h15,2'b01} , GAMMA_8[7:0] };
	5'd05 : Lookup_data = { {6'h16,2'b01} , GAMMA_16[7:0] };
	5'd06 : Lookup_data = { {6'h17,2'b01} , GAMMA_32[7:0] };
	5'd07 : Lookup_data = { {6'h18,2'b01} , GAMMA_64[7:0] };
	5'd08 : Lookup_data = { {6'h19,2'b01} , GAMMA_96[7:0] };
	5'd09 : Lookup_data = { {6'h1A,2'b01} , GAMMA_128[7:0] };
	5'd10 : Lookup_data = { {6'h1B,2'b01} , GAMMA_192[7:0] };
	5'd11 : Lookup_data = { {6'h1C,2'b01} , GAMMA_224[7:0] };
	5'd12 : Lookup_data = { {6'h1D,2'b01} , GAMMA_240[7:0] };
	5'd13 : Lookup_data = { {6'h1E,2'b01} , GAMMA_248[7:0] };
	5'd14 : Lookup_data = { {6'h1F,2'b01} , GAMMA_256[7:0] };
	5'd15 : Lookup_data = { {6'h20,2'b01} , {4'hF,4'h0} };
	5'd16 : Lookup_data = { {6'h21,2'b01} , {4'hF,4'h0} };
	5'd17 : Lookup_data = { {6'h03,2'b01} , 8'hDF };
	5'd18 : Lookup_data = { {6'h02,2'b01} , 8'h07 };
	5'd19 : Lookup_data = { {6'h04,2'b01} , { 6'b000101, ~vr , ~hr } };
	default : Lookup_data = 16'h0000;
endcase end

// I2C control state machine
always_ff @(posedge Clock or negedge Resetn) begin
	if (~Resetn) begin
		I2C_start <= 1'b0;
		I2C_state <= 5'd0;
		I2C_data <= 16'h0000;
		Done <= 1'b1;
	end else begin
		if (I2C_state == 5'd0) begin
			if (Start) begin 
				Done <= 1'b0;
				I2C_state <= 5'd01; 
				I2C_start <= 1'b1; 
				I2C_data <= Lookup_data;
			end
		end else begin
			I2C_start <= 1'b0; 
			if (I2C_done & ~I2C_start) begin
				if (I2C_Acknowledge & (I2C_state == 5'd20)) begin
					Done <= 1'b1;
					I2C_state <= 5'd00; 
				end else begin
					I2C_start <= 1'b1; 
					if (I2C_Acknowledge) begin
						I2C_state <= I2C_state + 5'd1; 
						I2C_data <= Lookup_data;
					end	
				end
			end	
		end
	end
end

// I2C master unit
I2C_M16_Controller I2C_unit (
	.Clock(Clock),
	.Resetn(Resetn),	
	.I2C_sclk(LCD_I2C_sclk),
 	.I2C_sdat(LCD_I2C_sdat),
 	.I2C_scen(LCD_I2C_scen),
	.Start(I2C_start),
	.Data_I(I2C_data),
	.Acknowledge(I2C_Acknowledge),
	.Done(I2C_done)
);

endmodule
