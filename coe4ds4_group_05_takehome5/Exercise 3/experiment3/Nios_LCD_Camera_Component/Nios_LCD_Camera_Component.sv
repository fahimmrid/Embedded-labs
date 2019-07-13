// Copyright by Adam Kinsman, Henry Ko and Nicola Nicolici
// Developed for the Embedded Systems course (COE4DS4)
// Department of Electrical and Computer Engineering
// McMaster University
// Ontario, Canada

`timescale 1ns/100ps
`default_nettype none

// This module is the main Nios component
// for the LCD / Touch panel and camera peripherals
module Nios_LCD_Camera_Component (
	LCD_Camera_Component_clk,
	LCD_Camera_Component_resetn,
	
	Touchpanel_address,
	Touchpanel_chipselect,
	Touchpanel_read,
	Touchpanel_write,
	Touchpanel_readdata,
	Touchpanel_writedata,
	Touchpanel_irq,
	
	Camera_address,
	Camera_chipselect,
	Camera_read,
	Camera_write,
	Camera_readdata,
	Camera_writedata,

	Console_address,
	Console_chipselect,
	Console_read,
	Console_write,
	Console_readdata,
	Console_writedata,
	
	Imageline_address,
	Imageline_chipselect,
	Imageline_read,
	Imageline_write,
	Imageline_readdata,
	Imageline_writedata,
	Imageline_waitrequest,

	DRAM_DQ,
	DRAM_ADDR,
	DRAM_LDQM,
	DRAM_UDQM,
	DRAM_WE_N,
	DRAM_CAS_N,
	DRAM_RAS_N,
	DRAM_CS_N,
	DRAM_BA_0,
	DRAM_BA_1,
	DRAM_CLK,
	DRAM_CKE,

	GPIO_0,
	GPIO_1	
);

input 	logic 		LCD_Camera_Component_clk;
input 	logic 		LCD_Camera_Component_resetn;

input  logic [3:0] 	Touchpanel_address;
input  logic 		Touchpanel_chipselect;
input  logic 		Touchpanel_read;
input  logic 		Touchpanel_write;
output logic [31:0]	Touchpanel_readdata;
input  logic [31:0]	Touchpanel_writedata;
output logic 		Touchpanel_irq;
	
input  logic [3:0] 	Camera_address;
input  logic 		Camera_chipselect;
input  logic 		Camera_read;
input  logic 		Camera_write;
output logic [31:0]	Camera_readdata;
input  logic [31:0]	Camera_writedata;

input  logic [10:0] 	Console_address;
input  logic 		Console_chipselect;
input  logic 		Console_read;
input  logic 		Console_write;
output logic [31:0]	Console_readdata;
input  logic [31:0]	Console_writedata;

input  logic [10:0] 	Imageline_address;
input  logic 		Imageline_chipselect;
input  logic 		Imageline_read;
input  logic 		Imageline_write;
output logic [31:0]	Imageline_readdata;
input  logic [31:0] 	Imageline_writedata;
output logic 		Imageline_waitrequest;

inout wire	[15:0] 	DRAM_DQ;
output logic	[11:0] 	DRAM_ADDR;
output logic 		DRAM_LDQM;
output logic 		DRAM_UDQM;
output logic 		DRAM_WE_N;
output logic 		DRAM_CAS_N;
output logic 		DRAM_RAS_N;
output logic 		DRAM_CS_N;
output logic 		DRAM_BA_0;
output logic 		DRAM_BA_1;
output logic 		DRAM_CLK;
output logic 		DRAM_CKE;

inout wire	[35:0] 	GPIO_0;
inout wire	[35:0] 	GPIO_1;

// Signals for LCD Touch Module (LTM)
// LCD display interface
logic 	[7:0]	LTM_R, LTM_G, LTM_B;
logic 			LTM_HD, LTM_VD;
logic 			LTM_NCLK, LTM_DEN, LTM_GRST;

