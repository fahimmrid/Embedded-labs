// Copyright by Adam Kinsman, Henry Ko and Nicola Nicolici
// Developed for the Embedded Systems course (COE4DS4)
// Department of Electrical and Computer Engineering
// McMaster University
// Ontario, Canada

#ifndef	  __define_H__
#define	  __define_H__

#include <io.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "sys/alt_alarm.h"
#include "alt_types.h"
#include "system.h"
#include <sys/alt_irq.h>
#include "PB_button.h"
#include "switch.h"
#include "custom_counter_0.h"
#include "custom_counter_1.h"

typedef struct elevator{
	int door_open;
	int door_hold;
	int drc;
	int instruction;
	int cur_flo;
	int betweenflo;


} elevator;

#endif
