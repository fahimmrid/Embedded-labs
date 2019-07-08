// Copyright by Adam Kinsman, Henry Ko and Nicola Nicolici
// Developed for the Embedded Systems course (COE4DS4)
// Department of Electrical and Computer Engineering
// McMaster University
// Ontario, Canada

`timescale 1ns/100ps
`default_nettype none

// This is the top module
// It interfaces to the LCD display and touch panel
module exercise1 (
	/////// board clocks                      ////////////
	input logic CLOCK_50_I,                   // 50 MHz clock
	
	/////// pushbuttons/switches              ////////////
	input logic[3:0] PUSH_BUTTON_I,           // pushbuttons
	input logic[17:0] SWITCH_I,               // toggle switches
	
	/////// 7 segment displays/LEDs           ////////////
	output logic[6:0] SEVEN_SEGMENT_N_O[7:0], // 8 seven segment displays
	output logic[8:0] LED_GREEN_O,            // 9 green LEDs
	output logic[17:0] LED_RED_O,             // 18 red LEDs
	
	/////// GPIO connections                  ////////////
	inout wire[35:0] GPIO_0                   // GPIO Connection 0 (LTM)
);

// Signals for LCD Touch Module (LTM)
// LCD display interface
logic 	[7:0]	LTM_R, LTM_G, LTM_B;
logic 			LTM_HD, LTM_VD;
logic 			LTM_NCLK, LTM_DEN, LTM_GRST;

// LCD configuration interface
wire 			LTM_SDA;
logic 			LTM_SCLK, LTM_SCEN;

// LCD touch panel interface
logic 			TP_DCLK, TP_CS, TP_DIN, TP_DOUT;
logic 			TP_PENIRQ_N, TP_BUSY;

// Internal signals
logic 			Clock, Resetn;
logic 	[2:0] 	Top_state;


//NEW **
logic [2:0] color [7:0]; //8 -  3bits
logic [2:0] new_color;
logic    [2:0] block;  
logic[15:0] secounter;
logic  [1:0] update; 

logic TP_touch_en_detect;
logic TP_coord_en_detect;
logic TP_touch_flag;
logic [4:0] SSD [7:0];



			 
logic [2:0] next_color;
logic [25:0] ms_counter [7:0]; //8 - 23 bits



// For LCD display / touch screen
logic 			LCD_TPn_sel, LCD_TPn_sclk;
logic 			LCD_config_start, LCD_config_done;
logic 			LCD_enable, TP_enable;
logic 			TP_touch_en, TP_coord_en;
logic 	[11:0]	TP_X_coord, TP_Y_coord;

logic 	[9:0] 	colorbar_X, colorbar_Y;
 
logic 	[7:0]	colorbar_Red, colorbar_Green, colorbar_Blue;

logic 	[4:0] 	TP_position[7:0];

assign Clock = CLOCK_50_I;
assign Resetn = SWITCH_I[17];

assign LCD_TPn_sclk = (LCD_TPn_sel) ? LTM_SCLK : TP_DCLK;
assign LTM_SCEN = (LCD_TPn_sel) ? 1'b0 : ~TP_CS;
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
assign GPIO_0[8]     = LTM_B[0];
assign GPIO_0[16:13] = LTM_B[7:4];
assign GPIO_0[24:17] = LTM_G[7:0];
assign GPIO_0[32:25] = LTM_R[7:0];

// Top state machine for controlling resets
always_ff @(posedge Clock or negedge Resetn) begin
	if (~Resetn) begin
		Top_state <= 3'h0;
		TP_enable <= 1'b0;
		LCD_enable <= 1'b0;
		LCD_config_start <= 1'b0;
		LCD_TPn_sel <= 1'b1;
	end else begin
		case (Top_state)
			3'h0 : begin
				LCD_config_start <= 1'b1;
				LCD_TPn_sel <= 1'b1;
				Top_state <= 3'h1;
			end			
			3'h1 : begin
				LCD_config_start <= 1'b0;
				if (LCD_config_done & ~LCD_config_start) begin
					TP_enable <= 1'b1;
					LCD_enable <= 1'b1;
					LCD_TPn_sel <= 1'b0;
					Top_state <= 3'h2;
				end
			end			
			3'h2 : begin
				Top_state <= 3'h2;
			end
		endcase
	end
end				

// LCD Configuration
LCD_Config_Controller LCD_Config_unit(
	.Clock(Clock),
	.Resetn(Resetn),
	.Start(LCD_config_start),
	.Done(LCD_config_done),
	.LCD_I2C_sclk(LTM_SCLK),
 	.LCD_I2C_sdat(LTM_SDA),
	.LCD_I2C_scen()
);

