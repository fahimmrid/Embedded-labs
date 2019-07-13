Copyright by Phil Kinsman, Adam Kinsman, Henry Ko and Nicola Nicolici
Developed for the Embedded Systems course (COE4DS4)
Department of Electrical and Computer Engineering
McMaster University, Ontario, Canada

This file contains instructions for creating a NIOS system that can be simulated using Modelsim

Top Level Toolflow
==================

The toolflow for hardware/software co-design using Altera Nios has 4 main tools:

1. Quartus (for the hardware project)
2. Qsys (for system generation)
3. Nios SDK (for the software project)
4. Modelsim-Altera (for simulating the system)

Usage of these tools is documented below. Steps for creating a new system from scratch using these 4 tools follow directly, i.e. what you will have to do for experiment 1.

1. Quartus
==========

- When creating a new system, a Quartus project should be created in the same way as in previous labs. Use "experiment1" as the project name. Ensure that the correct device (Cyclone II - EP2C35F672C6) is selected.

2. Qsys Builder
===============

- Once the project has been created, select "Qsys" from the "Tools" menu, this will launch the system design tool. Immediately save the system as "experiment1.qsys". Follow the steps below:

- Rename the Clock Source component:
	-- rename "clk_0" to "CLOCK_50_I"
	-- under the export column, rename "clk" to "clock_50_i_clk_in"
	-- rename "reset" to "clock_50_i_clk_in_reset"
- Adding a program/data memory to the system
	-- Under the "System Contents" tab expand "Memories and Memory Controllers" in the Component Library
	-- Under "Memories and Memory Controllers" expand "On-Chip"
	-- Double-click on "On-Chip Memory (RAM or ROM)"
	-- A configuration window will appear, change the memory size to 128 KBytes (131072 Bytes)
	-- Click "Finish"
- Adding a processor the the system
	-- Under the "System Contents" tab expand "Embedded Processors" in the Component Library
	-- Double-click on "Nios II Processor"
	-- A configuration window will appear, select Nios II/e
	-- Click "Finish"
	-- Rename the processor to "cpu_0"
- Adding a UART port for STDIO
	-- Under the "System Contents" tab expand "Interface Protocols" in the Component Library
	-- Under "Interface Protocols" expand "Serial"
	-- Double-click "JTAG-UART"
	-- Under "Prepare Interactive Windows", ensure that "Option" is set to "INTERACTIVE_ASCII_OUTPUT"
	-- The other settings are fine, click "Finish"
	
- Adding the toggle switches
	-- Under the "System Contents" tab expand "Peripherals"
	-- Expand "Microcontroller Peripherals"
	-- Double-click "PIO (Parallel I/O)"
	-- Put 17 as width even though there are 18 switches on the board. This is because we are using SWITCH[17] as the resetn
	-- Select "Input", then click "Finish"
	-- Rename this module to "SWITCH_I" by right-clicking on the module name "pio_0"

- Adding the push buttons
	-- Under the "System Contents" tab expand "Peripherals"
	-- Expand "Microcontroller Peripherals"
	-- Double-click "PIO (Parallel I/O)"
	-- Put 4 as width
	-- Select "Input"
	-- Select "Synchronously capture" and "RISING"
	-- Select "Generate IRQ" and "EDGE"
	-- Click "Finish"
	-- Rename this module to "PUSH_BUTTON_I" by right-clicking on the module name "pio_0"

- Adding the red LEDs
	-- Under the "System Contents" tab expand "Peripherals"
	-- Expand "Microcontroller Peripherals"
	-- Double-click "PIO (Parallel I/O)"
	-- Put 18 as width
	-- Select "Output"
	-- Click "Finish"
	-- Rename this module to "LED_RED_O" by right-clicking on the module name "pio_0"		

- Adding the green LEDs
	-- Under the "System Contents" tab expand "Peripherals"
	-- Expand "Microcontroller Peripherals"
	-- Double-click "PIO (Parallel I/O)"
	-- Put 9 as width
	-- Select "Output"
	-- Click "Finish"
	-- Rename this module to "LED_GREEN_O" by right-clicking on the module name "pio_0"		

- Adding the custom counter
	-- Under the "System Contents" tab expand "coe4ds4_components"
	-- double click on the component "custom_counter_component"
	-- Click "Finish"

- Configure the top-level connections of the system.  Under the "Export" column, click the following items (the default names are fine):
	-- "conduit endpoint" of "LED_GREEN_O"
	-- "conduit endpoint" of "LED_RED_O"
	-- "conduit endpoint" of "SWITCH_I"
	-- "conduit endpoint" of "PUSH_BUTTON_I"
