// Copyright by Adam Kinsman, Henry Ko and Nicola Nicolici
// Developed for the Embedded Systems course (COE4DS4)
// Department of Electrical and Computer Engineering
// McMaster University
// Ontario, Canada

`timescale 1ns/100ps
`default_nettype none

// This module instantiates the 7 segment display
// converters for all 8 the displays on the board
module seven_seg_displays (
	input logic[4:0] hex_values[7:0],
	output logic[6:0] SEVEN_SEGMENT_N_O[7:0]
);

logic [6:0] converted_values[7:0];

convert_hex_to_seven_segment seg0 (
	.hex_value(hex_values[0][3:0]),
	.converted_value(converted_values[0])
);
assign SEVEN_SEGMENT_N_O[0] = (hex_values[0][4]) ? 
	converted_values[0] : 7'b1111111;

convert_hex_to_seven_segment seg1 (
	.hex_value(hex_values[1][3:0]),
	.converted_value(converted_values[1])
);
assign SEVEN_SEGMENT_N_O[1] = (hex_values[1][4]) ? 
	converted_values[1] : 7'b1111111;

convert_hex_to_seven_segment seg2 (
	.hex_value(hex_values[2][3:0]),
	.converted_value(converted_values[2])
);
assign SEVEN_SEGMENT_N_O[2] = (hex_values[2][4]) ? 
	converted_values[2] : 7'b1111111;

convert_hex_to_seven_segment seg3 (
	.hex_value(hex_values[3][3:0]),
	.converted_value(converted_values[3])
);
assign SEVEN_SEGMENT_N_O[3] = (hex_values[3][4]) ? 
	converted_values[3] : 7'b1111111;

convert_hex_to_seven_segment seg4 (
	.hex_value(hex_values[4][3:0]),
	.converted_value(converted_values[4])
);
assign SEVEN_SEGMENT_N_O[4] = (hex_values[4][4]) ? 
	converted_values[4] : 7'b1111111;

convert_hex_to_seven_segment seg5 (
	.hex_value(hex_values[5][3:0]),
	.converted_value(converted_values[5])
);
assign SEVEN_SEGMENT_N_O[5] = (hex_values[5][4]) ? 
	converted_values[5] : 7'b1111111;

convert_hex_to_seven_segment seg6 (
	.hex_value(hex_values[6][3:0]),
	.converted_value(converted_values[6])
);
assign SEVEN_SEGMENT_N_O[6] = (hex_values[6][4]) ? 
	converted_values[6] : 7'b1111111;

convert_hex_to_seven_segment seg7 (
	.hex_value(hex_values[7][3:0]),
	.converted_value(converted_values[7])
);
assign SEVEN_SEGMENT_N_O[7] = (hex_values[7][4]) ? 
	converted_values[7] : 7'b1111111;

endmodule
