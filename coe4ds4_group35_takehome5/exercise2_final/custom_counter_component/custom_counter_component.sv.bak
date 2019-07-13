// Copyright by Adam Kinsman, Henry Ko and Nicola Nicolici
// Developed for the Embedded Systems course (COE4DS4)
// Department of Electrical and Computer Engineering
// McMaster University
// Ontario, Canada

// synthesis translate_off
`timescale 1ns / 1ps
// synthesis translate_on

module custom_counter_component (
	input logic clock,
	input logic resetn,

	input  logic [1:0] 	address,
	input  logic 		chipselect,
	input  logic 		read,
	input  logic 		write,
	output logic [31:0]	readdata,
	input  logic [31:0]	writedata,
	
	output logic counter_expire_irq
);

logic reset_counter, load;
logic [25:0] counter_value;
logic [1:0] load_config;
logic counter_expire_buf, counter_expire;

// for getting the configuration from NIOS
always_ff @ (posedge clock or negedge resetn) begin
	if (!resetn) begin
		reset_counter <= 'd0;
		load <= 1'b0;
		load_config <= 'd0;
	end else begin
		load <= 1'b0;
		if (chipselect & write) begin
			case (address)
			'd1: reset_counter <= writedata[0];
			'd3: begin
				load <= 1'b1;
				load_config <= writedata[1:0];
			end
			endcase
		end
	end
end

// for sending information to NIOS
always_ff @ (posedge clock or negedge resetn) begin
	if (!resetn) begin
		readdata <= 'd0;
	end else begin
		if (chipselect & read) begin
			case (address)
			'd0: readdata <= {6'd0, counter_value};
			'd1: readdata <= {31'd0, reset_counter};
			'd2: readdata <= {31'd0, counter_expire};
			'd3: readdata <= {31'd0, load_config};
			endcase
		end
	end
end

always_ff @ (posedge clock or negedge resetn) begin
	if (!resetn) begin
		counter_expire_buf <= 1'b0;
	end else begin
		counter_expire_buf <= counter_expire;
			
		if (counter_expire & ~counter_expire_buf) counter_expire_irq <= 1'b1;
		if (chipselect & write & address == 'd2) counter_expire_irq <= 1'b0;
	end
end

custom_counter_unit custom_counter_unit_inst (
	.clock(clock),
	.resetn(resetn),
	.reset_counter(reset_counter),
	.load(load),
	.load_config(load_config),
	.counter_value(counter_value),
	
	.counter_expire(counter_expire)
);

endmodule

