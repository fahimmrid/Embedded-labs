// Code provided by Terasic with LCD / Camera modules
// Modified by Adam Kinsman, McMaster University, 2009

`timescale 1ns/100ps
`default_nettype none
`include "Sdram_Params.h"

module Sdram_Control_4Port (
	//	HOST Side
	input logic REF_CLK,					// System Clock
    input logic RESET_N,                    // System Reset
	output logic CLK,
	
	//	FIFO Write Side
    input logic [`DSIZE-1:0] WR1_DATA,		// Write Data Input 1
	input logic [`DSIZE-1:0] WR2_DATA,		// Write Data Input 2
	input logic WR,							// Write Request
	input logic WR_LOAD,					// Write Register Load / FIFO Clear
	input logic WR_CLK,						// Write FIFO Clock

	//	FIFO Read Side
    output logic [`DSIZE-1:0] RD1_DATA,		// Read Data Output 1
	output logic [`DSIZE-1:0] RD2_DATA,		// Read Data Output 2
	input logic RD,							// Read Request
	input logic RD_LOAD,					// Read Register Load / FIFO Clear
	input logic RD_CLK,						// Read FIFO Clock

	//	SDRAM Side
	output logic [11:0] SA,					// SDRAM Address
	output logic [1:0] BA,					// SDRAM Bank Address
    output logic CS_N,						// SDRAM Chip Selects
    output logic CKE,						// SDRAM Clock Enable
	output logic RAS_N,						// SDRAM Row Address Strobe
	output logic CAS_N,						// SDRAM Column Address Strobe
    output logic WE_N,						// SDRAM Write Enable
	inout wire [15:0] DQ,					// SDRAM Data Bus
    output logic [`DSIZE/8-1:0] DQM,		// SDRAM Data Mask Lines
	output logic SDR_CLK					// SDRAM Clock
);

// Internal Registers/Wires

// Controller
logic 	[`ASIZE-1:0] 	mADDR;			// Internal address
logic 	[8:0] 			mLENGTH;		// Internal length
logic 	[`ASIZE-1:0] 	rWR1_ADDR;		// Register write address				
logic 	[`ASIZE-1:0] 	rWR1_MAX_ADDR;	// Register max write address				
logic 	[8:0] 			rWR1_LENGTH;	// Register write length
logic 	[`ASIZE-1:0] 	rWR2_ADDR;		// Register write address				
logic 	[`ASIZE-1:0] 	rWR2_MAX_ADDR;	// Register max write address				
logic 	[8:0] 			rWR2_LENGTH;	// Register write length
logic 	[`ASIZE-1:0] 	rRD1_ADDR;		// Register read address
logic 	[`ASIZE-1:0] 	rRD1_MAX_ADDR;	// Register max read address
logic 	[8:0] 			rRD1_LENGTH;	// Register read length
logic 	[`ASIZE-1:0] 	rRD2_ADDR;		// Register read address
logic 	[`ASIZE-1:0] 	rRD2_MAX_ADDR;	// Register max read address
logic 	[8:0]			rRD2_LENGTH;	// Register read length
logic 	[1:0]			WR_MASK;		// Write port active mask
logic 	[1:0]			RD_MASK;		// Read port active mask
logic 					mWR_DONE;		// Flag write done, 1 pulse SDR_CLK
logic 					mRD_DONE;		// Flag read done, 1 pulse SDR_CLK
logic 					mWR,Pre_WR;		// Internal WR edge capture
logic 					mRD,Pre_RD;		// Internal RD edge capture
logic 	[9:0] 			ST;				// Controller status
logic 	[2:0] 			CMD;			// Controller command
logic 					PM_STOP;		// Flag page mode stop
logic 					PM_DONE;		// Flag page mode done
logic 					Read;			// Flag read active
logic 					Write;			// Flag write active
logic 	[`DSIZE-1:0] 	mDATAOUT;		// Controller Data output
logic 	[`DSIZE-1:0] 	mDATAIN;		// Controller Data input
logic 	[`DSIZE-1:0] 	mDATAIN1;		// Controller Data input 1
logic 	[`DSIZE-1:0] 	mDATAIN2;		// Controller Data input 2
logic 					CMDACK;			// Controller command acknowledgement

//	DRAM Control
logic 	[`DSIZE-1:0] 	DQOUT;			// SDRAM data out link
logic 	[`DSIZE/8-1:0] 	IDQM;			// SDRAM data mask lines
logic 	[11:0] 			ISA;			// SDRAM address output
logic 	[1:0] 			IBA;			// SDRAM bank address
logic 	[1:0] 			ICS_N;			// SDRAM Chip Selects
logic 					ICKE;			// SDRAM clock enable
logic 					IRAS_N;			// SDRAM Row address Strobe
logic 					ICAS_N;			// SDRAM Column address Strobe
logic 					IWE_N;			// SDRAM write enable

//	FIFO Control
logic 					OUT_VALID;		//Output data request to read side fifo
logic 					IN_REQ;			//Input	data request to write side fifo
logic 	[8:0] 			write_side_fifo_rusedw1;
logic 	[8:0] 			read_side_fifo_wusedw1;
logic 	[8:0] 			write_side_fifo_rusedw2;
logic 	[8:0] 			read_side_fifo_wusedw2;

//	DRAM Internal Control
logic 	[`ASIZE-1:0]	saddr;
logic 					load_mode;
logic 					nop;
logic 					reada;
logic 					writea;
logic 					refresh;
logic 					precharge;
logic 					oe;
logic 					ref_ack;
logic 					ref_req;
logic 					init_req;
logic 					cm_ack;
logic 					active;

