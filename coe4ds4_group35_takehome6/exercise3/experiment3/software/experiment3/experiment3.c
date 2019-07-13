// Copyright by Adam Kinsman, Henry Ko and Nicola Nicolici
// Developed for the Embedded Systems course (COE4DS4)
// Department of Electrical and Computer Engineering
// McMaster University
// Ontario, Canada

#include "define.h"

// Definition of uCOS data structures
extern OS_EVENT *PBSemaphore[];
extern OS_EVENT *RedLEDMutex;
extern OS_EVENT *GreenLEDMutex;
extern OS_EVENT *SwitchAMutex;
extern OS_EVENT *SwitchBMutex;

// Definition of task stacks
extern OS_STK initialize_task_stk[TASK_STACKSIZE];
extern OS_STK task_launcher_stk[TASK_STACKSIZE];

alt_up_character_lcd_dev *lcd_0;

// Local function prototypes
int init_OS_data_structs(void);
int init_create_tasks(void);

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

   	lcd_0 = alt_up_character_lcd_open_dev(CHARACTER_LCD_0_NAME);

    if (lcd_0 == NULL) alt_printf("Error opening LCD device\n");
    else alt_printf("LCD device opened.\n");

    alt_up_character_lcd_init(lcd_0);
    
    alt_up_character_lcd_string(lcd_0, "COE4DS4 Winter18");

    alt_up_character_lcd_set_cursor_pos(lcd_0, 0, 1);

    alt_up_character_lcd_string(lcd_0, "Lab6      exp. 3");

    printf("Character LCD initialized...\n");

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

// This function creates the data structures for uCOS
int init_OS_data_structs(void) {
	int i;
	INT8U return_code = OS_NO_ERR;

	printf("Init data structs...\n");

	for (i = 0; i < NUM_PB_BUTTON; i++)
		PBSemaphore[i] = OSSemCreate(0);

	RedLEDMutex = OSMutexCreate(RED_LED_MUTEX_PRIORITY, &return_code);
	alt_ucosii_check_return_code(return_code);
	GreenLEDMutex = OSMutexCreate(GREEN_LED_MUTEX_PRIORITY, &return_code);
	alt_ucosii_check_return_code(return_code);
	SwitchAMutex = OSMutexCreate(SWITCH_A_MUTEX_PRIORITY, &return_code);
	alt_ucosii_check_return_code(return_code);
	SwitchBMutex = OSMutexCreate(SWITCH_B_MUTEX_PRIORITY, &return_code);
	alt_ucosii_check_return_code(return_code);

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
