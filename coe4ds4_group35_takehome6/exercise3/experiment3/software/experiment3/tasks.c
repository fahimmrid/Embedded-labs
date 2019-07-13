// Copyright by Adam Kinsman, Henry Ko and Nicola Nicolici
// Developed for the Embedded Systems course (COE4DS4)
// Department of Electrical and Computer Engineering
// McMaster University
// Ontario, Canada

#include "define.h"

// Definition of semaphore for PBs
OS_EVENT *PBSemaphore[4];

// Definition of Mutex for LCD
//OS_EVENT *LCDMutex;
OS_EVENT *RedLEDMutex;
OS_EVENT *GreenLEDMutex;
OS_EVENT *SwitchAMutex;
OS_EVENT *SwitchBMutex;

// Definition of task stacks
OS_STK	  initialize_task_stk[TASK_STACKSIZE];
OS_STK	  task_launcher_stk[TASK_STACKSIZE];

OS_STK	  custom_task_stk[NUM_TASK][TASK_STACKSIZE];
OS_TCB	  custom_task_tcb[NUM_TASK];

extern alt_up_character_lcd_dev *lcd_0;

// Local function prototypes
void custom_delay(int);

// Custom task 0
// It has a high priority to monitor PB0
// And it display OS info when PB0 is pressed
void custom_task_0(void* pdata) {
	INT8U return_code = OS_NO_ERR;
	OS_TCB tcb_data;

	OS_MUTEX_DATA mutex_data;
	OS_SEM_DATA sem_data;
	int i;

	while (1) {
		// Wait for PB0
		OSSemPend(PBSemaphore[0], 0, &return_code);
		alt_ucosii_check_return_code(return_code);

		#if MY_MUTEX_ENABLE == 1
			printf("-Waiting for Green LED Mutex (0)...\n");
			OSMutexPend(GreenLEDMutex, 0, &return_code);
			alt_ucosii_check_return_code(return_code);
			printf("-Green LED Mutex obtained (0)...\n");
		#endif
		#if MY_MUTEX_ENABLE == 1
			printf("-Waiting for SwitchA Mutex (0)...\n");
			OSMutexPend(SwitchAMutex, 0, &return_code);
			alt_ucosii_check_return_code(return_code);
			printf("-SwitchA Mutex obtained (0)...\n");
		#endif

		printf("Printing Green LEDs for SW_GRPA:\n");
		IOWR(LED_GREEN_O_BASE, 0, IORD(SWITCH_GRPA_I_BASE, 0));

		OSTimeDlyHMSM(0, 0, 1, 500);
		//custom_delay(DELAY_0);

		IOWR(LED_GREEN_O_BASE, 0, 0x0);

		#if MY_MUTEX_ENABLE == 1
			printf("-Releasing Green LED Mutex (0)...\n");
			return_code = OSMutexPost(GreenLEDMutex);
			alt_ucosii_check_return_code(return_code);
			printf("-Green LED Mutex released (0)...\n");
		#endif
		#if MY_MUTEX_ENABLE == 1
			printf("-Releasing SwitchA Mutex (0)...\n");
			return_code = OSMutexPost(SwitchAMutex);
			alt_ucosii_check_return_code(return_code);
			printf("-SwitchA Mutex released (0)...\n");
		#endif


	}
}