logic WR1, WR2, RD1, RD2;
logic [`ASIZE-1:0] WR1_ADDR, WR2_ADDR, RD1_ADDR, RD2_ADDR;
logic [`ASIZE-1:0] WR1_MAX_ADDR, WR2_MAX_ADDR, RD1_MAX_ADDR, RD2_MAX_ADDR;
logic [8:0] WR1_LENGTH, WR2_LENGTH, RD1_LENGTH, RD2_LENGTH;
logic WR1_LOAD, WR2_LOAD, RD1_LOAD, RD2_LOAD;
logic WR1_CLK, WR2_CLK, RD1_CLK, RD2_CLK;
logic WR1_FULL, WR2_FULL, RD1_EMPTY, RD2_EMPTY;
logic [8:0] WR1_USE, WR2_USE, RD1_USE, RD2_USE;

//000000 - 0A0000
//100000 - 1A0000
//200000 - 2A0000
//3FFFFF

assign WR1 = WR; assign WR2 = WR; assign RD1 = RD; assign RD2 = RD; 
assign WR1_CLK = WR_CLK; assign WR2_CLK = WR_CLK; assign RD1_CLK = RD_CLK; assign RD2_CLK = RD_CLK;
assign WR1_ADDR = 23'd0; assign WR2_ADDR = 23'h100000; 
assign RD1_ADDR = 23'd0; assign RD2_ADDR = 23'h100000;
assign WR1_MAX_ADDR = 640*512; assign WR2_MAX_ADDR = 23'h100000+640*512; 
assign RD1_MAX_ADDR = 640*480; assign RD2_MAX_ADDR = 23'h100000+640*480; 
assign WR1_LENGTH = 9'h100; assign WR2_LENGTH = 9'h100;
assign RD1_LENGTH = 9'h100; assign RD2_LENGTH = 9'h100;
assign WR1_LOAD = WR_LOAD; assign WR2_LOAD = WR_LOAD;
assign RD1_LOAD = RD_LOAD; assign RD2_LOAD = RD_LOAD;

Sdram_PLL sdram_pll1 (
	.inclk0(REF_CLK),
	.c0(CLK),
	.c1(SDR_CLK)
);

control_interface control1 (
	.CLK(CLK),
	.RESET_N(RESET_N),
	.CMD(CMD),
	.ADDR(mADDR),
	.REF_ACK(ref_ack),
	.CM_ACK(cm_ack),
	.NOP(nop),
	.READA(reada),
	.WRITEA(writea),
	.REFRESH(refresh),
	.PRECHARGE(precharge),
	.LOAD_MODE(load_mode),
	.SADDR(saddr),
	.REF_REQ(ref_req),
	.INIT_REQ(init_req),
	.CMD_ACK(CMDACK)
);

