// Copyright by Adam Kinsman, Henry Ko and Nicola Nicolici
// Developed for the Embedded Systems course (COE4DS4)
// Department of Electrical and Computer Engineering
// McMaster University
// Ontario, Canada

#include "define.h"

int main()
{
	printf("Start main...\n");

	IOWR(LED_GREEN_O_BASE, 0, 0x0);
	IOWR(LED_RED_O_BASE, 0, 0x0);

	init_button_irq();
	printf("PB initialized...\n");
	
	init_counter_irq();
	printf("Counter IRQ initialized...\n");
	
	printf("System is up!\n");

	IOWR(LED_RED_O_BASE, 0, 0xF);


	short int array[1024];
	short int arrayDPRAM[1024];
	int i;
	short int temp;
	int currentLength=0;
	int length=0;
	int address=0;

//	for(i = 0; i <10;i++){
//		array[i] = 1023-i;
//		IOWR(CUSTOM_DEC_COMPONENT_0_BASE,1,((0<<26)|((i & 0x3FF)<<16)|((array[i]) & 0xFFFF)));
//	}
//
//	for(i = 10; i <1024;i++){
//		array[i] = i;
//		IOWR(CUSTOM_DEC_COMPONENT_0_BASE,1,((0<<26)|((i & 0x3FF)<<16)|((array[i]) & 0xFFFF)));
//	}


		srand(time(NULL));
		for(i = 0; i <1024;i++){
			array[i] = 2 * (short int)rand() / (short int)RAND_MAX - 1;
			IOWR(CUSTOM_DEC_COMPONENT_0_BASE,1,((0<<26)|((i & 0x3FF)<<16)|((array[i]) & 0xFFFF)));
		}



//		for(i = 0; i <1024;i++){
//			array[i] = i;
//			IOWR(CUSTOM_DEC_COMPONENT_0_BASE,1,((0<<26)|((i & 0x3FF)<<16)|((array[i]) & 0xFFFF)));
//		}
//
//
//		for(i =10; i <1020;i++){
//			array[i] = 1023-i;
//			IOWR(CUSTOM_DEC_COMPONENT_0_BASE,1,((0<<26)|((i & 0x3FF)<<16)|((array[i]) & 0xFFFF)));
//		}
//
//		for(i = 1013; i <1023;i++){
//			array[i] = i;
//			IOWR(CUSTOM_DEC_COMPONENT_0_BASE,1,((0<<26)|((i & 0x3FF)<<16)|((array[i]) & 0xFFFF)));
//		}
//
//		for(i = 1023; i <1024;i++){
//			array[i] = i;
//			IOWR(CUSTOM_DEC_COMPONENT_0_BASE,1,((0<<26)|((i & 0x3FF)<<16)|((array[i]) & 0xFFFF)));
//		}

	for(i = 0; i <1024;i++){
		IOWR(CUSTOM_DEC_COMPONENT_0_BASE,1,((1<<26)|((i & 0x3FF)<<16)));
		arrayDPRAM[i] = IORD(CUSTOM_DEC_COMPONENT_0_BASE,0);
		printf("%d Temp= %d \n",i, arrayDPRAM[i]);
	}

	IOWR(CUSTOM_DEC_COMPONENT_0_BASE,4,0);
	IOWR(CUSTOM_DEC_COMPONENT_0_BASE,4,1);

	for(i = 1; i <1024;i++){
		if(arrayDPRAM[i]<arrayDPRAM[i-1]){
			currentLength++;
		}else{
			if(currentLength+1>=length){
				length = currentLength+1;
				address = i - length;
			}
			currentLength = 0;
		}
	}
	if(currentLength+1>=length){
		length = currentLength+1;
		address = i - length;
	}

	if(length!=1){
		printf("Software verified Address is = %d \n", address);
		printf("Software verified Length is= %d \n", length);
	}else{
		printf("No Subsequence found in Software! \n");
	}

		
	while (1);
	
	return 0;
}
