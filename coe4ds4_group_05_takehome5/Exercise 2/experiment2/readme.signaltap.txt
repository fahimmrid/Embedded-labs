Copyright by Adam Kinsman, Henry Ko and Nicola Nicolici
Developed for the Embedded Systems course (COE4DS4)
Department of Electrical and Computer Engineering
McMaster University, Ontario, Canada

This file contains instructions for using SignalTap to monitor signals in real-time.

Top Level Toolflow
==================

The toolflow for hardware/software co-design using Altera Nios has 3 main tools:

1. Quartus (for the hardware project)
2. SignalTap (for real-time embedded logic analysis)
3. Nios SDK (for the software project)

Usage of these tools is documented below. Steps for creating a new system from scratch using these 3 tools follow directly, i.e. what you will have to do for experiment 2.

1. Quartus
==========

- Create a new project and include the "experiment2/synthesis/experiment2.v".
- Compile the design.

2. SignalTap
===========

- To launch SignalTap, after opening the project in Quartus, go to "Tools" -> "SignalTap II Logic Analyzer"

- In the "Hardware" box on the upper-right corner of the SignalTap window, select "USB-Blaster"

- To select the reference clock used for sampling data:
	-- In the "Signal Configuration" section underneath, click on the "..." button for the "Clock" box
	-- In the new window, click on "List"
	-- For the lab, use 50 MHz clock "clock_50_i_clk_in_clk" as the sampling clock by double clicking on it, and then click "OK"
	-- When prompted "Do you want to set the netlist type of the Top partition to Post-Fit...", select "Yes"
	-- Now go back to the SignalTap window

- To add the signals you wish to use as trigger signals:
	-- In the "Setup" tab, where it says "Double-click to add nodes", double-click on any blank area
	-- The signal selection window will pop up. Click on "List"
	-- Here you can select different "Filter" and type in the name of the signals you want to use in the provided boxes
	-- For the lab, we target to use SignalTap to monitor the custom counter. So, select the following signals
		--- custom_counter_component:custom_counter_component_0|load
		--- custom_counter_component:custom_counter_component_0|load_config
		--- custom_counter_component:custom_counter_component_0|reset_counter
		--- custom_counter_component:custom_counter_component_0|counter_expire_irq
		--- custom_counter_component:custom_counter_component_0|custom_counter_unit:custom_counter_unit_inst|load_config_buf
		--- custom_counter_component:custom_counter_component_0|custom_counter_unit:custom_counter_unit_inst|counter_value
		--- custom_counter_component:custom_counter_component_0|custom_counter_unit:custom_counter_unit_inst|counter_expire

- Setting the trace length
	-- You can setup the trace length by changing the "Sample depth" in the "Signal Configuration" section of the SignalTap window
	-- For the lab, choose a "Sample depth" of "1K"

- After finish setting up SignalTap, go back to Quartus, and compile the design.
	-- When prompted "Save changes to stp1.stp", click "Yes"
	-- Name the SignalTap file "experiment2.stp", the click "Save"
	-- When prompted "Do you want to enable SignalTap II File ...", click "Yes"
	-- Wait for compilation to finish

- Program the device with the compiled design

- To setup the trigger conditions for sampling data
	-- Go to the SignalTap window
	-- In the setup tab, you can setup the trigger conditions for sampling based on the setting you choose for each signal that was added under the column labeled "Trigger Conditions"
	-- For the lab, we target to sample data when the custom counter expires and the interrupt is raised
		--- Right click on the cell for the row that contains the signal "counter_expire_irq" and the column that reads "Trigger Conditions"
		--- Choose "Rising Edge" in the pop-up tag
	-- Now click on icon that starts SignalTap and wait for the trigger condition to occur (it looks like a red "Play" button with a magnify glass and it is usually underneath "Edit")
	-- SignalTap should now say "Acquisition in progress" and should be "Waiting for trigger"

3. Nios SDK
===========

- Launching Nios II SDK
	-- Start the SDK from within the Qsys Builder, the Desktop or the Start menu
	
- Import "experiment2" and "experiment2_bsp" to the workspace as in previous lab

- Build and run the design under Nios SDK as hardware as in previous lab

- To trigger SignalTap, press push button 0
	-- You can view the sampled data in the "Data" tab in the SignalTap window
