// Copyright by Adam Kinsman, Henry Ko and Nicola Nicolici
// Developed for the Embedded Systems course (COE4DS4)
// Department of Electrical and Computer Engineering
// McMaster University
// Ontario, Canada

#include "define.h"

// For the performance counter
void *performance_name = PERFORMANCE_COUNTER_0_BASE;

// Definition of semaphore for PBs
OS_EVENT *PBSemaphore[4];

// Definition of mailboxes
OS_EVENT *MboxGenArrayStart[2];

OS_EVENT *MboxMultBegin0[4];
OS_EVENT *MboxMultBegin1[4];
OS_EVENT *MboxMultFin[4];
OS_EVENT *MboxMultMerge;

// memory partition
OS_MEM	*MemoryPartition;

OS_MEM *MemoryPartitionDistinct;

// Definition of task stacks
OS_STK	  initialize_task_stk[TASK_STACKSIZE];
OS_STK	  task_launcher_stk[TASK_STACKSIZE];


OS_STK	  gen_array_stk[2][TASK_STACKSIZE];
OS_TCB	  gen_array_tcb[2];


OS_STK	  mul_stk[TASK_STACKSIZE];
OS_TCB	  mul_tcb;
OS_STK	  cal_mul_stk[4][TASK_STACKSIZE];
OS_TCB	  cal_mul_tcb[4];
OS_STK	  merge_stk[TASK_STACKSIZE];
OS_TCB	  merge_tcb;


// The sorting task
// It has the highest priority
// But it initiates other tasks by posting a message in the corresponding mailboxes
// Then it wait for the result to be computed by monitoring other mailboxes
// In the mean time, it'll suspend itself to free up the processor
void multiply(void* pdata) {
	INT8U return_code = OS_NO_ERR;
	int i;
	int *data_array[2];
	int *merge_value;
	int x;
	int y=0;

	// Delay for 2 secs so that the message from this task will be displayed last
	// If not delay, since it has highest priority, the wait message for PB0 will be displayed first
	OSTimeDlyHMSM(0, 0, 2, 0);

	printf("Waiting for PB0 to determine min/max 2 arrays each with %d entries\n", ARRAY_SIZE);
	OSSemPend(PBSemaphore[0], 0, &return_code);
	alt_ucosii_check_return_code(return_code);

	printf("multiply started\n");

	// Get the memory block from memory partition, and pass that memory block to other task through mailboxes
	// to start data generation
	for (i = 0; i < 2; i++) {
		data_array[i] = OSMemGet(MemoryPartition, &return_code);
		alt_ucosii_check_return_code(return_code);
			
		return_code = OSMboxPost(MboxGenArrayStart[i], (void *)(data_array[i]));
		alt_ucosii_check_return_code(return_code);
		}
		
		// Start the performance counter
		//PERF_START_MEASURING(performance_name);
	    PERF_RESET(performance_name);

		printf("-waiting for merge...\n");

		// Now wait for merged value
		//OSTimeDlyHMSM(0, 0, 4, 0);
		merge_value = (int *)OSMboxPend(MboxMultMerge, 0, &return_code);
		alt_ucosii_check_return_code(return_code);

		//delay
		OSTimeDlyHMSM(0, 0, 4, 0);
		printf("\n C: \n");
		//printf("merg_value = %d\n", merge_value[0]);
		//merged array C
		for(i=0; i<ARRAY_XY;i++){
			for(x=0;x<ARRAY_XY;x++){
				y=x+(i*ARRAY_XY);
				printf("%d ",merge_value[y]);
				if(x==(ARRAY_XY -1)){
					printf("\n");

				}
			}
			OSTimeDlyHMSM(0, 0, 0, 60);
		}


		// Now wait for max value
		//max_value = (INT16U *)OSMboxPend(MboxFindMinMax, 0, &return_code);
		//alt_ucosii_check_return_code(return_code);

		// Stop the performance counter
		//PERF_STOP_MEASURING(performance_name);

		//printf("Done: Min: %d, Max: %d\n", *min_value, *max_value);

		printf("\nArray random generation PC: %d\n", (unsigned int)perf_get_section_time(performance_name,1));
		OSTimeDlyHMSM(0, 0, 0, 60);
		printf("Array calculation PC: %d\n", (unsigned int)perf_get_section_time(performance_name,2));
		OSTimeDlyHMSM(0, 0, 0, 60);
		printf("Merge	PC: %d\n", (unsigned int)perf_get_section_time(performance_name,3));
		OSTimeDlyHMSM(0, 0, 0, 60);
		

		return_code = OSMemPut(MemoryPartition, (void *)merge_value);
		alt_ucosii_check_return_code(return_code);


}

