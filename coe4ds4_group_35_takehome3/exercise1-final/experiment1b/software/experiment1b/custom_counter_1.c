////////////////////////
// CODE SECTION BEGIN //
////////////////////////

#include "define.h"

// ISR when the counter is expired
void handle_counter_1_expire_interrupts(elevator *data)
{
	if((*data).door_hold!=1){
	printf("door closed\n");
	(*data).door_open=0;
	IOWR(CUSTOM_COUNTER_COMPONENT_1_BASE, 2, 0);
	}
}

void reset_counter_1() {
	//printf("Resetting counter value\n");

	IOWR(CUSTOM_COUNTER_COMPONENT_1_BASE, 1, 1);
	IOWR(CUSTOM_COUNTER_COMPONENT_1_BASE, 1, 0);

	IOWR(CUSTOM_COUNTER_COMPONENT_1_BASE, 2, 0);
}

int read_counter_1() {
	return IORD(CUSTOM_COUNTER_COMPONENT_1_BASE, 0);
}

int read_counter_1_interrupt() {
	return IORD(CUSTOM_COUNTER_COMPONENT_1_BASE, 2);
}

void load_counter_1_config(int config) {
	//printf("Loading counter config %d\n", config);

	IOWR(CUSTOM_COUNTER_COMPONENT_1_BASE, 3, config);
}

// Function for initializing the ISR of the Counter
void init_counter_1_irq(elevator *data) {
	IOWR(CUSTOM_COUNTER_COMPONENT_1_BASE, 2, 0);

	alt_irq_register(CUSTOM_COUNTER_COMPONENT_1_IRQ, (void*)data, (void*)handle_counter_1_expire_interrupts );
}

////////////////////////
// CODE SECTION END   //
////////////////////////
