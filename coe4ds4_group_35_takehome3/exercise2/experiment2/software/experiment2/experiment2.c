// Copyright by Adam Kinsman, Henry Ko and Nicola Nicolici
// Developed for the Embedded Systems course (COE4DS4)
// Department of Electrical and Computer Engineering
// McMaster University
// Ontario, Canada

#include "define.h"

int main()
{
	volatile PS2_buffer_struct PS2_buffer_data;

	printf("Start main...\n");

	PS2_buffer_data.buffer_flush = 0;
	PS2_buffer_data.cur_buf_length = 0;
	PS2_buffer_data.caps_lock = 0;;

		
	init_PS2_irq(&PS2_buffer_data);
	printf("PS2 IRQ initialized...\n");

	IOWR(LED_GREEN_O_BASE, 0, 0x0);
	IOWR(LED_RED_O_BASE, 0, 0x0);
	
	printf("Switch value: %X\n", IORD(SWITCH_I_BASE, 0));
		
	while (1) {
		if (PS2_buffer_data.buffer_flush == 1) {
			printf("%s", PS2_buffer_data.string_buffer);
			PS2_buffer_data.buffer_flush = 0;
			PS2_buffer_data.string_buffer[0] = '\n';
		    //PS2_buffer_data.capslock = 0;
			PS2_buffer_data.cur_buf_length = 0;
		}
	};
	
	return 0;
}