// gen_array_0 task
// It randomly generates numbers in the range of 0-65535 (16 bits)
// And stores them in the data array obtained from the mailbox
void gen_array_0(void* pdata) {
	INT8U return_code = OS_NO_ERR;
	int i;
	//INT16U min_value, max_value;
	int *data_array;
	int switches;
	int x;
	int y=0;

	while (1) {
		printf("gen_array_0 wait for start\n");
		data_array = (int *)OSMboxPend(MboxGenArrayStart[0], 0, &return_code);
		alt_ucosii_check_return_code(return_code);

		printf("gen_array_0 started (%p)\n", data_array);
		PERF_START_MEASURING(performance_name);
		PERF_BEGIN(performance_name,1);

		//max_value = 0;
		//min_value = 65535;

		// Get the seed from the switches
		switches = IORD(SWITCH_I_BASE, 0);

		srand(switches);

		// Start generation
		for (i = 0; i < ARRAY_SIZE; i++) {
			data_array[i] = ((unsigned int)rand() % 60001) - 30000;
		}

		PERF_END(performance_name,1);
		PERF_STOP_MEASURING(performance_name);

		//delay
		OSTimeDlyHMSM(0, 0, 4, 0);
		printf("\n A: \n");

		for(i=0; i<ARRAY_XY;i++){
			for(x=0;x<ARRAY_XY;x++){
				y=x+(i*ARRAY_XY);
				printf("%d ",data_array[y]);
				if(x==(ARRAY_XY -1)){
					printf("\n");
						}
					}
			OSTimeDlyHMSM(0, 0, 0, 60);
		}


		printf("gen_array_0 done \n");
		
		// When data generation is finished, the data array is posted to
		// two different mailboxes, so that the two tasks for finding
		// the min and max values in the array will be initiated
		for(i=0;i<4;i++){
			return_code = OSMboxPost(MboxMultBegin0[i], (void *)(data_array));
		    alt_ucosii_check_return_code(return_code);
		}

		OSTimeDlyHMSM(0, 0, 1, 0);
	}
}

// gen_array_1 task
// It randomly generates numbers in the range of 0-65535 (16 bits)
// And stores them in the data array obtained from the mailbox
void gen_array_1(void* pdata) {
	int *data_array;
	INT8U return_code = OS_NO_ERR;
	int i;
	//INT16U min_value, max_value;
	int switches;
	int x;
	int y=0;

	while (1) {
		printf("gen_array_1 wait for start\n");
		data_array = (int *)OSMboxPend(MboxGenArrayStart[1], 0, &return_code);
		alt_ucosii_check_return_code(return_code);

		printf("gen_array_1 started (%p)\n", data_array);
		PERF_START_MEASURING(performance_name);
		PERF_BEGIN(performance_name,1);

		//max_value = 0;
		//min_value = 65535;

		// Get the seed from the switches
		switches = IORD(SWITCH_I_BASE, 0);

		srand(~switches);

		// Start generation
		for (i = 0; i < ARRAY_SIZE; i++) {
			data_array[i] = ((unsigned int)rand() % 2001) - 1000;
		}

		PERF_END(performance_name,1);
		PERF_STOP_MEASURING(performance_name);

		//delay
		OSTimeDlyHMSM(0, 0, 8, 0);
		printf("\n B: \n");
		for(i=0; i<ARRAY_XY;i++){
			for(x=0;x<ARRAY_XY;x++){
				y=x+(i*ARRAY_XY);
				printf("%d ",data_array[y]);
				if(x==(ARRAY_XY -1)){
					printf("\n");
				}
			}
			OSTimeDlyHMSM(0, 0, 0, 120);
		}
		printf("gen_array_1 done \n");

		// When data generation is finished, the data array is posted to
		// two different mailboxes, so that the two tasks for finding
		// the min and max values in the array will be initiated
		for(i=0;i<4;i++){
			return_code = OSMboxPost(MboxMultBegin1[i], (void *)(data_array));
			alt_ucosii_check_return_code(return_code);
		}
		OSTimeDlyHMSM(0, 0, 1, 0);
	}
}

