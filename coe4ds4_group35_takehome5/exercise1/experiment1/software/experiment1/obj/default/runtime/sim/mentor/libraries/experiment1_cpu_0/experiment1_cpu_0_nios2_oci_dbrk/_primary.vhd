library verilog;
use verilog.vl_types.all;
entity experiment1_cpu_0_nios2_oci_dbrk is
    port(
        E_st_data       : in     vl_logic_vector(31 downto 0);
        av_ld_data_aligned_filtered: in     vl_logic_vector(31 downto 0);
        clk             : in     vl_logic;
        d_address       : in     vl_logic_vector(18 downto 0);
        d_read          : in     vl_logic;
        d_waitrequest   : in     vl_logic;
        d_write         : in     vl_logic;
        debugack        : in     vl_logic;
        reset_n         : in     vl_logic;
        cpu_d_address   : out    vl_logic_vector(18 downto 0);
        cpu_d_read      : out    vl_logic;
        cpu_d_readdata  : out    vl_logic_vector(31 downto 0);
        cpu_d_wait      : out    vl_logic;
        cpu_d_write     : out    vl_logic;
        cpu_d_writedata : out    vl_logic_vector(31 downto 0);
        dbrk_break      : out    vl_logic;
        dbrk_goto0      : out    vl_logic;
        dbrk_goto1      : out    vl_logic;
        dbrk_traceme    : out    vl_logic;
        dbrk_traceoff   : out    vl_logic;
        dbrk_traceon    : out    vl_logic;
        dbrk_trigout    : out    vl_logic
    );
end experiment1_cpu_0_nios2_oci_dbrk;
