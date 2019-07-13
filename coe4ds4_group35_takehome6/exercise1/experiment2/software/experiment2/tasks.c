// Copyright by Adam Kinsman, Henry Ko and Nicola Nicolici
// Developed for the Embedded Systems course (COE4DS4)
// Department of Electrical and Computer Engineering
// McMaster University
// Ontario, Canada

#include "define.h"
#define MY_NON_PREEMPTIVE_SCH 0
//change to 1 here when needed!

// For the performance counter
void *performance_name = PERFORMANCE_COUNTER_0_BASE;

// Definition of semaphore for PBs
OS_EVENT *PBSemaphore[4];

// Definition of task stacks
OS_STK	  initialize_task_stk[TASK_STACKSIZE];
OS_STK	  custom_scheduler_stk[TASK_STACKSIZE];
OS_TCB	  custom_scheduler_tcb;

OS_STK	  periodic_task_stk[NUM_TASK][TASK_STACKSIZE];
OS_TCB	  periodic_task_tcb[NUM_TASK];

// Struct for storing information about each custom task
typedef struct task_info_struct {
	int priority;
	int execution_time;
	int os_delay;
} task_info_struct;

// Struct for storing information about tasks during dynamic scheduling using the custom_scheduler
typedef struct scheduler_info_struct {
	int valid;
	int id;
	int period;
} scheduler_info_struct;

// Local function prototypes
void custom_delay(int);
int custom_task_del(int, scheduler_info_struct [], task_info_struct []);
int custom_task_create(int [], int, scheduler_info_struct [], task_info_struct []);

// Periodic task 0
// It periodically uses a custom delay to occupy the CPU
// Then it suspends itself for a specified period of time
void periodic_task0(void* pdata) {
	task_info_struct *task_info_ptr;

	//since our group members both have similar numnber of letters in our names our execution times and delays are very similar. This makes the preemptive case and non-preemtive
	//similar to each other. We tried a longer execution time for task 2 and noticed that in the preemptive case at times task 1 would stop task 2 and complete exectuion
	//and then task 2 will resume and end
	task_info_ptr = (task_info_struct *)pdata;
	while (1) {

		#if MY_NON_PREEMPTIVE_SCH == 1
			OSSchedLock();
		#endif
		printf("Start periodic_task 1:\t OStick: %d, \t execution_time=%d \n", OSTimeGet(),PERIODIC_TASK_1_EXECUTION_TIME);
		custom_delay(PERIODIC_TASK_1_EXECUTION_TIME);

		#if MY_NON_PREEMPTIVE_SCH == 1
			printf("Idle periodic_task 1: \t OStick: %d, \t idle_time=%d \n", OSTimeGet(),PERIODIC_TASK_1_IDLE_TIME);
			OSSchedUnlock();
		#endif
		#if MY_NON_PREEMPTIVE_SCH == 0
			printf("Idle periodic_task 1: \t OStick: %d, \t idle_time=%d \n", OSTimeGet(),PERIODIC_TASK_1_IDLE_TIME);
		#endif

		OSTimeDly(PERIODIC_TASK_1_IDLE_TIME);
	}
}

// Periodic task 1
// It periodically uses a custom delay to occupy the CPU
// Then it suspends itself for a specified period of time
void periodic_task1(void* pdata) {
	task_info_struct *task_info_ptr;


		task_info_ptr = (task_info_struct *)pdata;
		while (1) {

			#if MY_NON_PREEMPTIVE_SCH == 1
				OSSchedLock();
			#endif
			printf("Start periodic_task 2:\t OStick: %d, \t execution_time=%d \n", OSTimeGet(),PERIODIC_TASK_2_EXECUTION_TIME);
			custom_delay(PERIODIC_TASK_2_EXECUTION_TIME);

			#if MY_NON_PREEMPTIVE_SCH == 1
				printf("Idle periodic_task 2: \t OStick: %d, \t idle_time=%d \n", OSTimeGet(),PERIODIC_TASK_2_IDLE_TIME);
				OSSchedUnlock();
			#endif

			#if MY_NON_PREEMPTIVE_SCH == 0
				printf("Idle periodic_task 2: \t OStick: %d, \t idle_time=%d \n", OSTimeGet(),PERIODIC_TASK_2_IDLE_TIME);
			#endif
			OSTimeDly(PERIODIC_TASK_2_IDLE_TIME);
		}
}

// Periodic task 2
// It periodically uses a custom delay to occupy the CPU
// Then it suspends itself for a specified period of time
void periodic_task2(void* pdata) {

}

// Periodic task 3
// It periodically uses a custom delay to occupy the CPU
// Then it suspends itself for a specified period of time
void periodic_task3(void* pdata) {

}

