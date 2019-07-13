// Copyright by Adam Kinsman, Henry Ko and Nicola Nicolici
// Developed for the Embedded Systems course (COE4DS4)
// Department of Electrical and Computer Engineering
// McMaster University
// Ontario, Canada

// synthesis translate_off
`timescale 1ns / 1ps
// synthesis translate_on

module PS2_controller_component (
	input logic clock,
	input logic resetn,

	input  logic 	 	address,
	input  logic 		chipselect,
	input  logic 		read,
	input  logic 		write,
	output logic [31:0]	readdata,
	input  logic [31:0]	writedata,
	
	input logic PS2_clock,
	input logic PS2_data,
	
	output logic PS2_code_ready_irq
);

logic [7:0] PS2_code;
logic PS2_code_ready, PS2_code_ready_buf;
logic PS2_make_code;

// for sending information to NIOS
always_ff @ (posedge clock or negedge resetn) begin
	if (!resetn) begin
		readdata <= 'd0;
	end else begin
		if (chipselect & read) begin
			case (address)
			'd0: readdata <= {23'd0, PS2_make_code, PS2_code};
			endcase
		end
	end
end

always_ff @ (posedge clock or negedge resetn) begin
	if (!resetn) begin
		PS2_code_ready_buf <= 1'b0;
		PS2_code_ready_irq <= 1'b0;
	end else begin
		PS2_code_ready_buf <= PS2_code_ready;
		
		if (PS2_code_ready & ~PS2_code_ready_buf) PS2_code_ready_irq <= 1'b1;
		if (chipselect & write & address == 'd0) PS2_code_ready_irq <= 1'b0;
	end
end

PS2_controller PS2_controller_inst (
	.Clock_50(clock),
	.Resetn(resetn),
	
	.PS2_clock(PS2_clock),
	.PS2_data(PS2_data),
	
	.PS2_code(PS2_code),
	.PS2_code_ready(PS2_code_ready),
	.PS2_make_code(PS2_make_code)
);

endmodule