// LCD configuration interface
wire 			LTM_SDA;
logic 			LTM_SCLK, LCD_SCEN, LTM_SCEN;

// LCD touch panel interface
logic 			TP_DCLK, TP_CS, TP_DIN, TP_DOUT;
logic 			TP_PENIRQ_N, TP_BUSY;

// Digital Camera interface
logic 			Camera_SCLK;
logic 	[9:0]	Camera_DATA;
logic 			Camera_FVAL, Camera_LVAL;
logic 			Camera_PIXCLK;
logic 			Camera_MCLK;

// Internal signals
logic 			Clock, Resetn;

// For LCD display / touch screen
logic 			LCD_TPn_sel, LCD_TPn_sclk;
logic 			LCD_config_start, LCD_config_done;
logic 			LCD_enable, TP_enable;
logic 			TP_touch_en, TP_coord_en;
logic 	[11:0]	TP_X_coord, TP_Y_coord;

// sdram to touch panel timing
logic				LCD_read_en;
logic	[15:0]	SDRAM_RD_Data_1;
logic	[15:0]	SDRAM_RD_Data_2;	

logic	[31:0]	Camera_Frame_count;

logic	[9:0]	Camera_Data_R;
logic	[9:0]	Camera_Data_G;
logic	[9:0]	Camera_Data_B;
logic			Camera_Data_En;

//////////////////////////////////////////
assign Clock = LCD_Camera_Component_clk;
assign Resetn = LCD_Camera_Component_resetn;

assign LCD_TPn_sclk = (LCD_TPn_sel) ? LTM_SCLK : TP_DCLK;
assign LTM_SCEN = (LCD_TPn_sel) ? LCD_SCEN : ~TP_CS;
assign LTM_GRST = Resetn;

// Connections to GPIO for LTM
assign TP_PENIRQ_N   = GPIO_0[0];
assign TP_DOUT       = GPIO_0[1];
assign TP_BUSY       = GPIO_0[2];
assign GPIO_0[3]	 = TP_DIN;

assign GPIO_0[4]	 = LCD_TPn_sclk;

assign GPIO_0[35]    = LTM_SDA;
assign GPIO_0[34]    = LTM_SCEN;
assign GPIO_0[33]    = LTM_GRST;

assign GPIO_0[9]	 = LTM_NCLK;
assign GPIO_0[10]    = LTM_DEN;
assign GPIO_0[11]    = LTM_HD;
assign GPIO_0[12]    = LTM_VD;

assign GPIO_0[5]     = LTM_B[3];
assign GPIO_0[6]     = LTM_B[2];
assign GPIO_0[7]     = LTM_B[1];
assign GPIO_0[8]   	 = LTM_B[0];
assign GPIO_0[16:13] = LTM_B[7:4];
assign GPIO_0[24:17] = LTM_G[7:0];
assign GPIO_0[32:25] = LTM_R[7:0];

// Connections to GPIO for Digital Camera
assign Camera_DATA[1:0] = GPIO_1[1:0];
assign Camera_DATA[2]   = GPIO_1[5];
assign Camera_DATA[3]   = GPIO_1[3];
assign Camera_DATA[4]   = GPIO_1[2];
assign Camera_DATA[5]   = GPIO_1[4];
assign Camera_DATA[9:6] = GPIO_1[9:6];

assign Camera_FVAL      = GPIO_1[13];
assign Camera_LVAL      = GPIO_1[12];

assign GPIO_1[11]       = Camera_MCLK;
assign Camera_PIXCLK    = GPIO_1[10];

//assign GPIO_1[15]       = Camera_SDAT;
assign GPIO_1[14]       = Camera_SCLK;

// Start of hardware description
always_ff @(posedge Clock or negedge Resetn) begin
	if (~Resetn) Camera_MCLK <= 1'b0;
	else Camera_MCLK = ~Camera_MCLK;
end

logic Camera_unit_enable;

