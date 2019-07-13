
# (C) 2001-2018 Altera Corporation. All rights reserved.
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

# ACDS 12.0sp2 263 linux 2018.02.10.17:38:51

# ----------------------------------------
# Auto-generated simulation script

# ----------------------------------------
# Initialize the variable
if ![info exists SYSTEM_INSTANCE_NAME] { 
  set SYSTEM_INSTANCE_NAME ""
} elseif { ![ string match "" $SYSTEM_INSTANCE_NAME ] } { 
  set SYSTEM_INSTANCE_NAME "/$SYSTEM_INSTANCE_NAME"
} 

if ![info exists TOP_LEVEL_NAME] { 
  set TOP_LEVEL_NAME "experiment1"
} elseif { ![ string match "" $TOP_LEVEL_NAME ] } { 
  set TOP_LEVEL_NAME "$TOP_LEVEL_NAME"
} 

if ![info exists QSYS_SIMDIR] { 
  set QSYS_SIMDIR "./../"
} elseif { ![ string match "" $QSYS_SIMDIR ] } { 
  set QSYS_SIMDIR "$QSYS_SIMDIR"
} 


# ----------------------------------------
# Copy ROM/RAM files to simulation directory
file copy -force /home/ECE/arfeenh/Desktop/coe4ds4_lab5_2018/experiment1/experiment1/simulation/submodules/experiment1_cpu_0_rf_ram_b.mif ./
file copy -force /home/ECE/arfeenh/Desktop/coe4ds4_lab5_2018/experiment1/experiment1/simulation/submodules/experiment1_cpu_0_rf_ram_a.mif ./
file copy -force /home/ECE/arfeenh/Desktop/coe4ds4_lab5_2018/experiment1/experiment1/simulation/submodules/experiment1_cpu_0_ociram_default_contents.mif ./
file copy -force /home/ECE/arfeenh/Desktop/coe4ds4_lab5_2018/experiment1/experiment1/simulation/submodules/experiment1_cpu_0_ociram_default_contents.dat ./
file copy -force /home/ECE/arfeenh/Desktop/coe4ds4_lab5_2018/experiment1/experiment1/simulation/submodules/experiment1_cpu_0_rf_ram_a.dat ./
file copy -force /home/ECE/arfeenh/Desktop/coe4ds4_lab5_2018/experiment1/experiment1/simulation/submodules/experiment1_cpu_0_rf_ram_b.dat ./
file copy -force /home/ECE/arfeenh/Desktop/coe4ds4_lab5_2018/experiment1/experiment1/simulation/submodules/experiment1_cpu_0_rf_ram_a.hex ./
file copy -force /home/ECE/arfeenh/Desktop/coe4ds4_lab5_2018/experiment1/experiment1/simulation/submodules/experiment1_cpu_0_ociram_default_contents.hex ./
file copy -force /home/ECE/arfeenh/Desktop/coe4ds4_lab5_2018/experiment1/experiment1/simulation/submodules/experiment1_cpu_0_rf_ram_b.hex ./
file copy -force /home/ECE/arfeenh/Desktop/coe4ds4_lab5_2018/experiment1/experiment1/simulation/submodules/experiment1_onchip_memory2_0.hex ./
file copy -force /home/ECE/arfeenh/Desktop/coe4ds4_lab5_2018/experiment1/software/experiment1/mem_init/hdl_sim/experiment1_onchip_memory2_0.dat ./
file copy -force /home/ECE/arfeenh/Desktop/coe4ds4_lab5_2018/experiment1/software/experiment1/mem_init/experiment1_onchip_memory2_0.hex ./

