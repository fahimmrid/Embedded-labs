// Copyright by Adam Kinsman, Henry Ko and Nicola Nicolici
// Developed for the Embedded Systems course (COE4DS4)
// Department of Electrical and Computer Engineering
// McMaster University
// Ontario, Canada

`timescale 1ns/100ps
`default_nettype none

// This module creates the console for
// the LCD with button areas / text
module LCD_Console_Generation (
	input logic Clock,
	input logic Clock_en,
	input logic Resetn,
	
	input logic [5:0] Button_Invert,

	input logic [7:0] Image_Red,
	input logic [7:0] Image_Green,
	input logic [7:0] Image_Blue,

	input logic [10:0] H_Count,
	input logic [9:0] V_Count,

	output logic [7:0] Console_Red,
	output logic [7:0] Console_Green,
	output logic [7:0] Console_Blue,
	
	input logic [9:0] CharMap_address,
	input logic [15:0] CharMap_data,
	input logic CharMap_wren,
	output logic [15:0] CharMap_q,
	
	input logic [7:0] Label_address,
	input logic [7:0] Label_data,
	input logic Label_wren,
	output logic [7:0] Label_q	
);

logic [10:0] LCD_Coord_X_long;
logic [9:0] LCD_Coord_X, LCD_Coord_Y;
logic [7:0] Touch_key_red, Touch_key_green, Touch_key_blue;
logic [7:0] Console_frame_red, Console_frame_green, Console_frame_blue;

assign LCD_Coord_X_long = H_Count - 11'd216;
assign LCD_Coord_X = LCD_Coord_X_long[9:0];
assign LCD_Coord_Y = V_Count - 10'd35;

logic LCD_Character_Pixel;

assign Console_Red   = (Image_X) ? Image_Red   : Console_frame_red;
assign Console_Green = (Image_X) ? Image_Green : Console_frame_green;
assign Console_Blue  = (Image_X) ? Image_Blue  : Console_frame_blue; 

always_ff @(posedge Clock or negedge Resetn) begin
	if (~Resetn) begin
		Console_frame_red <= 8'h00;
		Console_frame_green <= 8'h00;
		Console_frame_blue <= 8'h00;
	end else if (Clock_en) begin
		Console_frame_red   <= (|Button_Y & Button_X) ? 
			{8{LCD_Character_Pixel ^ |(Button_Y & Button_Invert) }} : Touch_key_red;
		Console_frame_green <= (|Button_Y & Button_X) ? 
			{8{LCD_Character_Pixel ^ |(Button_Y & Button_Invert) }} : Touch_key_green;
		Console_frame_blue  <= (|Button_Y & Button_X) ? 
			{8{LCD_Character_Pixel ^ |(Button_Y & Button_Invert) }} : Touch_key_blue;
	end
end

logic Button_X, Image_X;
logic [5:0] Button_Y;

