library verilog;
use verilog.vl_types.all;
entity experiment1_cpu_0_nios2_oci_xbrk is
    port(
        D_valid         : in     vl_logic;
        E_valid         : in     vl_logic;
        F_pc            : in     vl_logic_vector(16 downto 0);
        clk             : in     vl_logic;
        reset_n         : in     vl_logic;
        trigger_state_0 : in     vl_logic;
        trigger_state_1 : in     vl_logic;
        xbrk_ctrl0      : in     vl_logic_vector(7 downto 0);
        xbrk_ctrl1      : in     vl_logic_vector(7 downto 0);
        xbrk_ctrl2      : in     vl_logic_vector(7 downto 0);
        xbrk_ctrl3      : in     vl_logic_vector(7 downto 0);
        xbrk_break      : out    vl_logic;
        xbrk_goto0      : out    vl_logic;
        xbrk_goto1      : out    vl_logic;
        xbrk_traceoff   : out    vl_logic;
        xbrk_traceon    : out    vl_logic;
        xbrk_trigout    : out    vl_logic
    );
end experiment1_cpu_0_nios2_oci_xbrk;
