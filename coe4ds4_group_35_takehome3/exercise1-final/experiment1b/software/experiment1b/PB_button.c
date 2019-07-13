// Copyright by Adam Kinsman, Henry Ko and Nicola Nicolici
// Developed for the Embedded Systems course (COE4DS4)
// Department of Electrical and Computer Engineering
// McMaster University
// Ontario, Canada

#include "define.h"

//void KEY0_Pressed() {
	//reset_counter();
//}

void KEY1_Pressed(elevator *data) {
	int val;
	printf("button 1 pressed\n");
	if(((IORD(PUSH_BUTTON_I_BASE,0)>>1)&0x1)==0){
		if((*data).drc==0&&(*data).door_open==0&& (*data).door_hold==0){
			val=(IORD(SWITCH_I_BASE, 0) & 0x18000) >> 15;
			load_counter_1_config(val);
		}
	}

}

void KEY2_Pressed(elevator *data) {
	int val;
	printf("button 2 pressed\n");
	if(((IORD(PUSH_BUTTON_I_BASE,0)>>2)&0x1)==0){
		if((*data).drc==0&&(*data).door_open==0&& (*data).door_hold==0){
			val=(IORD(SWITCH_I_BASE, 0) & 0x18000) >> 15;
			load_counter_0_config(val);
			}
		}
}

void KEY3_Pressed(elevator *data) {
		printf("button 3 pressed\n");
		if((*data).drc==0||(*data).door_open==1||(*data).door_hold==1){
			if(((IORD(PUSH_BUTTON_I_BASE,0)>>3)&0x1)==0){
				printf("door kept open\n");
				(*data).door_hold=1;
			}else {
				printf("door is now close\n");
				(*data).door_hold=0;
			}

		}

}

// ISR when any PB is pressed
void handle_button_interrupts(elevator *data)
{
	//IOWR(LED_GREEN_O_BASE, 0, IORD(PUSH_BUTTON_I_BASE, 3)*IORD(PUSH_BUTTON_I_BASE, 3));
	
	switch(IORD(PUSH_BUTTON_I_BASE, 3)) {
	//case 1: KEY0_Pressed(); break;
	case 2: KEY1_Pressed(data); break;
	case 4: KEY2_Pressed(data); break;
	case 8: KEY3_Pressed(data); break;
	}
	IOWR(PUSH_BUTTON_I_BASE, 3, 0x0);
}

// Function for initializing the ISR of the PBs
// The PBs are setup to generate interrupt on falling edge,
// and the interrupt is captured when the edge comes
void init_button_irq(elevator *data) {
  // Enable all 4 button interrupts
  IOWR(PUSH_BUTTON_I_BASE, 2, BUTTON_INT_MASK);

  // Reset the edge capture register
  IOWR(PUSH_BUTTON_I_BASE, 3, 0x0);

  // Register the interrupt handler
  alt_irq_register(PUSH_BUTTON_I_IRQ, (void*)data, (void*)handle_button_interrupts );
}
