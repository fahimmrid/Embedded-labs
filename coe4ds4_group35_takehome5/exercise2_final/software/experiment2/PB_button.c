// Copyright by Adam Kinsman, Henry Ko and Nicola Nicolici
// Developed for the Embedded Systems course (COE4DS4)
// Department of Electrical and Computer Engineering
// McMaster University
// Ontario, Canada

#include "define.h"

void KEY0_Pressed() {
}

void KEY1_Pressed() {
}

void KEY2_Pressed() {
}

void KEY3_Pressed() {
}

// ISR when any PB is pressed
void handle_button_interrupts(void *context)
{
	IOWR(LED_GREEN_O_BASE, 0, IORD(PUSH_BUTTON_I_BASE, 3)*IORD(PUSH_BUTTON_I_BASE, 3));
	
	switch(IORD(PUSH_BUTTON_I_BASE, 3)) {
	case 1: KEY0_Pressed(); break;
	case 2: KEY1_Pressed(); break;
	case 4: KEY2_Pressed(); break;
	case 8: KEY3_Pressed(); break;
	}
	*(unsigned char *)context = 0x1;
	IOWR(PUSH_BUTTON_I_BASE, 3, 0x0);
}

// Function for initializing the ISR of the PBs
// The PBs are setup to generate interrupt on falling edge,
// and the interrupt is captured when the edge comes
void init_button_irq(void *context) {
  // Enable all 4 button interrupts
  IOWR(PUSH_BUTTON_I_BASE, 2, BUTTON_INT_MASK);

  // Reset the edge capture register
  IOWR(PUSH_BUTTON_I_BASE, 3, 0x0);

  // Register the interrupt handler
  alt_irq_register(PUSH_BUTTON_I_IRQ, context, (void*)handle_button_interrupts );
}