// find_min_0 task
// It obtains the data array from the mailbox
// and then find the min value in the array
void top_left_mult(void* pdata) {
	int *data_array_a;
	int *data_array_b;
	int *data_array_distinct;
	INT8U return_code = OS_NO_ERR;
	int i;
	int x;
	int y;
	int z=0;
	int n=0;
	int u=0;

	while (1) {
		printf("top_left_mult wait for start\n");
		data_array_a = (int *)OSMboxPend(MboxMultBegin0[0], 0, &return_code);
		alt_ucosii_check_return_code(return_code);
		data_array_b = (int *)OSMboxPend(MboxMultBegin1[0], 0, &return_code);
		alt_ucosii_check_return_code(return_code);
		printf("top_left_mult started (%p,%p)\n", data_array_a,data_array_b);

		// Start performance counter
		PERF_START_MEASURING(performance_name);
		PERF_BEGIN(performance_name, 2);

		data_array_distinct=OSMemGet(MemoryPartitionDistinct, &return_code);
		alt_ucosii_check_return_code(return_code);

		//min_value = 65535;
		for (i = 0; i < (ARRAY_SIZE/4); i++) {
			data_array_distinct[i]=0;
		}

		for(i=0; i<(ARRAY_XY/2);i++){
			for(x=0;x<(ARRAY_XY/2);x++){
				for(y=0;y<ARRAY_XY;y++){
					z=y+(i*ARRAY_XY);
					n=x+(i*(ARRAY_XY/2));
					u=x+(y*ARRAY_XY);
					data_array_distinct[n]+=data_array_a[z]*data_array_b[u];
				}
			}
		}
		// Stop performance counter
		PERF_END(performance_name, 2);
		PERF_STOP_MEASURING(performance_name);
		
        //DEBUG
        //printf("first val = %d\n", data_array_distinct[0]);
		printf("top_left_mult done \n");
		
		// Post the min value to the mailbox for other task
		return_code = OSMboxPost(MboxMultFin[0], (void *)(data_array_distinct));
		alt_ucosii_check_return_code(return_code);

		OSTimeDlyHMSM(0, 0, 1, 0);
	}
}

