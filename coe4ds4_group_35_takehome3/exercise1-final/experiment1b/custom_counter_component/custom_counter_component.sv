////////////////////////
// CODE SECTION BEGIN //
////////////////////////

// Define the component module
module custom_counter_component (
	input logic clock,
	input logic resetn,

	input  logic [1:0] 	address,
	input  logic 		chipselect,
	input  logic 		read,
	input  logic 		write,
	output logic [31:0]	readdata,
	input  logic [31:0]	writedata,
	
	output logic counter_expire_irq
);

// Declare internal signals for connecting to the custom_counter_unit
logic reset_counter, load;
logic [26:0] counter_value;
logic [1:0] load_config;
logic counter_expire_buf, counter_expire;

// For getting the data from NIOS through IOWR in software
// Offset address 1 is used to reset the counter
// Offset address 3 is used to buffer the "load_config" info
always_ff @ (posedge clock or negedge resetn) begin
	if (!resetn) begin
		reset_counter <= 'd0;
		load <= 1'b0;
		load_config <= 'd0;
	end else begin
		load <= 1'b0;
		if (chipselect & write) begin
			case (address)
			'd1: reset_counter <= writedata[0];
			'd3: begin
				load <= 1'b1;
				load_config <= writedata[1:0];
			end
			endcase
		end
	end
end

// For sending information to NIOS using IORD in software
// Offset address 0 is used to send the counter value
// Offset address 1 is used to send the data in the "reset_counter" signal
// Offset address 2 is used to send the data in the "counter_expire" signal
// Offset address 3 is used to send the data in the "load_config" signal
always_ff @ (posedge clock or negedge resetn) begin
	if (!resetn) begin
		readdata <= 'd0;
	end else begin
		if (chipselect & read) begin
			case (address)
			'd0: readdata <= {5'd0, counter_value};
			'd1: readdata <= {31'd0, reset_counter};
			'd2: readdata <= {31'd0, counter_expire};
			'd3: readdata <= {31'd0, load_config};
			endcase
		end
	end
end

// For generating interrupt when the counter expires
// Offset address 2 is used to clear the interrupt
always_ff @ (posedge clock or negedge resetn) begin
	if (!resetn) begin
		counter_expire_buf <= 1'b0;
	end else begin
		counter_expire_buf <= counter_expire;
			
		if (counter_expire & ~counter_expire_buf) counter_expire_irq <= 1'b1;
		if (chipselect & write & address == 'd2) counter_expire_irq <= 1'b0;
	end
end

// Instantiate the counter
custom_counter_unit custom_counter_unit_inst (
	.clock(clock),
	.resetn(resetn),
	.reset_counter(reset_counter),
	.load(load),
	.load_config(load_config),
	.counter_value(counter_value),
	
	.counter_expire(counter_expire)
);

endmodule

////////////////////////
// CODE SECTION END   //
////////////////////////
