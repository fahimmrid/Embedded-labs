library verilog;
use verilog.vl_types.all;
entity experiment1 is
    port(
        push_button_i_external_connection_export: in     vl_logic_vector(3 downto 0);
        switch_i_external_connection_export: in     vl_logic_vector(16 downto 0);
        led_red_o_external_connection_export: out    vl_logic_vector(17 downto 0);
        clock_50_i_clk_in_reset_reset_n: in     vl_logic;
        led_green_o_external_connection_export: out    vl_logic_vector(8 downto 0);
        clock_50_i_clk_in_clk: in     vl_logic
    );
end experiment1;
