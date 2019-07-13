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

logic start_seq, seq_flag;
logic finish, finish_buf;

logic [15:0] start_seq_pos;
logic [15:0] length;

logic [8:0] addr_1, addr_2;
logic [15:0] write_data_a, write_data_b;
logic [15:0] wren_1, wren_2;
logic [15:0] read_data_a, read_data_b;


always_ff @ (posedge clock or negedge resetn) begin
 if (!resetn) begin
		start_seq <= 'd0;
		seq_flag <= 'd0;
		write_data_a <= 'd1;
		wren_1 <= 1'b1;
		addr_1 <= 'd0;
		
	end else begin
	//	if(finish & ~finish_buf) counter_expire_irq <= 1'd1;
		if (chipselect & write) begin
			case (address)
			'd1: begin
				if (writedata[25])begin
					write_data_a <= writedata[15:0];
					wren_1 <= 1'b1;
					addr_1 <= writedata[24:16];
				
				end else begin
				//if (writedata[24:16])begin
					wren_1 <= 1'b0;
					addr_1 <= writedata[24:16];
				 end
			  end
			     'd3: begin
			      //wren_1 <= 1'b1;
				   start_seq <= writedata[31];
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
			'd2: readdata <= {start_seq_pos, length}; 
			
			endcase
		end
		
	end
end



/*
always_ff @ (posedge clock or negedge resetn) begin
	if (!resetn) begin
		finish_buf <= 1'b0;
		finish <= finish_buf;
	end else begin
		if(finish & ~finish_buf)
		counter_expire_irq <= 1'd10;
		else if(chipselect & write & address == 'd3) 
		counter_expire_irq <= 1'd0;
	end
end

*/

always_ff @ (posedge clock or negedge resetn) begin
	if (!resetn) begin
		finish_buf <= 1'b0;
	end else begin
		finish_buf <= finish;
		if(finish & ~finish_buf) 
		   counter_expire_irq <= 1'd1;
		if(chipselect & write & address == 'd3)
		   counter_expire_irq <= 1'd0;
			
	end
end


custom_counter_unit custom_counter_unit_inst (
	.clock(clock),
	.resetn(resetn),
	.start(start_seq),
	.read_data(read_data_b),
	.write_enable(wren_2),
	.address(addr_2),
	.start_seq_pos(start_seq_pos),
	.length(length),
	.finish(finish)
);

array dual_port_ram_unit_inst (
	.address_a(addr_1),
	.address_b(addr_2),
	.clock(clock),
	.data_a(write_data_a),
	.data_b(write_data_b),
	.wren_a(wren_1),
	.wren_b(wren_2),
	.q_a(read_data_a),
	.q_b(read_data_b)
);

endmodule

