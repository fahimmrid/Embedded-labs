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

// Number of custom tasks
#define NUM_TASK 4

// Global function
void custom_scheduler(void *pdata);

#endif
