// Copyright by Adam Kinsman, Henry Ko and Nicola Nicolici
// Developed for the Embedded Systems course (COE4DS4)
// Department of Electrical and Computer Engineering
// McMaster University
// Ontario, Canada

#include "define.h"

// ISR when the counter is expired
void handle_counter_expire_interrupts()
{
	IOWR(LED_RED_O_BASE, 0, 0x7);

	printf("Counter expires\n");
	
	IOWR(CUSTOM_COUNTER_COMPONENT_0_BASE, 2, 0);

	IOWR(LED_RED_O_BASE, 0, 0xF);
}

void reset_counter() {
	IOWR(LED_RED_O_BASE, 0, 0xB);
	
	printf("Resetting counter value\n");

	IOWR(CUSTOM_COUNTER_COMPONENT_0_BASE, 1, 1);
	IOWR(CUSTOM_COUNTER_COMPONENT_0_BASE, 1, 0);

	IOWR(CUSTOM_COUNTER_COMPONENT_0_BASE, 2, 0);

	IOWR(LED_RED_O_BASE, 0, 0xF);
}

int read_counter() {
	return IORD(CUSTOM_COUNTER_COMPONENT_0_BASE, 0);
}

int read_counter_interrupt() {
	return IORD(CUSTOM_COUNTER_COMPONENT_0_BASE, 2);
}

void load_counter_config(int config) {
	IOWR(LED_RED_O_BASE, 0, 0xD);
	printf("Loading counter value %d\n", config);
	
	IOWR(CUSTOM_COUNTER_COMPONENT_0_BASE, 3, config);

	IOWR(LED_RED_O_BASE, 0, 0xF);
}

// Function for initializing the ISR of the Counter
void init_counter_irq() {
	IOWR(CUSTOM_COUNTER_COMPONENT_0_BASE, 2, 0);

	alt_irq_register(CUSTOM_COUNTER_COMPONENT_0_IRQ, NULL, (void*)handle_counter_expire_interrupts );
}
