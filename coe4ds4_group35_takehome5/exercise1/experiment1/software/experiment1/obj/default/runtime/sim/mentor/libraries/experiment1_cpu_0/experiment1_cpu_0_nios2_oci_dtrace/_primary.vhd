library verilog;
use verilog.vl_types.all;
entity experiment1_cpu_0_nios2_oci_dtrace is
    port(
        clk             : in     vl_logic;
        cpu_d_address   : in     vl_logic_vector(18 downto 0);
        cpu_d_read      : in     vl_logic;
        cpu_d_readdata  : in     vl_logic_vector(31 downto 0);
        cpu_d_wait      : in     vl_logic;
        cpu_d_write     : in     vl_logic;
        cpu_d_writedata : in     vl_logic_vector(31 downto 0);
        jrst_n          : in     vl_logic;
        trc_ctrl        : in     vl_logic_vector(15 downto 0);
        atm             : out    vl_logic_vector(35 downto 0);
        dtm             : out    vl_logic_vector(35 downto 0)
    );
end experiment1_cpu_0_nios2_oci_dtrace;
