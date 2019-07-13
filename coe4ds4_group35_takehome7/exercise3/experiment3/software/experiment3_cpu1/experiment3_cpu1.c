// Copyright by Adam Kinsman, Henry Ko and Nicola Nicolici
// Developed for the Embedded Systems course (COE4DS4)
// Department of Electrical and Computer Engineering
// McMaster University
// Ontario, Canada

#include <stdio.h>
#include <string.h>
#include "sys/alt_alarm.h"
#include "alt_types.h"
#include "sys/alt_irq.h"
#include "system.h"
#include "nios2.h"
#include "io.h"
#include "altera_avalon_mutex.h"
#include "altera_avalon_performance_counter.h"


#define ARRAY_SIZE 512
#define MAX_VALUE 65536
#define SUB_MAX_LENGTH 10
#define SUB_FREQUENCY 50
#define MAX_EXPERIMENTS 25
#define DEBUG_LEVEL 1
#define MAX 2400
#define MIN 400
#define BUF_SIZE 2042


#define MESSAGE_WAITING_LCD 2
#define MESSAGE_WAITING_UART 1
#define NO_MESSAGE 0

#define CPU1_WAIT_FLAG 0x1
#define CPU2_WAIT_FLAG 0x2
#define CPU2_SEND 0x3
#define CPU1_SEND 0x4
#define FINISH_CPU1 0x5

#define LOCK_SUCCESS 0
#define LOCK_FAIL 1

#define MESSAGE_BUFFER_BASE MESSAGE_BUFFER_RAM_BASE

#define MS_DELAY 1000


//int x = PERF_RESET;
// Message buffer structure
typedef struct { //4K so made sure its 4095 used!
	char flag;
	unsigned short int buf_size;
	unsigned short int start_arr;
	
	// the buffer can hold up to 4KBytes data
//	short buf[4095];
	unsigned short int buf[BUF_SIZE];
	unsigned short int cpu2_start;
	unsigned short int cpu2_length;
} message_buffer_struct;

// For performance counter
//void *performance_name = CPU1_PERFORMANCE_COUNTER_BASE; ****


// Global functions
unsigned char a = 0;
		unsigned char b = 0;
void handle_cpu1_button_interrupts(int *count) { //without this syntax didnt run
	switch(IORD(CPU1_PB_BUTTON_I_BASE, 3)) {
	case 1: printf("CPU1 PB0 pressed: Please Wait \n"); *count = *count + 1; break;
	case 2: printf("CPU1 PB1 pressed: Please Wait \n"); *count = *count + 1; break;
	}
	IOWR(CPU1_PB_BUTTON_I_BASE, 3, 0x0);
}

//---------------- LAB 3 EXERCISE 3 ----------------------
//----------------------------------------------------------------------------------------------------------------------------------------------
void print_array(unsigned short int *array,
                 unsigned short int size)
{
    unsigned int short i;
    printf("Array: ");
    for (i=0; i<size; i++)
        printf("%d ", array[i]);
    printf("\n");
}

unsigned char found_value_in_array(unsigned short int *array,
                                   unsigned short int size,
                                   unsigned short int value)
{
    unsigned int short i;
    for (i=0; i<size; i++)
        if (array[i] == value)
            return 1;
    return 0;
}

void reshuffle_subsequence(unsigned short int *array,
                           unsigned short int start_pos,
                           unsigned short int sub_length)
{
    unsigned int short i;
    for (i=start_pos; i<start_pos+sub_length; i++) {
        unsigned short int j = start_pos + (unsigned short int)(rand() % sub_length);
        unsigned short int tmp = array[i];
        array[i] = array[j];
        array[j] = tmp;
    }
}

unsigned short int* generate_random_array(unsigned int size)
{
    unsigned short int *array = malloc(sizeof(unsigned short int)*size);
    unsigned int short i;
    for (i=0; i<size; i++)
    {
        unsigned short int sub_avoid = (unsigned short int)(rand() % SUB_FREQUENCY);
        unsigned short int sub_length = (unsigned short int)(rand() % (SUB_MAX_LENGTH-2))+2;
        unsigned short int value = (unsigned short int)(rand() % MAX_VALUE);
        if ((!sub_avoid) && ((i+sub_length) < size)) {
            unsigned short int j;
            for (j=0; j<sub_length; j++) {
                if (found_value_in_array(array, i+j, value)) {
                    break;
                } else {
                    array[i+j] = value;
                    value++;
                }
            }
            // printf("Generated subsequence of length %d starting at start_arr %d\n", j, i);
            reshuffle_subsequence(array, i, j);
            i += j-1;
        } else {
            while (found_value_in_array(array, i, value))
                value = (unsigned short int)(rand() % MAX_VALUE);
            array[i] = value;
        }
    }
    return array;
}

void delete_array(unsigned short int *array)
{
    free(array);
}

