// Copyright by Adam Kinsman, Henry Ko and Nicola Nicolici
// Developed for the Embedded Systems course (COE4DS4)
// Department of Electrical and Computer Engineering
// McMaster University
// Ontario, Canada

#include "define.h"

volatile char string_buffer[MAX_STRING_LENGTH];
volatile int cur_buf_length;
volatile int buffer_flush;

int main()
{
	printf("Start main...\n");

	buffer_flush = 0;
	cur_buf_length = 0;
		
	init_PS2_irq();
	printf("PS2 IRQ initialized...\n");

	IOWR(LED_GREEN_O_BASE, 0, 0x0);
	IOWR(LED_RED_O_BASE, 0, 0x0);
	
	printf("Switch value: %X\n", IORD(SWITCH_I_BASE, 0));
		
	while (1) {
		if (buffer_flush == 1) {
			printf("%s", string_buffer);
			buffer_flush = 0;
			string_buffer[0] = '\0';
			cur_buf_length = 0;
		}
	};
	
	return 0;
}