# ----------------------------------------
# Create compilation libraries
proc ensure_lib { lib } { if ![file isdirectory $lib] { vlib $lib } }
ensure_lib      ./libraries/     
ensure_lib      ./libraries/work/
vmap       work ./libraries/work/
if { ![ string match "*ModelSim ALTERA*" [ vsim -version ] ] } {
  ensure_lib                  ./libraries/altera_ver/      
  vmap       altera_ver       ./libraries/altera_ver/      
  ensure_lib                  ./libraries/lpm_ver/         
  vmap       lpm_ver          ./libraries/lpm_ver/         
  ensure_lib                  ./libraries/sgate_ver/       
  vmap       sgate_ver        ./libraries/sgate_ver/       
  ensure_lib                  ./libraries/altera_mf_ver/   
  vmap       altera_mf_ver    ./libraries/altera_mf_ver/   
  ensure_lib                  ./libraries/altera_lnsim_ver/
  vmap       altera_lnsim_ver ./libraries/altera_lnsim_ver/
  ensure_lib                  ./libraries/cycloneii_ver/   
  vmap       cycloneii_ver    ./libraries/cycloneii_ver/   
}
ensure_lib                                                                                        ./libraries/experiment1_irq_mapper/                                                                
vmap       experiment1_irq_mapper                                                                 ./libraries/experiment1_irq_mapper/                                                                
ensure_lib                                                                                        ./libraries/experiment1_rsp_xbar_mux_001/                                                          
vmap       experiment1_rsp_xbar_mux_001                                                           ./libraries/experiment1_rsp_xbar_mux_001/                                                          
ensure_lib                                                                                        ./libraries/experiment1_rsp_xbar_mux/                                                              
vmap       experiment1_rsp_xbar_mux                                                               ./libraries/experiment1_rsp_xbar_mux/                                                              
ensure_lib                                                                                        ./libraries/experiment1_rsp_xbar_demux_002/                                                        
vmap       experiment1_rsp_xbar_demux_002                                                         ./libraries/experiment1_rsp_xbar_demux_002/                                                        
ensure_lib                                                                                        ./libraries/experiment1_cmd_xbar_mux/                                                              
vmap       experiment1_cmd_xbar_mux                                                               ./libraries/experiment1_cmd_xbar_mux/                                                              
ensure_lib                                                                                        ./libraries/experiment1_cmd_xbar_demux_001/                                                        
vmap       experiment1_cmd_xbar_demux_001                                                         ./libraries/experiment1_cmd_xbar_demux_001/                                                        
ensure_lib                                                                                        ./libraries/experiment1_cmd_xbar_demux/                                                            
vmap       experiment1_cmd_xbar_demux                                                             ./libraries/experiment1_cmd_xbar_demux/                                                            
ensure_lib                                                                                        ./libraries/experiment1_rst_controller/                                                            
vmap       experiment1_rst_controller                                                             ./libraries/experiment1_rst_controller/                                                            
ensure_lib                                                                                        ./libraries/experiment1_id_router_002/                                                             
vmap       experiment1_id_router_002                                                              ./libraries/experiment1_id_router_002/                                                             
ensure_lib                                                                                        ./libraries/experiment1_id_router/                                                                 
vmap       experiment1_id_router                                                                  ./libraries/experiment1_id_router/                                                                 
ensure_lib                                                                                        ./libraries/experiment1_addr_router_001/                                                           
vmap       experiment1_addr_router_001                                                            ./libraries/experiment1_addr_router_001/                                                           
ensure_lib                                                                                        ./libraries/experiment1_addr_router/                                                               
vmap       experiment1_addr_router                                                                ./libraries/experiment1_addr_router/                                                               
ensure_lib                                                                                        ./libraries/experiment1_cpu_0_jtag_debug_module_translator_avalon_universal_slave_0_agent_rsp_fifo/
vmap       experiment1_cpu_0_jtag_debug_module_translator_avalon_universal_slave_0_agent_rsp_fifo ./libraries/experiment1_cpu_0_jtag_debug_module_translator_avalon_universal_slave_0_agent_rsp_fifo/
ensure_lib                                                                                        ./libraries/experiment1_cpu_0_jtag_debug_module_translator_avalon_universal_slave_0_agent/         
vmap       experiment1_cpu_0_jtag_debug_module_translator_avalon_universal_slave_0_agent          ./libraries/experiment1_cpu_0_jtag_debug_module_translator_avalon_universal_slave_0_agent/         
ensure_lib                                                                                        ./libraries/experiment1_cpu_0_instruction_master_translator_avalon_universal_master_0_agent/       
vmap       experiment1_cpu_0_instruction_master_translator_avalon_universal_master_0_agent        ./libraries/experiment1_cpu_0_instruction_master_translator_avalon_universal_master_0_agent/       
ensure_lib                                                                                        ./libraries/experiment1_cpu_0_jtag_debug_module_translator/                                        
vmap       experiment1_cpu_0_jtag_debug_module_translator                                         ./libraries/experiment1_cpu_0_jtag_debug_module_translator/                                        
ensure_lib                                                                                        ./libraries/experiment1_cpu_0_instruction_master_translator/                                       
vmap       experiment1_cpu_0_instruction_master_translator                                        ./libraries/experiment1_cpu_0_instruction_master_translator/                                       
ensure_lib                                                                                        ./libraries/experiment1_SWITCH_I/                                                                  
vmap       experiment1_SWITCH_I                                                                   ./libraries/experiment1_SWITCH_I/                                                                  
ensure_lib                                                                                        ./libraries/experiment1_custom_counter_component_0/                                                
vmap       experiment1_custom_counter_component_0                                                 ./libraries/experiment1_custom_counter_component_0/                                                
ensure_lib                                                                                        ./libraries/experiment1_LED_GREEN_O/                                                               
vmap       experiment1_LED_GREEN_O                                                                ./libraries/experiment1_LED_GREEN_O/                                                               
ensure_lib                                                                                        ./libraries/experiment1_LED_RED_O/                                                                 
vmap       experiment1_LED_RED_O                                                                  ./libraries/experiment1_LED_RED_O/                                                                 
ensure_lib                                                                                        ./libraries/experiment1_PUSH_BUTTON_I/                                                             
vmap       experiment1_PUSH_BUTTON_I                                                              ./libraries/experiment1_PUSH_BUTTON_I/                                                             
ensure_lib                                                                                        ./libraries/experiment1_jtag_uart_0/                                                               
vmap       experiment1_jtag_uart_0                                                                ./libraries/experiment1_jtag_uart_0/                                                               
ensure_lib                                                                                        ./libraries/experiment1_cpu_0/                                                                     
vmap       experiment1_cpu_0                                                                      ./libraries/experiment1_cpu_0/                                                                     
ensure_lib                                                                                        ./libraries/experiment1_onchip_memory2_0/                                                          
vmap       experiment1_onchip_memory2_0                                                           ./libraries/experiment1_onchip_memory2_0/                                                          

