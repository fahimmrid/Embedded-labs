library verilog;
use verilog.vl_types.all;
entity experiment1_cpu_0_oci_test_bench is
    port(
        dct_buffer      : in     vl_logic_vector(29 downto 0);
        dct_count       : in     vl_logic_vector(3 downto 0);
        test_ending     : in     vl_logic;
        test_has_ended  : in     vl_logic
    );
end experiment1_cpu_0_oci_test_bench;
