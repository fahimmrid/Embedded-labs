// (C) 2001-2012 Altera Corporation. All rights reserved.
// Your use of Altera Corporation's design tools, logic functions and other 
// software and tools, and its AMPP partner logic functions, and any output 
// files any of the foregoing (including device programming or simulation 
// files), and any associated documentation or information are expressly subject 
// to the terms and conditions of the Altera Program License Subscription 
// Agreement, Altera MegaCore Function License Agreement, or other applicable 
// license agreement, including, without limitation, that your use is for the 
// sole purpose of programming logic devices manufactured by Altera and sold by 
// Altera or its authorized distributors.  Please refer to the applicable 
// agreement for further details.


// $Id: //acds/rel/12.0/ip/merlin/altera_merlin_router/altera_merlin_router.sv.terp#1 $
// $Revision: #1 $
// $Date: 2012/02/13 $
// $Author: swbranch $

// -------------------------------------------------------
// Merlin Router
//
// Asserts the appropriate one-hot encoded channel based on 
// either (a) the address or (b) the dest id. The DECODER_TYPE
// parameter controls this behaviour. 0 means address decoder,
// 1 means dest id decoder.
//
// In the case of (a), it also sets the destination id.
// -------------------------------------------------------

`timescale 1 ns / 1 ns

module experiment3_addr_router_001_default_decode
  #(
     parameter DEFAULT_CHANNEL = 1,
               DEFAULT_DESTID = 1 
   )
  (output [83 - 80 : 0] default_destination_id,
   output [12-1 : 0] default_src_channel
  );

  assign default_destination_id = 
    DEFAULT_DESTID[83 - 80 : 0];
  generate begin : default_decode
    if (DEFAULT_CHANNEL == -1)
      assign default_src_channel = '0;
    else
      assign default_src_channel = 12'b1 << DEFAULT_CHANNEL;
  end endgenerate

endmodule


module experiment3_addr_router_001
(
    // -------------------
    // Clock & Reset
    // -------------------
    input clk,
    input reset,

    // -------------------
    // Command Sink (Input)
    // -------------------
    input                       sink_valid,
    input  [94-1 : 0]    sink_data,
    input                       sink_startofpacket,
    input                       sink_endofpacket,
    output                      sink_ready,

    // -------------------
    // Command Source (Output)
    // -------------------
    output                          src_valid,
    output reg [94-1    : 0] src_data,
    output reg [12-1 : 0] src_channel,
    output                          src_startofpacket,
    output                          src_endofpacket,
    input                           src_ready
);

    // -------------------------------------------------------
    // Local parameters and variables
    // -------------------------------------------------------
    localparam PKT_ADDR_H = 56;
    localparam PKT_ADDR_L = 36;
    localparam PKT_DEST_ID_H = 83;
    localparam PKT_DEST_ID_L = 80;
    localparam ST_DATA_W = 94;
    localparam ST_CHANNEL_W = 12;
    localparam DECODER_TYPE = 0;

    localparam PKT_TRANS_WRITE = 59;
    localparam PKT_TRANS_READ  = 60;

    localparam PKT_ADDR_W = PKT_ADDR_H-PKT_ADDR_L + 1;
    localparam PKT_DEST_ID_W = PKT_DEST_ID_H-PKT_DEST_ID_L + 1;




    // -------------------------------------------------------
    // Figure out the number of bits to mask off for each slave span
    // during address decoding
    // -------------------------------------------------------
    localparam PAD0 = log2ceil(32'h400 - 32'h0);
    localparam PAD1 = log2ceil(32'h100000 - 32'h80000);
    localparam PAD2 = log2ceil(32'h102000 - 32'h100000);
    localparam PAD3 = log2ceil(32'h104000 - 32'h102000);
    localparam PAD4 = log2ceil(32'h105000 - 32'h104800);
    localparam PAD5 = log2ceil(32'h105440 - 32'h105400);
    localparam PAD6 = log2ceil(32'h105480 - 32'h105440);
    localparam PAD7 = log2ceil(32'h105490 - 32'h105480);
    localparam PAD8 = log2ceil(32'h1054a0 - 32'h105490);
    localparam PAD9 = log2ceil(32'h1054b0 - 32'h1054a0);
    localparam PAD10 = log2ceil(32'h1054c0 - 32'h1054b0);
    localparam PAD11 = log2ceil(32'h1054c8 - 32'h1054c0);

    // -------------------------------------------------------
    // Work out which address bits are significant based on the
    // address range of the slaves. If the required width is too
    // large or too small, we use the address field width instead.
    // -------------------------------------------------------
    localparam ADDR_RANGE = 32'h1054c8;
    localparam RANGE_ADDR_WIDTH = log2ceil(ADDR_RANGE);
    localparam OPTIMIZED_ADDR_H = (RANGE_ADDR_WIDTH > PKT_ADDR_W) ||
                                  (RANGE_ADDR_WIDTH == 0) ?
                                        PKT_ADDR_H :
                                        PKT_ADDR_L + RANGE_ADDR_WIDTH - 1;
    localparam RG = RANGE_ADDR_WIDTH-1;

      wire [PKT_ADDR_W-1 : 0] address = sink_data[OPTIMIZED_ADDR_H : PKT_ADDR_L];

    // -------------------------------------------------------
    // Pass almost everything through, untouched
    // -------------------------------------------------------
    assign sink_ready        = src_ready;
    assign src_valid         = sink_valid;
    assign src_startofpacket = sink_startofpacket;
    assign src_endofpacket   = sink_endofpacket;

    wire [PKT_DEST_ID_W-1:0] default_destid;
    wire [12-1 : 0] default_src_channel;




    experiment3_addr_router_001_default_decode the_default_decode(
      .default_destination_id (default_destid),
      .default_src_channel (default_src_channel)
    );

    always @* begin
        src_data    = sink_data;
        src_channel = default_src_channel;

        src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = default_destid;
        // --------------------------------------------------
        // Address Decoder
        // Sets the channel and destination ID based on the address
        // --------------------------------------------------

        // ( 0x0 .. 0x400 )
        if ( {address[RG:PAD0],{PAD0{1'b0}}} == 'h0 ) begin
            src_channel = 12'b100000000000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 11;
        end

        // ( 0x80000 .. 0x100000 )
        if ( {address[RG:PAD1],{PAD1{1'b0}}} == 'h80000 ) begin
            src_channel = 12'b000000000010;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 1;
        end

        // ( 0x100000 .. 0x102000 )
        if ( {address[RG:PAD2],{PAD2{1'b0}}} == 'h100000 ) begin
            src_channel = 12'b000000000100;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 2;
        end

        // ( 0x102000 .. 0x104000 )
        if ( {address[RG:PAD3],{PAD3{1'b0}}} == 'h102000 ) begin
            src_channel = 12'b000000001000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 3;
        end

        // ( 0x104800 .. 0x105000 )
        if ( {address[RG:PAD4],{PAD4{1'b0}}} == 'h104800 ) begin
            src_channel = 12'b000000000001;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 0;
        end

        // ( 0x105400 .. 0x105440 )
        if ( {address[RG:PAD5],{PAD5{1'b0}}} == 'h105400 ) begin
            src_channel = 12'b000000010000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 4;
        end

        // ( 0x105440 .. 0x105480 )
        if ( {address[RG:PAD6],{PAD6{1'b0}}} == 'h105440 ) begin
            src_channel = 12'b000000100000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 5;
        end

        // ( 0x105480 .. 0x105490 )
        if ( {address[RG:PAD7],{PAD7{1'b0}}} == 'h105480 ) begin
            src_channel = 12'b000001000000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 6;
        end

        // ( 0x105490 .. 0x1054a0 )
        if ( {address[RG:PAD8],{PAD8{1'b0}}} == 'h105490 ) begin
            src_channel = 12'b000010000000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 7;
        end

        // ( 0x1054a0 .. 0x1054b0 )
        if ( {address[RG:PAD9],{PAD9{1'b0}}} == 'h1054a0 ) begin
            src_channel = 12'b000100000000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 8;
        end

        // ( 0x1054b0 .. 0x1054c0 )
        if ( {address[RG:PAD10],{PAD10{1'b0}}} == 'h1054b0 ) begin
            src_channel = 12'b001000000000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 9;
        end

        // ( 0x1054c0 .. 0x1054c8 )
        if ( {address[RG:PAD11],{PAD11{1'b0}}} == 'h1054c0 ) begin
            src_channel = 12'b010000000000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 10;
        end
    end

    // --------------------------------------------------
    // Ceil(log2()) function
    // --------------------------------------------------
    function integer log2ceil;
        input reg[63:0] val;
        reg [63:0] i;

        begin
            i = 1;
            log2ceil = 0;

            while (i < val) begin
                log2ceil = log2ceil + 1;
                i = i << 1;
            end
        end
    endfunction

endmodule


