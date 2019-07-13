// Copyright by Adam Kinsman, Henry Ko and Nicola Nicolici
// Developed for the Embedded Systems course (COE4DS4)
// Department of Electrical and Computer Engineering
// McMaster University
// Ontario, Canada

#include "define.h"

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

void print_array(unsigned short int *array,
                 unsigned short int size)
{
    unsigned int short i;
    printf("Array: ");
    for (i=0; i<size; i++)
        printf("%d ", array[i]);
    printf("\n");
}

int random_array(alt_u16* array, int size, alt_u16 index){
	int i;
	for(i=0; i<size; ++i){
		if(array[i]==index)
			return 1;
	}
	return 0;
}

//max seq for testing verfication purposes
void max_subsequence(alt_u16 *array, int size, final_ele *value){

	value->seq_one = 0, value->seq_two = 0;
	int i,j;
	alt_u16 min,max;

	for(i = 0; i < size; ++i){
		min = array[i];
		max = array[i];
	  for(j = i+1; j < size; ++j){
		if(array[j] < min)
				min = array[j];
			else if (array[j] > max)
				max = array[j];
			 if( (max-min == j-i) && (j-i > value->seq_two - value->seq_one) ){
				    value->seq_one = i;
				 	value->seq_two = j;
			}

		   }
	}
}



int main()
{
	printf("Start main...\n");
	hardware();
	//IOWR(LED_GREEN_O_BASE, 0, 0x0);
	IOWR(LED_RED_O_BASE, 0, 0x0);

	unsigned char volatile pb_pvaluesed = 0x0;
	init_button_irq((void *)&pb_pvaluesed);
	printf("PB initialized...\n");

	while (1) {
			printf("Pvalues any push button to generate a random array.\n");
			unsigned int seed = 0;
			while (!pb_pvaluesed) seed++;
			pb_pvaluesed = 0;
			srand(seed);

    alt_u16 array_random;
	alt_u16 data_set[ARRAY_SIZE];

	printf("Array Generated: \n");
	printf("\nWriting to the DP RAM: \n");

	int i;
	for (i = 0; i < ARRAY_SIZE; ++i){
		array_random = (alt_u16)rand()%NUM_MAX;
		 while(random_array(data_set, i, array_random) == 1)
			array_random = (alt_u16)rand()%NUM_MAX;
		data_set[i] = array_random;

		printf("%d ", array_random);

	   //WRITE_ELEMENT(CUSTOM_COUNTER_COMPONENT_0_BASE, i, data_set[i])
		IOWR(CUSTOM_COUNTER_COMPONENT_0_BASE, 1, (0x1<<25) | (i & 0x1FF) << 16 |(array_random & 0xFFFF));
	  }

	printf("\n\nWriting to DP RAM complete.\n");

	printf("\n Now Reading from DP RAM:  \n ");
	for(i = 0; i < ARRAY_SIZE; ++i){
		//READ_ELEMENT(CUSTOM_COUNTER_COMPONENT_0_BASE, i, data_set[i])
		IOWR(CUSTOM_COUNTER_COMPONENT_0_BASE, 1, (0x0<<25) | (i & 0x1FF) << 16);
		printf("%d ", IORD(CUSTOM_COUNTER_COMPONENT_0_BASE, 0));
	}
	printf("\nDONE!\n Reading from RAM was successful.\n\n");

	final_ele value;

	max_subsequence(data_set, ARRAY_SIZE, &value);

	printf("The result from Software sequence: \n");

	printf("Array Position: %d, Array size:  %d\n", value.seq_one, value.seq_two - value.seq_one +1);
	printf("\n");
    //harware n clear
	IOWR(CUSTOM_COUNTER_COMPONENT_0_BASE, 3, (0x1<<31) | (0x0));

	while (1);

	printf("Software and Hardware Match!! \n");

	return 0;
	}
}