# ----------------------------------------
# Compile device library files
alias dev_com {
  echo "\[exec\] dev_com"
  if { ![ string match "*ModelSim ALTERA*" [ vsim -version ] ] } {
    vlog     "/tools/altera/12.0/quartus/eda/sim_lib/altera_primitives.v" -work altera_ver      
    vlog     "/tools/altera/12.0/quartus/eda/sim_lib/220model.v"          -work lpm_ver         
    vlog     "/tools/altera/12.0/quartus/eda/sim_lib/sgate.v"             -work sgate_ver       
    vlog     "/tools/altera/12.0/quartus/eda/sim_lib/altera_mf.v"         -work altera_mf_ver   
    vlog -sv "/tools/altera/12.0/quartus/eda/sim_lib/altera_lnsim.sv"     -work altera_lnsim_ver
    vlog     "/tools/altera/12.0/quartus/eda/sim_lib/cycloneii_atoms.v"   -work cycloneii_ver   
  }
}

# ----------------------------------------
# Compile the design files in correct order
alias com {
  echo "\[exec\] com"
  vlog -sv "/home/ECE/arfeenh/Desktop/coe4ds4_lab5_2018/experiment1/experiment1/simulation/submodules/experiment1_irq_mapper.sv"                     -work experiment1_irq_mapper                                                                
  vlog -sv "/home/ECE/arfeenh/Desktop/coe4ds4_lab5_2018/experiment1/experiment1/simulation/submodules/altera_merlin_arbitrator.sv"                   -work experiment1_rsp_xbar_mux_001                                                          
  vlog -sv "/home/ECE/arfeenh/Desktop/coe4ds4_lab5_2018/experiment1/experiment1/simulation/submodules/experiment1_rsp_xbar_mux_001.sv"               -work experiment1_rsp_xbar_mux_001                                                          
  vlog -sv "/home/ECE/arfeenh/Desktop/coe4ds4_lab5_2018/experiment1/experiment1/simulation/submodules/altera_merlin_arbitrator.sv"                   -work experiment1_rsp_xbar_mux                                                              
  vlog -sv "/home/ECE/arfeenh/Desktop/coe4ds4_lab5_2018/experiment1/experiment1/simulation/submodules/experiment1_rsp_xbar_mux.sv"                   -work experiment1_rsp_xbar_mux                                                              
  vlog -sv "/home/ECE/arfeenh/Desktop/coe4ds4_lab5_2018/experiment1/experiment1/simulation/submodules/experiment1_rsp_xbar_demux_002.sv"             -work experiment1_rsp_xbar_demux_002                                                        
  vlog -sv "/home/ECE/arfeenh/Desktop/coe4ds4_lab5_2018/experiment1/experiment1/simulation/submodules/altera_merlin_arbitrator.sv"                   -work experiment1_cmd_xbar_mux                                                              
  vlog -sv "/home/ECE/arfeenh/Desktop/coe4ds4_lab5_2018/experiment1/experiment1/simulation/submodules/experiment1_cmd_xbar_mux.sv"                   -work experiment1_cmd_xbar_mux                                                              
  vlog -sv "/home/ECE/arfeenh/Desktop/coe4ds4_lab5_2018/experiment1/experiment1/simulation/submodules/experiment1_cmd_xbar_demux_001.sv"             -work experiment1_cmd_xbar_demux_001                                                        
  vlog -sv "/home/ECE/arfeenh/Desktop/coe4ds4_lab5_2018/experiment1/experiment1/simulation/submodules/experiment1_cmd_xbar_demux.sv"                 -work experiment1_cmd_xbar_demux                                                            
  vlog     "/home/ECE/arfeenh/Desktop/coe4ds4_lab5_2018/experiment1/experiment1/simulation/submodules/altera_reset_controller.v"                     -work experiment1_rst_controller                                                            
  vlog     "/home/ECE/arfeenh/Desktop/coe4ds4_lab5_2018/experiment1/experiment1/simulation/submodules/altera_reset_synchronizer.v"                   -work experiment1_rst_controller                                                            
  vlog -sv "/home/ECE/arfeenh/Desktop/coe4ds4_lab5_2018/experiment1/experiment1/simulation/submodules/experiment1_id_router_002.sv"                  -work experiment1_id_router_002                                                             
  vlog -sv "/home/ECE/arfeenh/Desktop/coe4ds4_lab5_2018/experiment1/experiment1/simulation/submodules/experiment1_id_router.sv"                      -work experiment1_id_router                                                                 
  vlog -sv "/home/ECE/arfeenh/Desktop/coe4ds4_lab5_2018/experiment1/experiment1/simulation/submodules/experiment1_addr_router_001.sv"                -work experiment1_addr_router_001                                                           
  vlog -sv "/home/ECE/arfeenh/Desktop/coe4ds4_lab5_2018/experiment1/experiment1/simulation/submodules/experiment1_addr_router.sv"                    -work experiment1_addr_router                                                               
  vlog     "/home/ECE/arfeenh/Desktop/coe4ds4_lab5_2018/experiment1/experiment1/simulation/submodules/altera_avalon_sc_fifo.v"                       -work experiment1_cpu_0_jtag_debug_module_translator_avalon_universal_slave_0_agent_rsp_fifo
  vlog -sv "/home/ECE/arfeenh/Desktop/coe4ds4_lab5_2018/experiment1/experiment1/simulation/submodules/altera_merlin_slave_agent.sv"                  -work experiment1_cpu_0_jtag_debug_module_translator_avalon_universal_slave_0_agent         
  vlog -sv "/home/ECE/arfeenh/Desktop/coe4ds4_lab5_2018/experiment1/experiment1/simulation/submodules/altera_merlin_burst_uncompressor.sv"           -work experiment1_cpu_0_jtag_debug_module_translator_avalon_universal_slave_0_agent         
  vlog -sv "/home/ECE/arfeenh/Desktop/coe4ds4_lab5_2018/experiment1/experiment1/simulation/submodules/altera_merlin_master_agent.sv"                 -work experiment1_cpu_0_instruction_master_translator_avalon_universal_master_0_agent       
  vlog -sv "/home/ECE/arfeenh/Desktop/coe4ds4_lab5_2018/experiment1/experiment1/simulation/submodules/altera_merlin_slave_translator.sv"             -work experiment1_cpu_0_jtag_debug_module_translator                                        
  vlog -sv "/home/ECE/arfeenh/Desktop/coe4ds4_lab5_2018/experiment1/experiment1/simulation/submodules/altera_merlin_master_translator.sv"            -work experiment1_cpu_0_instruction_master_translator                                       
  vlog     "/home/ECE/arfeenh/Desktop/coe4ds4_lab5_2018/experiment1/experiment1/simulation/submodules/experiment1_SWITCH_I.v"                        -work experiment1_SWITCH_I                                                                  
  vlog -sv "/home/ECE/arfeenh/Desktop/coe4ds4_lab5_2018/experiment1/experiment1/simulation/submodules/custom_counter_component.sv"                   -work experiment1_custom_counter_component_0                                                
  vlog -sv "/home/ECE/arfeenh/Desktop/coe4ds4_lab5_2018/experiment1/experiment1/simulation/submodules/custom_counter_unit.sv"                        -work experiment1_custom_counter_component_0                                                
  vlog     "/home/ECE/arfeenh/Desktop/coe4ds4_lab5_2018/experiment1/experiment1/simulation/submodules/experiment1_LED_GREEN_O.v"                     -work experiment1_LED_GREEN_O                                                               
  vlog     "/home/ECE/arfeenh/Desktop/coe4ds4_lab5_2018/experiment1/experiment1/simulation/submodules/experiment1_LED_RED_O.v"                       -work experiment1_LED_RED_O                                                                 
  vlog     "/home/ECE/arfeenh/Desktop/coe4ds4_lab5_2018/experiment1/experiment1/simulation/submodules/experiment1_PUSH_BUTTON_I.v"                   -work experiment1_PUSH_BUTTON_I                                                             
  vlog     "/home/ECE/arfeenh/Desktop/coe4ds4_lab5_2018/experiment1/experiment1/simulation/submodules/experiment1_jtag_uart_0.v"                     -work experiment1_jtag_uart_0                                                               
  vlog     "/home/ECE/arfeenh/Desktop/coe4ds4_lab5_2018/experiment1/experiment1/simulation/submodules/experiment1_cpu_0_jtag_debug_module_sysclk.v"  -work experiment1_cpu_0                                                                     
  vlog     "/home/ECE/arfeenh/Desktop/coe4ds4_lab5_2018/experiment1/experiment1/simulation/submodules/experiment1_cpu_0_jtag_debug_module_wrapper.v" -work experiment1_cpu_0                                                                     
  vlog     "/home/ECE/arfeenh/Desktop/coe4ds4_lab5_2018/experiment1/experiment1/simulation/submodules/experiment1_cpu_0_oci_test_bench.v"            -work experiment1_cpu_0                                                                     
  vlog     "/home/ECE/arfeenh/Desktop/coe4ds4_lab5_2018/experiment1/experiment1/simulation/submodules/experiment1_cpu_0.v"                           -work experiment1_cpu_0                                                                     
  vlog     "/home/ECE/arfeenh/Desktop/coe4ds4_lab5_2018/experiment1/experiment1/simulation/submodules/experiment1_cpu_0_test_bench.v"                -work experiment1_cpu_0                                                                     
  vlog     "/home/ECE/arfeenh/Desktop/coe4ds4_lab5_2018/experiment1/experiment1/simulation/submodules/experiment1_cpu_0_jtag_debug_module_tck.v"     -work experiment1_cpu_0                                                                     
  vlog     "/home/ECE/arfeenh/Desktop/coe4ds4_lab5_2018/experiment1/experiment1/simulation/submodules/experiment1_onchip_memory2_0.v"                -work experiment1_onchip_memory2_0                                                          
  vlog     "/home/ECE/arfeenh/Desktop/coe4ds4_lab5_2018/experiment1/experiment1/simulation/experiment1.v"                                                                                                                                        
}

