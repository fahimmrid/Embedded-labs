// Copyright by Adam Kinsman, Henry Ko and Nicola Nicolici
// Developed for the Embedded Systems course (COE4DS4)
// Department of Electrical and Computer Engineering
// McMaster University
// Ontario, Canada

#ifndef __task_H__
#define __task_H__

// Size of stack for each task
#define	  TASK_STACKSIZE	   2048

// Definition of Task Priorities
#define INITIALIZE_TASK_PRIORITY   6
#define SD_MUTEX_PRIORITY			10
#define SD_PRESENCE_DETECT_PRIORITY	  11
#define SD_READ_PRIORITY		  12
#define SD_READTWO_PRIORITY		  13
#define COMPUTE_Y_PRIORITY		  14
#define PROCESS_Y_PRIORITY		  15
#define SD_WRITE_PRIORITY		  16
#define TASK_LAUNCHER_PRIORITY	  17

// Global function
void task_launcher(void *pdata);

#endif