void top_right_mult(void* pdata) {
	int *data_array_a;
	int *data_array_b;
	int *data_array_distinct;
	INT8U return_code = OS_NO_ERR;
	int i;
	int x;
	int y;
	int z=0;
	int n=0;
	int u=0;

	while (1) {
		printf("top_right_mult wait for start\n");
		data_array_a = (int *)OSMboxPend(MboxMultBegin0[1], 0, &return_code);
		alt_ucosii_check_return_code(return_code);
		data_array_b = (int *)OSMboxPend(MboxMultBegin1[1], 0, &return_code);
		alt_ucosii_check_return_code(return_code);
		printf("top_right_mult started (%p,%p)\n", data_array_a,data_array_b);

		// Start performance counter
		PERF_START_MEASURING(performance_name);
		PERF_BEGIN(performance_name, 2);

		data_array_distinct=OSMemGet(MemoryPartitionDistinct, &return_code);
		alt_ucosii_check_return_code(return_code);

		//min_value = 65535;
		for (i = 0; i < (ARRAY_SIZE/4); i++) {
			data_array_distinct[i]=0;
		}

		for(i=0; i<(ARRAY_XY/2);i++){
			for(x=0;x<(ARRAY_XY/2);x++){
				for(y=0;y<ARRAY_XY;y++){
					z=y+(i*ARRAY_XY);
					n=x+(i*(ARRAY_XY/2));
					u=(x+(ARRAY_XY/2))+(y*ARRAY_XY);
					data_array_distinct[n]+=data_array_a[z]*data_array_b[u];
				}
			}
		}
		// Stop performance counter
		PERF_END(performance_name, 2);
		PERF_STOP_MEASURING(performance_name);

		printf("top_right_mult done\n");

		// Post the min value to the mailbox for other task
		return_code = OSMboxPost(MboxMultFin[1], (void *)(data_array_distinct));
		alt_ucosii_check_return_code(return_code);

		OSTimeDlyHMSM(0, 0, 1, 0);
	}
}

void bottom_left_mult(void* pdata) {
	int *data_array_a;
	int *data_array_b;
	int *data_array_distinct;
	INT8U return_code = OS_NO_ERR;
	int i;
	int x;
	int y;
	int z=0;
	int n=0;
	int u=0;

	while (1) {
		printf("bottom_left_mult wait for start\n");
		data_array_a = (int *)OSMboxPend(MboxMultBegin0[2], 0, &return_code);
		alt_ucosii_check_return_code(return_code);
		data_array_b = (int *)OSMboxPend(MboxMultBegin1[2], 0, &return_code);
		alt_ucosii_check_return_code(return_code);
		printf("bottom_left_mult started (%p,%p)\n", data_array_a,data_array_b);

		// Start performance counter
		PERF_START_MEASURING(performance_name);
		PERF_BEGIN(performance_name, 2);

		data_array_distinct=OSMemGet(MemoryPartitionDistinct, &return_code);
		alt_ucosii_check_return_code(return_code);

		//min_value = 65535;
		for (i = 0; i < (ARRAY_SIZE/4); i++) {
			data_array_distinct[i]=0;
		}

		for(i=0; i<(ARRAY_XY/2);i++){
			for(x=0;x<(ARRAY_XY/2);x++){
				for(y=0;y<ARRAY_XY;y++){
					z=y+((i+(ARRAY_XY/2))*ARRAY_XY);
					n=x+(i*(ARRAY_XY/2));
					u=x+(y*ARRAY_XY);
					data_array_distinct[n]+=data_array_a[z]*data_array_b[u];
				}
			}
		}
		// Stop performance counter
		PERF_END(performance_name, 2);
		PERF_STOP_MEASURING(performance_name);

		printf("bottom_left_mult done \n");

		// Post the min value to the mailbox for other task
		return_code = OSMboxPost(MboxMultFin[2], (void *)(data_array_distinct));
		alt_ucosii_check_return_code(return_code);

		OSTimeDlyHMSM(0, 0, 1, 0);
	}
}

