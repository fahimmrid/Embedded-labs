#************************************************************
# THIS IS A WIZARD-GENERATED FILE.                           
#
# Version 12.0 Build 263 08/02/2012 Service Pack 2 SJ Full Version
#
#************************************************************

# Copyright (C) 1991-2012 Altera Corporation
# Your use of Altera Corporation's design tools, logic functions 
# and other software and tools, and its AMPP partner logic 
# functions, and any output files from any of the foregoing 
# (including device programming or simulation files), and any 
# associated documentation or information are expressly subject 
# to the terms and conditions of the Altera Program License 
# Subscription Agreement, Altera MegaCore Function License 
# Agreement, or other applicable license agreement, including, 
# without limitation, that your use is for the sole purpose of 
# programming logic devices manufactured by Altera and sold by 
# Altera or its authorized distributors.  Please refer to the 
# applicable agreement for further details.



# Clock constraints

create_clock -name "C_50MHz" -period 20.000ns [get_ports {CLOCK_50_I}]


# Automatically constrain PLL and other generated clocks
derive_pll_clocks -create_base_clocks

# Automatically calculate clock uncertainty to jitter and other effects.
#derive_clock_uncertainty
# Not supported for family Cyclone II

# tsu/th constraints

# set_input_delay -clock "C_50MHz" -max 6ns [get_ports {GPIO_1[10]}] 
# set_input_delay -clock "C_50MHz" -min 5ns [get_ports {GPIO_1[10]}] 

# tco constraints

# set_output_delay -clock "C_50MHz" -max 6ns [get_ports {GPIO_1[11] GPIO_1[14]}] 
# set_output_delay -clock "C_50MHz" -min 5ns [get_ports {GPIO_1[11] GPIO_1[14]}] 


# tpd constraints