- Configure the connections of the system:
	-- Select "Create Global Reset Network" from the "System" menu
	-- Attach the "Clock Output" of "CLOCK_50_I" to the "Clock Input" of all other components
	-- Attach the following signals to the "data_master" of "cpu_0"
		> "s1" of "onchip_memory2_0"
		> "avalon_jtag_slave" of "jtag_uart_0"
		> "s1" of "SWITCH_I"
		> "s1" of "PUSH_BUTTON_I"
		> "s1" of "LED_RED_O"
		> "s1" of "LED_GREEN_O"
		> "avalon_slave_0" of "custom_counter_component_0"
	-- Attach the "instruction_master" of "cpu_0" to "s1" of "onchip_memory2_0"
	-- Under the "IRQ" column, attach the irq signals for "jtag_uart_0", "PUSH_BUTTON_I", and "custom_counter_component_0"
	-- Double click on "cpu_0" to open its configuration window
	-- For "Reset Vector Memory", select "onchip_memory2_0.s1"
	-- For "Exception Vector Memory", select "onchip_memory2_0.s1"
	-- Click "Finish"
- To automatically configure the base address and IRQ number of the system
	-- Go to "System"->"Assign Base Addresses"
	-- Go to "System"->"Assign Interrupt Numbers"

- Generating the system
	-- Click the "Generation" tab
	-- Change the "Create simulation model" to "Verilog"
	-- Uncheck "Create HDL design files for synthesis" and "Create block symbol file (.bsf)"
	-- Save the system
	-- Click "Generate", wait for the message "Generate Completed"
	-- Click "Close"

- Pin assignments
	-- Pin assignments are not necessary here, since you will only be simulating the design

- Synthesis
	-- Synthesis is not necessary here, since you will only be simulating the design

3. Nios SDK
===========

- Launching Nios II SDK
	-- Start the SDK from within Qsys, the Desktop or the Start menu
	
- To start a new project with the newly created system described above:
	-- Select the experiment folder as your workspace (i.e. experiment1)
	-- Click "OK" and wait for Nios II SDK to be launched
	-- Go to "File" -> "New" -> "Nios II Application and BSP from Template"
	-- Use "experiment1" as the project name
	-- In "SOPC Information File Name", browse for the sopcinfo file generated by Qsys (experiment1.sopcinfo)
	-- In "CPU", select the corresponding CPU from the system
	-- Now select project type, for the system created as described above, select "Hello World"
	-- Click "Finish" and wait for the project to be created
	
- Getting the C source files
	-- Expand the "experiment1" entry in the "Nios II C/C++ Projects" window
	-- Right click on "hello_world.c" and rename it to "experiment1.c"
	-- Copy all the files from folder "C_sources" to the folder "experiment1" where NIOS stores the sources
	-- Overwrite the "experiment1.c" when prompted
	-- Right click on "experiment1" entry, and choose "Refresh"

- Setting up NIOS SDK for simulation
	-- Right click on "experiment1_bsp", and select "Properties"
	-- Select "Nios II BSP Properties" (you may have to wait for the settings to become active)
	-- Check the box that says "ModelSim only, no hardware support"
	
- To start ModelSim for simulation
	-- Choose "Project"->"Build All" to start compilation in NIOS
	-- Right click on "experiment1" in the project window
	-- Select "Run As" -> "Nios II ModelSim"
	-- When the "Run Configurations" window opens, under "Qsys Testbench Simulation Package Descriptor Filename" select "experiment1.spd" from the project folder
	-- Click "Run"
	-- After a short delay you should see Modelsim being launched
	
4. ModelSim-Altera
===========
- Compile the test bench module
	-- At the prompt of ModelSim, enter:
	 	--- "vlog -sv ../../../../../../../test_bench.v"
- Configure the simulation environment
	-- At the prompt of ModelSim, enter:
		--- "set TOP_LEVEL_NAME test_bench"
		--- "set SYSTEM_INSTANCE_NAME /DUT"
	-- Loading the design files
		-- At the prompt of ModelSim, enter "ld"
	-- Adding signals into the waveforms
	-- Run the "wave.do" file in the experiment folder, at the prompt of ModelSim, enter:
		--- "do ../../../../../../../wave.do"
- To start the simulation
	-- At the prompt of ModelSim, enter "run -all"
	-- The simulation should start, and you can see the output of the simulation in the ModelSim environment
	-- All of the $write statements have been prefaced by "TBINFO" so that they can be distinguished from the printf statements in the C code