void bottom_right_mult(void* pdata) {
	int *data_array_a;
	int *data_array_b;
	int *data_array_distinct;
	INT8U return_code = OS_NO_ERR;
	int i;
	int x;
	int y;
	int z=0;
	int n=0;
	int u=0;

	while (1) {
		printf("bottom_right_mult wait for start\n");
		data_array_a = (int *)OSMboxPend(MboxMultBegin0[3], 0, &return_code);
		alt_ucosii_check_return_code(return_code);
		data_array_b = (int *)OSMboxPend(MboxMultBegin1[3], 0, &return_code);
		alt_ucosii_check_return_code(return_code);
		printf("bottom_right_mult started (%p,%p)\n", data_array_a,data_array_b);

		// Start performance counter
		PERF_START_MEASURING(performance_name);
		PERF_BEGIN(performance_name, 2);

		data_array_distinct=OSMemGet(MemoryPartitionDistinct, &return_code);
		alt_ucosii_check_return_code(return_code);

		//min_value = 65535;
		for (i = 0; i < (ARRAY_SIZE/4); i++) {
			data_array_distinct[i]=0;
		}

		for(i=0; i<(ARRAY_XY/2);i++){
			for(x=0;x<(ARRAY_XY/2);x++){
				for(y=0;y<ARRAY_XY;y++){
					z=y+((i+(ARRAY_XY/2))*ARRAY_XY);
					n=x+(i*(ARRAY_XY/2));
					u=(x+(ARRAY_XY/2))+(y*ARRAY_XY);
					data_array_distinct[n]+=data_array_a[z]*data_array_b[u];
				}
			}
		}
		// Stop performance counter
		PERF_END(performance_name, 2);
		PERF_STOP_MEASURING(performance_name);

		printf("bottom_right_mult done \n");

		// Post the min value to the mailbox for other task
		return_code = OSMboxPost(MboxMultFin[3], (void *)(data_array_distinct));
		alt_ucosii_check_return_code(return_code);

		OSTimeDlyHMSM(0, 0, 1, 0);
	}
}

void merge(void* pdata) {
	int *array_c;
	int *distinct_c[4];
	int return_code = OS_NO_ERR;
	int i;
	int x;
	int y;
	int z=0;
	int n=0;
	int u=0;
	int d=0;
	int b=0;

	while (1) {
		printf("merge wait for start\n");

		for(i=0;i<4;i++){
			distinct_c[i]=(int *)OSMboxPend(MboxMultFin[i], 0, &return_code);
			alt_ucosii_check_return_code(return_code);
		}

		//data_array = (INT16U *)OSMboxPend(MboxFindMaxStart[0], 0, &return_code);
		//alt_ucosii_check_return_code(return_code);
		printf("merge  started \n");

		// Start performance counter
		PERF_START_MEASURING(performance_name);
		PERF_BEGIN(performance_name, 3);

		array_c=(int *)OSMemGet(MemoryPartition, &return_code);
		alt_ucosii_check_return_code(return_code);

		//DEBUG
		//printf("first val merge = %d\n", distinct_c[0][0]);

		for(i=0;i<4;i++){
			for(x=0;x<(ARRAY_XY/2);x++){
				for(y=0;y<(ARRAY_XY/2);y++){
					z=y+(x*ARRAY_XY);
					n=y+((x+(ARRAY_XY/2))*ARRAY_XY);
					u=(y+(ARRAY_XY/2))+(x*ARRAY_XY);
					d=(y+(ARRAY_XY/2))+((x+(ARRAY_XY/2))*ARRAY_XY);
					b=y+(x * (ARRAY_XY/2));
					if(i<2){
						if(i%2==0){
							array_c[z]=distinct_c[i][b];
						}else{
							array_c[u]=distinct_c[i][b];
						}
					}else{
						if(i%2==0){
							array_c[n]=distinct_c[i][b];
						}else{
							array_c[d]=distinct_c[i][b];
						}
					}

				}
			}
		}
		//DEBUG
		//printf("first val merge = %d\n", array_c[0]);
		// Stop performance counter
		PERF_END(performance_name, 3);
	    PERF_STOP_MEASURING(performance_name);

		printf("merge done \n");

		for(i=0;i<4;i++){
			OSMemPut(MemoryPartitionDistinct, (void *)distinct_c[i]);
			alt_ucosii_check_return_code(return_code);
		}

		// Post the max value to the mailbox for other task
		return_code = OSMboxPost(MboxMultMerge, (void *)array_c);
		alt_ucosii_check_return_code(return_code);

		OSTimeDlyHMSM(0, 0, 1, 0);
	}
}



