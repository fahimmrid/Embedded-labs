// Copyright by Adam Kinsman, Henry Ko and Nicola Nicolici
// Developed for the Embedded Systems course (COE4DS4)
// Department of Electrical and Computer Engineering
// McMaster University
// Ontario, Canada

#include "define.h"

int main()
{
	printf("Start main...\n");

	IOWR(LED_GREEN_O_BASE, 0, 0x0);
	IOWR(LED_RED_O_BASE, 0, 0x0);

	init_button_irq();
	printf("PB initialized...\n");
	
	init_counter_irq();
	printf("Counter IRQ initialized...\n");
	
	printf("System is up!\n");

	IOWR(LED_RED_O_BASE, 0, 0xF);
		
	while (1);
	
	return 0;
}
