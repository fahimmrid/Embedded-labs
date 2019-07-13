library verilog;
use verilog.vl_types.all;
entity experiment1_PUSH_BUTTON_I is
    port(
        address         : in     vl_logic_vector(1 downto 0);
        chipselect      : in     vl_logic;
        clk             : in     vl_logic;
        in_port         : in     vl_logic_vector(3 downto 0);
        reset_n         : in     vl_logic;
        write_n         : in     vl_logic;
        writedata       : in     vl_logic_vector(31 downto 0);
        irq             : out    vl_logic;
        readdata        : out    vl_logic_vector(31 downto 0)
    );
end experiment1_PUSH_BUTTON_I;