# ----------------------------------------
# Elaborate top level design
alias elab {
  echo "\[exec\] elab"
  vsim -t ps \
    -G/$TOP_LEVEL_NAME$SYSTEM_INSTANCE_NAME/onchip_memory2_0/INIT_FILE=\"/home/ECE/arfeenh/Desktop/coe4ds4_lab5_2018/experiment1/software/experiment1/mem_init/experiment1_onchip_memory2_0.hex\" \
     -L work -L experiment1_irq_mapper -L experiment1_rsp_xbar_mux_001 -L experiment1_rsp_xbar_mux -L experiment1_rsp_xbar_demux_002 -L experiment1_cmd_xbar_mux -L experiment1_cmd_xbar_demux_001 -L experiment1_cmd_xbar_demux -L experiment1_rst_controller -L experiment1_id_router_002 -L experiment1_id_router -L experiment1_addr_router_001 -L experiment1_addr_router -L experiment1_cpu_0_jtag_debug_module_translator_avalon_universal_slave_0_agent_rsp_fifo -L experiment1_cpu_0_jtag_debug_module_translator_avalon_universal_slave_0_agent -L experiment1_cpu_0_instruction_master_translator_avalon_universal_master_0_agent -L experiment1_cpu_0_jtag_debug_module_translator -L experiment1_cpu_0_instruction_master_translator -L experiment1_SWITCH_I -L experiment1_custom_counter_component_0 -L experiment1_LED_GREEN_O -L experiment1_LED_RED_O -L experiment1_PUSH_BUTTON_I -L experiment1_jtag_uart_0 -L experiment1_cpu_0 -L experiment1_onchip_memory2_0 -L altera_ver -L lpm_ver -L sgate_ver -L altera_mf_ver -L altera_lnsim_ver -L cycloneii_ver $TOP_LEVEL_NAME
}

