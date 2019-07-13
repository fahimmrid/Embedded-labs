library verilog;
use verilog.vl_types.all;
entity custom_counter_unit is
    port(
        clock           : in     vl_logic;
        resetn          : in     vl_logic;
        reset_counter   : in     vl_logic;
        load            : in     vl_logic;
        load_config     : in     vl_logic_vector(1 downto 0);
        counter_value   : out    vl_logic_vector(25 downto 0);
        counter_expire  : out    vl_logic
    );
end custom_counter_unit;
