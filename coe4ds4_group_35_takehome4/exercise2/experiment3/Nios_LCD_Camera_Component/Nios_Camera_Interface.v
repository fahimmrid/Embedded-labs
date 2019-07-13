// Copyright by Adam Kinsman, Henry Ko and Nicola Nicolici
// Developed for the Embedded Systems course (COE4DS4)
// Department of Electrical and Computer Engineering
// McMaster University
// Ontario, Canada

`timescale 1ns/100ps
`default_nettype none

// This module interfaces to the camera slave
module Nios_Camera_Interface (
	input logic Clock,
	input logic Resetn,
	
	output logic Config_start,
	input logic Config_done,
	output logic [15:0] Config_Exposure,
	output logic Capture_start,
	output logic Capture_stop,
	input logic [31:0] Capture_Framecount,
	
	input logic [3:0] address,
	input logic chipselect,
	input logic read,
	input logic write,
	output logic [31:0] readdata,
	input logic [31:0] writedata	
);

// wa 0 - exposure
// wa 1,0 - config done
// wa 1,1 - config start
// wa 1,2 - capture start
// wa 1,3 - capture stop
// ra 2 - framecount

always_ff @(posedge Clock or negedge Resetn) begin
	if (~Resetn) Config_Exposure <= 16'h0100;
	else if (chipselect & write &
		(address == 4'd0)) Config_Exposure <= writedata[15:0];
end

always_ff @(posedge Clock or negedge Resetn) begin
	if (~Resetn) readdata <= 32'd0;
	else if (chipselect) begin
		case (address[1:0])
			2'd0 : readdata <= { 16'h0000 , Config_Exposure };
			2'd1 : readdata <= { 31'd0 , Config_done };
			2'd2 : readdata <= Capture_Framecount;
		endcase
	end
end

logic [1:0] config_edge, start_edge, stop_edge;

always_ff @(posedge Clock or negedge Resetn) begin
	if (~Resetn) begin
		config_edge <= 2'b00;
		start_edge <= 2'b00;
		stop_edge <= 2'b00;

		Config_start <= 1'b0;
		Capture_start <= 1'b0;
		Capture_stop <= 1'b0;
	end else begin
		config_edge <= { config_edge[0], 
			chipselect & (address == 4'd1) & writedata[1] };
		start_edge <= { start_edge[0],
			chipselect & (address == 4'd1) & writedata[2] };
		stop_edge <= { stop_edge[0],
			chipselect & (address == 4'd1) & writedata[3] };

		Config_start <= (config_edge == 2'b01);
		Capture_start <= (start_edge == 2'b01);
		Capture_stop <= (stop_edge == 2'b01);
	end
end

endmodule