command command1(
	.CLK(CLK),
	.RESET_N(RESET_N),
	.SADDR(saddr),
	.NOP(nop),
	.READA(reada),
	.WRITEA(writea),
	.REFRESH(refresh),
	.LOAD_MODE(load_mode),
	.PRECHARGE(precharge),
	.REF_REQ(ref_req),
	.INIT_REQ(init_req),
	.REF_ACK(ref_ack),
	.CM_ACK(cm_ack),
	.OE(oe),
	.PM_STOP(PM_STOP),
	.PM_DONE(PM_DONE),
	.SA(ISA),
	.BA(IBA),
	.CS_N(ICS_N),
	.CKE(ICKE),
	.RAS_N(IRAS_N),
	.CAS_N(ICAS_N),
	.WE_N(IWE_N)
);

logic [1:0] data_path1_DM;
assign data_path1_DM = 2'b00;
sdr_data_path data_path1(
	.CLK(CLK),
	.RESET_N(RESET_N),
	.DATAIN(mDATAIN),
	.DM(data_path1_DM),
	.DQOUT(DQOUT),
	.DQM(IDQM)
);

logic write_fifo1_rdreq;
assign write_fifo1_rdreq = IN_REQ & WR_MASK[0];
Sdram_WR_FIFO write_fifo1 (
	.data(WR1_DATA),
	.wrreq(WR1),
	.wrclk(WR1_CLK),
	.aclr(WR1_LOAD),
	.rdreq(write_fifo1_rdreq),
	.rdclk(CLK),
	.q(mDATAIN1),
	.wrfull(WR1_FULL),
	.wrusedw(WR1_USE),
	.rdusedw(write_side_fifo_rusedw1)
);

logic write_fifo2_rdreq;
assign write_fifo2_rdreq = IN_REQ & WR_MASK[1];
Sdram_WR_FIFO write_fifo2 (
	.data(WR2_DATA),
	.wrreq(WR2),
	.wrclk(WR2_CLK),
	.aclr(WR2_LOAD),
	.rdreq(write_fifo2_rdreq),
	.rdclk(CLK),
	.q(mDATAIN2),
	.wrfull(WR2_FULL),
	.wrusedw(WR2_USE),
	.rdusedw(write_side_fifo_rusedw2)
);
				
assign mDATAIN = (WR_MASK[0]) ?	mDATAIN1 : mDATAIN2;

logic read_fifo1_rdreq;
assign read_fifo1_rdreq = OUT_VALID & RD_MASK[0];
Sdram_RD_FIFO read_fifo1 (
	.data(mDATAOUT),
	.wrreq(read_fifo1_rdreq),
	.wrclk(CLK),
	.aclr(RD1_LOAD),
	.rdreq(RD1),
	.rdclk(RD1_CLK),
	.q(RD1_DATA),
	.wrusedw(read_side_fifo_wusedw1),
	.rdempty(RD1_EMPTY),
	.rdusedw(RD1_USE)
);
				
logic read_fifo2_rdreq;
assign read_fifo2_rdreq = OUT_VALID & RD_MASK[1];
Sdram_RD_FIFO read_fifo2 (
	.data(mDATAOUT),
	.wrreq(read_fifo2_rdreq),
	.wrclk(CLK),
	.aclr(RD2_LOAD),
	.rdreq(RD2),
	.rdclk(RD2_CLK),
	.q(RD2_DATA),
	.wrusedw(read_side_fifo_wusedw2),
	.rdempty(RD2_EMPTY),
	.rdusedw(RD2_USE)
);

