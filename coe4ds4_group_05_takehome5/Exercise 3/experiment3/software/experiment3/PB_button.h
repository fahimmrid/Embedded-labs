// Copyright by Adam Kinsman, Henry Ko and Nicola Nicolici
// Developed for the Embedded Systems course (COE4DS4)
// Department of Electrical and Computer Engineering
// McMaster University
// Ontario, Canada

#ifndef __PB_Button_H__
#define __PB_Button_H__

// Mask for enabling interrupts for the PB
#define BUTTON_INT_MASK	  0xF

#define NUM_PB_BUTTON 4

typedef struct PB_irq_data_type {
	char filename[13];
	int load_img_flag;
	int save_img_flag;
} PB_irq_data_struct;

// Global functions
void handle_button_interrupts(PB_irq_data_struct *);
void init_button_irq(PB_irq_data_struct *);

#endif
