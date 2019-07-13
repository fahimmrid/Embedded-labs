// Copyright by Adam Kinsman, Henry Ko and Nicola Nicolici
// Developed for the Embedded Systems course (COE4DS4)
// Department of Electrical and Computer Engineering
// McMaster University
// Ontario, Canada

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "sys/alt_alarm.h"
#include "alt_types.h"
#include "system.h"
#include "altera_avalon_performance_counter.h"

#define ARRAY_SIZE 512

// For performance counter
void *performance_name = PERFORMANCE_COUNTER_0_BASE;

int bubble_sort(int *data_array, int size) //simple bubble sort referenced from online, link provided, (sorting for max-min)
{
		int i, j;
		//int MAX = data_array[0];
		//int MIN = data_array[size - 1];
		//alt_32 final;
		int MAX, MIN; //only using this to get the max and min
		int SWAP_data;
		for (i = 0 ; i < size - 1; i++) {
			for (j = 0 ; j < size - i - 1; j++) {
				//scanf ( % ,  )
			if (data_array[j] > data_array[j+1]) {
				SWAP_data  = data_array[j];
				data_array[j] = data_array[j+1];
				data_array[j+1] = SWAP_data;
			}
			}
			// printf("%d ", data_array[i]);

		}

		MIN = data_array[0];
	    MAX = data_array[size - 1];
        //final = MAX - MIN;
		return MAX - MIN; //once sorted, smallest always left, largest rigth

		//printf("%d ", data_array[j]);
	}

void func_Seq(int *data_array, int size)
{
	int start, j, k;
	int result, length, check;

	int sub_array[size];
	int start_pos = 0, sub_length = 0;

	for (start=0; start <size; start++) {
		for (j=start; j<size; j++) { //let j be the end...
		length = 0;
	        for (k=start; k<=j; k++) {  //1st creteria
	        	if ((data_array[k] <= data_array[start]+j-1) && data_array[k] > 0) {// && (data_array[k] != data_array[k])) { // V  to V+N-1, no duplicates
	        		sub_array[length] = data_array[k];
	        		//data_array[k+1] != data_array[k]);
	        	//	printf("sub:  %d", sub_array[length]);
	        		length++; //keep inc lengh of array here, then compare make sub_leght the longest lenght
	        	}
	        	else{
	        		k = j+1;
	        	   //printf("data:  %d", data_array[k]);
	        	}

	        //	printf("data:  %d", data_array[k]);
	        }

	        result = bubble_sort(sub_array, length); //current lenght and the max-min
	      //  printf("\n");
	       // printf("max-min= : %d\n", result);

	        if (result == (length - 1)) {  //2nd creteria
	        	if (length == sub_length && start < start_pos){
	        		start_pos = start;
	        		//length = sub_length;
	        	}
	        	if (length > sub_length && length > 1) {
	        		start_pos = start;
	        		sub_length = length;  //make newest long seqeunce the one
	            }
	        	/*if (start < start_pos || length > sub_lenght){
	        	  start_pos = start;
	        	  sub_length = length;

	        	 }*/
	        }
	      }
	    }
/*	for (check=start_pos;  check<sub_length+start_pos; check++)
		  {
		  printf("data:     %d", data_array[check]);
		  }*/

}


int main()
{ 
	alt_u16 data_set[ARRAY_SIZE];
	int i, j;
	alt_u64 SUM = 0;
	alt_u32 total = 0;
	alt_u32 val;
	//val = perf_get_section_time;

 /*  data_set[0] = 1;
	 data_set[0] = 8;
	 data_set[0] = 3;
	 data_set[0] = 7;
	 */
	

//	printf("Generating random data...");
	for ( j = 0; j < 25; j++)  {

	for (i = 0; i < ARRAY_SIZE; i++) {
		data_set[i] = rand() % 65536;
		//printf("data: %d ", data_set[i]);
	}
	
	// Reset the performance counter
	PERF_RESET(PERFORMANCE_COUNTER_0_BASE);
	
	// Start the performance counter
	PERF_START_MEASURING(performance_name);
	
//	printf("Generating Subsequemce S...");
	
	// Start measuring code section
	PERF_BEGIN(performance_name, 1);
	
	func_Seq(data_set, ARRAY_SIZE);
	//bubble_sort(data_set, ARRAY_SIZE);
	
	// Stop measuring code section
	PERF_END(performance_name, 1);

	// Stop the performance counter
	PERF_STOP_MEASURING(performance_name);
	
	//printf("------------------\n");
	printf("PC: %llu", perf_get_section_time(performance_name, 1));
	val = perf_get_section_time(performance_name, 1);
	  printf("\n");
	//printf("------------------\n");
  /* Event loop never exits. */



	SUM += val;

	}

	total = SUM/25;
	printf("------------------\n");
	printf("Average running time:      %d\n", total );
	printf("------------------\n");


  while (1);

  return 0;
}