// LCD Image
LCD_Data_Controller LCD_Data_unit (
	.Clock(Clock),
	.oClock_en(),
	.Resetn(Resetn),
	.Enable(LCD_enable),
	.iRed(colorbar_Red),
	.iGreen(colorbar_Green),
	.iBlue(colorbar_Blue),
	.oCoord_X(colorbar_X),
	.oCoord_Y(colorbar_Y),
	.H_Count(), // not used in this experiment
	.V_Count(), // not used in this experiment
	.LTM_NCLK(LTM_NCLK),
	.LTM_HD(LTM_HD),
	.LTM_VD(LTM_VD),
	.LTM_DEN(LTM_DEN),
	.LTM_R(LTM_R),
	.LTM_G(LTM_G),
	.LTM_B(LTM_B)
);


// Controller for the TP on the LTM
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


always_comb begin

if (colorbar_Y < 10'd240)  begin
  if (colorbar_X < 10'd200)
		block = color[0];
  else if (colorbar_X < 10'd400)
		block = color[1];
  else if (colorbar_X < 10'd600)
		block = color[2];
  else block = color[3];
end else begin


  if (colorbar_X < 10'd200)
		block = color[4];
  else if (colorbar_X < 10'd400)
		block = color[5];
  else if (colorbar_X < 10'd600)
		block = color[6];
  else block = color[7];
  
  end
end  




// State machine for generating the color bars
always_ff @(posedge Clock or negedge Resetn) begin
	if (~Resetn) begin
		colorbar_Red <= 8'h00; 
		colorbar_Green <= 8'h00;
		colorbar_Blue <= 8'h00;
	end else begin
		colorbar_Red <= {8{block[2]}};
		colorbar_Green = {8{block[1]}};
		colorbar_Blue = {8{block[0]}};
	end
end





logic [2:0] state;
logic [2:0] old_block;
logic [7:0] Press;



always_ff @(posedge Clock or negedge Resetn) begin
	if (~Resetn) begin
		Press <= 8'd0;

	end else begin
		if (TP_touch_en) begin	
			if (TP_coord_en) begin	
			if (TP_Y_coord < 12'h800) begin //2000K
				if (TP_X_coord < 12'h400) Press[0] <= 1'b1; 
				else if (TP_X_coord < 12'h800) Press[1] <= 1'b1;
				else if (TP_X_coord < 12'hc00) Press[2] <= 1'b1;
				else Press[3] <= 1'b1;
			end else begin
				if (TP_X_coord < 12'h400) Press[4] <= 1'b1;
				else if (TP_X_coord < 12'h800) Press[5] <= 1'b1;
				else if (TP_X_coord < 12'hc00) Press[6] <= 1'b1;
				else Press[7] <= 1'b1;
			end
				
			end  else begin
				Press <= 8'b0;
			end	
			end
		end
	end

	
	always_ff @(posedge Clock or negedge Resetn) begin
	if (~Resetn) begin
		
		state<=3'd0;
	end else begin
		if (TP_touch_en) begin	
			if (TP_coord_en) begin	
			if (TP_Y_coord < 12'h800) begin //2000K
				if (TP_X_coord < 12'h400) state<=3'd0;//1049
				else if (TP_X_coord < 12'h800) state<=3'd1;
				else if (TP_X_coord < 12'hc00)state<=3'd2;
				else state<=3'd3;
			end else begin
				if (TP_X_coord < 12'h400) state<=3'd4;
				else if (TP_X_coord < 12'h800) state<=3'd5;
				else if (TP_X_coord < 12'hc00) state<=3'd6;
				else state<=3'd7;
			end
				
			end 
			end
		end
	end
logic [2:0] current_block [7:0];

logic flag_7seg;




always_ff @(posedge Clock or negedge Resetn) begin
	if (~Resetn) begin
		current_block[0] <= 3'd0;
		current_block[1] <= 3'd0;
		current_block[2] <= 3'd0;
		current_block[3] <= 3'd0;
		current_block[4] <= 3'd0;
		current_block[5] <= 3'd0;
		current_block[6] <= 3'd0;
		current_block[7] <= 3'd0;
		TP_touch_en_detect<=1'b0;
		TP_coord_en_detect<=1'b0;
		old_block <= 3'd0;
	end else begin
	TP_touch_en_detect<=TP_touch_en;   
		if (TP_touch_en && ~TP_touch_en_detect) begin
			current_block[0] <= state ;
			current_block[1] <= current_block[0];
			current_block[2] <= current_block[1];
			current_block[3] <= current_block[2];
			current_block[4] <= current_block[3];
			current_block[5] <= current_block[4];
			current_block[6] <= current_block[5];
			current_block[7] <= current_block[6];
		//end
		end else if (state!= old_block) begin		    
			old_block <= state; 
			current_block[0] <= state ;
			current_block[1] <= current_block[0];
			current_block[2] <= current_block[1];
			current_block[3] <= current_block[2];
			current_block[4] <= current_block[3];
			current_block[5] <= current_block[4];
			current_block[6] <= current_block[5];
			current_block[7] <= current_block[6];
		
		end
		

		end
		end







always_ff @(posedge Clock or negedge Resetn) begin
	if (~Resetn) begin
		ms_counter[0] <= 26'd0;
		ms_counter[1] <= 26'd0;
		ms_counter[2] <= 26'd0;
		ms_counter[3] <= 26'd0;
		ms_counter[4] <= 26'd0;
		ms_counter[5] <= 26'd0;
		ms_counter[6] <= 26'd0;
		ms_counter[7] <= 26'd0;
		color[0] <= 3'd0;
		color[1] <= 3'd1;
		color[2] <= 3'd2;
		color[3] <= 3'd3;
		color[4] <= 3'd4;
		color[5] <= 3'd5;
		color[6] <= 3'd6;
		color[7] <= 3'd7;
	
	
		
		
		
	end else begin
	  
		
		

	   	if (Press[0]) begin  
				ms_counter[0] <= 26'd0; 
				end else //if ((!Press[0]) || (each_block != old_block)) 
				begin
			ms_counter[0] <= ms_counter[0] + 26'd1;
		end 
		

		 	if (Press[1]) begin
				ms_counter[1] <= 26'd0; 
				end else //if ((!Press[1]) || (each_block != old_block)) 
				begin
			ms_counter[1] <= ms_counter[1] + 26'd1;
		end 
		
		 	if (Press[2]) begin
				ms_counter[2] <= 26'd0; 
				end else //if ((!Press[2]) || (each_block != old_block)) 
				begin
			ms_counter[2] <= ms_counter[2] + 26'd1;
		end 
		
		 	if (Press[3]) begin
				ms_counter[3] <= 26'd0; 
				end else// if ((!Press[3]) || (each_block != old_block)) 
				begin
			ms_counter[3] <= ms_counter[3] + 26'd1;
		end 
		
		 	if (Press[4]) begin
				ms_counter[4] <= 26'd0; 
				end else //if ((!Press[4]) || (each_block != old_block))
				begin
			ms_counter[4] <= ms_counter[4] + 26'd1;
		end  
			if (Press[5]) begin
				ms_counter[5] <= 26'd0; 
				end else //if ((!Press[5]) || (each_block != old_block))
				begin
			ms_counter[5] <= ms_counter[5] + 26'd1;
		end  
		 	if (Press[6]) begin
				ms_counter[6] <= 26'd0; 
				end else //if ((!Press[6]) || (each_block != old_block))
				begin
			ms_counter[6] <= ms_counter[6] + 26'd1;
		end 
		 	if (Press[7]) begin
				ms_counter[7] <= 26'd0; 
				end else //if ((!Press[7]) || (each_block != old_block)) 
				begin
			ms_counter[7] <= ms_counter[7] + 26'd1;
		end 
		
		if (ms_counter[0] == 26'd49999999) begin
			ms_counter[0] <= 26'd0;
			color[0] <= color[0] + 3'd1;
         
		end
		if (ms_counter[1] == 26'd49999999) begin
			ms_counter[1] <= 26'd0;	
			color[1] <= color[1] + 3'd1;
		
			
		end
		if (ms_counter[2] == 26'd49999999) begin
			ms_counter[2] <= 26'd0;
			color[2] <= color[2] + 3'd1;		
		end
		if (ms_counter[3] == 26'd49999999) begin
			ms_counter[3] <= 26'd0;	
			color[3] <= color[3] + 3'd1;
			
			
		end
		if (ms_counter[4] == 26'd49999999) begin
			ms_counter[4] <= 26'd0;	
			color[4] <= color[4] + 3'd1;
			
			
		end
		if (ms_counter[5] == 26'd49999999) begin
			ms_counter[5] <= 26'd0;			
			color[5] <= color[5] + 3'd1;
	    
		end
		if (ms_counter[6] == 26'd49999999) begin
			ms_counter[6] <= 26'd0;	
			color[6] <= color[6] + 3'd1;
         
		end
		if (ms_counter[7] == 26'd49999999) begin
			ms_counter[7] <= 26'd0;			
			color[7] <= color[7] + 3'd1;
	      
		end

	end
end
logic [2:0] high_detect [7:0];
logic [3:0]color_count0;
logic [3:0]color_count1;
logic [3:0]color_count2;
logic [3:0]color_count3;
logic [3:0]color_count4;
logic [3:0]color_count5;
logic [3:0]color_count6;
logic [3:0]color_count7;
always_ff @(posedge Clock or negedge Resetn) begin
	if (~Resetn) begin
	color_count0 <= 4'd0;
	color_count1 <= 4'd0;
	color_count2 <= 4'd0;
	color_count3 <= 4'd0;
	color_count4 <= 4'd0;
	color_count5 <= 4'd0;
	color_count6 <= 4'd0;
	color_count7 <= 4'd0;
	high_detect[0] <= 3'd0;
	high_detect[1] <= 3'd0;
	high_detect[2] <= 3'd0;
	high_detect[3] <= 3'd0;
	high_detect[4] <= 3'd0;
	high_detect[5] <= 3'd0;
	high_detect[6] <= 3'd0;
	high_detect[7] <= 3'd0;
	
	end else begin
	high_detect[0] <= color[0];
	high_detect[1] <= color[1];
	high_detect[2] <= color[2];
	high_detect[3] <= color[3];
	high_detect[4] <= color[4];
	high_detect[5] <= color[5];
	high_detect[6] <= color[6];
	high_detect[7] <= color[7];
	
	color_count0 <= (high_detect[0]==3'd0)+(high_detect[1]==3'd0)+(high_detect[2]==3'd0)+(high_detect[3]==3'd0)+(high_detect[4]==3'd0)+(high_detect[5]==3'd0)+(high_detect[6]==3'd0)+(high_detect[7]==3'd0);
	color_count1 <= (high_detect[0]==3'd1)+(high_detect[1]==3'd1)+(high_detect[2]==3'd1)+(high_detect[3]==3'd1)+(high_detect[4]==3'd1)+(high_detect[5]==3'd1)+(high_detect[6]==3'd1)+(high_detect[7]==3'd1);
	color_count2 <= (high_detect[0]==3'd2)+(high_detect[1]==3'd2)+(high_detect[2]==3'd2)+(high_detect[3]==3'd2)+(high_detect[4]==3'd2)+(high_detect[5]==3'd2)+(high_detect[6]==3'd2)+(high_detect[7]==3'd2);
	color_count3 <= (high_detect[0]==3'd3)+(high_detect[1]==3'd3)+(high_detect[2]==3'd3)+(high_detect[3]==3'd3)+(high_detect[4]==3'd3)+(high_detect[5]==3'd3)+(high_detect[6]==3'd3)+(high_detect[7]==3'd3);
	color_count4 <= (high_detect[0]==3'd4)+(high_detect[1]==3'd4)+(high_detect[2]==3'd4)+(high_detect[3]==3'd4)+(high_detect[4]==3'd4)+(high_detect[5]==3'd4)+(high_detect[6]==3'd4)+(high_detect[7]==3'd4);
	color_count5 <= (high_detect[0]==3'd5)+(high_detect[1]==3'd5)+(high_detect[2]==3'd5)+(high_detect[3]==3'd5)+(high_detect[4]==3'd5)+(high_detect[5]==3'd5)+(high_detect[6]==3'd5)+(high_detect[7]==3'd5);
	color_count6 <= (high_detect[0]==3'd6)+(high_detect[1]==3'd6)+(high_detect[2]==3'd6)+(high_detect[3]==3'd6)+(high_detect[4]==3'd6)+(high_detect[5]==3'd6)+(high_detect[6]==3'd6)+(high_detect[7]==3'd6);
	color_count7 <= (high_detect[0]==3'd7)+(high_detect[1]==3'd7)+(high_detect[2]==3'd7)+(high_detect[3]==3'd7)+(high_detect[4]==3'd7)+(high_detect[5]==3'd7)+(high_detect[6]==3'd7)+(high_detect[7]==3'd7);
		
		end
		

		end
		


always_comb begin 

	if (~SWITCH_I[0]) begin
	SSD[0] = {2'b10, current_block[0]};
	SSD[1] = {2'b10, current_block[1]};
	SSD[2] = {2'b10, current_block[2]};
	SSD[3] = {2'b10, current_block[3]};
	SSD[4] = {2'b10, current_block[4]};
	SSD[5] = {2'b10, current_block[5]};
	SSD[6] = {2'b10, current_block[6]};
	SSD[7] = {2'b10, current_block[7]};

	end else
	// if (SWITCH_I[1])

	 begin
	//color_count[1]=4'b1000;
	SSD[0] = {1'b1, color_count0};
	SSD[1] = {1'b1, color_count1};
	SSD[2] = {1'b1, color_count2};
	SSD[3] = {1'b1, color_count3};
	SSD[4] = {1'b1, color_count4};
	SSD[5] = {1'b1, color_count5};
	SSD[6] = {1'b1, color_count6};
	SSD[7] = {1'b1, color_count7};



	 end
end

seven_seg_displays display_unit (
	.hex_values(SSD),
	.SEVEN_SEGMENT_N_O(SEVEN_SEGMENT_N_O)
);
endmodule
