
# (C) 2001-2019 Altera Corporation. All rights reserved.
# Your use of Altera Corporation's design tools, logic functions and 
# other software and tools, and its AMPP partner logic functions, and 
# any output files any of the foregoing (including device programming 
# or simulation files), and any associated documentation or information 
# are expressly subject to the terms and conditions of the Altera 
# Program License Subscription Agreement, Altera MegaCore Function 
# License Agreement, or other applicable license agreement, including, 
# without limitation, that your use is for the sole purpose of 
# programming logic devices manufactured by Altera and sold by Altera 
# or its authorized distributors. Please refer to the applicable 
# agreement for further details.

# ACDS 12.0sp2 263 linux 2019.02.28.20:38:41

# ----------------------------------------
# vcs - auto-generated simulation script

# ----------------------------------------
# initialize variables
TOP_LEVEL_NAME="experiment1"
SKIP_FILE_COPY=0
QSYS_SIMDIR="./../../"
SKIP_ELAB=0
SKIP_SIM=0
USER_DEFINED_ELAB_OPTIONS=""
USER_DEFINED_SIM_OPTIONS="+vcs+finish+100"
# ----------------------------------------
# overwrite variables - DO NOT MODIFY!
# This block evaluates each command line argument, typically used for 
# overwriting variables. An example usage:
#   sh <simulator>_setup.sh SKIP_ELAB=1 SKIP_SIM=1
for expression in "$@"; do
  eval $expression
  if [ $? -ne 0 ]; then
    echo "Error: This command line argument, \"$expression\", is/has an invalid expression." >&2
    exit $?
  fi
done

# ----------------------------------------
# copy RAM/ROM files to simulation directory
if [ $SKIP_FILE_COPY -eq 0 ]; then
  cp -f /home/ECE/fahimr/Desktop/experiment1/experiment1/simulation/submodules/experiment1_cpu_0_rf_ram_b.mif ./
  cp -f /home/ECE/fahimr/Desktop/experiment1/experiment1/simulation/submodules/experiment1_cpu_0_rf_ram_a.mif ./
  cp -f /home/ECE/fahimr/Desktop/experiment1/experiment1/simulation/submodules/experiment1_cpu_0_ociram_default_contents.mif ./
  cp -f /home/ECE/fahimr/Desktop/experiment1/experiment1/simulation/submodules/experiment1_cpu_0_ociram_default_contents.dat ./
  cp -f /home/ECE/fahimr/Desktop/experiment1/experiment1/simulation/submodules/experiment1_cpu_0_rf_ram_a.dat ./
  cp -f /home/ECE/fahimr/Desktop/experiment1/experiment1/simulation/submodules/experiment1_cpu_0_rf_ram_b.dat ./
  cp -f /home/ECE/fahimr/Desktop/experiment1/experiment1/simulation/submodules/experiment1_cpu_0_rf_ram_a.hex ./
  cp -f /home/ECE/fahimr/Desktop/experiment1/experiment1/simulation/submodules/experiment1_cpu_0_ociram_default_contents.hex ./
  cp -f /home/ECE/fahimr/Desktop/experiment1/experiment1/simulation/submodules/experiment1_cpu_0_rf_ram_b.hex ./
  cp -f /home/ECE/fahimr/Desktop/experiment1/experiment1/simulation/submodules/experiment1_onchip_memory2_0.hex ./
  cp -f /home/ECE/fahimr/Desktop/experiment1/software/experiment1/mem_init/hdl_sim/experiment1_onchip_memory2_0.dat ./
  cp -f /home/ECE/fahimr/Desktop/experiment1/software/experiment1/mem_init/experiment1_onchip_memory2_0.hex ./
fi

