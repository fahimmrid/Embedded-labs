// Copyright by Adam Kinsman, Henry Ko and Nicola Nicolici
// Developed for the Embedded Systems course (COE4DS4)
// Department of Electrical and Computer Engineering
// McMaster University
// Ontario, Canada

This file contains instructions for using the toolflow for coe4ds4_lab7 experiment 3 which uses multiprocessing.

Nios IDE
========

Operating in Nios IDE with multiple processors differs from a single processor design on only a couple of points. 
After loading the SOF file into the Cyclone FPGA on the DE2 board, use the following procedure for setting up the software environment.

- Importing the software projects
	-- import the _cpu1 and _cpu1_bsp projects as in previous experiments
	-- right click on the _cpu1_bsp project and select "Generate BSP" from the "NIOS II" menu
	-- import the _cpu2 and _cpu2_bsp projects as in previous experiments
	-- right click on the _cpu2_bsp project and select "Generate BSP" from the "NIOS II" menu
- Building the projects
	-- Select "Build All" from the "Project" menu to build, as in previous experiments

- To load the program onto the CPUs in Nios IDE
	-- Go to "Run"->"Run Configurations"
	-- Right click "Nios II Hardware" in the configuration list
	-- Click "New"
	-- On the Main tab, change the Name to "experiment3_cpu1"
	-- Select "experiment3_cpu1" as the project name
	-- On the Target Connection tab, ensure that the device named "cpu1" is selected
	-- Again, right click "Nios II Hardware" in the configuration list and click "New"
		-- If prompted to save the changes to "New Configuration", select "Yes"
	-- Change the Name to "experiment3_cpu2"
	-- Select "experiment3_cpu2" as the project name
	-- On the Target Connection tab, ensure that the device named "cpu2" is selected
	-- Right click on "Launch Group" and click "New"
		-- Again if prompted to save, select "Yes"
	-- Change the name to "experiment3_HW_collection"
	-- Select "Add" from the Launches tab, and select "experiment3_cpu1" from under "Nios II Hardware"
	-- Select "Add" from the Launches tab, and select "experiment3_cpu2" from under "Nios II Hardware"
	-- Once both launches are added, you may run the multiprocessor system by selecting "experiment3_HW_collection" and clicking "Run" 

IMPORTANT NOTE:
	-- Whenever you change and rebuild your code, you should select "experiment3_HW_collection" from the "Run->Run History" menu
	   to launch the program.  However, after the code is downloaded, you should toggle switch 17 to reset the system.
