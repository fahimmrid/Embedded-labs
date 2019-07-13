// Copyright by Adam Kinsman, Henry Ko and Nicola Nicolici
// Developed for the Embedded Systems course (COE4DS4)
// Department of Electrical and Computer Engineering
// McMaster University
// Ontario, Canada

#include "define.h"

void KEY0_Pressed(PB_irq_data_struct *PB_irq_data) {
	int status;
	
	status = sd_card_find_next(PB_irq_data->filename);
	switch (status) {
		case 0: printf("File found: \"%s\"\n", PB_irq_data->filename); break;
		case -1: printf("End of directory\n"); break;
		case 2: printf("No card or incorrect FS\n"); break;
	}
}

void KEY1_Pressed(PB_irq_data_struct *PB_irq_data) {
}

void KEY2_Pressed(PB_irq_data_struct *PB_irq_data) {
	PB_irq_data->load_img_flag = 1;
}

void KEY3_Pressed(PB_irq_data_struct *PB_irq_data) {
	PB_irq_data->save_img_flag = 1;	
}

// ISR when any PB is pressed
void handle_button_interrupts(PB_irq_data_struct *PB_irq_data)
{
	IOWR(LED_GREEN_O_BASE, 0, IORD(PUSH_BUTTON_I_BASE, 3)*IORD(PUSH_BUTTON_I_BASE, 3));
	
	switch(IORD(PUSH_BUTTON_I_BASE, 3)) {
	case 1: KEY0_Pressed(PB_irq_data); break;
	case 2: KEY1_Pressed(PB_irq_data); break;
	case 4: KEY2_Pressed(PB_irq_data); break;
	case 8: KEY3_Pressed(PB_irq_data); break;
	}
	IOWR(PUSH_BUTTON_I_BASE, 3, 0x0);
}

// Function for initializing the ISR of the PBs
// The PBs are setup to generate interrupt on falling edge,
// and the interrupt is captured when the edge comes
void init_button_irq(PB_irq_data_struct *PB_irq_data) {
  // Enable all 4 button interrupts
  IOWR(PUSH_BUTTON_I_BASE, 2, BUTTON_INT_MASK);

  // Reset the edge capture register
  IOWR(PUSH_BUTTON_I_BASE, 3, 0x0);

  // Register the interrupt handler
  alt_irq_register(PUSH_BUTTON_I_IRQ, (void *)PB_irq_data, (void*)handle_button_interrupts );
}
