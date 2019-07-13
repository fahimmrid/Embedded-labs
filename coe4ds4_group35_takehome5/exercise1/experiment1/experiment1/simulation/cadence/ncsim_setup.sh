
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

# ACDS 12.0sp2 263 linux 2019.02.28.20:31:01

# ----------------------------------------
# ncsim - auto-generated simulation script

# ----------------------------------------
# initialize variables
TOP_LEVEL_NAME="experiment1"
QSYS_SIMDIR="./../"
SKIP_FILE_COPY=0
SKIP_DEV_COM=0
SKIP_COM=0
SKIP_ELAB=0
SKIP_SIM=0
USER_DEFINED_ELAB_OPTIONS=""
USER_DEFINED_SIM_OPTIONS="-input \"@run 100; exit\""

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
# create compilation libraries
mkdir -p ./libraries/work/
mkdir -p ./libraries/experiment1_irq_mapper/
mkdir -p ./libraries/experiment1_rsp_xbar_mux_001/
mkdir -p ./libraries/experiment1_rsp_xbar_mux/
mkdir -p ./libraries/experiment1_rsp_xbar_demux_002/
mkdir -p ./libraries/experiment1_cmd_xbar_mux/
mkdir -p ./libraries/experiment1_cmd_xbar_demux_001/
mkdir -p ./libraries/experiment1_cmd_xbar_demux/
mkdir -p ./libraries/experiment1_rst_controller/
mkdir -p ./libraries/experiment1_id_router_002/
mkdir -p ./libraries/experiment1_id_router/
mkdir -p ./libraries/experiment1_addr_router_001/
mkdir -p ./libraries/experiment1_addr_router/
mkdir -p ./libraries/experiment1_cpu_0_jtag_debug_module_translator_avalon_universal_slave_0_agent_rsp_fifo/
mkdir -p ./libraries/experiment1_cpu_0_jtag_debug_module_translator_avalon_universal_slave_0_agent/
mkdir -p ./libraries/experiment1_cpu_0_instruction_master_translator_avalon_universal_master_0_agent/
mkdir -p ./libraries/experiment1_cpu_0_jtag_debug_module_translator/
mkdir -p ./libraries/experiment1_cpu_0_instruction_master_translator/
mkdir -p ./libraries/experiment1_custom_counter_component_0/
mkdir -p ./libraries/experiment1_LED_GREEN_O/
mkdir -p ./libraries/experiment1_LED_RED_O/
mkdir -p ./libraries/experiment1_PUSH_BUTTON_I/
mkdir -p ./libraries/experiment1_SWITCH_I/
mkdir -p ./libraries/experiment1_jtag_uart_0/
mkdir -p ./libraries/experiment1_cpu_0/
mkdir -p ./libraries/experiment1_onchip_memory2_0/
mkdir -p ./libraries/altera_ver/
mkdir -p ./libraries/lpm_ver/
mkdir -p ./libraries/sgate_ver/
mkdir -p ./libraries/altera_mf_ver/
mkdir -p ./libraries/altera_lnsim_ver/
mkdir -p ./libraries/cycloneii_ver/

# ----------------------------------------
# copy RAM/ROM files to simulation directory
if [ $SKIP_FILE_COPY -eq 0 ]; then
  cp -f $QSYS_SIMDIR/submodules/experiment1_cpu_0_rf_ram_b.mif ./
  cp -f $QSYS_SIMDIR/submodules/experiment1_cpu_0_rf_ram_a.mif ./
  cp -f $QSYS_SIMDIR/submodules/experiment1_cpu_0_ociram_default_contents.mif ./
  cp -f $QSYS_SIMDIR/submodules/experiment1_cpu_0_ociram_default_contents.dat ./
  cp -f $QSYS_SIMDIR/submodules/experiment1_cpu_0_rf_ram_a.dat ./
  cp -f $QSYS_SIMDIR/submodules/experiment1_cpu_0_rf_ram_b.dat ./
  cp -f $QSYS_SIMDIR/submodules/experiment1_cpu_0_rf_ram_a.hex ./
  cp -f $QSYS_SIMDIR/submodules/experiment1_cpu_0_ociram_default_contents.hex ./
  cp -f $QSYS_SIMDIR/submodules/experiment1_cpu_0_rf_ram_b.hex ./
  cp -f $QSYS_SIMDIR/submodules/experiment1_onchip_memory2_0.hex ./
