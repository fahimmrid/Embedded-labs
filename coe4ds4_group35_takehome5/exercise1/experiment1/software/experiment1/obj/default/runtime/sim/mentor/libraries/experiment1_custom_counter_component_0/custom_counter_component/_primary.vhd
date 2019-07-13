library verilog;
use verilog.vl_types.all;
entity custom_counter_component is
    port(
        clock           : in     vl_logic;
        resetn          : in     vl_logic;
        address         : in     vl_logic_vector(1 downto 0);
        chipselect      : in     vl_logic;
        read            : in     vl_logic;
        write           : in     vl_logic;
        readdata        : out    vl_logic_vector(31 downto 0);
        writedata       : in     vl_logic_vector(31 downto 0);
        counter_expire_irq: out    vl_logic
    );
end custom_counter_component;