// Custom task 1
// It monitors PB1
// And it display a message on LCD when PB1 is pressed
void custom_task_1(void* pdata) {
	INT8U return_code = OS_NO_ERR;

	while (1) {
		// Wait for PB1
		// Task will be suspended while waiting
		OSSemPend(PBSemaphore[1], 0, &return_code);
		alt_ucosii_check_return_code(return_code);

		#if MY_MUTEX_ENABLE == 1
			printf("-Waiting for Red LED Mutex (1)...\n");
			OSMutexPend(RedLEDMutex, 0, &return_code);
			alt_ucosii_check_return_code(return_code);
			printf("-Red LED Mutex obtained (1)...\n");
		#endif
		#if MY_MUTEX_ENABLE == 1
			printf("-Waiting for SwitchA Mutex (1)...\n");
			OSMutexPend(SwitchAMutex, 0, &return_code);
			alt_ucosii_check_return_code(return_code);
			printf("-SwitchA Mutex obtained (1)...\n");
		#endif

		printf("Printing Red LEDs for SW_GRPA:\n");
		IOWR(LED_RED_O_BASE, 0, IORD(SWITCH_GRPA_I_BASE, 0));

		OSTimeDlyHMSM(0, 0, 3, 500);

		IOWR(LED_RED_O_BASE, 0, 0x0);

		#if MY_MUTEX_ENABLE == 1
			printf("-Releasing Red LED Mutex (1)...\n");
			return_code = OSMutexPost(RedLEDMutex);
			alt_ucosii_check_return_code(return_code);
			printf("-Red LED Mutex released (1)...\n");
		#endif
		#if MY_MUTEX_ENABLE == 1
			printf("-Releasing SwitchA Mutex (1)...\n");
			return_code = OSMutexPost(SwitchAMutex);
			alt_ucosii_check_return_code(return_code);
			printf("-SwitchA Mutex released (1)...\n");
		#endif


	}
}

// Custom task 2
// It monitors PB2
// And it display a message on LCD when PB2 is pressed
void custom_task_2(void* pdata) {
	INT8U return_code = OS_NO_ERR;

	while (1) {
		// Wait for PB2
		// Task will be suspended while waiting
		OSSemPend(PBSemaphore[2], 0, &return_code);
		alt_ucosii_check_return_code(return_code);

		#if MY_MUTEX_ENABLE == 1
			printf("-Waiting for Green LED Mutex (2)...\n");
			OSMutexPend(GreenLEDMutex, 0, &return_code);
			alt_ucosii_check_return_code(return_code);
			printf("-Green LED Mutex obtained (2)...\n");
		#endif
		#if MY_MUTEX_ENABLE == 1
			printf("-Waiting for SwitchB Mutex (2)...\n");
			OSMutexPend(SwitchBMutex, 0, &return_code);
			alt_ucosii_check_return_code(return_code);
			printf("-SwitchB Mutex obtained (2)...\n");
		#endif

		printf("Printing Green LEDs for SW_GRPB:\n");
		IOWR(LED_GREEN_O_BASE, 0, IORD(SWITCH_GRPB_I_BASE, 0));

		OSTimeDlyHMSM(0, 0, 2, 500);

		IOWR(LED_GREEN_O_BASE, 0, 0x0);

		#if MY_MUTEX_ENABLE == 1
			printf("-Releasing Green LED Mutex (2)...\n");
			return_code = OSMutexPost(GreenLEDMutex);
			alt_ucosii_check_return_code(return_code);
			printf("-Green LED Mutex released (2)...\n");
		#endif
		#if MY_MUTEX_ENABLE == 1
			printf("-Releasing SwitchB Mutex (2)...\n");
			return_code = OSMutexPost(SwitchBMutex);
			alt_ucosii_check_return_code(return_code);
			printf("-SwitchB Mutex released (2)...\n");
		#endif


	}
}