Camera_Data_Controller Camera_Data_unit (
	.Clock_50(Clock),
	.Resetn(Resetn),	
	.Enable(Camera_unit_enable),	
	.Camera_PIXCLK(Camera_PIXCLK),
	.Start(Camera_Capture_start),
	.Stop(Camera_Capture_stop),
	.iCamera_Data(Camera_DATA),
	.iFrame_Valid(Camera_FVAL),
	.iLine_Valid(Camera_LVAL),
	.oRed(Camera_Data_R),
	.oGreen(Camera_Data_G),
	.oBlue(Camera_Data_B),
	.oData_Valid(Camera_Data_En),
	.oFrame_Count(Camera_Frame_count)
);

logic [15:0] Camera_Config_unit_Exposure;
logic Camera_Config_unit_start, Camera_Config_unit_done;
logic Camera_Capture_start, Camera_Capture_stop;

Camera_Config_Controller Camera_Config_unit (
	.Clock(Clock),
	.Resetn(Resetn),
	.Start(Camera_Config_unit_start),
	.Done(Camera_Config_unit_done),
	.iExposure(Camera_Config_unit_Exposure),
	.Camera_I2C_sclk(Camera_SCLK),
	.Camera_I2C_sdat(GPIO_1[15])
);

Nios_Camera_Interface Nios_Camera_Interface_unit (
	.Clock(Clock),
	.Resetn(Resetn),
	.Config_start(Camera_Config_unit_start),
	.Config_done(Camera_Config_unit_done),
	.Config_Exposure(Camera_Config_unit_Exposure),
	.Capture_start(Camera_Capture_start),
	.Capture_stop(Camera_Capture_stop),
	.Capture_Framecount(Camera_Frame_count),
	.address(Camera_address),
	.chipselect(Camera_chipselect),
	.read(Camera_read),
	.write(Camera_write),
	.readdata(Camera_readdata),
	.writedata(Camera_writedata)	
);

logic LCD_Config_unit_start;
logic LCD_Config_unit_done;
assign LCD_TPn_sel = ~LCD_Config_unit_done;

LCD_Config_Controller LCD_Config_unit (
	.Clock(Clock),
	.Resetn(Resetn),
	.Start(LCD_Config_unit_start),
	.Done(LCD_Config_unit_done),
	.LCD_I2C_sclk(LTM_SCLK),
 	.LCD_I2C_sdat(LTM_SDA),
	.LCD_I2C_scen(LCD_SCEN)
);

Touch_Panel_Controller Touch_Panel_unit(
	.Clock_50MHz(Clock),
	.Resetn(Resetn),
	.Enable(~LTM_VD),	
	.Touch_En(TP_touch_en),
	.Coord_En(TP_coord_en),
	.X_Coord(TP_X_coord),
	.Y_Coord(TP_Y_coord),
	.TP_PENIRQ_N_I(TP_PENIRQ_N),
	.TP_BUSY_I(TP_BUSY),
	.TP_SCLK_O(TP_DCLK),
	.TP_MOSI_O(TP_DIN),
	.TP_MISO_I(TP_DOUT),
	.TP_SS_N_O(TP_CS)
);

Nios_Touch_Panel_Interface Nios_Touch_Panel_unit(
	.Clock(Clock),
	.Resetn(Resetn),	
	.Touch_En(TP_touch_en),
	.Coord_En(TP_coord_en),
	.X_Coord(TP_X_coord),
	.Y_Coord(TP_Y_coord),
	.address(Touchpanel_address),
	.chipselect(Touchpanel_chipselect),
	.read(Touchpanel_read),
	.write(Touchpanel_write),
	.readdata(Touchpanel_readdata),
	.writedata(Touchpanel_writedata),
	.irq(Touchpanel_irq)
);

logic LCD_Clock_en;
logic LCD_unit_enable;
logic [10:0] LCD_Data_unit_H_Count;
logic [9:0] LCD_Data_unit_V_Count;
logic [9:0] LCD_Coord_X, LCD_Coord_Y;
logic [7:0] LCD_Data_unit_iRed, LCD_Data_unit_iGreen, LCD_Data_unit_iBlue;

