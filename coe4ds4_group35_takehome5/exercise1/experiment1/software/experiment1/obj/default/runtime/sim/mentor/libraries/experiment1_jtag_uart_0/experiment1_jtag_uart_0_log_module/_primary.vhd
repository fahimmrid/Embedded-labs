library verilog;
use verilog.vl_types.all;
entity experiment1_jtag_uart_0_log_module is
    port(
        clk             : in     vl_logic;
        data            : in     vl_logic_vector(7 downto 0);
        strobe          : in     vl_logic;
        valid           : in     vl_logic
    );
end experiment1_jtag_uart_0_log_module;