// Custom task 3
// It monitors PB3
// And it erases all characters on LCD when PB3 is pressed
void custom_task_3(void* pdata) {

	// to be completed ...
	INT8U return_code = OS_NO_ERR;

	while (1) {

		// Wait for PB3
		// Task will be suspended while waiting
		OSSemPend(PBSemaphore[3], 0, &return_code);
		alt_ucosii_check_return_code(return_code);

		#if MY_MUTEX_ENABLE == 1
			printf("-Waiting for Red LED Mutex (3)...\n");
			OSMutexPend(RedLEDMutex, 0, &return_code);
			alt_ucosii_check_return_code(return_code);
			printf("-RedLEDMutex obtained (3)...\n");
		#endif
		#if MY_MUTEX_ENABLE == 1
			printf("-Waiting for SwitchB Mutex (3)...\n");
			OSMutexPend(SwitchBMutex, 0, &return_code);
			alt_ucosii_check_return_code(return_code);
			printf("-SwitchBMutex obtained (3)...\n");
		#endif

		printf("Printing Red LEDs for SW_GRPB:\n");
		IOWR(LED_RED_O_BASE, 0, IORD(SWITCH_GRPB_I_BASE, 0));

		OSTimeDlyHMSM(0, 0, 3, 500);

		IOWR(LED_RED_O_BASE, 0, 0x0);

		#if MY_MUTEX_ENABLE == 1
			printf("-Releasing Red LED Mutex (3)...\n");
			return_code = OSMutexPost(RedLEDMutex);
			alt_ucosii_check_return_code(return_code);
			printf("-RedLEDMutex released (3)...\n");
		#endif
		#if MY_MUTEX_ENABLE == 1
			printf("-Releasing SwitchB Mutex (3)...\n");
			return_code = OSMutexPost(SwitchBMutex);
			alt_ucosii_check_return_code(return_code);
			printf("-SwitchB Mutex released (3)...\n");
		#endif


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
		
		//IOWR(LED_GREEN_O_BASE, 0, IORD(SWITCH_GRPA_I_BASE, 0));
		//IOWR(LED_RED_O_BASE, 0, IORD(SWITCH_GRPB_I_BASE, 0));
		IOWR(LED_GREEN_O_BASE, 0, 0);
		IOWR(LED_RED_O_BASE, 0, 0);
		
		printf("Creating tasks...\n");

		return_code = OSTaskCreateExt(custom_task_0,
			NULL,
			(void *)&custom_task_stk[0][TASK_STACKSIZE-1],
			CUSTOM_TASK_0_PRIORITY,
			CUSTOM_TASK_0_PRIORITY,
			&custom_task_stk[0][0],
			TASK_STACKSIZE,
			&custom_task_tcb[0],
			0);
		alt_ucosii_check_return_code(return_code);

		return_code = OSTaskCreateExt(custom_task_1,
			NULL,
			(void *)&custom_task_stk[1][TASK_STACKSIZE-1],
			CUSTOM_TASK_1_PRIORITY,
			CUSTOM_TASK_1_PRIORITY,
			&custom_task_stk[1][0],
			TASK_STACKSIZE,
			&custom_task_tcb[1],
			0);
		alt_ucosii_check_return_code(return_code);

		return_code = OSTaskCreateExt(custom_task_2,
			NULL,
			(void *)&custom_task_stk[2][TASK_STACKSIZE-1],
			CUSTOM_TASK_2_PRIORITY,
			CUSTOM_TASK_2_PRIORITY,
			&custom_task_stk[2][0],
			TASK_STACKSIZE,
			&custom_task_tcb[2],
			0);
		alt_ucosii_check_return_code(return_code);

		return_code = OSTaskCreateExt(custom_task_3,
			NULL,
			(void *)&custom_task_stk[3][TASK_STACKSIZE-1],
			CUSTOM_TASK_3_PRIORITY,
			CUSTOM_TASK_3_PRIORITY,
			&custom_task_stk[3][0],
			TASK_STACKSIZE,
			&custom_task_tcb[3],
			0);
		alt_ucosii_check_return_code(return_code);


		printf("Finish creating tasks...\n");

		printf("PB 0: Task 0 - Switch A for Green LED\n");
		printf("PB 1: Task 1 - Switch A for Red LED\n");
		printf("PB 2: Task 2 - Switch B for Green LED\n");
		printf("PB 3: Task 3 - Switch B for Red LED\n");
		printf("\n");

		IOWR(LED_RED_O_BASE, 0, 0x0);
		IOWR(LED_GREEN_O_BASE, 0, 0x0);

		// Delay for 1 sec
		OSTimeDlyHMSM(0, 0, 1, 0);

		// Delete itself
		return_code = OSTaskDel(OS_PRIO_SELF);
		alt_ucosii_check_return_code(return_code);

		OS_EXIT_CRITICAL();
	}
}

// Function for occupying the processor for the specified number of clock ticks
// to simulate custom delay while keeping the task in the processor
void custom_delay(int ticks) {
    INT32U cur_tick;
    ticks--;
    cur_tick = OSTimeGet();
    while (ticks > 0) {
         if (OSTimeGet() > cur_tick) {
            ticks--;
            cur_tick = OSTimeGet();
         }  
    }
}
