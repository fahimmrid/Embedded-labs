// Copyright by Adam Kinsman, Henry Ko and Nicola Nicolici
// Developed for the Embedded Systems course (COE4DS4)
// Department of Electrical and Computer Engineering
// McMaster University
// Ontario, Canada

// synthesis translate_off
`timescale 1ns / 1ps
// synthesis translate_on

module custom_dec_component (
	input logic clock,
	input logic resetn,

	input  logic [2:0] 	address,
	input  logic 		chipselect,
	input  logic 		read,
	input  logic 		write,
	output logic [31:0]	readdata,
	input  logic [31:0]	writedata,
	
	output logic dec_irq
);

logic start, done;
logic start_buf, done_buf;
logic [25:0] counter_value;
logic [1:0] load_config;
logic counter_expire_buf, counter_expire;

logic [9:0]NIOS_address_A;
logic [9:0]dec_address_B;
logic [9:0]seq_address;
logic [10:0]seq_length;
logic [15:0]NIOS_data_a;
//logic [15:0]write_data_b;
logic NIOS_wren_a;
//logic write_enable_b;
logic [15:0]NIOS_read_a;
logic [15:0]dec_read_b;


// for getting the configuration from NIOS
always_ff @ (posedge clock or negedge resetn) begin
	if (!resetn) begin
		start<=1'b0;
		start_buf<=1'b0;
		NIOS_data_a<=16'b0;
		NIOS_address_A<=10'b0;
		NIOS_wren_a<=1'b0;
	end else begin
		start<=1'b0;
		NIOS_wren_a<=1'b0;
		if (chipselect & write) begin
			case (address)
		   'd1:begin
				NIOS_wren_a<=~writedata[26];
				NIOS_address_A<=writedata[25:16];
				NIOS_data_a<=writedata[15:0];
			end
			'd4:begin
				if(writedata[0]&&~start_buf)begin
					start <= 1'b1;
				end
				start_buf<=writedata[0];		
			end
			endcase
		end
	end
end

// for sending information to NIOS
always_ff @ (posedge clock or negedge resetn) begin
	if (!resetn) begin

	end else begin
		if (chipselect & read) begin
			case (address)
			'd0: readdata <= {16'd0,NIOS_read_a};
			'd2: readdata <= {22'd0,seq_address};
			'd3: readdata <= {21'd0,seq_length};
			endcase
		end
	end
end

always_ff @ (posedge clock or negedge resetn) begin
	if (!resetn) begin
		done_buf <= 1'b0;
	end else begin
		done_buf <= done;
			
		if (done & ~done_buf) dec_irq <= 1'b1;
		if (chipselect & write & address == 'd5) dec_irq <= 1'b0;
	end
end



custom_dec_unit custom_dec_unit_inst (
	.clock(clock),
	.resetn(resetn),
	.start(start),
	.array(dec_read_b),
	.array_address(dec_address_B),
	.seq_address(seq_address),
	.length(seq_length),
	
	.done(done)
);

Array Array_inst(
	.address_a (NIOS_address_A),
	.address_b (dec_address_B),
	.clock (clock),
	.data_a (NIOS_data_a),
	.data_b (16'hffff),
	.wren_a (NIOS_wren_a),
	.wren_b (1'b0),
	.q_a (NIOS_read_a),
	.q_b (dec_read_b)
);

endmodule
