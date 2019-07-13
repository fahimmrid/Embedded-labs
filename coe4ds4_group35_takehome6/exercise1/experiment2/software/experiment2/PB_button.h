// Copyright by Adam Kinsman, Henry Ko and Nicola Nicolici
// Developed for the Embedded Systems course (COE4DS4)
// Department of Electrical and Computer Engineering
// McMaster University
// Ontario, Canada

#ifndef __PB_Button_H__
#define __PB_Button_H__

// Mask for enabling interrupts for the PB
#define BUTTON_INT_MASK   0xF

#define NUM_PB_BUTTON 4

// Global functions
void handle_button_interrupts();
void init_button_irq();

#endif
