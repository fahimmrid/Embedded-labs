// Copyright by Adam Kinsman, Henry Ko and Nicola Nicolici
// Developed for the Embedded Systems course (COE4DS4)
// Department of Electrical and Computer Engineering
// McMaster University
// Ontario, Canada

`timescale 1ns/100ps
`default_nettype none

// This module interfaces to the LCD touch panel through SPI
module Touch_Panel_Controller (
	input  logic Clock_50MHz,
	input  logic Resetn,

	input  logic Enable,	
	
	output logic Touch_En,
	output logic Coord_En,
	output logic [11:0] X_Coord,
	output logic [11:0] Y_Coord,

	input  logic TP_PENIRQ_N_I,
	input  logic TP_BUSY_I,
	output logic TP_SCLK_O,
	output logic TP_MOSI_O,
	input  logic TP_MISO_I,
	output logic TP_SS_N_O
);

typedef enum logic [3:0] {
	S_TP_IDLE,
	S_TP_ENABLE,
	S_TP_SYNC_1K,
	S_TP_SEND_X,
	S_TP_RECV_X,
	S_TP_ZF_X,
	S_TP_SEND_Y,
	S_TP_RECV_Y,
	S_TP_ZF_Y,
	S_TP_BACKOFF,
	S_TP_DEBOUNCE
} TP_state_type;

TP_state_type TP_state;

logic 			Done;
logic 			En_SPI_Clock;
logic [11:0]	SPI_Clock_counter;
logic 			TP_penirq, TP_penirq0, TP_penirq1;
logic [7:0] 	TP_penirq_db;
logic [3:0]		TP_debounce_counter;
logic [3:0] 	TP_data_count;
logic [11:0] 	TP_data_reg;
logic [4:0] 	TP_busy_timeout;
logic [1:0] 	Enable_reg;

assign TP_MOSI_O = 
	((TP_state == S_TP_SEND_X) || (TP_state == S_TP_SEND_Y)) ? 
		TP_data_reg[11] : 1'b0;

always_ff @(posedge Clock_50MHz or negedge Resetn) begin
	if (~Resetn) begin
		TP_penirq <= 1'b0;
		TP_penirq0 <= 1'b0;
		TP_penirq1 <= 1'b0;
		TP_penirq_db <= 8'd0;
	end else begin
		TP_penirq_db <= 
			{TP_penirq_db[6:0] , ~TP_PENIRQ_N_I};
		TP_penirq0 <= &TP_penirq_db;
		TP_penirq1 <= |TP_penirq_db;
		TP_penirq <= (Touch_En) ? TP_penirq1 : TP_penirq0;
	end
end