LCD_Data_Controller LCD_Data_unit (
	.Clock(Clock),
	.oClock_en(LCD_Clock_en),
	.Resetn(Resetn),
	.Enable(LCD_unit_enable),
	.iRed(LCD_Data_unit_iRed),
	.iGreen(LCD_Data_unit_iGreen),
	.iBlue(LCD_Data_unit_iBlue),
	.oCoord_X(LCD_Coord_X),
	.oCoord_Y(LCD_Coord_Y),
	.H_Count(LCD_Data_unit_H_Count),
	.V_Count(LCD_Data_unit_V_Count),
	.LTM_NCLK(LTM_NCLK),
	.LTM_HD(LTM_HD),
	.LTM_VD(LTM_VD),
	.LTM_DEN(LTM_DEN),
	.LTM_R(LTM_R),
	.LTM_G(LTM_G),
	.LTM_B(LTM_B)
);

logic [5:0] LCD_Console_Button_Invert;
logic [7:0] LCD_Console_unit_Image_Red;
logic [7:0] LCD_Console_unit_Image_Green;
logic [7:0] LCD_Console_unit_Image_Blue;

logic Filter_read_en;
logic [31:0] Filter_config;
logic [7:0] Filter_unit_Red;
logic [7:0] Filter_unit_Green;
logic [7:0] Filter_unit_Blue;
logic [31:0] Filter_config_buf;
logic [1:0] vsync_edge;

assign Filter_unit_Red = SDRAM_RD_Data_2[9:2];
assign Filter_unit_Green[7:3] = SDRAM_RD_Data_1[14:10];
assign Filter_unit_Green[2:0] = SDRAM_RD_Data_2[14:12];
assign Filter_unit_Blue = SDRAM_RD_Data_1[9:2];

