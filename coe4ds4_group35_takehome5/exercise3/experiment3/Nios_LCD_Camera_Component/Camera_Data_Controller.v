// Copyright by Adam Kinsman, Henry Ko and Nicola Nicolici
// Developed for the Embedded Systems course (COE4DS4)
// Department of Electrical and Computer Engineering
// McMaster University
// Ontario, Canada

`timescale 1ns/100ps
`default_nettype none

// This module provides the data interface
// to the Camera module and performs the 
// Raw 2 RGB conversion
module Camera_Data_Controller (
	input logic Clock_50,
	input logic Resetn,	
	input logic Camera_PIXCLK,

	input logic Enable,
	input logic Start,
	input logic Stop,

	input logic [9:0] iCamera_Data,
	input logic iFrame_Valid,
	input logic iLine_Valid,

	output logic [9:0] oRed,
	output logic [9:0] oGreen,
	output logic [9:0] oBlue,
	output logic oData_Valid,

	output logic [31:0] oFrame_Count
);

logic 	[9:0] 	iCamera_Data_PIX;
logic 			iFrame_Valid_PIX, iLine_Valid_PIX;

// capturing camera inputs on Camera_PIXCLK 
// domain upon entry to the FPGA
always_ff @(posedge Camera_PIXCLK or negedge Resetn) begin
	if (~Resetn) begin
		iCamera_Data_PIX <= 10'd0;
		iFrame_Valid_PIX <= 1'b0;
		iLine_Valid_PIX <= 1'b0;
	end else begin
		iCamera_Data_PIX <= iCamera_Data;
		iFrame_Valid_PIX <= iFrame_Valid;
		iLine_Valid_PIX <= iLine_Valid;
	end
end

logic 	[2:0] 	Camera_PIXCLK_50;
logic 	[9:0] 	iCamera_Data_50[1:0];
logic 			iFrame_Valid_50[1:0], iLine_Valid_50[1:0];

// handing over to the Clock_50 domain
// two stage capture 		
always_ff @(posedge Clock_50 or negedge Resetn) begin
	if (~Resetn) begin
		Camera_PIXCLK_50 <= 3'b000;
		iCamera_Data_50[1] <= 10'd0; iCamera_Data_50[0] <= 10'd0;
		iFrame_Valid_50[1] <= 1'b0; iFrame_Valid_50[0] <= 1'b0;
		iLine_Valid_50[1] <= 1'b0; iLine_Valid_50[0] <= 1'b0;
	end else begin   
		Camera_PIXCLK_50 <= { Camera_PIXCLK_50[1:0], Camera_PIXCLK };
		iCamera_Data_50[1] <= iCamera_Data_50[0]; 
		iCamera_Data_50[0] <= iCamera_Data_PIX;
		iFrame_Valid_50[1] <= iFrame_Valid_50[0];
		iFrame_Valid_50[0] <= iFrame_Valid_PIX;
		iLine_Valid_50[1] <= iLine_Valid_50[0];
		iLine_Valid_50[0] <= iLine_Valid_PIX;
	end
end

logic Capture_active;
always_ff @(posedge Clock_50 or negedge Resetn) begin
	if (~Resetn) Capture_active <= 1'b0;
	else if (~Enable) Capture_active <= 1'b0;
	else begin
		if (Start) Capture_active <= 1'b1;
		if (Stop) Capture_active <= 1'b0;
	end
end

logic 	[9:0] 	Camera_Data;
logic 			Frame_Valid, Frame_Valid_edge; 
logic 			Line_Valid, Data_Valid;

// finalize domain crossing and generate 
// data valid signal using edge detection
always_ff @(posedge Clock_50 or negedge Resetn) begin
	if (~Resetn) begin
		Camera_Data <= 10'd0;
		Frame_Valid <= 1'b0;
		Frame_Valid_edge <= 1'b0;
		Line_Valid <= 1'b0;
		Data_Valid <= 1'b0;
		oFrame_Count <= 32'd0;
	end else if (~Enable) begin
		Camera_Data <= 10'd0;
		Frame_Valid <= 1'b0;
		Frame_Valid_edge <= 1'b0;
		Line_Valid <= 1'b0;	
		Data_Valid <= 1'b0;
		oFrame_Count <= 32'd0;
	end else begin
		if (Camera_PIXCLK_50[2:1] == 2'b10) begin
			Camera_Data <= iCamera_Data_50[1];
			Frame_Valid_edge <= iFrame_Valid_50[1];
			if (~iFrame_Valid_50[1])
				Frame_Valid <= 1'b0;
			else if (~Frame_Valid_edge & Capture_active) begin
				Frame_Valid <= 1'b1;
				oFrame_Count <= oFrame_Count + 32'd1;			
			end
		end

		if (Frame_Valid) begin 
			Line_Valid <= iLine_Valid_50[1];
			Data_Valid <= (Camera_PIXCLK_50[2:1] == 2'b10) & 
				iFrame_Valid_50[1] & iLine_Valid_50[1];
		end else begin
			Line_Valid <= 1'b0;
			Data_Valid <= 1'b0;
		end
	end
end

logic 	[9:0]	Camera_Data_Tap0, Camera_Data_Tap1;

// memory based shift register
// for Raw 2 RGB filter
Line_Buffer Raw_Buffer (
	.clken(Data_Valid),
	.clock(Clock_50),
	.shiftin(Camera_Data),
	.taps0x(Camera_Data_Tap0),
	.taps1x(Camera_Data_Tap1)
);

logic 			Line_Valid_edge;
logic 	[1:0]	XY_parity;

// X/Y odd even generation
always_ff @(posedge Clock_50 or negedge Resetn) begin
	if (~Resetn) begin
		XY_parity <= 2'b00;
		Line_Valid_edge <= 1'b0;
	end else if (~Enable) begin
		XY_parity <= 2'b00;
		Line_Valid_edge <= 1'b0;
	end else begin
		Line_Valid_edge <= Line_Valid;
		if (~Frame_Valid) XY_parity <= 2'b00;
		else begin
			if (Data_Valid) 
				XY_parity[0] <= ~XY_parity[0];
			if (~Line_Valid & Line_Valid_edge)
				XY_parity[1] <= ~XY_parity[1];
		end
	end
end

logic 			Data_Valid_dly;
logic 	[9:0] 	Camera_Data_Tap0_dly;
logic 	[9:0] 	Camera_Data_Tap1_dly;
logic 	[10:0] 	Camera_Data_sum;

assign Camera_Data_sum = 
	( Camera_Data_Tap1_dly + Camera_Data_Tap0 );

// output data assignments
always_ff @(posedge Clock_50 or negedge Resetn) begin
	if (~Resetn) begin
		oRed <= 10'd0;
		oGreen <= 10'd0;
		oBlue <= 10'd0;
		oData_Valid <= 1'b0;
		Data_Valid_dly <= 1'b0;
		Camera_Data_Tap0_dly <= 10'd0;
		Camera_Data_Tap1_dly <= 10'd0;
	end else begin
		Data_Valid_dly <= Data_Valid;
		oData_Valid <= Data_Valid_dly & (XY_parity == 2'b01);
		if (Data_Valid) begin
			Camera_Data_Tap0_dly <= Camera_Data_Tap0;
			Camera_Data_Tap1_dly <= Camera_Data_Tap1;
		end
		if (Data_Valid_dly & (XY_parity == 2'b01)) begin
			oRed <= Camera_Data_Tap1;
			oGreen <= Camera_Data_sum[10:1];
			oBlue <= Camera_Data_Tap0_dly;
		end
	end
end

endmodule