void find_max_subsequence(unsigned short int *array,
                          unsigned short int size,
                          unsigned short int *start_pos,
                          unsigned short int *sub_length)
{
    unsigned int short i;
    for (i=0; i<size; i++) {
        unsigned short int sub_min = array[i];
        unsigned short int sub_max = array[i];
        unsigned int short j;
        for (j=i+1; j<size; j++) {
            if (array[j] < sub_min) sub_min = array[j];
            if (array[j] > sub_max) sub_max = array[j];
            // detect neighbourhood in subsequence
            if ((sub_max - sub_min) == (j - i)) {
                // update starting position and subsequence length
                if ((*sub_length) < (sub_max - sub_min + 1)) {
                    *start_pos = i;
                    *sub_length = sub_max - sub_min + 1;
                }
                // printf("Found subsequence at position %d\n", i);
            }
        }
    }
}

void print_subsequence(unsigned short int *array,
                       unsigned short int start_pos,
                       unsigned short int sub_length)
{
    unsigned int short i;
    printf("\nSubsequence of length %d starting at position %d: ", sub_length, start_pos);
    for (i=start_pos; i<start_pos+sub_length; i++)
        printf("%d ", array[i]);
    printf("\n\n");
}

//----------------------------------------------------------------------------------------------------------------------------------------------
// The main function



