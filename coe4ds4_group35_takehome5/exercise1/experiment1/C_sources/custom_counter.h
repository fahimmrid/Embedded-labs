// Copyright by Adam Kinsman, Henry Ko and Nicola Nicolici
// Developed for the Embedded Systems course (COE4DS4)
// Department of Electrical and Computer Engineering
// McMaster University
// Ontario, Canada

#ifndef __CUSTOM_COUNTER_H__
#define __CUSTOM_COUNTER_H__

// Global functions
void handle_counter_expire_interrupts();
int read_counter();
void reset_counter();
int read_counter_interrupt();
void init_counter_irq();
void load_counter_config(int);

#endif
