////////////////////////
// CODE SECTION BEGIN //
////////////////////////

#include "define.h"

// ISR when the counter is expired
void handle_counter_0_expire_interrupts(elevator *data)
{
    if((*data).drc==1){
    	(*data).cur_flo=(*data).cur_flo+1;
    }
    if((*data).drc==-1){
    	(*data).cur_flo=(*data).cur_flo-1;
    }
	//printf("Counter expires\n");
	(*data).betweenflo=0;
	IOWR(CUSTOM_COUNTER_COMPONENT_0_BASE, 2, 0);

}

void reset_counter_0() {
	//printf("Resetting counter value\n");

	IOWR(CUSTOM_COUNTER_COMPONENT_0_BASE, 1, 1);
	IOWR(CUSTOM_COUNTER_COMPONENT_0_BASE, 1, 0);

	IOWR(CUSTOM_COUNTER_COMPONENT_0_BASE, 2, 0);
}

int read_counter_0() {
	return IORD(CUSTOM_COUNTER_COMPONENT_0_BASE, 0);
}

int read_counter_0_interrupt() {
	return IORD(CUSTOM_COUNTER_COMPONENT_0_BASE, 2);
}

void load_counter_0_config(int config) {
	//printf("Loading counter config %d\n", config);

	IOWR(CUSTOM_COUNTER_COMPONENT_0_BASE, 3, config);
}

// Function for initializing the ISR of the Counter
void init_counter_0_irq(elevator *data) {
	IOWR(CUSTOM_COUNTER_COMPONENT_0_BASE, 2, 0);

	alt_irq_register(CUSTOM_COUNTER_COMPONENT_0_IRQ, (void*)data, (void*)handle_counter_0_expire_interrupts );
}

////////////////////////
// CODE SECTION END   //
////////////////////////
