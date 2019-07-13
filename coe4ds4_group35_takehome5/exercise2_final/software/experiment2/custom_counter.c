// Copyright by Adam Kinsman, Henry Ko and Nicola Nicolici
// Developed for the Embedded Systems course (COE4DS4)
// Department of Electrical and Computer Engineering
// McMaster University
// Ontario, Canada

#include "define.h"

// ISR when the counter is expired
void handle_irq_interrupts()
{
//	printf("\nHardware verification complete!\n");

	int ADDR = IORD(CUSTOM_COUNTER_COMPONENT_0_BASE, 2);
	printf("The result from Hardware sequence: \n");

	printf("Array Position : %d Array size: = %d", (ADDR >> 16) & 0xFFFF, ADDR & 0xFFFF);
	IOWR(CUSTOM_COUNTER_COMPONENT_0_BASE, 3, 0);
}

void hardware() {
	IOWR(CUSTOM_COUNTER_COMPONENT_0_BASE, 3, 0);
	alt_irq_register(CUSTOM_COUNTER_COMPONENT_0_IRQ, NULL, (void*)handle_irq_interrupts );
}
