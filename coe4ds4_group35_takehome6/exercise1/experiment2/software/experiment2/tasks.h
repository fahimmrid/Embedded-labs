// Copyright by Adam Kinsman, Henry Ko and Nicola Nicolici
// Developed for the Embedded Systems course (COE4DS4)
// Department of Electrical and Computer Engineering
// McMaster University
// Ontario, Canada

#ifndef __task_H__
#define __task_H__

// Size of stack for each task
#define   TASK_STACKSIZE       2048

// Definition of Task Priorities
#define INITIALIZE_TASK_PRIORITY   6
#define CUSTOM_SCHEDULER_PRIORITY  9
#define TASK_START_PRIORITY       10
#define PERIODIC_TASK_1       11
#define PERIODIC_TASK_2        12

// Global function
void custom_scheduler(void *pdata);

// Number of custom tasks
#define NUM_TASK 2 //not really using this constant looped to 2
//periodic task delays values

#define PERIODIC_TASK_1_EXECUTION_TIME   1000 //Member #1: Fahim = 5*200 = 1000
#define PERIODIC_TASK_1_IDLE_TIME        3600 //Member #2: Gao = 3*1200 = 3600
#define PERIODIC_TASK_2_EXECUTION_TIME   1200 //Ridwan : 6*200 = 1200
#define PERIODIC_TASK_2_IDLE_TIME        7200 //  Audrey : 6*1200 = 7200

#endif