// The custom_scheduler
// It has the highest priority
// It checks the PBs every 500ms
// It a button has been pressed, it creates/deletes the corresponding task in the OS
// When creating a task, it will assign the new task with the lowest priority among the running tasks
void custom_scheduler(void *pdata) {
	INT8U return_code = OS_NO_ERR;
	int i;
	int PB_pressed[NUM_PB_BUTTON];
	int sem_value;
	int new_pressed;

	int num_active_task;
	// Array of task_info
	task_info_struct task_info[NUM_TASK];
	scheduler_info_struct scheduler_info[NUM_TASK];


	num_active_task = 0;

	for (i = 0; i < 2; i++) {  // since 2 custom tasks are made!

		// Creating periodic task 0 with random execution time and delay time for periodic arrival
		task_info[i].execution_time = rand() % EXECUTION_TIME_LIMIT + 1;
		task_info[i].os_delay = rand() % OS_DELAY_LIMIT + 1;
		task_info[i].priority = num_active_task;

		scheduler_info[num_active_task].valid = 1;
		scheduler_info[num_active_task].id = i;
		scheduler_info[num_active_task].period = task_info[i].execution_time + task_info[i].os_delay * 1000;


		switch (i) {
			case 0:
				return_code = OSTaskCreateExt(periodic_task0,
								 &task_info[i],
								 (void *)&periodic_task_stk[num_active_task][TASK_STACKSIZE-1],
								 PERIODIC_TASK_1,
								 PERIODIC_TASK_1,
								 &periodic_task_stk[i][0],
								 TASK_STACKSIZE,
								 &periodic_task_tcb[i],
								 0);
			break;
			case 1:
				return_code = OSTaskCreateExt(periodic_task1,
								 &task_info[i],
								 (void *)&periodic_task_stk[num_active_task][TASK_STACKSIZE-1],
								 PERIODIC_TASK_2,
								 PERIODIC_TASK_2,
								 &periodic_task_stk[i][0],
								 TASK_STACKSIZE,
								 &periodic_task_tcb[i],
								 0);
			break;
			case 2:
				return_code = OSTaskCreateExt(periodic_task2,
								 &task_info[i],
								 (void *)&periodic_task_stk[num_active_task][TASK_STACKSIZE-1],
								 TASK_START_PRIORITY+num_active_task,
								 num_active_task,
								 &periodic_task_stk[num_active_task][0],
								 TASK_STACKSIZE,
								 &periodic_task_tcb[num_active_task],
								 0);
			break;
			default:
				return_code = OSTaskCreateExt(periodic_task3,
								 &task_info[i],
								 (void *)&periodic_task_stk[num_active_task][TASK_STACKSIZE-1],
								 TASK_START_PRIORITY+num_active_task,
								 num_active_task,
								 &periodic_task_stk[num_active_task][0],
								 TASK_STACKSIZE,
								 &periodic_task_tcb[num_active_task],
								 0);
			break;
		}
		alt_ucosii_check_return_code(return_code);

		num_active_task++;
	}
	printf("Finish creating initial tasks...\n");

/*	printf("Printing task info:\n");
	for (i = 0; i < num_active_task; i++) {
		printf("Priority %d: valid=%d, task_id=%d, period=%d, exec_time=%d, os_delay=%d, pri=%d\n",
			i,
			scheduler_info[i].valid,
			scheduler_info[i].id,
			scheduler_info[i].period,
			task_info[scheduler_info[i].id].execution_time,
			task_info[scheduler_info[i].id].os_delay,
			task_info[scheduler_info[i].id].priority);
	}*/

	// Scheduler never returns
	while (1) {
		new_pressed = 0;
		// Check for PBs
		for (i = 0; i < NUM_PB_BUTTON; i++) {
			PB_pressed[i] = 0;
			sem_value = OSSemAccept(PBSemaphore[i]);
			if (sem_value != 0) {
				PB_pressed[i] = 1;
				new_pressed = 1;
			}
		}

		if (new_pressed != 0) {
			printf("Locking OS scheduler for new scheduling\n");
			OSSchedLock();

			for (i = 0; i < num_active_task; i++) {
				// check for task to delete if PB is pressed
				if (scheduler_info[i].valid == 1 && PB_pressed[scheduler_info[i].id] == 1) {
					// task is valid, mark it for deletion
					printf("-Marking task with id (%d) and priority (%d) for deletion\n", scheduler_info[i].id, i);
					scheduler_info[i].valid = -1;

					PB_pressed[scheduler_info[i].id] = 0;
				}
			}

			// Delete the corresponding task first
			num_active_task -= custom_task_del(num_active_task, scheduler_info, task_info);

			// Create the new task if available
			num_active_task += custom_task_create(PB_pressed, num_active_task, scheduler_info, task_info);

			printf("Printing task info:\n");
			for (i = 0; i < num_active_task; i++) {
				printf("Priority %d: valid=%d, task_id=%d, period=%d, exec_time=%d, os_delay=%d, pri=%d\n",
					i,
					scheduler_info[i].valid,
					scheduler_info[i].id,
					scheduler_info[i].period,
					task_info[scheduler_info[i].id].execution_time,
					task_info[scheduler_info[i].id].os_delay,
					task_info[scheduler_info[i].id].priority);
			}

			printf("Unlocking OS scheduler\n");
			OSSchedUnlock();
		}

		OSTimeDlyHMSM(0, 0, 0, 500);
	}
}