int main() {
	// Pointer to our mutex device



	int switches;
	unsigned int swit_buf;
	unsigned int num_iteration; //# of times cpu runs
	unsigned int PB_count;
	unsigned short int start_pos;
	unsigned short int sub_length;

	alt_mutex_dev* mutex = NULL;
	unsigned int id;
	unsigned int value;
	unsigned int count = 0;
	unsigned int ticks_at_last_message;
	unsigned short int *array_store;

	int SIZE;

	//unsigned short int *final_set;

	void *performance_name = NULL;
	message_buffer_struct *message;

	// Get our processor ID (add 1 so it matches the cpu name in SOPC Builder)
		NIOS2_READ_CPUID(id);

	printf("COE4DS4 Winter19\n");
	printf("Lab7     exp.  3\n\n");
	printf("Press Push button 1 or 2 :\n");

	// Value can be any non-zero value
	value = 1;

	// Reading switches 15-8 for CPU1
	switches = IORD(CPU1_SWITCH_I_BASE, 0);
	swit_buf = switches;
	unsigned int seed = switches;
	srand(seed);

	// Enable all button interrupts
		PB_count = 0;
		IOWR(CPU1_PB_BUTTON_I_BASE, 2, 0x3);
		IOWR(CPU1_PB_BUTTON_I_BASE, 3, 0x0);
		alt_irq_register(CPU1_PB_BUTTON_I_IRQ, (void*)&PB_count, (void*)handle_cpu1_button_interrupts );


	 unsigned short int i, j;
	 /*
	 while (altera_avalon_mutex_trylock(mutex, value) != LOCK_SUCCESS);

	 if (SIZE > BUF_SIZE) {
		 for (i = 0; i < BUF_SIZE; i++) {
			 message->buf[i] = array_store[i];
		 }
	 }
	 else {
		 for (i = 0; i < SIZE; i++) {
			 message->buf[i] = array_store[i];
		 }
	 }

	 message->size = SIZE;
	 message->start_arr = 1;
	 message->flag = CPU2_WAIT_FLAG;
	 altera_avalon_mutex_unlock(mutex);

	 while (message->flag != CPU1_WAIT_FLAG);

	 if (SIZE > BUF_SIZE) {
		 while (altera_avalon_mutex_trylock(mutex, value) != LOCK_SUCCESS);
		 for (i = 0; i < SIZE - BUF_SIZE; i++) {
			 message->buf[i] = array_store[BUF_SIZE + i];
		 }
		 message->flag = CPU2_WAIT_FLAG;
		 altera_avalon_mutex_unlock(mutex);
	 }

	 while (message->flag != CPU1_WAIT_FLAG);
	 */

	// Initialize the message buffer location
	message = (message_buffer_struct*)MESSAGE_BUFFER_BASE;

	// Okay, now we'll open the real mutex
	// It's not actually a mutex to share the jtag_uart, but to share a message
	// buffer which CPU1 is responsible for reading and printing to the jtag_uart.
	mutex = altera_avalon_mutex_open(MESSAGE_BUFFER_MUTEX_NAME);

	performance_name = (void *)CPU1_PERFORMANCE_COUNTER_BASE;

	// For performance counter
	//PERF_RESET(CPU1_PERFORMANCE_COUNTER_BASE);
	//PERF_START_MEASURING(CPU1_PERFORMANCE_COUNTER_BASE);

	//printf (" %d \n", PERF_RESET);
//	printf (" %d \n",CPU1_PERFORMANCE_COUNTER_BASE );

//	message->CPU_2_Flag = NO_MESSAGE  ;

//	buf[message]

	if (mutex) {
		//message->flag = NO_MESSAGE;
		while(1) {
			SIZE = (rand() % 2001) + 400;

			start_pos = 0;
			sub_length = 1;
			//printf("PB count = %d\n", PB_count);
			while (altera_avalon_mutex_trylock(mutex, value) != LOCK_SUCCESS);

			message->cpu2_start = 0;
			message->cpu2_length = 1;
			altera_avalon_mutex_unlock(mutex);

			if (PB_count > 0) {
			     PB_count = 0;

				 PERF_RESET(CPU1_PERFORMANCE_COUNTER_BASE);
			     PERF_START_MEASURING(performance_name);

			    //if ((a == 1 || b ==1)) {// generate random seq

				//while (PB_count) PB_count--;
				 array_store = generate_random_array(SIZE);
				 printf("Generated array:\n");
				 print_array(array_store, SIZE);

//---------------------------P 2--------------
				 PERF_BEGIN(performance_name, 2);

				 find_max_subsequence(array_store, SIZE, &start_pos, &sub_length);

				 PERF_END(performance_name, 2);
 //---------------------------P 2--------------

				 print_subsequence(array_store, start_pos, sub_length);

				 while (altera_avalon_mutex_trylock(mutex, value) != LOCK_SUCCESS);


				 printf("CPU 2 is ready to search! \n");
				 if (SIZE > BUF_SIZE) { //Send as many ele to cpu2
					 for (i = 0; i < BUF_SIZE; i++) {
						 message->buf[i] = array_store[i];
					 }
				 }

				 else {
					 for (i = 0; i < SIZE; i++) {
						 message->buf[i] = array_store[i];
							//printf(" %d", message->buf[i] \n");
					 }
				 }

				// printf("Array from CPU1 transferred to CPU2!\n");
				 	 message->buf_size = SIZE;
				 	 message->start_arr = 1;
				 message->flag = CPU2_WAIT_FLAG;
				 altera_avalon_mutex_unlock(mutex);


				 printf("Press Push button 2 or 3 \n");
				 while ((*(char volatile *)(&(message->flag))) != CPU1_WAIT_FLAG);

				 //printf("came back to CPU1 \n"); //debug
				 if (SIZE > BUF_SIZE) {
					 while (altera_avalon_mutex_trylock(mutex, value) != LOCK_SUCCESS);
					 for (i = 0; i < SIZE - BUF_SIZE; i++) {
						 message->buf[i] = array_store[BUF_SIZE + i];
					 }

					  message->flag = CPU2_WAIT_FLAG;
					 altera_avalon_mutex_unlock(mutex);
					 printf("More data sent!");
				 }
				 while ((*(char volatile *)(&(message->flag))) != CPU1_WAIT_FLAG);

				 printf("Completed! (Debugging purposes) \n");

//----------------PERFORMANCE COUNTER 1-------------

				PERF_BEGIN(performance_name, 1);

				 printf("Finding longest for CPU1 (half of array)  \n");
				 //doing Half the size search, from middle to end*****
				 //****- modified longest seq****
				 for (i = SIZE / 2; i < SIZE; i++) {
					 unsigned short int sub_min = array_store[i];
					 unsigned short int sub_max = array_store[i];
					 for (j=i+1; j < SIZE; j++) {
						 if (array_store[j] < sub_min) sub_min = array_store[j];
						 if (array_store[j] > sub_max) sub_max = array_store[j];
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

//					while (altera_avalon_mutex_trylock(mutex, value) != LOCK_SUCCESS);
//					i = message->start_arr + 1;
//					message->start_arr = i;
//					altera_avalon_mutex_unlock(mutex);


				 }

//----------------------- PERFORMAANCE COUNTER 1 DONE

				printf("Modifed sorting complete, continue to CPU2!\n");
				while ((*(char volatile *)(&(message->flag))) != CPU1_WAIT_FLAG);
				while (altera_avalon_mutex_trylock(mutex, value) != LOCK_SUCCESS);

				 PERF_END(performance_name, 1);

				if (message->cpu2_length > sub_length) {
					sub_length = message->cpu2_length;
					start_pos = message->cpu2_start;
				}
				altera_avalon_mutex_unlock(mutex);

				printf("Searching on both CPU complete, longest subsequence obtained!\n");

				print_subsequence(array_store, start_pos, sub_length);

				//PERFORMANCE COUNTER RESULTS ----

				printf("PERFORMANCE RESULTS: \n");

				printf("Measuring Only CPU1 performance: %d clock cycles for finding subseqeunce\n" ,(unsigned int)perf_get_section_time(performance_name, 2));
				printf("Measuring concurrent performance: %d clock cycles for finding subseqeunce\n",(unsigned int)perf_get_section_time(performance_name, 1));

				printf("**Speed up is: %4.2fx\n", ((double)perf_get_section_time(performance_name, 2))/((double)perf_get_section_time(performance_name, 1)));

				PERF_STOP_MEASURING(performance_name);


				free(array_store);

			}

		//	swit_buf = switches;
		//	switches = IORD(CPU1_SWITCH_I_BASE, 0);
		}
	}


	return(0);
}




