// Copyright by Adam Kinsman, Henry Ko and Nicola Nicolici
// Developed for the Embedded Systems course (COE4DS4)
// Department of Electrical and Computer Engineering
// McMaster University
// Ontario, Canada

#include "define.h"

// Semaphore from uCOS
extern OS_EVENT *PBSemaphore[];

// Function for post semaphore when PB0 is pressed
void KEY0_Pressed() {
	INT8U return_code = OS_NO_ERR;

	return_code = OSSemPost(PBSemaphore[0]);
  	alt_ucosii_check_return_code(return_code);
}

// Function for post semaphore when PB1 is pressed
void KEY1_Pressed() {
	INT8U return_code = OS_NO_ERR;

	return_code = OSSemPost(PBSemaphore[1]);
  	alt_ucosii_check_return_code(return_code);
}

// Function for post semaphore when PB2 is pressed
void KEY2_Pressed() {
	INT8U return_code = OS_NO_ERR;

	return_code = OSSemPost(PBSemaphore[2]);
  	alt_ucosii_check_return_code(return_code);
}

// Function for post semaphore when PB3 is pressed
void KEY3_Pressed() {
	INT8U return_code = OS_NO_ERR;

	return_code = OSSemPost(PBSemaphore[3]);
  	alt_ucosii_check_return_code(return_code);
}
// ISR when any PB is pressed
void handle_button_interrupts()
{
	OSIntEnter();

    outport(LED_GREEN_O_BASE,get_pio_edge_cap(PUSH_BUTTON_I_BASE)*get_pio_edge_cap(PUSH_BUTTON_I_BASE));
    switch(get_pio_edge_cap(PUSH_BUTTON_I_BASE)) {
    case 1: KEY0_Pressed(); break;
    case 2: KEY1_Pressed(); break;
    case 4: KEY2_Pressed(); break;
    case 8: KEY3_Pressed(); break;
    }
    set_pio_edge_cap(PUSH_BUTTON_I_BASE,0x0);

	OSIntExit();
}

// Function for initializing the ISR of the PBs
// The PBs are setup to generate interrupt on falling edge,
// and the interrupt is captured when the edge comes
void init_button_irq() {
  // Enable all 4 button interrupts
  set_pio_irq_mask(PUSH_BUTTON_I_BASE, BUTTON_INT_MASK);

  // Reset the edge capture register
  set_pio_edge_cap(PUSH_BUTTON_I_BASE, 0x0);

  // Register the interrupt handler
  alt_irq_register( PUSH_BUTTON_I_IRQ, NULL, (void*)handle_button_interrupts );
}
