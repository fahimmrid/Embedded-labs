// Copyright by Adam Kinsman, Henry Ko and Nicola Nicolici
// Developed for the Embedded Systems course (COE4DS4)
// Department of Electrical and Computer Engineering
// McMaster University
// Ontario, Canada

// synthesis translate_off
`timescale 1ns / 1ps
// synthesis translate_on

module custom_dec_unit (
	input logic clock,
	input logic resetn,
	
	input logic start,
	input logic [15:0] array,
	output logic [9:0] array_address,
	output logic [9:0] seq_address,
	output logic [10:0] length,
	
	output logic done
);

enum logic[2:0] {state1,state2,state3,state4,state5,state6,state7} cur_state;
logic [15:0] arrayOld;
logic [9:0] currentLength;
logic [10:0] tempAddress;


always_ff @ (posedge clock or negedge resetn) begin
	if (!resetn) begin
		cur_state <= state1;
		seq_address <= 10'b0;
		length <= 11'b0;
		arrayOld<=16'b0;
		done<=1'b0;
		tempAddress<= 11'b0;
	end else begin
		case(cur_state)
			state1:begin
				array_address<=10'd0;
				done<=1'b0;
				tempAddress<= 11'b0;
				if(start)begin
				
					cur_state<=state2;
					seq_address <= 10'b0;
					length <= 11'b0;
					currentLength <=10'b0;
					arrayOld<=array;
				
				end
			end
			state2:			
				cur_state<=state3;			
			state3:begin
			
				arrayOld<=array;
				array_address<=array_address+1'b1;
				
				if($signed(array)<$signed(arrayOld))begin
					currentLength <= currentLength + 1'b1;
				end else begin
					if(((currentLength+1'b1)>=length))begin				
						
						length <= currentLength+1'b1;
						tempAddress <= array_address;
						
					end
					currentLength <= 0;
					
				end
				
				if(array_address==10'd1023)begin
					
					cur_state<=state4;
				end
			end
			state4:begin
				arrayOld<=array;
				if($signed(array)<$signed(arrayOld))begin
					currentLength <= currentLength + 1'b1;
				end else begin
					if(((currentLength+1'b1)>=length))begin				
						
						length <= currentLength+1'b1;
						
					end
					currentLength <= 0;
					
				end
				//seq_address <= tempAddress - length - 10'd2;
				cur_state<=state5;
			end
			state5:begin
				arrayOld<=array;
				if($signed(array)<$signed(arrayOld))begin
					currentLength <= currentLength + 1'b1;
				end else begin
					if(((currentLength+1'b1)>=length))begin				
						
						length <= currentLength+1'b1;
						tempAddress <= array_address+2'd1;
						
					end
					currentLength <= 0;
					
				end
				cur_state<=state6;
			end
			state6:begin
				arrayOld<=array;
				if($signed(array)<$signed(arrayOld))begin
					currentLength <= currentLength + 1'b1;
				end else begin
					if(((currentLength+1'b1)>=length))begin				
						
						length <= currentLength+1'b1;
						tempAddress <= array_address+2'd2;
						
					end
					currentLength <= 0;
					
				end
				cur_state<=state7;
			end
			state7:begin
				if(length!=11'd0)begin
					seq_address <= tempAddress - length - 10'd2;
				end else begin
					seq_address <= 10'd0;
				end
				cur_state<=state1;
				done<=1'b1;
			end
		endcase	
	end
end

endmodule