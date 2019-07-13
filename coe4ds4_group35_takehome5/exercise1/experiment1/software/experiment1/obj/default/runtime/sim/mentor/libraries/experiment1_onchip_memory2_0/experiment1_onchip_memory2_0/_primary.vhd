library verilog;
use verilog.vl_types.all;
entity experiment1_onchip_memory2_0 is
    generic(
        INIT_FILE       : string  := "../experiment1_onchip_memory2_0.hex"
    );
    port(
        address         : in     vl_logic_vector(14 downto 0);
        byteenable      : in     vl_logic_vector(3 downto 0);
        chipselect      : in     vl_logic;
        clk             : in     vl_logic;
        clken           : in     vl_logic;
        reset           : in     vl_logic;
        write           : in     vl_logic;
        writedata       : in     vl_logic_vector(31 downto 0);
        readdata        : out    vl_logic_vector(31 downto 0)
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of INIT_FILE : constant is 1;
end experiment1_onchip_memory2_0;
