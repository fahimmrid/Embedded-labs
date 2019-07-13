// Copyright by Adam Kinsman, Henry Ko and Nicola Nicolici
// Developed for the Embedded Systems course (COE4DS4)
// Department of Electrical and Computer Engineering
// McMaster University
// Ontario, Canada

#ifndef __CUSTOM_COUNTER_H__
#define __CUSTOM_COUNTER_H__

#define WRITE_ELEMENT(BASE, ADDR, DATA) \
	IOWR((BASE), 1, ((1 << 25) | (((ADDR) & 0x1FF) << 16) | ((DATA) & 0xFFFF)))

#define READ_ELEMENT(BASE, ADDR, RESULT) \
	IOWR((BASE), 1, (((ADDR) & 0x1FF) << 16)); RESULT = IORD((BASE), 0)

// Global functions
void handle_counter_expire_interrupts();
void find_sequence_hardware();
void init_counter_irq();

#endif
