// Copyright by Adam Kinsman, Henry Ko and Nicola Nicolici
// Developed for the Embedded Systems course (COE4DS4)
// Department of Electrical and Computer Engineering
// McMaster University
// Ontario, Canada

#include "alt_types.h"
#include "sys/alt_alarm.h"
#include "sys/alt_irq.h"
#include "system.h"
#include "nios2.h"
#include "io.h"
#include "altera_avalon_mutex.h"
#include "altera_up_avalon_character_lcd.h"


//#define ARRAY_SIZE 512
#define MAX_VALUE 65536
#define SUB_MAX_LENGTH 10
#define SUB_FREQUENCY 50
#define MAX_EXPERIMENTS 25
#define DEBUG_LEVEL 1


#define CPU1_WAIT_FLAG 0x1
#define CPU2_WAIT_FLAG 0x2
#define CPU2_SEND 0x3
#define CPU1_SEND 0x4
#define FINISH_CPU1 0x5

#define BUF_SIZE 2042
#define MAX_ELE 2400
#define MIN_ELE 400




#define MESSAGE_WAITING_LCD 2
#define MESSAGE_WAITING_UART 1
#define NO_MESSAGE 0

#define LOCK_SUCCESS 0
#define LOCK_FAIL 1

#define MESSAGE_BUFFER_BASE MESSAGE_BUFFER_RAM_BASE

#define MS_DELAY 1000

// Message buffer structure

typedef struct {
	char flag;
	unsigned short int buf_size;
	unsigned short int start_arr;
	
	// the buffer can hold up to 4KBytes data
//	short buf[4095];
	unsigned short int buf[BUF_SIZE];
	unsigned short int cpu2_start;
	unsigned short int cpu2_length;
} message_buffer_struct;
// Global functions
void handle_cpu2_button_interrupts(int *count) {
    // alt_up_character_lcd_set_cursor_pos((alt_up_character_lcd_dev *)lcd_0, 0, 0);
    // alt_up_character_lcd_string((alt_up_character_lcd_dev *)lcd_0, "CPU2 PB pressed!");

	switch(IORD(CPU2_PB_BUTTON_I_BASE, 3)) {
		case 1: *count = *count + 1;  break;
		case 2: *count = *count + 1;  break;

	}

	IOWR(CPU2_PB_BUTTON_I_BASE, 3, 0x0);
}



// The main function
int main() {
	alt_up_character_lcd_dev *lcd_0;

	// Pointer to our mutex device
	alt_mutex_dev* mutex = NULL;

	// Local variables
	unsigned int id;
	unsigned int PB_count;
	unsigned int value;
	unsigned short int *data_set;
	unsigned int count = 0;
	unsigned int ticks_at_last_message;
    int switches, swit_buf;
    unsigned short int start_pos = 0;
    unsigned short int sub_length = 1;
   // unsigned short int *final_set;

	message_buffer_struct *message;
	
	PB_count = 0;
	IOWR(CPU2_PB_BUTTON_I_BASE, 2, 0x3);
	IOWR(CPU2_PB_BUTTON_I_BASE, 3, 0x0);
	alt_irq_register(CPU2_PB_BUTTON_I_IRQ, (void*)&PB_count, (void*)handle_cpu2_button_interrupts );
  
   	lcd_0 = alt_up_character_lcd_open_dev(CPU2_CHARACTER_LCD_0_NAME);
        
    alt_up_character_lcd_init(lcd_0);
    
    alt_up_character_lcd_string(lcd_0, "COE4DS4 Winter19");
    
    alt_up_character_lcd_set_cursor_pos(lcd_0, 0, 1);
    
    alt_up_character_lcd_string(lcd_0, "Lab7     exp.  3");
    
    // Reading switches 7-0 for CPU2
    switches = IORD(CPU2_SWITCH_I_BASE, 0);

	// Get our processor ID (add 1 so it matches the cpu name in SOPC Builder)
	NIOS2_READ_CPUID(id);

	// Value can be any non-zero value
	value = 1;

	switches = IORD(CPU2_SWITCH_I_BASE, 0);
	swit_buf = switches;

	//final_set =  find_max_subsequence(data_set, ARRAY_SIZE, &start_pos, &sub_length);

	// Initialize the message buffer location
	message = (message_buffer_struct*)MESSAGE_BUFFER_BASE;

	// Okay, now we'll open the real mutex
	// It's not actually a mutex to share the jtag_uart, but to share a message
	// buffer which CPU1 is responsible for reading and printing to the jtag_uart.
	mutex = altera_avalon_mutex_open(MESSAGE_BUFFER_MUTEX_NAME);

	// We'll use the system clock to keep track of our delay time.
	// Here we initialize delay tracking variable.
	ticks_at_last_message = alt_nticks();

	int i, j;

	if (mutex) {
		//message->buf[0] = NO_MESSAGE;

		while(1) {
			if (PB_count > 0) {
				      PB_count = 0;

				while ((*(char volatile *)(&(message->flag))) != CPU2_WAIT_FLAG);

				data_set = (unsigned short int *)malloc(sizeof(unsigned short int) * message->buf_size);
				unsigned short int SIZE = message->buf_size;

				if (SIZE > BUF_SIZE) {
					for (i = 0; i < BUF_SIZE; i++) {
						data_set[i] = message->buf[i];
					}
				}
				else {
					for (i = 0; i < SIZE; i++) {
						data_set[i] = message->buf[i];
					}
				}

				while (altera_avalon_mutex_trylock(mutex, value) != LOCK_SUCCESS);
				message->flag = CPU1_WAIT_FLAG;
				altera_avalon_mutex_unlock(mutex);

				while ((*(char volatile *)(&(message->flag))) != CPU2_WAIT_FLAG);

				if (SIZE > BUF_SIZE) {
					for (i = 0; i < SIZE - BUF_SIZE; i++) {
						data_set[i + BUF_SIZE] = message->buf[i];
					}
				}


				while (altera_avalon_mutex_trylock(mutex, value) != LOCK_SUCCESS);
				message->flag = CPU1_WAIT_FLAG;
				altera_avalon_mutex_unlock(mutex);



				for (i = 0; i < SIZE / 2; i++) {
					 unsigned short int sub_min = data_set[i];
					 unsigned short int sub_max = data_set[i];
					 for (j=i+1; j < SIZE; j++) {
						 if (data_set[j] < sub_min) sub_min = data_set[j];
						 if (data_set[j] > sub_max) sub_max = data_set[j];
						 // detect neighbourhood in subsequence
						 if ((sub_max - sub_min) == (j - i)) {
							 // update starting position and subsequence length
							 if ((sub_length) < (sub_max - sub_min + 1)) {
								 start_pos = i;
								 sub_length = sub_max - sub_min + 1;
							 }
						 // printf("Found subsequence at position %d\n", i);
						 }

					 }

//						while (altera_avalon_mutex_trylock(mutex, value) != LOCK_SUCCESS);
//						i = message->start_arr + 1;
//						message->start_arr = i;
//						altera_avalon_mutex_unlock(mutex);


				 }

				while (altera_avalon_mutex_trylock(mutex, value) != LOCK_SUCCESS);
				message->cpu2_start = start_pos;
				message->cpu2_length = sub_length;
				message->flag = CPU1_WAIT_FLAG;
				altera_avalon_mutex_unlock(mutex);

				free(data_set);
			}
		}


	}




	return(0);
}