fi

# ----------------------------------------
# compile device library files
if [ $SKIP_DEV_COM -eq 0 ]; then
  ncvlog     "/tools/altera/12.0/quartus/eda/sim_lib/altera_primitives.v" -work altera_ver      
  ncvlog     "/tools/altera/12.0/quartus/eda/sim_lib/220model.v"          -work lpm_ver         
  ncvlog     "/tools/altera/12.0/quartus/eda/sim_lib/sgate.v"             -work sgate_ver       
  ncvlog     "/tools/altera/12.0/quartus/eda/sim_lib/altera_mf.v"         -work altera_mf_ver   
  ncvlog -sv "/tools/altera/12.0/quartus/eda/sim_lib/altera_lnsim.sv"     -work altera_lnsim_ver
  ncvlog     "/tools/altera/12.0/quartus/eda/sim_lib/cycloneii_atoms.v"   -work cycloneii_ver   
fi

# ----------------------------------------
# compile design files in correct order
if [ $SKIP_COM -eq 0 ]; then
  ncvlog -sv "$QSYS_SIMDIR/submodules/experiment1_irq_mapper.sv"                     -work experiment1_irq_mapper                                                                 -cdslib ./cds_libs/experiment1_irq_mapper.cds.lib                                                                
  ncvlog -sv "$QSYS_SIMDIR/submodules/altera_merlin_arbitrator.sv"                   -work experiment1_rsp_xbar_mux_001                                                           -cdslib ./cds_libs/experiment1_rsp_xbar_mux_001.cds.lib                                                          
  ncvlog -sv "$QSYS_SIMDIR/submodules/experiment1_rsp_xbar_mux_001.sv"               -work experiment1_rsp_xbar_mux_001                                                           -cdslib ./cds_libs/experiment1_rsp_xbar_mux_001.cds.lib                                                          
  ncvlog -sv "$QSYS_SIMDIR/submodules/altera_merlin_arbitrator.sv"                   -work experiment1_rsp_xbar_mux                                                               -cdslib ./cds_libs/experiment1_rsp_xbar_mux.cds.lib                                                              
  ncvlog -sv "$QSYS_SIMDIR/submodules/experiment1_rsp_xbar_mux.sv"                   -work experiment1_rsp_xbar_mux                                                               -cdslib ./cds_libs/experiment1_rsp_xbar_mux.cds.lib                                                              
  ncvlog -sv "$QSYS_SIMDIR/submodules/experiment1_rsp_xbar_demux_002.sv"             -work experiment1_rsp_xbar_demux_002                                                         -cdslib ./cds_libs/experiment1_rsp_xbar_demux_002.cds.lib                                                        
  ncvlog -sv "$QSYS_SIMDIR/submodules/altera_merlin_arbitrator.sv"                   -work experiment1_cmd_xbar_mux                                                               -cdslib ./cds_libs/experiment1_cmd_xbar_mux.cds.lib                                                              
  ncvlog -sv "$QSYS_SIMDIR/submodules/experiment1_cmd_xbar_mux.sv"                   -work experiment1_cmd_xbar_mux                                                               -cdslib ./cds_libs/experiment1_cmd_xbar_mux.cds.lib                                                              
  ncvlog -sv "$QSYS_SIMDIR/submodules/experiment1_cmd_xbar_demux_001.sv"             -work experiment1_cmd_xbar_demux_001                                                         -cdslib ./cds_libs/experiment1_cmd_xbar_demux_001.cds.lib                                                        
  ncvlog -sv "$QSYS_SIMDIR/submodules/experiment1_cmd_xbar_demux.sv"                 -work experiment1_cmd_xbar_demux                                                             -cdslib ./cds_libs/experiment1_cmd_xbar_demux.cds.lib                                                            
  ncvlog     "$QSYS_SIMDIR/submodules/altera_reset_controller.v"                     -work experiment1_rst_controller                                                             -cdslib ./cds_libs/experiment1_rst_controller.cds.lib                                                            
  ncvlog     "$QSYS_SIMDIR/submodules/altera_reset_synchronizer.v"                   -work experiment1_rst_controller                                                             -cdslib ./cds_libs/experiment1_rst_controller.cds.lib                                                            
  ncvlog -sv "$QSYS_SIMDIR/submodules/experiment1_id_router_002.sv"                  -work experiment1_id_router_002                                                              -cdslib ./cds_libs/experiment1_id_router_002.cds.lib                                                             
  ncvlog -sv "$QSYS_SIMDIR/submodules/experiment1_id_router.sv"                      -work experiment1_id_router                                                                  -cdslib ./cds_libs/experiment1_id_router.cds.lib                                                                 
  ncvlog -sv "$QSYS_SIMDIR/submodules/experiment1_addr_router_001.sv"                -work experiment1_addr_router_001                                                            -cdslib ./cds_libs/experiment1_addr_router_001.cds.lib                                                           
  ncvlog -sv "$QSYS_SIMDIR/submodules/experiment1_addr_router.sv"                    -work experiment1_addr_router                                                                -cdslib ./cds_libs/experiment1_addr_router.cds.lib                                                               
  ncvlog     "$QSYS_SIMDIR/submodules/altera_avalon_sc_fifo.v"                       -work experiment1_cpu_0_jtag_debug_module_translator_avalon_universal_slave_0_agent_rsp_fifo -cdslib ./cds_libs/experiment1_cpu_0_jtag_debug_module_translator_avalon_universal_slave_0_agent_rsp_fifo.cds.lib
  ncvlog -sv "$QSYS_SIMDIR/submodules/altera_merlin_slave_agent.sv"                  -work experiment1_cpu_0_jtag_debug_module_translator_avalon_universal_slave_0_agent          -cdslib ./cds_libs/experiment1_cpu_0_jtag_debug_module_translator_avalon_universal_slave_0_agent.cds.lib         
  ncvlog -sv "$QSYS_SIMDIR/submodules/altera_merlin_burst_uncompressor.sv"           -work experiment1_cpu_0_jtag_debug_module_translator_avalon_universal_slave_0_agent          -cdslib ./cds_libs/experiment1_cpu_0_jtag_debug_module_translator_avalon_universal_slave_0_agent.cds.lib         
  ncvlog -sv "$QSYS_SIMDIR/submodules/altera_merlin_master_agent.sv"                 -work experiment1_cpu_0_instruction_master_translator_avalon_universal_master_0_agent        -cdslib ./cds_libs/experiment1_cpu_0_instruction_master_translator_avalon_universal_master_0_agent.cds.lib       
  ncvlog -sv "$QSYS_SIMDIR/submodules/altera_merlin_slave_translator.sv"             -work experiment1_cpu_0_jtag_debug_module_translator                                         -cdslib ./cds_libs/experiment1_cpu_0_jtag_debug_module_translator.cds.lib                                        
  ncvlog -sv "$QSYS_SIMDIR/submodules/altera_merlin_master_translator.sv"            -work experiment1_cpu_0_instruction_master_translator                                        -cdslib ./cds_libs/experiment1_cpu_0_instruction_master_translator.cds.lib                                       
  ncvlog -sv "$QSYS_SIMDIR/submodules/custom_counter_component.sv"                   -work experiment1_custom_counter_component_0                                                 -cdslib ./cds_libs/experiment1_custom_counter_component_0.cds.lib                                                
  ncvlog -sv "$QSYS_SIMDIR/submodules/custom_counter_unit.sv"                        -work experiment1_custom_counter_component_0                                                 -cdslib ./cds_libs/experiment1_custom_counter_component_0.cds.lib                                                
  ncvlog     "$QSYS_SIMDIR/submodules/experiment1_LED_GREEN_O.v"                     -work experiment1_LED_GREEN_O                                                                -cdslib ./cds_libs/experiment1_LED_GREEN_O.cds.lib                                                               
  ncvlog     "$QSYS_SIMDIR/submodules/experiment1_LED_RED_O.v"                       -work experiment1_LED_RED_O                                                                  -cdslib ./cds_libs/experiment1_LED_RED_O.cds.lib                                                                 
  ncvlog     "$QSYS_SIMDIR/submodules/experiment1_PUSH_BUTTON_I.v"                   -work experiment1_PUSH_BUTTON_I                                                              -cdslib ./cds_libs/experiment1_PUSH_BUTTON_I.cds.lib                                                             
  ncvlog     "$QSYS_SIMDIR/submodules/experiment1_SWITCH_I.v"                        -work experiment1_SWITCH_I                                                                   -cdslib ./cds_libs/experiment1_SWITCH_I.cds.lib                                                                  
  ncvlog     "$QSYS_SIMDIR/submodules/experiment1_jtag_uart_0.v"                     -work experiment1_jtag_uart_0                                                                -cdslib ./cds_libs/experiment1_jtag_uart_0.cds.lib                                                               
  ncvlog     "$QSYS_SIMDIR/submodules/experiment1_cpu_0_jtag_debug_module_sysclk.v"  -work experiment1_cpu_0                                                                      -cdslib ./cds_libs/experiment1_cpu_0.cds.lib                                                                     
  ncvlog     "$QSYS_SIMDIR/submodules/experiment1_cpu_0_jtag_debug_module_wrapper.v" -work experiment1_cpu_0                                                                      -cdslib ./cds_libs/experiment1_cpu_0.cds.lib                                                                     
  ncvlog     "$QSYS_SIMDIR/submodules/experiment1_cpu_0_oci_test_bench.v"            -work experiment1_cpu_0                                                                      -cdslib ./cds_libs/experiment1_cpu_0.cds.lib                                                                     
  ncvlog     "$QSYS_SIMDIR/submodules/experiment1_cpu_0.v"                           -work experiment1_cpu_0                                                                      -cdslib ./cds_libs/experiment1_cpu_0.cds.lib                                                                     
  ncvlog     "$QSYS_SIMDIR/submodules/experiment1_cpu_0_test_bench.v"                -work experiment1_cpu_0                                                                      -cdslib ./cds_libs/experiment1_cpu_0.cds.lib                                                                     
  ncvlog     "$QSYS_SIMDIR/submodules/experiment1_cpu_0_jtag_debug_module_tck.v"     -work experiment1_cpu_0                                                                      -cdslib ./cds_libs/experiment1_cpu_0.cds.lib                                                                     
  ncvlog     "$QSYS_SIMDIR/submodules/experiment1_onchip_memory2_0.v"                -work experiment1_onchip_memory2_0                                                           -cdslib ./cds_libs/experiment1_onchip_memory2_0.cds.lib                                                          
  ncvlog     "$QSYS_SIMDIR/experiment1.v"                                                                                                                                                                                                                                                          
fi

# ----------------------------------------
# elaborate top level design
if [ $SKIP_ELAB -eq 0 ]; then
  ncelab -access +w+r+c -namemap_mixgen $USER_DEFINED_ELAB_OPTIONS $TOP_LEVEL_NAME
fi

# ----------------------------------------
# simulate
if [ $SKIP_SIM -eq 0 ]; then
  eval ncsim $USER_DEFINED_SIM_OPTIONS $TOP_LEVEL_NAME
fi