vcs -lca -timescale=1ps/1ps -sverilog +verilog2001ext+.v -ntb_opts dtm $USER_DEFINED_ELAB_OPTIONS \
  -v /tools/altera/12.0/quartus/eda/sim_lib/altera_primitives.v \
  -v /tools/altera/12.0/quartus/eda/sim_lib/220model.v \
  -v /tools/altera/12.0/quartus/eda/sim_lib/sgate.v \
  -v /tools/altera/12.0/quartus/eda/sim_lib/altera_mf.v \
  /tools/altera/12.0/quartus/eda/sim_lib/altera_lnsim.sv \
  -v /tools/altera/12.0/quartus/eda/sim_lib/cycloneii_atoms.v \
  /home/ECE/fahimr/Desktop/experiment1/experiment1/simulation/submodules/experiment1_irq_mapper.sv \
  /home/ECE/fahimr/Desktop/experiment1/experiment1/simulation/submodules/altera_merlin_arbitrator.sv \
  /home/ECE/fahimr/Desktop/experiment1/experiment1/simulation/submodules/experiment1_rsp_xbar_mux_001.sv \
  /home/ECE/fahimr/Desktop/experiment1/experiment1/simulation/submodules/experiment1_rsp_xbar_mux.sv \
  /home/ECE/fahimr/Desktop/experiment1/experiment1/simulation/submodules/experiment1_rsp_xbar_demux_002.sv \
  /home/ECE/fahimr/Desktop/experiment1/experiment1/simulation/submodules/experiment1_cmd_xbar_mux.sv \
  /home/ECE/fahimr/Desktop/experiment1/experiment1/simulation/submodules/experiment1_cmd_xbar_demux_001.sv \
  /home/ECE/fahimr/Desktop/experiment1/experiment1/simulation/submodules/experiment1_cmd_xbar_demux.sv \
  /home/ECE/fahimr/Desktop/experiment1/experiment1/simulation/submodules/altera_reset_controller.v \
  /home/ECE/fahimr/Desktop/experiment1/experiment1/simulation/submodules/altera_reset_synchronizer.v \
  /home/ECE/fahimr/Desktop/experiment1/experiment1/simulation/submodules/experiment1_id_router_002.sv \
  /home/ECE/fahimr/Desktop/experiment1/experiment1/simulation/submodules/experiment1_id_router.sv \
  /home/ECE/fahimr/Desktop/experiment1/experiment1/simulation/submodules/experiment1_addr_router_001.sv \
  /home/ECE/fahimr/Desktop/experiment1/experiment1/simulation/submodules/experiment1_addr_router.sv \
  /home/ECE/fahimr/Desktop/experiment1/experiment1/simulation/submodules/altera_avalon_sc_fifo.v \
  /home/ECE/fahimr/Desktop/experiment1/experiment1/simulation/submodules/altera_merlin_slave_agent.sv \
  /home/ECE/fahimr/Desktop/experiment1/experiment1/simulation/submodules/altera_merlin_burst_uncompressor.sv \
  /home/ECE/fahimr/Desktop/experiment1/experiment1/simulation/submodules/altera_merlin_master_agent.sv \
  /home/ECE/fahimr/Desktop/experiment1/experiment1/simulation/submodules/altera_merlin_slave_translator.sv \
  /home/ECE/fahimr/Desktop/experiment1/experiment1/simulation/submodules/altera_merlin_master_translator.sv \
  /home/ECE/fahimr/Desktop/experiment1/experiment1/simulation/submodules/custom_counter_component.sv \
  /home/ECE/fahimr/Desktop/experiment1/experiment1/simulation/submodules/custom_counter_unit.sv \
  /home/ECE/fahimr/Desktop/experiment1/experiment1/simulation/submodules/experiment1_LED_GREEN_O.v \
  /home/ECE/fahimr/Desktop/experiment1/experiment1/simulation/submodules/experiment1_LED_RED_O.v \
  /home/ECE/fahimr/Desktop/experiment1/experiment1/simulation/submodules/experiment1_PUSH_BUTTON_I.v \
  /home/ECE/fahimr/Desktop/experiment1/experiment1/simulation/submodules/experiment1_SWITCH_I.v \
  /home/ECE/fahimr/Desktop/experiment1/experiment1/simulation/submodules/experiment1_jtag_uart_0.v \
  /home/ECE/fahimr/Desktop/experiment1/experiment1/simulation/submodules/experiment1_cpu_0_jtag_debug_module_sysclk.v \
  /home/ECE/fahimr/Desktop/experiment1/experiment1/simulation/submodules/experiment1_cpu_0_jtag_debug_module_wrapper.v \
  /home/ECE/fahimr/Desktop/experiment1/experiment1/simulation/submodules/experiment1_cpu_0_oci_test_bench.v \
  /home/ECE/fahimr/Desktop/experiment1/experiment1/simulation/submodules/experiment1_cpu_0.v \
  /home/ECE/fahimr/Desktop/experiment1/experiment1/simulation/submodules/experiment1_cpu_0_test_bench.v \
  /home/ECE/fahimr/Desktop/experiment1/experiment1/simulation/submodules/experiment1_cpu_0_jtag_debug_module_tck.v \
  /home/ECE/fahimr/Desktop/experiment1/experiment1/simulation/submodules/experiment1_onchip_memory2_0.v \
  /home/ECE/fahimr/Desktop/experiment1/experiment1/simulation/experiment1.v \
  -top $TOP_LEVEL_NAME
# ----------------------------------------
# simulate
if [ $SKIP_SIM -eq 0 ]; then
  ./simv $USER_DEFINED_SIM_OPTIONS
fi
