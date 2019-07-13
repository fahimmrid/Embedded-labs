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

// Dua port ram a-write b-read
logic [8:0] address_a;
logic [8:0] address_b;
logic [15:0] write_data_a;
logic [15:0] write_data_b;
logic [15:0] write_enable_a;
logic [15:0] write_enable_b;
logic [15:0] read_data_a;
logic [15:0] read_data_b;

logic [15:0] start_pos;
logic [15:0] length;
logic start;
logic reset_irq;
logic done_search;
logic done_search_buf;

// for getting the configuration from NIOS
always_ff @ (posedge clock or negedge resetn) begin
	if (!resetn) begin
		write_data_a <= 'd1;
		write_enable_a <= 1'b1;
		address_a <= 'd0;
		start <= 'd0;
		reset_irq <= 'd0;
	end else begin
		if (chipselect & write) begin
			case (address)
			'd1: begin
				if (writedata[25])begin
					write_enable_a <= 1'b1;
					address_a <= writedata[24:16];
					write_data_a <= writedata[15:0];
				end
				else begin
					write_enable_a <= 1'b0;
					address_a <= writedata[24:16];
				end
				end
			'd3: begin
				start <= writedata[31];
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
			'd0: readdata <= {16'd0, read_data_a};
			'd2: readdata <= {start_pos, length}; // subsequence
			endcase
		end
	end
end

always_ff @ (posedge clock or negedge resetn) begin
	if (!resetn) begin
		done_search_buf <= 1'b0;
	end else begin
		done_search_buf <= done_search;
		if(done_search & ~done_search_buf) counter_expire_irq <= 1'd1;
		if(chipselect & write & address == 'd3) counter_expire_irq <= 1'd0;
	end
end

custom_counter_unit custom_counter_unit_inst (
	.clock(clock),
	.resetn(resetn),
	.start(start),
	.read_data(read_data_b),
	.write_enable(write_enable_b),
	.address(address_b),
	.start_pos(start_pos),
	.length(length),
	.done_search(done_search)
);

dual_port_ram_unit dual_port_ram_unit_inst (
	.address_a(address_a),
	.address_b(address_b),
	.clock(clock),
	.data_a(write_data_a),
	.data_b(write_data_b),
	.wren_a(write_enable_a),
	.wren_b(write_enable_b),
	.q_a(read_data_a),
	.q_b(read_data_b)
);

endmodule

