// Copyright by Adam Kinsman, Henry Ko and Nicola Nicolici
// Developed for the Embedded Systems course (COE4DS4)
// Department of Electrical and Computer Engineering
// McMaster University
// Ontario, Canada

`timescale 1ns/100ps
`default_nettype none

// This module generates the synchronization
// signals for the LCD using modulo counters
module LCD_Data_Controller (
	input logic Clock,
	output logic oClock_en,
	input logic Resetn,

	input logic Enable,
	input logic [7:0] iRed,
	input logic [7:0] iGreen,
	input logic [7:0] iBlue,
	output logic [9:0] oCoord_X,
	output logic [9:0] oCoord_Y,
	
	output logic [10:0] H_Count,
	output logic [9:0] V_Count,
	
	output logic LTM_NCLK,  	// LCD Interface clock
	output logic LTM_HD, 		// LCD Horizontal sync
	output logic LTM_VD,        // LCD Vertical sync
	output logic LTM_DEN, 		// LCD Data Enable
	output logic [7:0] LTM_R, 	// LCD Red color data  
	output logic [7:0] LTM_G, 	// LCD Green color data
	output logic [7:0] LTM_B  	// LCD Blue color data 
);

parameter H_LINE = 11'd1056;
parameter V_LINE = 10'd525;
parameter Hsync_Blank = 11'd216;
parameter Hsync_Front_Porch = 11'd40;
parameter Vertical_Back_Porch = 10'd35;
parameter Vertical_Front_Porch = 10'd10;

logic H_Sync, V_Sync, H_den, V_den;
logic [7:0] Red, Green, Blue;

logic [10:0] oCoord_X_long;
assign oCoord_X_long = H_Count - Hsync_Blank;
assign oCoord_X = oCoord_X_long[9:0];
assign oCoord_Y = V_Count - Vertical_Back_Porch;

// For generating a 25 MHz pulse
always_ff @(posedge Clock or negedge Resetn) begin
	if (~Resetn) oClock_en <= 1'b0;
	else if (~Enable) oClock_en <= 1'b0;
	else oClock_en <= ~oClock_en;
end

// H_Sync Generator
always_ff @(posedge Clock or negedge Resetn) begin
	if (~Resetn) begin
		H_Count <= 11'd0;
		H_Sync <= 1'b0;
		H_den <= 1'b0;
	end else if (~Enable) begin
		H_Count <= 11'd0;
		H_Sync <= 1'b0;
		H_den <= 1'b0;
	end	else if (oClock_en) begin
		//	H_Sync Counter
		if (H_Count == H_LINE-1) begin
			H_Count <= 11'd0;
			H_Sync <= 1'b0;
		end else begin
			H_Count <= H_Count + 11'd1;
			H_Sync <= 1'b1;
			if (H_Count == (Hsync_Blank - 11'd1)) 
				H_den <= 1'b1;
			if (H_Count == (H_LINE - Hsync_Front_Porch - 11'd1)) 
//			if (H_Count == (H_LINE - Hsync_Front_Porch - 11'd160 - 11'd1)) 
				H_den <= 1'b0;
		end
	end
end

// V_Sync Generator
always_ff @(posedge Clock or negedge Resetn) begin
	if (~Resetn) begin
		V_Count <= 10'd0;
		V_Sync <= 1'b1;
		V_den <= 1'b0;
	end	else if (~Enable) begin
		V_Count <= 10'd0;
		V_Sync <= 1'b1;
		V_den <= 1'b0;
	end else if (oClock_en) begin
		if (H_Count == (H_LINE-1)) begin
			if (V_Count == (V_LINE-1)) V_Count <= 10'd0;
			else V_Count <= V_Count + 10'd1;
			if (V_Count == (Vertical_Back_Porch - 10'd1)) 
				V_den <= 1'b1;
			if (V_Count == (V_LINE - Vertical_Front_Porch - 10'd1))
				V_den <= 1'b0;
		end
		if (V_Count == 10'd0) V_Sync <= 1'b0;
		else V_Sync <= 1'b1;
	end
end

//assign LTM_NCLK = ~oClock_en;

// buffer the RGB signals to synchronize them with V_Sync and H_Sync
// the RGB signals need also to be disabled during blanking
always_ff @(posedge Clock or negedge Resetn) begin
	if(~Resetn) begin
		LTM_NCLK <= 1'b1;
		LTM_R <= 8'h00;
		LTM_G <= 8'h00;
		LTM_B <= 8'h00;
		LTM_DEN <= 1'b0;
		LTM_HD <= 1'b0;
		LTM_VD <= 1'b1;
	end else if (~Enable) begin
		LTM_NCLK <= 1'b1;
		LTM_R <= 8'h00;
		LTM_G <= 8'h00;
		LTM_B <= 8'h00;
		LTM_DEN <= 1'b0;
		LTM_HD <= 1'b0;
		LTM_VD <= 1'b1;
	end else begin
		LTM_NCLK <= oClock_en;
		if (oClock_en) begin
			if (V_den && H_den) begin
				LTM_DEN <= 1'b1;
				if (
					(oCoord_X == 'd0) || (oCoord_X == 'd799) || 
					(oCoord_Y == 'd0) || (oCoord_Y == 'd479)
				) begin
					LTM_R <= 8'hFF;
					LTM_G <= 8'hFF;
					LTM_B <= 8'hFF;
				end else begin
					LTM_R <= iRed;
					LTM_G <= iGreen;
					LTM_B <= iBlue;
				end			
			end else begin
				LTM_R <= 8'h00;
				LTM_G <= 8'h00;
				LTM_B <= 8'h00;
				LTM_DEN <= 1'b0;
			end
			LTM_HD <= H_Sync;
			LTM_VD <= V_Sync;
		end
	end
end

endmodule