always_ff @(posedge Clock or negedge Resetn) begin
	if (~Resetn) begin
		Image_X <= 1'b1;
		Button_X <= 1'b0;
		Button_Y <= 6'd0; 
	end else if (Clock_en) begin
		if (LCD_Coord_X == (10'd799 - 10'd1)) Image_X <= 1'b1;
		if (LCD_Coord_X == (10'd639 - 10'd1)) Image_X <= 1'b0;
		
		if (LCD_Coord_X == (10'd655 - 10'd1)) Button_X <= 1'b1;
		if (LCD_Coord_X == (10'd783 - 10'd1)) Button_X <= 1'b0;
		
		if (LCD_Coord_Y == 10'd16)  Button_Y[0] <= 1'b1;
		if (LCD_Coord_Y == 10'd96)  Button_Y[1] <= 1'b1;
		if (LCD_Coord_Y == 10'd176) Button_Y[2] <= 1'b1;
		if (LCD_Coord_Y == 10'd256) Button_Y[3] <= 1'b1;
		if (LCD_Coord_Y == 10'd336) Button_Y[4] <= 1'b1;
		if (LCD_Coord_Y == 10'd416) Button_Y[5] <= 1'b1;

		if (LCD_Coord_Y == 10'd64)  Button_Y[0] <= 1'b0;
		if (LCD_Coord_Y == 10'd144) Button_Y[1] <= 1'b0;
		if (LCD_Coord_Y == 10'd224) Button_Y[2] <= 1'b0;
		if (LCD_Coord_Y == 10'd304) Button_Y[3] <= 1'b0;
		if (LCD_Coord_Y == 10'd384) Button_Y[4] <= 1'b0;
		if (LCD_Coord_Y == 10'd464) Button_Y[5] <= 1'b0;
	end
end		
	
//assign Touch_key_red = 8'h00;
assign Touch_key_green = Touch_key_red;
assign Touch_key_blue = Touch_key_red;

logic Touch_key_V;
always_ff @(posedge Clock or negedge Resetn) begin
	if (~Resetn) begin
		Touch_key_V <= 1'b0;
		Touch_key_red <= 8'h00;
	end else if (Clock_en) begin
		if (
			(LCD_Coord_Y == 10'd10) |
			(LCD_Coord_Y == 10'd90) |
			(LCD_Coord_Y == 10'd170) |
			(LCD_Coord_Y == 10'd250) |
			(LCD_Coord_Y == 10'd330) |
			(LCD_Coord_Y == 10'd410)
		) begin
			if (LCD_Coord_X == (10'd649 - 10'd1)) 
				Touch_key_red <= 8'hFF;
			if (LCD_Coord_X == (10'd789 - 10'd1)) begin
				Touch_key_red <= 8'h00;
				Touch_key_V <= 1'b1;
			end
		end
		
		if (
			(LCD_Coord_Y == 10'd69) |
			(LCD_Coord_Y == 10'd149) |
			(LCD_Coord_Y == 10'd229) |
			(LCD_Coord_Y == 10'd309) |
			(LCD_Coord_Y == 10'd389) |
			(LCD_Coord_Y == 10'd469)
		) begin
			if (LCD_Coord_X == (10'd649 - 10'd1)) begin
				Touch_key_red <= 8'hFF;
				Touch_key_V <= 1'b0;
			end 
			if (LCD_Coord_X == (10'd789 - 10'd1)) Touch_key_red <= 8'h00;
		end
		
		if (Touch_key_V) begin
			if (
				(LCD_Coord_X == (10'd649 - 10'd1)) | 
				(LCD_Coord_X == (10'd788 - 10'd1))
			) Touch_key_red <= 8'hFF;
			else Touch_key_red <= 8'h00;
		end
	end
end

logic [10:0] character_column_pixel_long;
logic [9:0] character_row_pixel_long;

logic [6:0] character_column_pixel;
logic [8:0] character_row_pixel;

assign character_column_pixel_long = H_Count - 11'd874 + 11'd4;
assign character_column_pixel = character_column_pixel_long[6:0];

assign character_row_pixel_long = V_Count - (
	(V_Count < 10'd99) ? 10'd51 :
	(V_Count < 10'd179) ? 10'd83 :
	(V_Count < 10'd259) ? 10'd115 : 
	(V_Count < 10'd339) ? 10'd147 : 
	(V_Count < 10'd419) ? 10'd179 : 10'd211);
//	(V_Count < 10'd499) ? 10'd211 : 
assign character_row_pixel = character_row_pixel_long[8:0];

logic [7:0] LCD_Character_Address;
logic [7:0] LCD_Character_Code;

// address 0 - character for button 0, row 0, column 0
// address 7 - character for button 0, row 0, column 7
// address 8 - character for button 0, row 1, column 0
// address 24 - character for button 1, row 0, column 0
// address 143 - character for button 5, row 2, column 7
assign LCD_Character_Address = {
	character_row_pixel[8:4],
	character_column_pixel[6:4] };
 
//label_ram label_ram1 (
Button_Label_RAM Button_Labels (
	.address_a(LCD_Character_Address),
	.address_b(Label_address),
	.clock(Clock),
	.data_a(8'h00),
	.data_b(Label_data),
	.wren_a(1'b0),
	.wren_b(Label_wren),
	.q_a(LCD_Character_Code),
	.q_b(Label_q)
);

logic [3:0] character_row_pixel_reg1;
logic [3:0] character_column_pixel_reg1;
logic [3:0] character_column_pixel_reg2;

always_ff @(posedge Clock or negedge Resetn) begin
	if (~Resetn) begin
		character_row_pixel_reg1 <= 4'h0;
		character_column_pixel_reg1 <= 4'h0;
		character_column_pixel_reg2 <= 4'h0;
	end else begin //if (Clock_en) begin
		character_row_pixel_reg1 <= character_row_pixel[3:0];
		character_column_pixel_reg1 <= character_column_pixel[3:0];
		character_column_pixel_reg2 <= character_column_pixel_reg1;
	end
end

//logic LCD_Character_Pixel;
logic [9:0] LCD_Charmap_Address;
logic [15:0] LCD_Character_Row;

assign LCD_Charmap_Address = {
	LCD_Character_Code[5:0],
	character_row_pixel_reg1[3:0] };

Button_Character_Map Character_Map (
	.address_a(LCD_Charmap_Address),
	.address_b(CharMap_address),
	.clock(Clock),
	.data_a(16'h0000),
	.data_b(CharMap_data),
	.wren_a(1'b0),
	.wren_b(CharMap_wren),
	.q_a(LCD_Character_Row),
	.q_b(CharMap_q)
);

assign LCD_Character_Pixel = 
	LCD_Character_Row[~character_column_pixel_reg2];

endmodule

// Button layout			// Text
//							656 - 671, 672 - 687, 688 - 703, 704 - 719,
//	   650       789		720 - 735, 736 - 751, 752 - 767, 768 - 783 
//	10	-----------			
//		|         |			16 - 31, 32 - 47, 48 - 63
//	69	-----------
//	
//	90	-----------
//		|         |			96 - 111, 112 - 127, 128 - 143
//	149	-----------
//	
//	170	-----------
//		|         |			176 - 191, 192 - 207, 208 - 223
//	229	-----------
//	
//	250	-----------
//		|         |			256 - 271, 272 - 287, 288 - 303
//	309	-----------
//	
//	330	-----------
//		|         |			336 - 351, 352 - 367, 368 - 383 
//	389	-----------
//	
//	410	-----------
//		|         |			416 - 431, 432 - 447, 448 - 463
//	469	-----------