// Function for deleting a task from the OS, and from the data structure task_info
int custom_task_del(int num_active_task, scheduler_info_struct scheduler_info[], task_info_struct task_info[]) {

	int i, total_task_del = 0;
	INT8U return_code = OS_NO_ERR;

	printf("Deleting task(s) from the OS ...\n");
	for (i = 0; i < num_active_task; i++) {
		if (scheduler_info[i].valid == -1) {
			// delete tasks that were marked for deletion
			return_code = OSTaskDel(TASK_START_PRIORITY+i);
			alt_ucosii_check_return_code(return_code);
			total_task_del++;
		}
		else {
			// active tasks will upgrade their priority
			if (total_task_del != 0) {
				return_code = OSTaskChangePrio(TASK_START_PRIORITY+i, TASK_START_PRIORITY+i-total_task_del);
				alt_ucosii_check_return_code(return_code);
				scheduler_info[i-total_task_del].valid = scheduler_info[i].valid;
				scheduler_info[i-total_task_del].id = scheduler_info[i].id;
				scheduler_info[i-total_task_del].period = scheduler_info[i].period;
				task_info[scheduler_info[i-total_task_del].id].priority = i-total_task_del;
			}
		}
	}

	// clear the valid flag for all the inactive tasks
	for (i = num_active_task - total_task_del; i < num_active_task; i++)
			scheduler_info[i].valid = 0;

	return total_task_del;
}

// Function for creating a task in the OS, and update the data structure task_info
// The new task has the lowest priority among the existing tasks
int custom_task_create(int PB_pressed[], int num_active_task, scheduler_info_struct scheduler_info[], task_info_struct task_info[]) {
	int i;
	int num_task_created;
	INT8U return_code = OS_NO_ERR;

	num_task_created = 0;
	printf("Creating task(s) in the OS ...\n");

	for (i = 0; i < NUM_PB_BUTTON; i++) {
		if (PB_pressed[i] == 1) {            
			task_info[i].execution_time = rand() % EXECUTION_TIME_LIMIT + 1;
			task_info[i].os_delay = rand() % OS_DELAY_LIMIT + 1;
			task_info[i].priority = num_active_task + num_task_created;

            scheduler_info[num_active_task + num_task_created].valid = 1;
            scheduler_info[num_active_task + num_task_created].period = task_info[i].execution_time + task_info[i].os_delay * 1000;
            scheduler_info[num_active_task + num_task_created].id = i;

			printf("-Creating periodic_task%d: execution_time_tick = %d, os_delay_time = %d: priority (%d)\n",
				i,
				task_info[i].execution_time,
				task_info[i].os_delay,
                num_active_task + num_task_created
                );

			// Create the task in the OS
			switch(i) {
				case 0:
					return_code = OSTaskCreateExt(periodic_task0,
											 &task_info[i],
											 (void *)&periodic_task_stk[i][TASK_STACKSIZE-1],
											 TASK_START_PRIORITY+num_active_task + num_task_created,
											 i,
											 &periodic_task_stk[i][0],
											 TASK_STACKSIZE,
											 &periodic_task_tcb[i],
											 0);
					alt_ucosii_check_return_code(return_code);
				break;
				case 1:
					return_code = OSTaskCreateExt(periodic_task1,
						 					&task_info[i],
											 (void *)&periodic_task_stk[i][TASK_STACKSIZE-1],
											 TASK_START_PRIORITY+num_active_task + num_task_created,
											 i,
											 &periodic_task_stk[i][0],
											 TASK_STACKSIZE,
											 &periodic_task_tcb[i],
											 0);
					alt_ucosii_check_return_code(return_code);
				break;
				case 2:
					return_code = OSTaskCreateExt(periodic_task2,
						 					&task_info[i],
											 (void *)&periodic_task_stk[i][TASK_STACKSIZE-1],
											 TASK_START_PRIORITY+num_active_task + num_task_created,
											 i,
											 &periodic_task_stk[i][0],
											 TASK_STACKSIZE,
											 &periodic_task_tcb[i],
											 0);
					alt_ucosii_check_return_code(return_code);
				break;
				default:
					return_code = OSTaskCreateExt(periodic_task3,
						 					&task_info[i],
											 (void *)&periodic_task_stk[i][TASK_STACKSIZE-1],
											 TASK_START_PRIORITY+num_active_task + num_task_created,
											 i,
											 &periodic_task_stk[i][0],
											 TASK_STACKSIZE,
											 &periodic_task_tcb[i],
											 0);
					alt_ucosii_check_return_code(return_code);
				break;
			}


			num_task_created++;
		}
	}

	printf("%d task created...\n", num_task_created);

	return num_task_created;
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