# ----------------------------------------
# Elaborate the top level design with novopt option
alias elab_debug {
  echo "\[exec\] elab_debug"
  vsim -novopt -t ps \
    -G/$TOP_LEVEL_NAME$SYSTEM_INSTANCE_NAME/onchip_memory2_0/INIT_FILE=\"/home/ECE/arfeenh/Desktop/coe4ds4_lab5_2018/experiment1/software/experiment1/mem_init/experiment1_onchip_memory2_0.hex\" \
     -L work -L experiment1_irq_mapper -L experiment1_rsp_xbar_mux_001 -L experiment1_rsp_xbar_mux -L experiment1_rsp_xbar_demux_002 -L experiment1_cmd_xbar_mux -L experiment1_cmd_xbar_demux_001 -L experiment1_cmd_xbar_demux -L experiment1_rst_controller -L experiment1_id_router_002 -L experiment1_id_router -L experiment1_addr_router_001 -L experiment1_addr_router -L experiment1_cpu_0_jtag_debug_module_translator_avalon_universal_slave_0_agent_rsp_fifo -L experiment1_cpu_0_jtag_debug_module_translator_avalon_universal_slave_0_agent -L experiment1_cpu_0_instruction_master_translator_avalon_universal_master_0_agent -L experiment1_cpu_0_jtag_debug_module_translator -L experiment1_cpu_0_instruction_master_translator -L experiment1_SWITCH_I -L experiment1_custom_counter_component_0 -L experiment1_LED_GREEN_O -L experiment1_LED_RED_O -L experiment1_PUSH_BUTTON_I -L experiment1_jtag_uart_0 -L experiment1_cpu_0 -L experiment1_onchip_memory2_0 -L altera_ver -L lpm_ver -L sgate_ver -L altera_mf_ver -L altera_lnsim_ver -L cycloneii_ver $TOP_LEVEL_NAME
}

# ----------------------------------------
# Compile all the design files and elaborate the top level design
alias ld "
  dev_com
  com
  elab
"

# ----------------------------------------
# Compile all the design files and elaborate the top level design with -novopt
alias ld_debug "
  dev_com
  com
  elab_debug
"

# ----------------------------------------
# Print out user commmand line aliases
alias h {
  echo "List Of Command Line Aliases"
  echo
  echo "dev_com                       -- Compile device library files"
  echo
  echo "com                           -- Compile the design files in correct order"
  echo
  echo "elab                          -- Elaborate top level design"
  echo
  echo "elab_debug                    -- Elaborate the top level design with novopt option"
  echo
  echo "ld                            -- Compile all the design files and elaborate the top level design"
  echo
  echo "ld_debug                      -- Compile all the design files and elaborate the top level design with -novopt"
  echo
  echo 
  echo
  echo "List Of Variables"
  echo
  echo "TOP_LEVEL_NAME                -- Top level module name."
  echo
  echo "SYSTEM_INSTANCE_NAME          -- Instantiated system module name inside top level module."
  echo
  echo "QSYS_SIMDIR                   -- Qsys base simulation directory."
}
h
