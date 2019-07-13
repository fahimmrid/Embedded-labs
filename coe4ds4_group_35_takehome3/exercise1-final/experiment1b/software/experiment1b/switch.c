// Copyright by Adam Kinsman, Henry Ko and Nicola Nicolici
// Developed for the Embedded Systems course (COE4DS4)
// Department of Electrical and Computer Engineering
// McMaster University
// Ontario, Canada

#include "define.h"

extern volatile int instruction;

void handle_switch_interrupts(elevator *data){
	(*data).instruction=(*data).instruction | (IORD(SWITCH_I_BASE,3)& 0XFFF);
	IOWR(SWITCH_I_BASE,3,0X0);
}

void init_switch_irq(elevator *data){
	IOWR(SWITCH_I_BASE,2,0x18FFF);
	IOWR(SWITCH_I_BASE,3,0x0);
	
	alt_irq_register(SWITCH_I_IRQ, (void*)data, (void*)handle_switch_interrupts);
}
