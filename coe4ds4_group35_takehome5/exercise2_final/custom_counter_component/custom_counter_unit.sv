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
	output logic finish
);

logic [4:0]dummy_state;
logic [15:0]array_min, array_max;
logic [2:0]swap;

logic [9:0] i, j;
logic [3:0] software_state;
logic [15:0] seq_one, seq_two;

always_ff @ (posedge clock or negedge resetn) begin
	if (~resetn) begin
	   write_enable <= 'd0;
		address <= 'd0;
		dummy_state <= 'd0;
		swap <= 'd0;
		array_min <= 'd0;
		array_max <= 'd0;
		finish <= 1'b0;
		i <= 10'd0;
		j <= 10'd0;
		software_state <= 4'd0;
		length <= 'd0;
		start_pos <= 'd0;
		seq_one <= 'd0;
		seq_two <= 'd0;
		
	end else begin
		if (start) begin
		//fsm for max seq fun - state 0 to 9 ----
			if (software_state == 'd0)begin //memory 
			 if (i >0) begin
			   software_state <= 'd9;
			 
			 end else begin 
			   address <= i;
				write_enable <= 1'd0;
				software_state <= software_state + 'd1;
			
			end
				
		end else if(software_state == 'd1)begin
			//account for the 1cc delay
		  software_state <= software_state + 'd1; 
			
			
			//memory read here
		end else if(software_state == 'd2)begin 
		
			software_state <= software_state + 'd1;
			array_min <= read_data;
			array_max <= read_data;
			
			
		end else if(software_state == 'd3)begin 
		
			j <= i + 'd1;
			software_state <= software_state + 'd1;
			
			//now j 
		end else if (software_state == 'd4)begin 
		
			if (j > 'd0)begin
			   i <= i + 'd1;
			   software_state <= 'd0;
			end else begin 
		  	   address <= j;
			   software_state <= software_state + 'd1;
				
			end
			
			end else if (software_state == 'd5)begin
				software_state <= software_state + 'd1; 
			
			end else if (software_state == 'd6)begin // the longest and earliest!
				if (read_data < array_min)begin 
					array_min <= read_data;
				
				end else if (read_data > array_max)begin
					array_max <= read_data;
					
				end
				software_state <= software_state + 'd1;
			
			end else if (software_state == 'd7)begin 
			
				if (((j-i) > (seq_two-seq_one)) && ((array_max - array_min) == (j-i)) )begin
				//if (((array_max - array_min) == (j-i)) || ((j-i) > (seq_two-seq_one)))begin
					seq_one <= {6'd0, i};
					seq_two <= {6'd0, j};
				 end
			 j <= j +'d1;
			 software_state <= 'd4;
							
			end else if(software_state == 'd9)begin
				finish <= 'd1;
				start_pos <= seq_one;
				length <= seq_two - seq_one + 'd1;
				software_state <= software_state + 'd1;
			
			
			end else if (software_state == 'd10)begin//noneed
			end
	
	end else begin //re init for another run
		      write_enable <= 'd0;
				address <= 'd0;
				array_min <= 'd0;
				array_max <= 'd0;
				finish <= 1'b0;
				swap <= 'd0;
				i <= 'd0;
				j <= 'd0;
				software_state <= 'd0;
				seq_one <= 'd0;
				seq_two <= 'd0;
				
		end
	end
end

endmodule
