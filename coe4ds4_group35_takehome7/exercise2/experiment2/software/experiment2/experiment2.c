// Copyright by Adam Kinsman, Henry Ko and Nicola Nicolici
// Developed for the Embedded Systems course (COE4DS4)
// Department of Electrical and Computer Engineering
// McMaster University
// Ontario, Canada

#include "define.h"

// Definition of uCOS data structures
extern OS_EVENT *PBSemaphore[];

extern OS_FLAG_GRP *SDCardFlag;

// Definition of mutex
extern OS_EVENT *SDMutex;

// Definition of mailbox
extern OS_EVENT *YMailbox;
extern OS_EVENT *YImageWidthMailbox;
extern OS_EVENT *YImageHeightMailbox;
extern OS_EVENT *ReadImageWidthMailbox;
extern OS_EVENT *ReadImageHeightMailbox;
extern OS_EVENT *WriteImageWidthMailbox;
extern OS_EVENT *WriteImageHeightMailbox;

// Definition of message queue
extern OS_EVENT *SDWriteQueue;
extern OS_EVENT *SDReadQueue[2];

//extern OS_EVENT *SDReadQueue2;


// memory partition
extern OS_MEM	*MemoryPartition;

// Definition of task stacks
extern OS_STK	 initialize_task_stk[TASK_STACKSIZE];
extern OS_STK	 task_launcher_stk[TASK_STACKSIZE];

// Local function prototypes
int init_OS_data_structs(void);
int init_create_tasks(void);

//char line_buf[4][LINE_LEN];
char line_buf[7][LINE_LEN];
//void *ReadQueue[2][QUEUE_LEN];
void *ReadQueue[QUEUE_LEN];
void *ReadQueue2[QUEUE_LEN];

void *WriteQueue[QUEUE_LEN]; 

// Initialization task for uCOS
void initialize_task(void* pdata) {
	INT8U return_code = OS_NO_ERR;

	// Initialize statistic counters in OS
	OSStatInit();

	// create os data structures
	init_OS_data_structs();

	// create the tasks
	init_create_tasks();

	// This task is deleted because there is no need for it to run again
	return_code = OSTaskDel(OS_PRIO_SELF);
	alt_ucosii_check_return_code(return_code);

	while (1);
}

// The main function, it initializes the hardware, and create the initialization task,
// then it starts uCOS, and never returns
int main(void) {
	INT8U return_code = OS_NO_ERR;
	
	printf("Start main...\n");

	init_button_irq();
	printf("PB initialized...\n");

	seg7_show(SEG7_DISPLAY_0_BASE,SEG7_VALUE);
	printf("SEG7 initialized...\n");

    sd_card_open_dev();
	printf("Opened SD card device...\n");

	PERF_RESET(PERFORMANCE_COUNTER_0_BASE);
	printf("Reset performance counter...\n");

	OSInit();

	return_code = OSTaskCreateExt(initialize_task,
					NULL,
					(void *)&initialize_task_stk[TASK_STACKSIZE],
					INITIALIZE_TASK_PRIORITY,
					INITIALIZE_TASK_PRIORITY,
					initialize_task_stk,
					TASK_STACKSIZE,
					NULL,
					OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);
	alt_ucosii_check_return_code(return_code);
	printf("Starting uCOS...\n");

	OSStart();
	return 0;
}

/* This function simply creates a message queue and a semaphore
 */

int init_OS_data_structs(void)
{
	int i;
	INT8U return_code = OS_NO_ERR;

	printf("Init data structs...\n");

	for (i = 0; i < NUM_PB_BUTTON; i++)
		PBSemaphore[i] = OSSemCreate(0);
	
	YMailbox = OSMboxCreate((void *)0);
	YImageWidthMailbox = OSMboxCreate((void *)0);
	YImageHeightMailbox = OSMboxCreate((void *)0);
	ReadImageWidthMailbox = OSMboxCreate((void *)0);
	ReadImageHeightMailbox = OSMboxCreate((void *)0);
	WriteImageWidthMailbox = OSMboxCreate((void *)0);
	WriteImageHeightMailbox = OSMboxCreate((void *)0);

	MemoryPartition = OSMemCreate(&line_buf[0][0], 7, LINE_LEN, &return_code);

	SDReadQueue[0] = OSQCreate(&ReadQueue[0], QUEUE_LEN);
	//SDReadQueue2 = OSQCreate(&ReadQueue[1], QUEUE_LEN);
	SDReadQueue[1] = OSQCreate(&ReadQueue2[0], QUEUE_LEN);

	SDWriteQueue = OSQCreate(&WriteQueue[0], QUEUE_LEN);
	
	SDCardFlag = OSFlagCreate(0, &return_code);
	//SDReadFlag = OSFlagCreate(0, &return_code);
	
	SDMutex = OSMutexCreate(SD_MUTEX_PRIORITY, &return_code);

	return 0;
}

// This function creates the first task in uCOS
int init_create_tasks(void) {
	INT8U return_code = OS_NO_ERR;

	printf("Creating task launcher...\n");
	return_code = OSTaskCreateExt(task_launcher,
					NULL,
					(void *)&task_launcher_stk[TASK_STACKSIZE],
					TASK_LAUNCHER_PRIORITY,
					TASK_LAUNCHER_PRIORITY,
					task_launcher_stk,
					TASK_STACKSIZE,
					NULL,
					0);
	alt_ucosii_check_return_code(return_code);

	return 0;
}