// Task launcher
// It creates all the custom tasks
// And then it deletes itself
void task_launcher(void *pdata) {
	INT8U return_code = OS_NO_ERR;

	#if OS_CRITICAL_METHOD == 3
			OS_CPU_SR cpu_sr;
	#endif

	printf("Starting task launcher...\n");
	while (1) {
		OS_ENTER_CRITICAL();
		printf("Creating tasks...\n");

		return_code = OSTaskCreateExt(multiply,
			NULL,
			(void *)&mul_stk[TASK_STACKSIZE-1],
			MULT_PRIORITY,
			MULT_PRIORITY,
			&mul_stk[0],
			TASK_STACKSIZE,
			&mul_tcb,
			0);
		alt_ucosii_check_return_code(return_code);

		return_code = OSTaskCreateExt(gen_array_0,
			NULL,
			(void *)&gen_array_stk[0][TASK_STACKSIZE-1],
			GEN_ARRAY_0_PRIORITY,
			GEN_ARRAY_0_PRIORITY,
			&gen_array_stk[0][0],
			TASK_STACKSIZE,
			&gen_array_tcb[0],
			0);
		alt_ucosii_check_return_code(return_code);

		return_code = OSTaskCreateExt(gen_array_1,
			NULL,
			(void *)&gen_array_stk[1][TASK_STACKSIZE-1],
			GEN_ARRAY_1_PRIORITY,
			GEN_ARRAY_1_PRIORITY,
			&gen_array_stk[1][0],
			TASK_STACKSIZE,
			&gen_array_tcb[1],
			0);
		alt_ucosii_check_return_code(return_code);

		return_code = OSTaskCreateExt(top_left_mult,
			NULL,
			(void *)&cal_mul_stk[0][TASK_STACKSIZE-1],
			TOP_LEFT_MULT_PRIORITY,
			TOP_LEFT_MULT_PRIORITY,
			&cal_mul_stk[0][0],
			TASK_STACKSIZE,
			&cal_mul_tcb[0],
			0);
		alt_ucosii_check_return_code(return_code);

		return_code = OSTaskCreateExt(top_right_mult,
			NULL,
			(void *)&cal_mul_stk[1][TASK_STACKSIZE-1],
			TOP_RIGHT_MULT_PRIORITY,
			TOP_RIGHT_MULT_PRIORITY,
			&cal_mul_stk[1][0],
			TASK_STACKSIZE,
			&cal_mul_tcb[1],
			0);
		alt_ucosii_check_return_code(return_code);

		return_code = OSTaskCreateExt(bottom_left_mult,
			NULL,
			(void *)&cal_mul_stk[2][TASK_STACKSIZE-1],
			BOTTOM_LEFT_MULT_PRIORITY,
			BOTTOM_LEFT_MULT_PRIORITY,
			&cal_mul_stk[2][0],
			TASK_STACKSIZE,
			&cal_mul_tcb[2],
			0);
		alt_ucosii_check_return_code(return_code);

		return_code = OSTaskCreateExt(bottom_right_mult,
			NULL,
			(void *)&cal_mul_stk[3][TASK_STACKSIZE-1],
			BOTTOM_RIGHT_MULT_PRIORITY,
			BOTTOM_RIGHT_MULT_PRIORITY,
			&cal_mul_stk[3][0],
			TASK_STACKSIZE,
			&cal_mul_tcb[3],
			0);
		alt_ucosii_check_return_code(return_code);

		return_code = OSTaskCreateExt(merge,
			NULL,
			(void *)& merge_stk[TASK_STACKSIZE-1],
			MERGE_PRIORITY,
			MERGE_PRIORITY,
			&merge_stk[0],
			TASK_STACKSIZE,
			&merge_tcb,
			0);
		alt_ucosii_check_return_code(return_code);

		printf("Finish creating tasks...\n");

		printf("\n");
		OSTimeDlyHMSM(0, 0, 1, 0);

		return_code = OSTaskDel(OS_PRIO_SELF);
		alt_ucosii_check_return_code(return_code);

		OS_EXIT_CRITICAL();
	}
}