// Generate Enable for SPI Clock (half period = clock in / 4096)
always_ff @(posedge Clock_50MHz or negedge Resetn) begin
	if (~Resetn) begin
		SPI_Clock_counter <= 12'h000;
		En_SPI_Clock <= 1'b0;
	end else begin
		if (SPI_Clock_counter == 12'd511) begin
			En_SPI_Clock <= 1'b1;
			SPI_Clock_counter <= 12'd0;
		end else begin
			En_SPI_Clock <= 1'b0;
			SPI_Clock_counter <= SPI_Clock_counter + 12'd1;
		end
	end
end

// Main state machine
always_ff @(posedge Clock_50MHz or negedge Resetn) begin
	if (~Resetn) begin
		Done <= 1'b1;
		TP_SS_N_O <= 1'b1;
		TP_SCLK_O <= 1'b0;
		TP_data_count <= 4'h0;
		TP_data_reg <= 12'h000;
		TP_state <= S_TP_IDLE;	
		Coord_En <= 1'b0;
		X_Coord <= 12'h000;	
		Y_Coord <= 12'h000;	
		TP_busy_timeout <= 5'd0;
		Touch_En <= 1'b0;
		Enable_reg <= 2'b00;
	end else begin	
		Enable_reg <= {Enable_reg[0], Enable};
		if (TP_state == S_TP_IDLE) begin
			TP_SCLK_O <= 1'b0;
			Coord_En <= 1'b0;
			Done <= 1'b1;
			if (TP_penirq) begin 
				Touch_En <= 1'b1;
				TP_state <= S_TP_ENABLE;
				Done <= 1'b0;
			end
		end else if (TP_state == S_TP_ENABLE) begin
			if (Enable_reg == 2'b01) TP_state <= S_TP_SYNC_1K;
		end else if (En_SPI_Clock) begin
			case (TP_state)
				S_TP_SYNC_1K : begin
					TP_state <= S_TP_SEND_X;
					TP_SS_N_O <= 1'b0;
					TP_data_count <= 4'h0;
					TP_data_reg <= 12'h920; // X data
				end
			
				// X coordinate
				S_TP_SEND_X : begin
					TP_SCLK_O <= ~TP_SCLK_O;
					if (TP_SCLK_O == 1'b1) begin // negative edge
						TP_data_reg <= { TP_data_reg[10:0], TP_MISO_I };
						if (TP_data_count == 4'h7) begin
							TP_data_count <= 4'h0;
							TP_state <= S_TP_RECV_X;
							TP_busy_timeout <= 5'd0;
						end else TP_data_count <= TP_data_count + 4'd1;
					end
				end
				S_TP_RECV_X : begin
					TP_SCLK_O <= ~TP_SCLK_O;
					if (TP_BUSY_I) begin
						if (TP_busy_timeout == 5'd31) TP_state <= S_TP_IDLE;
						else TP_busy_timeout <= TP_busy_timeout + 5'd1;
					end else if (TP_SCLK_O == 1'b0) begin // positive edge
						TP_data_reg <= { TP_data_reg[10:0], TP_MISO_I };
						TP_busy_timeout <= 5'd0;
						if (TP_data_count == 4'hB) begin
							TP_data_count <= 4'h0;
							TP_state <= S_TP_ZF_X;
						end else TP_data_count <= TP_data_count + 4'd1;					
					end
				end
				S_TP_ZF_X : begin
					TP_SCLK_O <= ~TP_SCLK_O;
					if (TP_SCLK_O == 1'b0) begin // positive edge
						if (TP_data_count == 4'h3) begin
							// use Y here for rows
							// negation swaps top for bottom
							Y_Coord <= ~TP_data_reg; 
							TP_data_reg <= 12'h000;
						end
					end
					if (TP_SCLK_O == 1'b1) begin // negative edge
						if (TP_data_count == 4'hF) begin
							TP_data_count <= 4'h0;
							TP_data_reg <= 12'hD20; // Y data
							TP_state <= S_TP_SEND_Y;
						end else TP_data_count <= TP_data_count + 4'd1;
					end
				end
			
				// Y coordinate
				S_TP_SEND_Y : begin
					TP_SCLK_O <= ~TP_SCLK_O;
					if (TP_SCLK_O == 1'b1) begin // negative edge
						TP_data_reg <= { TP_data_reg[10:0], TP_MISO_I };
						if (TP_data_count == 4'h7) begin
							TP_data_count <= 4'h0;
							TP_state <= S_TP_RECV_Y;
							TP_busy_timeout <= 5'd0;
						end else TP_data_count <= TP_data_count + 4'd1;
					end
				end
				S_TP_RECV_Y : begin
					TP_SCLK_O <= ~TP_SCLK_O;
					if (TP_BUSY_I) begin
						if (TP_busy_timeout == 5'd31) TP_state <= S_TP_IDLE;
						else TP_busy_timeout <= TP_busy_timeout + 5'd1;						
					end else if (TP_SCLK_O == 1'b0) begin // positive edge
						TP_data_reg <= { TP_data_reg[10:0], TP_MISO_I };
						TP_busy_timeout <= 5'd0;
						if (TP_data_count == 4'hB) begin
							TP_data_count <= 4'h0;
							TP_state <= S_TP_ZF_Y;
						end else TP_data_count <= TP_data_count + 4'd1;
					end
				end
				S_TP_ZF_Y : begin
					TP_SCLK_O <= ~TP_SCLK_O;
					if (TP_SCLK_O == 1'b0) begin // positive edge
						if (TP_data_count == 4'h3) begin
							// use X here for columns
							X_Coord <= TP_data_reg; 
							TP_data_reg <= 12'h000;
						end
					end
					if (TP_SCLK_O == 1'b1) begin // negative edge
						if (TP_data_count == 4'hF) begin
							TP_SS_N_O <= 1'b1;
							TP_data_count <= 4'h0;
							TP_data_reg <= 12'h000; 
							TP_state <= S_TP_BACKOFF;
							if (TP_penirq) Coord_En <= 1'b1;
						end else TP_data_count <= TP_data_count + 4'd1;
					end
				end
				S_TP_BACKOFF : begin
					if (TP_data_reg == 12'h1FF) begin
						TP_data_reg <= 12'h000; 
						TP_state <= S_TP_IDLE;
					end else if (TP_penirq == 1'b0) begin
						TP_data_reg <= 12'h000; 
						TP_state <= S_TP_DEBOUNCE;
					end else TP_data_reg <= TP_data_reg + 12'd1;
				end
				S_TP_DEBOUNCE : begin
					if (TP_data_reg == 12'd63) begin
						Touch_En <= TP_penirq;
						TP_data_reg <= 12'h000; 
						TP_state <= S_TP_IDLE;
					end else begin
						TP_data_reg <= TP_data_reg + 12'd1;
						if (TP_penirq) TP_state <= S_TP_IDLE;
					end
				end
			endcase
		end
	end
end

endmodule