always @ (posedge Clock or negedge Resetn) begin
	if (!Resetn) begin
		Filter_config_buf <= 'd0;
		vsync_edge <= 'd0;
	end else begin
		vsync_edge <= { vsync_edge[0], LTM_VD };
		// only update filter config during vertical sync
		if (vsync_edge == 2'b10) 
			Filter_config_buf <= Filter_config;
	end
end

Filter_Pipe Filter_Pipe_unit (
	.Clock(Clock),
	.Clock_en(LCD_Clock_en),
	.Resetn(Resetn),
	.Enable(LCD_unit_enable),
	.Filter_config(Filter_config_buf),
	.H_Count(LCD_Data_unit_H_Count),
	.V_Count(LCD_Data_unit_V_Count),
	.oRead_in_en(Filter_read_en),
	.R_in(Filter_unit_Red),
	.G_in(Filter_unit_Green),
	.B_in(Filter_unit_Blue),
	.iRead_out_en(LCD_read_en),
	.R_out(LCD_Console_unit_Image_Red),
	.G_out(LCD_Console_unit_Image_Green),
	.B_out(LCD_Console_unit_Image_Blue)
);

logic LCD_CharMap_wren;
logic [9:0] LCD_CharMap_address;
logic [15:0] LCD_CharMap_data;
logic [15:0] LCD_CharMap_q;
	
logic LCD_Label_wren;
logic [7:0] LCD_Label_address;
logic [7:0] LCD_Label_data;
logic [7:0] LCD_Label_q;

LCD_Console_Generation LCD_Console_unit (
	.Clock(Clock),
	.Clock_en(LCD_Clock_en),
	.Resetn(Resetn),
	.Button_Invert(LCD_Console_Button_Invert),
	.Image_Red(LCD_Console_unit_Image_Red),
	.Image_Green(LCD_Console_unit_Image_Green),
	.Image_Blue(LCD_Console_unit_Image_Blue),
	.H_Count(LCD_Data_unit_H_Count),
	.V_Count(LCD_Data_unit_V_Count),
	.Console_Red(LCD_Data_unit_iRed),
	.Console_Green(LCD_Data_unit_iGreen),
	.Console_Blue(LCD_Data_unit_iBlue),
	.CharMap_address(LCD_CharMap_address),
	.CharMap_data(LCD_CharMap_data),
	.CharMap_wren(LCD_CharMap_wren),
	.CharMap_q(LCD_CharMap_q),
	.Label_address(LCD_Label_address),
	.Label_data(LCD_Label_data),
	.Label_wren(LCD_Label_wren),
	.Label_q(LCD_Label_q)	
);

Nios_Console_Interface Nios_Console_unit (
	.Clock(Clock),
	.Resetn(Resetn),
	.Button_Invert(LCD_Console_Button_Invert),
	.CharMap_address(LCD_CharMap_address),
	.CharMap_data(LCD_CharMap_data),
	.CharMap_wren(LCD_CharMap_wren),
	.CharMap_q(LCD_CharMap_q),
	.Label_address(LCD_Label_address),
	.Label_data(LCD_Label_data),
	.Label_wren(LCD_Label_wren),
	.Label_q(LCD_Label_q),
	.address(Console_address),
	.chipselect(Console_chipselect),
	.read(Console_read),
	.write(Console_write),
	.readdata(Console_readdata),
	.writedata(Console_writedata)
);

always @(posedge Clock or negedge Resetn) begin
	if (~Resetn) LCD_read_en <= 1'b0;
	else if (~LCD_unit_enable) LCD_read_en <= 1'b0;
	else LCD_read_en <= (
		(LCD_Data_unit_H_Count > (11'd216 - 11'd2)) &&
		(LCD_Data_unit_H_Count < (11'd216 - 11'd2 + 11'd640 + 11'd1)) &&
		(LCD_Data_unit_V_Count > (10'd35 - 10'd1 - 10'd1)) &&
		(LCD_Data_unit_V_Count < (10'd35 - 10'd1 + 10'd480 + 10'd1 - 10'd1))
	) ? ~LCD_Clock_en : 1'b0;
end
												
logic SDRAM_RD_Load, SDRAM_WR_Load;
logic SDRAM_wr_src, SDRAM_rd_src;
logic SDRAM_write_en, SDRAM_read_en;
logic Nios_SDRAM_wren, Nios_SDRAM_rden;

logic [15:0] SDRAM_WR_Data_1, SDRAM_WR_Data_2;
logic [15:0] Nios_SDRAM_wr_data_1, Nios_SDRAM_wr_data_2;

assign SDRAM_WR_Data_1 = (SDRAM_wr_src) ? Nios_SDRAM_wr_data_1 : 
	{ 1'b0, Camera_Data_G[9:5], Camera_Data_B[9:0] };
assign SDRAM_WR_Data_2 = (SDRAM_wr_src) ? Nios_SDRAM_wr_data_2 : 
	{ 1'b0, Camera_Data_G[4:0], Camera_Data_R[9:0] };

assign SDRAM_write_en = (SDRAM_wr_src) ? Nios_SDRAM_wren : Camera_Data_En;
assign SDRAM_read_en = (SDRAM_rd_src) ? Nios_SDRAM_rden : Filter_read_en;

logic [1:0] SDRAM_BA, SDRAM_DQM; 
assign DRAM_BA_1 = SDRAM_BA[1]; assign DRAM_BA_0 = SDRAM_BA[0]; 
assign DRAM_UDQM = SDRAM_DQM[1]; assign DRAM_LDQM = SDRAM_DQM[0];

//	SDRAM frame buffer
Sdram_Control_4Port u7 (	
	// HOST Side
	.REF_CLK(Clock),	
	.RESET_N(1'b1),

	// Write Side FIFO          // Read Side FIFO
	.WR1_DATA(SDRAM_WR_Data_1), .RD1_DATA(SDRAM_RD_Data_1),
	.WR2_DATA(SDRAM_WR_Data_2), .RD2_DATA(SDRAM_RD_Data_2),
	.WR(SDRAM_write_en),        .RD(SDRAM_read_en),           
	.WR_LOAD(SDRAM_WR_Load),    .RD_LOAD(SDRAM_RD_Load),      
	.WR_CLK(Clock),             .RD_CLK(Clock),    

	// SDRAM Side
	.SA(DRAM_ADDR),
	.BA(SDRAM_BA),
	.CS_N(DRAM_CS_N),
	.CKE(DRAM_CKE),
	.RAS_N(DRAM_RAS_N),
	.CAS_N(DRAM_CAS_N),
	.WE_N(DRAM_WE_N),
	.DQ(DRAM_DQ),
	.DQM(SDRAM_DQM),
	.SDR_CLK(DRAM_CLK)
);

logic [2:0] Top_state;
logic [2:0] State_reload;

Nios_Imageline_Interface Nios_Imageline_unit(
	.Clock(Clock),
	.Resetn(Resetn),
	.Filter_config(Filter_config),
	.State_reload(State_reload),
	.State_read(Top_state),
	.SDRAM_wr_src(SDRAM_wr_src),
	.SDRAM_rd_src(SDRAM_rd_src),
	.SDRAM_wren(Nios_SDRAM_wren),
	.SDRAM_rden(Nios_SDRAM_rden),
	.SDRAM_wr_data_1(Nios_SDRAM_wr_data_1),
	.SDRAM_wr_data_2(Nios_SDRAM_wr_data_2),
	.SDRAM_rd_data_1(SDRAM_RD_Data_1),
	.SDRAM_rd_data_2(SDRAM_RD_Data_2),
	.address(Imageline_address),
	.chipselect(Imageline_chipselect),
	.read(Imageline_read),
	.write(Imageline_write),
	.readdata(Imageline_readdata),
	.writedata(Imageline_writedata),
	.waitrequest(Imageline_waitrequest)
);

logic [19:0] start_delay;

// Top level state machine
always_ff @(posedge Clock or negedge Resetn) begin
	if (~Resetn) begin
		Top_state <= 3'd0;
		LCD_Config_unit_start <= 1'b0;
		Camera_unit_enable <= 1'b0;
		LCD_unit_enable <= 1'b0;
		SDRAM_RD_Load <= 1'b1;
		SDRAM_WR_Load <= 1'b1;
		start_delay <= 20'd0;
	end else begin
		case (Top_state) 
			3'd0 : begin // reset state
				LCD_Config_unit_start <= 1'b1;
				Top_state <= 3'd1;
			end
			3'd1 : begin // wait for LCD config
				LCD_Config_unit_start <= 1'b0;
				if ( LCD_Config_unit_done & 
					~LCD_Config_unit_start
				) begin
					SDRAM_RD_Load <= 1'b0;
					SDRAM_WR_Load <= 1'b0;
					start_delay <= 20'd0;
					Top_state <= 3'd2;
				end
			end
			3'd2 : begin // wait for SDRAM load
				if (start_delay == 20'hFFFFF) begin
					Camera_unit_enable <= 1'b1;
					Top_state <= 3'd3;
				end else start_delay <= start_delay + 20'd1;
			end
			3'd3 : begin // wait for camera start up
				if (start_delay == 20'hFFFFF) begin
					LCD_unit_enable <= 1'b1;
					Top_state <= 3'd4;
				end else start_delay <= start_delay + 20'd1;
			end
			3'd4 : begin // normal running state
				if (State_reload[2]) begin
					Camera_unit_enable <= 1'b0;
					LCD_unit_enable <= 1'b0;
					SDRAM_RD_Load <= State_reload[0];
					SDRAM_WR_Load <= State_reload[1];					
					start_delay <= 20'd0;
					Top_state <= 3'd5;
				end
			end
			3'd5 : begin // wait for State_reload
				if (start_delay == 20'hFFFFF) begin
					if (~State_reload[2]) 
						Top_state <= 3'd1;
				end else start_delay <= start_delay + 20'd1;
			end
		endcase
	end	
end

endmodule