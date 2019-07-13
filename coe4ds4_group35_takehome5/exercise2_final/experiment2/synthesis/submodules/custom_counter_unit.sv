// Copyright by Adam Kinsman, Henry Ko and Nicola Nicolici
// Developed for the Embedded Systems course (COE4DS4)
// Department of Electrical and Computer Engineering
// McMaster University
// Ontario, Canada

// synthesis translate_off
`timescale 1ns / 1ps
// synthesis translate_on

module custom_counter_unit (
	input logic clock,
	input logic resetn,
	input logic start,
	input logic [15:0] read_data,
	
	output logic write_enable,
	output logic [8:0] address,
	
	output logic [15:0] start_pos,
	output logic [15:0] length,
	output logic done_search
);

logic [1:0] load_config_buf;
logic [15:0] min;
logic [15:0] max;
logic [9:0] i;
logic [9:0] j;
logic [3:0] state_flag;
logic [15:0] s_i;
logic [15:0] s_j;
always_ff @ (posedge clock or negedge resetn) begin
	if (!resetn) begin
		done_search <= 1'b0;
		i <= 'd0;
		j <= 'd0;
		state_flag <= 'd0;
		length <= 'd0;
		start_pos <= 'd0;
		s_i <= 'd0;
		s_j <= 'd0;
		write_enable <= 'd0;
		address <= 'd0;
		min <= 'd0;
		max <= 'd0;
	end else begin
		if (start) begin
			if (state_flag == 'd0)begin //load stage
				if (i < 'd512)begin// load mem[i]
					write_enable <= 1'd0;
					address <= i;
					state_flag <= state_flag + 'd1;
				end
				else begin
					state_flag <= 'd9; // go to end
				end
			end
			else if(state_flag == 'd1)begin
				state_flag <= state_flag + 'd1; //dummy cycle to load from mem
			end
			else if(state_flag == 'd2)begin //read mem
				min <= read_data;
				max <= read_data;
				state_flag <= state_flag + 'd1;
			end
			else if(state_flag == 'd3)begin // j loop initial state
					j <= i + 'd1;
					state_flag <= state_flag + 'd1;
			end
			else if (state_flag == 'd4)begin //load data_array[j]
				if (j < 'd512)begin
					address <= j;
					state_flag <= state_flag + 'd1;
				end
				else begin // end j loop
					i <= i + 'd1;
					state_flag <= 'd0;
				end
			end
			else if (state_flag == 'd5)begin
				state_flag <= state_flag + 'd1; //dummy cycle to load from mem
			end
			else if (state_flag == 'd6)begin // update max/min
				if (read_data < min)begin 
					min <= read_data;
				end
				else if (read_data > max)begin
					max <= read_data;
				end
				state_flag <= state_flag + 'd1;
			end
			else if (state_flag == 'd7)begin 
				if (((max - min) == (j-i)) && ((j-i) > (s_j-s_i)))begin
					s_i <= {6'd0, i};
					s_j <= {6'd0, j};
				end
				j <= j +'d1;
				state_flag <= 'd4;
			end
			else if(state_flag == 'd9)begin
				done_search <= 'd1;
				start_pos <= s_i;
				length <= s_j - s_i + 'd1;
				state_flag <= state_flag + 'd1;
			end
			else if (state_flag == 'd10)begin
			end
		end
		else begin //re init for another run
			done_search <= 1'b0;
			i <= 'd0;
			j <= 'd0;
			state_flag <= 'd0;
			s_i <= 'd0;
			s_j <= 'd0;
			write_enable <= 'd0;
			address <= 'd0;
			min <= 'd0;
			max <= 'd0;
		end
	end
end

endmodule