always_ff @(posedge CLK) begin
	SA <= (ST == (SC_CL + mLENGTH)) ? 12'h200 : ISA;
	BA <= IBA;
	CS_N <= ICS_N[0];
	CKE <= ICKE;
	RAS_N <= (ST == (SC_CL + mLENGTH)) ? 1'b0 : IRAS_N;
	CAS_N <= (ST == (SC_CL + mLENGTH)) ? 1'b1 : ICAS_N;
	WE_N <= (ST == (SC_CL + mLENGTH)) ? 1'b0 : IWE_N;
	PM_STOP <= (ST == (SC_CL + mLENGTH)) ? 1'b1 : 1'b0;
	PM_DONE <= (ST == (SC_CL + SC_RCD + mLENGTH + 2)) ? 1'b1 : 1'b0;
	DQM <= ( active && (ST >= SC_CL) ) ?	
		( ((ST == (SC_CL + mLENGTH)) && Write) ? 2'b11 : 2'b00 ) : 2'b11 ;
	mDATAOUT <= DQ;
end

assign DQ = (oe) ? DQOUT : {`DSIZE{1'bz}};
assign active = Read | Write;

always_ff @ (posedge CLK or negedge RESET_N) begin
	if (~RESET_N) begin
		CMD <= 3'b000;
		ST <= 10'd0;
		Pre_RD <= 1'b0;
		Pre_WR <= 1'b0;
		Read <= 1'b0;
		Write <= 1'b0;
		OUT_VALID <= 1'b0;
		IN_REQ <= 1'b0;
		mWR_DONE <= 1'b0;
		mRD_DONE <= 1'b0;
	end else begin
		Pre_RD <= mRD; Pre_WR <= mWR;
		case (ST)
			10'd0 : begin
				if((Pre_RD == 1'b0) & (mRD == 1'b1)) begin
					Read <= 1'b1;
					Write <= 1'b0;
					CMD <= 3'b001;
					ST <= 10'd1;
				end else if ((Pre_WR == 1'b0) & (mWR == 1'b1)) begin
					Read <= 1'b0;
					Write <= 1'b1;
					CMD <= 3'b010;
					ST <= 10'd1;
				end
			end
			10'd1 : begin
				if (CMDACK == 1'b1) begin
					CMD <= 3'b000;
					ST <= 10'd2;
				end
			end
			default : begin	
				if(ST != (SC_CL + SC_RCD + mLENGTH + 1))
					ST <= ST + 10'd1;
				else ST <= 10'd0;
			end
		endcase
	
		if (Read) begin
			if (ST == (SC_CL + SC_RCD + 1))
				OUT_VALID <= 1'b1;
			else if(ST == (SC_CL + SC_RCD + mLENGTH + 1)) begin
				OUT_VALID <= 1'b0;
				Read <= 1'b0;
				mRD_DONE <= 1'b1;
			end
		end else mRD_DONE <= 1'b0;
		
		if (Write) begin
			if (ST == SC_CL-1)
				IN_REQ <= 1'b1;
			else if (ST == (SC_CL + mLENGTH - 1))
				IN_REQ <= 1'b0;
			else if (ST == (SC_CL + SC_RCD + mLENGTH)) begin
				Write <= 1'b0;
				mWR_DONE <= 1'b1;
			end
		end else mWR_DONE <= 1'b0;
	end
end

// Internal Address & Length Control
always_ff @(posedge CLK or negedge RESET_N) begin
	if (~RESET_N) begin
		rWR1_ADDR		<=	`ASIZE'd0;
		rWR1_MAX_ADDR	<=	640*512;
		rWR2_ADDR		<=	22'h100000;
		rWR2_MAX_ADDR	<=	22'h100000+640*512;

		rRD1_ADDR		<=	`ASIZE'd0;
		rRD1_MAX_ADDR	<=	640*480;
		rRD2_ADDR		<=	22'h100000;
		rRD2_MAX_ADDR	<=	22'h100000+640*480;
		
		rWR1_LENGTH		<=	128;
		rRD1_LENGTH		<=	128;
		rWR2_LENGTH		<=	128;
		rRD2_LENGTH		<=	128;
	end else begin
		//	Write Side 1
		if (WR1_LOAD) begin
			rWR1_ADDR <= WR1_ADDR;
			rWR1_LENGTH	<= WR1_LENGTH;
		end else if (mWR_DONE & WR_MASK[0]) begin
			if (rWR1_ADDR < (rWR1_MAX_ADDR - rWR1_LENGTH))
				rWR1_ADDR <= rWR1_ADDR + rWR1_LENGTH;
			else rWR1_ADDR <= WR1_ADDR;
		end
		
		//	Write Side 2
		if (WR2_LOAD) begin
			rWR2_ADDR <= WR2_ADDR;
			rWR2_LENGTH <= WR2_LENGTH;
		end else if(mWR_DONE & WR_MASK[1]) begin
			if (rWR2_ADDR < (rWR2_MAX_ADDR - rWR2_LENGTH))
				rWR2_ADDR <= rWR2_ADDR + rWR2_LENGTH;
			else rWR2_ADDR <= WR2_ADDR;
		end
		
		// Read Side 1
		if (RD1_LOAD) begin
			rRD1_ADDR <= RD1_ADDR;
			rRD1_LENGTH <= RD1_LENGTH;
		end else if (mRD_DONE & RD_MASK[0]) begin
			if(rRD1_ADDR < (rRD1_MAX_ADDR - rRD1_LENGTH))
				rRD1_ADDR <= rRD1_ADDR + rRD1_LENGTH;
			else rRD1_ADDR <= RD1_ADDR;
		end
		
		//	Read Side 2
		if (RD2_LOAD) begin
			rRD2_ADDR <= RD2_ADDR;
			rRD2_LENGTH <= RD2_LENGTH;
		end else if (mRD_DONE & RD_MASK[1]) begin
			if (rRD2_ADDR < (rRD2_MAX_ADDR - rRD2_LENGTH))
				rRD2_ADDR <= rRD2_ADDR + rRD2_LENGTH;
			else rRD2_ADDR <= RD2_ADDR;
		end
	end
end

// Auto Read/Write Control
always_ff @(posedge CLK or negedge RESET_N) begin
	if (~RESET_N) begin
		mWR <= 1'b0;
		mRD <= 1'b0;
		mADDR <= `ASIZE'd0;
		mLENGTH <= 9'd0;
	end else begin
		if(
			(mWR == 1'b0) & (mRD == 1'b0) & (ST == 10'd0) &&
			(WR_MASK == 2'b00) & (RD_MASK == 2'b00) &
			(WR1_LOAD == 1'b0) & (RD1_LOAD == 1'b0) &
			(WR2_LOAD == 1'b0) & (RD2_LOAD == 1'b0) 
		) begin
			if (read_side_fifo_wusedw1 < rRD1_LENGTH) begin
				// Read Side 1
				mADDR <= rRD1_ADDR;
				mLENGTH <= rRD1_LENGTH;
				WR_MASK <= 2'b00;
				RD_MASK	<= 2'b01;
				mWR <= 1'b0;
				mRD <= 1'b1;				
			end else if (read_side_fifo_wusedw2 < rRD2_LENGTH) begin
				//	Read Side 2
				mADDR <= rRD2_ADDR;
				mLENGTH <= rRD2_LENGTH;
				WR_MASK <= 2'b00;
				RD_MASK <= 2'b10;
				mWR <= 1'b0;
				mRD <= 1'b1;
			end else if ( ( rWR1_LENGTH != 9'd0) &
				(write_side_fifo_rusedw1 >= rWR1_LENGTH)
			) begin
				//	Write Side 1
				mADDR <= rWR1_ADDR;
				mLENGTH <= rWR1_LENGTH;
				WR_MASK <= 2'b01;
				RD_MASK <= 2'b00;
				mWR <= 1'b1;
				mRD <= 1'b0;
			end else if( ( rWR2_LENGTH != 9'd0) & 
				(write_side_fifo_rusedw2 >= rWR2_LENGTH)
			) begin
				//	Write Side 2
				mADDR <= rWR2_ADDR;
				mLENGTH <= rWR2_LENGTH;
				WR_MASK <= 2'b10;
				RD_MASK <= 2'b00;
				mWR <= 1'b1;
				mRD <= 1'b0;
			end
		end
		
		if (mWR_DONE) begin
			WR_MASK <= 2'b00;
			mWR <= 1'b0;
		end
		
		if (mRD_DONE) begin
			RD_MASK <= 2'b00;
			mRD <= 1'b0;
		end
	end
end

endmodule
