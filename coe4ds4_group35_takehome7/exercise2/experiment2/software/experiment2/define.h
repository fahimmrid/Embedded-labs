// Copyright by Adam Kinsman, Henry Ko and Nicola Nicolici
// Developed for the Embedded Systems course (COE4DS4)
// Department of Electrical and Computer Engineering
// McMaster University
// Ontario, Canada

#ifndef	  __define_H__
#define	  __define_H__

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "sys/alt_irq.h"
#include "includes.h"
#include "alt_ucosii_simple_error_check.h"
#include "ucos_ii.h"
#include "basic_io.h"
#include "SD_card_controller.h"
#include "PB_button.h"
#include "tasks.h"
#include "altera_up_avalon_character_lcd.h"
#include "altera_avalon_performance_counter.h"

// uCOSII Configuration flags
// #define OS_SHED_LOCK_EN 1

#define OS_SEM_EN 1
#define OS_SEM_ACCEPT_EN 1
#define OS_SEM_QUERY_EN 1

#define OS_TASK_QUERY_EN 1
#define OS_TASK_STAT_EN 1
#define OS_TASK_DEL_EN 1
#define OS_TASK_CREATE_EXT_EN 1
#define OS_TASK_PROFILE_EN 1
//#define OS_TASK_CHANGE_PRIO_EN 1
//#define OS_TASK_SUSPEND_EN 1

#define OS_TIME_GET_SET_EN 1
#define OS_TICKS_PER_SEC 1000

#define NUM_LINES 480
#define LINE_LEN 640
#define QUEUE_LEN 128

#endif
