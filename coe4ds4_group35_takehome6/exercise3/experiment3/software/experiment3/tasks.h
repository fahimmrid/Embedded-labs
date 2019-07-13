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
#define SWITCH_A_MUTEX_PRIORITY	   9
#define SWITCH_B_MUTEX_PRIORITY	  10
#define RED_LED_MUTEX_PRIORITY	  11
#define GREEN_LED_MUTEX_PRIORITY  12
#define CUSTOM_TASK_3_PRIORITY	  13
#define CUSTOM_TASK_2_PRIORITY	  14
#define CUSTOM_TASK_1_PRIORITY	  15
#define CUSTOM_TASK_0_PRIORITY	  16
#define TASK_LAUNCHER_PRIORITY	  17

// Number of clock ticks for delaying the LCD display
#define DELAY_TICK 1000

// Number of custom tasks
#define NUM_TASK 4

// Global function
void task_launcher(void *pdata);

#endif
