// Copyright by Adam Kinsman, Henry Ko and Nicola Nicolici
// Developed for the Embedded Systems course (COE4DS4)
// Department of Electrical and Computer Engineering
// McMaster University
// Ontario, Canada

`timescale 1ns/100ps
`default_nettype none

// This module is the main Nios component
// for the LCD / Touch panel peripheral
module Nios_LCD_Component (
	LCD_Component_clk,
	LCD_Component_resetn,
	
	Touchpanel_address,
	Touchpanel_chipselect,
	Touchpanel_read,
	Touchpanel_write,
	Touchpanel_readdata,
	Touchpanel_writedata,
	Touchpanel_irq,
	
	Image_address,
	Image_chipselect,
	Image_read,
	Image_write,
	Image_readdata,
	Image_writedata,

	Console_address,
	Console_chipselect,
	Console_read,
	Console_write,
	Console_readdata,
	Console_writedata,
	
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

	GPIO_0
);

input 	logic 		LCD_Component_clk;
input 	logic 		LCD_Component_resetn;

input  logic [3:0] 	Touchpanel_address;
input  logic 		Touchpanel_chipselect;
input  logic 		Touchpanel_read;
input  logic 		Touchpanel_write;
output logic  [31:0]	Touchpanel_readdata;
input  logic [31:0]	Touchpanel_writedata;
output logic 		Touchpanel_irq;
	
input  logic [3:0] 	Image_address;
input  logic 		Image_chipselect;
input  logic 		Image_read;
input  logic 		Image_write;
output logic  [31:0]	Image_readdata;
input  logic [31:0]	Image_writedata;

input  logic [10:0] 	Console_address;
input  logic 		Console_chipselect;
input  logic 		Console_read;
input  logic 		Console_write;
output logic  [31:0]	Console_readdata;
input  logic [31:0]	Console_writedata;

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

// Signals for LCD Touch Module (LTM)
// LCD display interface
logic 	[7:0]	LTM_R, LTM_G, LTM_B;
logic 			LTM_HD, LTM_VD;
logic 			LTM_NCLK, LTM_DEN, LTM_GRST;

// LCD configuration interface
wire 			LTM_SDA;
logic 			LTM_SCLK;
logic 			LCD_SCEN, LTM_SCEN;

// LCD touch panel interface
logic 			TP_DCLK, TP_CS, TP_DIN, TP_DOUT;
logic 			TP_PENIRQ_N, TP_BUSY;

// Internal signals
logic 			Clock, Resetn;
logic 	[2:0] 	Top_state;

// For LCD display / touch screen
logic 			LCD_TPn_sel, LCD_TPn_sclk;
logic 			LCD_config_start, LCD_config_done;
logic 			LCD_enable, TP_enable;
logic 			TP_touch_en, TP_coord_en;
logic 	[11:0]	TP_X_coord, TP_Y_coord;

// sdram to touch panel interface
logic				LCD_read_en;
logic	[15:0]	SDRAM_RD_Data_1;
logic	[15:0]	SDRAM_RD_Data_2;	

//////////////////////////////////////////
assign Clock = LCD_Component_clk;
assign Resetn = LCD_Component_resetn;

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

logic LCD_Config_unit_start, LCD_Config_unit_done;

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

assign LCD_Console_unit_Image_Red = SDRAM_RD_Data_2[9:2];
assign LCD_Console_unit_Image_Green = {SDRAM_RD_Data_1[14:10],SDRAM_RD_Data_2[14:12]};
assign LCD_Console_unit_Image_Blue = SDRAM_RD_Data_1[9:2];

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

always_ff @(posedge Clock or negedge Resetn) begin
	if (~Resetn) LCD_read_en <= 1'b0;
	else if (~LCD_unit_enable) LCD_read_en <= 1'b0;
	else LCD_read_en <= (
		(LCD_Data_unit_H_Count > (11'd216 - 11'd2)) &&
		(LCD_Data_unit_H_Count < (11'd216 - 11'd2 + 11'd640 + 11'd1)) &&
		(LCD_Data_unit_V_Count > (10'd35 - 10'd1 - 10'd1)) &&
		(LCD_Data_unit_V_Count < (10'd35 - 10'd1 + 10'd480 + 10'd1 - 10'd1))
	) ? ~LCD_Clock_en : 1'b0;
end

logic SDRAM_RD_Load;
logic SDRAM_WR_Load;
logic SDRAM_write_en, SDRAM_read_en;
logic [15:0] SDRAM_WR_Data_1, SDRAM_WR_Data_2;

assign SDRAM_read_en = LCD_read_en;

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

//reg [2:0] Top_state;

Nios_Image_Interface Nios_Image_Interface_Inst (
	.Clock(Clock),
	.Resetn(Resetn),
	.SRAM_writedata_1(SDRAM_WR_Data_1),
	.SRAM_writedata_2(SDRAM_WR_Data_2),
	.SRAM_write_en(SDRAM_write_en),
	.SRAM_load_en(SDRAM_WR_Load),
	.address(Image_address),
	.chipselect(Image_chipselect),
	.read(Image_read),
	.write(Image_write),
	.readdata(Image_readdata),
	.writedata(Image_writedata)	
);

logic [19:0] start_delay;

// Top level state machine
always_ff @(posedge Clock or negedge Resetn) begin
	if (~Resetn) begin
		Top_state <= 3'd0;
		LCD_Config_unit_start <= 1'b0;
		LCD_unit_enable <= 1'b0;
		SDRAM_RD_Load <= 1'b1;
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
					start_delay <= 20'd0;
					Top_state <= 3'd2;
				end
			end
			3'd2 : begin // wait for SDRAM load
				if (start_delay == 20'hFFFFF) begin
					LCD_unit_enable <= 1'b1;
					Top_state <= 3'd3;
				end else start_delay <= start_delay + 20'd1;
			end
			3'd3 : begin // normal running state
			end
		endcase
	end	
end


endmodule