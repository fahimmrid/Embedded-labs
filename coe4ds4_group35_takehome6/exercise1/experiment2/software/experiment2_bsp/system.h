/*
 * system.h - SOPC Builder system and BSP software package information
 *
 * Machine generated for CPU 'cpu_0' in SOPC Builder design 'experiment2'
 * SOPC Builder design path: ../../experiment2.sopcinfo
 *
 * Generated: Mon Nov 19 11:22:23 EST 2012
 */

/*
 * DO NOT MODIFY THIS FILE
 *
 * Changing this file will have subtle consequences
 * which will almost certainly lead to a nonfunctioning
 * system. If you do modify this file, be aware that your
 * changes will be overwritten and lost when this file
 * is generated again.
 *
 * DO NOT MODIFY THIS FILE
 */

/*
 * License Agreement
 *
 * Copyright (c) 2008
 * Altera Corporation, San Jose, California, USA.
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * This agreement shall be governed in all respects by the laws of the State
 * of California and by the laws of the United States of America.
 */

#ifndef __SYSTEM_H_
#define __SYSTEM_H_

/* Include definitions from linker script generator */
#include "linker.h"


/*
 * CPU configuration
 *
 */

#define ALT_CPU_ARCHITECTURE "altera_nios2_qsys"
#define ALT_CPU_BIG_ENDIAN 0
#define ALT_CPU_BREAK_ADDR 0x100820
#define ALT_CPU_CPU_FREQ 50000000u
#define ALT_CPU_CPU_ID_SIZE 1
#define ALT_CPU_CPU_ID_VALUE 0x00000000
#define ALT_CPU_CPU_IMPLEMENTATION "tiny"
#define ALT_CPU_DATA_ADDR_WIDTH 0x15
#define ALT_CPU_DCACHE_LINE_SIZE 0
#define ALT_CPU_DCACHE_LINE_SIZE_LOG2 0
#define ALT_CPU_DCACHE_SIZE 0
#define ALT_CPU_EXCEPTION_ADDR 0x80020
#define ALT_CPU_FLUSHDA_SUPPORTED
#define ALT_CPU_FREQ 50000000
#define ALT_CPU_HARDWARE_DIVIDE_PRESENT 0
#define ALT_CPU_HARDWARE_MULTIPLY_PRESENT 0
#define ALT_CPU_HARDWARE_MULX_PRESENT 0
#define ALT_CPU_HAS_DEBUG_CORE 1
#define ALT_CPU_HAS_DEBUG_STUB
#define ALT_CPU_HAS_JMPI_INSTRUCTION
#define ALT_CPU_ICACHE_LINE_SIZE 0
#define ALT_CPU_ICACHE_LINE_SIZE_LOG2 0
#define ALT_CPU_ICACHE_SIZE 0
#define ALT_CPU_INST_ADDR_WIDTH 0x15
#define ALT_CPU_NAME "cpu_0"
#define ALT_CPU_RESET_ADDR 0x80000


/*
 * CPU configuration (with legacy prefix - don't use these anymore)
 *
 */

#define NIOS2_BIG_ENDIAN 0
#define NIOS2_BREAK_ADDR 0x100820
#define NIOS2_CPU_FREQ 50000000u
#define NIOS2_CPU_ID_SIZE 1
#define NIOS2_CPU_ID_VALUE 0x00000000
#define NIOS2_CPU_IMPLEMENTATION "tiny"
#define NIOS2_DATA_ADDR_WIDTH 0x15
#define NIOS2_DCACHE_LINE_SIZE 0
#define NIOS2_DCACHE_LINE_SIZE_LOG2 0
#define NIOS2_DCACHE_SIZE 0
#define NIOS2_EXCEPTION_ADDR 0x80020
#define NIOS2_FLUSHDA_SUPPORTED
#define NIOS2_HARDWARE_DIVIDE_PRESENT 0
#define NIOS2_HARDWARE_MULTIPLY_PRESENT 0
#define NIOS2_HARDWARE_MULX_PRESENT 0
#define NIOS2_HAS_DEBUG_CORE 1
#define NIOS2_HAS_DEBUG_STUB
#define NIOS2_HAS_JMPI_INSTRUCTION
#define NIOS2_ICACHE_LINE_SIZE 0
#define NIOS2_ICACHE_LINE_SIZE_LOG2 0
#define NIOS2_ICACHE_SIZE 0
#define NIOS2_INST_ADDR_WIDTH 0x15
#define NIOS2_RESET_ADDR 0x80000


/*
 * Define for each module class mastered by the CPU
 *
 */

#define __ALTERA_AVALON_JTAG_UART
#define __ALTERA_AVALON_PERFORMANCE_COUNTER
#define __ALTERA_AVALON_PIO
#define __ALTERA_AVALON_TIMER
#define __ALTERA_NIOS2_QSYS
#define __ALTERA_UP_AVALON_CHARACTER_LCD
#define __ALTERA_UP_AVALON_SRAM
#define __SEG7_DISPLAY


/*
 * LED_GREEN_O configuration
 *
 */

#define ALT_MODULE_CLASS_LED_GREEN_O altera_avalon_pio
#define LED_GREEN_O_BASE 0x101090
#define LED_GREEN_O_BIT_CLEARING_EDGE_REGISTER 0
#define LED_GREEN_O_BIT_MODIFYING_OUTPUT_REGISTER 0
#define LED_GREEN_O_CAPTURE 0
#define LED_GREEN_O_DATA_WIDTH 9
#define LED_GREEN_O_DO_TEST_BENCH_WIRING 0
#define LED_GREEN_O_DRIVEN_SIM_VALUE 0x0
#define LED_GREEN_O_EDGE_TYPE "NONE"
#define LED_GREEN_O_FREQ 50000000u
#define LED_GREEN_O_HAS_IN 0
#define LED_GREEN_O_HAS_OUT 1
#define LED_GREEN_O_HAS_TRI 0
#define LED_GREEN_O_IRQ -1
#define LED_GREEN_O_IRQ_INTERRUPT_CONTROLLER_ID -1
#define LED_GREEN_O_IRQ_TYPE "NONE"
#define LED_GREEN_O_NAME "/dev/LED_GREEN_O"
#define LED_GREEN_O_RESET_VALUE 0x0
#define LED_GREEN_O_SPAN 16
#define LED_GREEN_O_TYPE "altera_avalon_pio"


/*
 * LED_RED_O configuration
 *
 */

#define ALT_MODULE_CLASS_LED_RED_O altera_avalon_pio
#define LED_RED_O_BASE 0x101080
#define LED_RED_O_BIT_CLEARING_EDGE_REGISTER 0
#define LED_RED_O_BIT_MODIFYING_OUTPUT_REGISTER 0
#define LED_RED_O_CAPTURE 0
#define LED_RED_O_DATA_WIDTH 18
#define LED_RED_O_DO_TEST_BENCH_WIRING 0
#define LED_RED_O_DRIVEN_SIM_VALUE 0x0
#define LED_RED_O_EDGE_TYPE "NONE"
#define LED_RED_O_FREQ 50000000u
#define LED_RED_O_HAS_IN 0
#define LED_RED_O_HAS_OUT 1
#define LED_RED_O_HAS_TRI 0
#define LED_RED_O_IRQ -1
#define LED_RED_O_IRQ_INTERRUPT_CONTROLLER_ID -1
#define LED_RED_O_IRQ_TYPE "NONE"
#define LED_RED_O_NAME "/dev/LED_RED_O"
#define LED_RED_O_RESET_VALUE 0x0
#define LED_RED_O_SPAN 16
#define LED_RED_O_TYPE "altera_avalon_pio"


/*
 * PUSH_BUTTON_I configuration
 *
 */

#define ALT_MODULE_CLASS_PUSH_BUTTON_I altera_avalon_pio
#define PUSH_BUTTON_I_BASE 0x101070
#define PUSH_BUTTON_I_BIT_CLEARING_EDGE_REGISTER 0
#define PUSH_BUTTON_I_BIT_MODIFYING_OUTPUT_REGISTER 0
#define PUSH_BUTTON_I_CAPTURE 1
#define PUSH_BUTTON_I_DATA_WIDTH 4
#define PUSH_BUTTON_I_DO_TEST_BENCH_WIRING 0
#define PUSH_BUTTON_I_DRIVEN_SIM_VALUE 0x0
#define PUSH_BUTTON_I_EDGE_TYPE "FALLING"
#define PUSH_BUTTON_I_FREQ 50000000u
#define PUSH_BUTTON_I_HAS_IN 1
#define PUSH_BUTTON_I_HAS_OUT 0
#define PUSH_BUTTON_I_HAS_TRI 0
#define PUSH_BUTTON_I_IRQ 2
#define PUSH_BUTTON_I_IRQ_INTERRUPT_CONTROLLER_ID 0
#define PUSH_BUTTON_I_IRQ_TYPE "EDGE"
#define PUSH_BUTTON_I_NAME "/dev/PUSH_BUTTON_I"
#define PUSH_BUTTON_I_RESET_VALUE 0x0
#define PUSH_BUTTON_I_SPAN 16
#define PUSH_BUTTON_I_TYPE "altera_avalon_pio"


/*
 * SEG7_Display_0 configuration
 *
 */

#define ALT_MODULE_CLASS_SEG7_Display_0 SEG7_Display
#define SEG7_DISPLAY_0_BASE 0x1010a8
#define SEG7_DISPLAY_0_IRQ -1
#define SEG7_DISPLAY_0_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SEG7_DISPLAY_0_NAME "/dev/SEG7_Display_0"
#define SEG7_DISPLAY_0_SPAN 4
#define SEG7_DISPLAY_0_TYPE "SEG7_Display"


/*
 * SWITCH_I configuration
 *
 */

#define ALT_MODULE_CLASS_SWITCH_I altera_avalon_pio
#define SWITCH_I_BASE 0x101060
#define SWITCH_I_BIT_CLEARING_EDGE_REGISTER 0
#define SWITCH_I_BIT_MODIFYING_OUTPUT_REGISTER 0
#define SWITCH_I_CAPTURE 0
#define SWITCH_I_DATA_WIDTH 17
#define SWITCH_I_DO_TEST_BENCH_WIRING 0
#define SWITCH_I_DRIVEN_SIM_VALUE 0x0
#define SWITCH_I_EDGE_TYPE "NONE"
#define SWITCH_I_FREQ 50000000u
#define SWITCH_I_HAS_IN 1
#define SWITCH_I_HAS_OUT 0
#define SWITCH_I_HAS_TRI 0
#define SWITCH_I_IRQ -1
#define SWITCH_I_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SWITCH_I_IRQ_TYPE "NONE"
#define SWITCH_I_NAME "/dev/SWITCH_I"
#define SWITCH_I_RESET_VALUE 0x0
#define SWITCH_I_SPAN 16
#define SWITCH_I_TYPE "altera_avalon_pio"


/*
 * System configuration
 *
 */

#define ALT_DEVICE_FAMILY "Cyclone II"
#define ALT_ENHANCED_INTERRUPT_API_PRESENT
#define ALT_IRQ_BASE NULL
#define ALT_LOG_PORT "/dev/null"
#define ALT_LOG_PORT_BASE 0x0
#define ALT_LOG_PORT_DEV null
#define ALT_LOG_PORT_TYPE ""
#define ALT_NUM_EXTERNAL_INTERRUPT_CONTROLLERS 0
#define ALT_NUM_INTERNAL_INTERRUPT_CONTROLLERS 1
#define ALT_NUM_INTERRUPT_CONTROLLERS 1
#define ALT_STDERR "/dev/jtag_uart_0"
#define ALT_STDERR_BASE 0x1010a0
#define ALT_STDERR_DEV jtag_uart_0
#define ALT_STDERR_IS_JTAG_UART
#define ALT_STDERR_PRESENT
#define ALT_STDERR_TYPE "altera_avalon_jtag_uart"
#define ALT_STDIN "/dev/jtag_uart_0"
#define ALT_STDIN_BASE 0x1010a0
#define ALT_STDIN_DEV jtag_uart_0
#define ALT_STDIN_IS_JTAG_UART
#define ALT_STDIN_PRESENT
#define ALT_STDIN_TYPE "altera_avalon_jtag_uart"
#define ALT_STDOUT "/dev/jtag_uart_0"
#define ALT_STDOUT_BASE 0x1010a0
#define ALT_STDOUT_DEV jtag_uart_0
#define ALT_STDOUT_IS_JTAG_UART
#define ALT_STDOUT_PRESENT
#define ALT_STDOUT_TYPE "altera_avalon_jtag_uart"
#define ALT_SYSTEM_NAME "experiment2"


/*
 * character_lcd_0 configuration
 *
 */

#define ALT_MODULE_CLASS_character_lcd_0 altera_up_avalon_character_lcd
#define CHARACTER_LCD_0_BASE 0x1010ac
#define CHARACTER_LCD_0_IRQ -1
#define CHARACTER_LCD_0_IRQ_INTERRUPT_CONTROLLER_ID -1
#define CHARACTER_LCD_0_NAME "/dev/character_lcd_0"
#define CHARACTER_LCD_0_SPAN 2
#define CHARACTER_LCD_0_TYPE "altera_up_avalon_character_lcd"


/*
 * hal configuration
 *
 */

#define ALT_MAX_FD 32
#define ALT_SYS_CLK TIMER
#define ALT_TIMESTAMP_CLK none


/*
 * jtag_uart_0 configuration
 *
 */

#define ALT_MODULE_CLASS_jtag_uart_0 altera_avalon_jtag_uart
#define JTAG_UART_0_BASE 0x1010a0
#define JTAG_UART_0_IRQ 1
#define JTAG_UART_0_IRQ_INTERRUPT_CONTROLLER_ID 0
#define JTAG_UART_0_NAME "/dev/jtag_uart_0"
#define JTAG_UART_0_READ_DEPTH 64
#define JTAG_UART_0_READ_THRESHOLD 8
#define JTAG_UART_0_SPAN 8
#define JTAG_UART_0_TYPE "altera_avalon_jtag_uart"
#define JTAG_UART_0_WRITE_DEPTH 64
#define JTAG_UART_0_WRITE_THRESHOLD 8


/*
 * performance_counter_0 configuration
 *
 */

#define ALT_MODULE_CLASS_performance_counter_0 altera_avalon_performance_counter
#define PERFORMANCE_COUNTER_0_BASE 0x101000
#define PERFORMANCE_COUNTER_0_HOW_MANY_SECTIONS 3
#define PERFORMANCE_COUNTER_0_IRQ -1
#define PERFORMANCE_COUNTER_0_IRQ_INTERRUPT_CONTROLLER_ID -1
#define PERFORMANCE_COUNTER_0_NAME "/dev/performance_counter_0"
#define PERFORMANCE_COUNTER_0_SPAN 64
#define PERFORMANCE_COUNTER_0_TYPE "altera_avalon_performance_counter"


/*
 * sram_0 configuration
 *
 */

#define ALT_MODULE_CLASS_sram_0 altera_up_avalon_sram
#define SRAM_0_BASE 0x80000
#define SRAM_0_IRQ -1
#define SRAM_0_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SRAM_0_NAME "/dev/sram_0"
#define SRAM_0_SPAN 524288
#define SRAM_0_TYPE "altera_up_avalon_sram"


/*
 * timer configuration
 *
 */

#define ALT_MODULE_CLASS_timer altera_avalon_timer
#define TIMER_ALWAYS_RUN 0
#define TIMER_BASE 0x101040
#define TIMER_COUNTER_SIZE 32
#define TIMER_FIXED_PERIOD 0
#define TIMER_FREQ 50000000u
#define TIMER_IRQ 0
#define TIMER_IRQ_INTERRUPT_CONTROLLER_ID 0
#define TIMER_LOAD_VALUE 49999ull
#define TIMER_MULT 0.0010
#define TIMER_NAME "/dev/timer"
#define TIMER_PERIOD 1
#define TIMER_PERIOD_UNITS "ms"
#define TIMER_RESET_OUTPUT 0
#define TIMER_SNAPSHOT 1
#define TIMER_SPAN 32
#define TIMER_TICKS_PER_SEC 1000u
#define TIMER_TIMEOUT_PULSE_OUTPUT 0
#define TIMER_TYPE "altera_avalon_timer"


/*
 * ucosii configuration
 *
 */

#define OS_ARG_CHK_EN 1
#define OS_CPU_HOOKS_EN 1
#define OS_DEBUG_EN 1
#define OS_EVENT_NAME_SIZE 32
#define OS_FLAGS_NBITS 16
#define OS_FLAG_ACCEPT_EN 1
#define OS_FLAG_DEL_EN 1
#define OS_FLAG_EN 1
#define OS_FLAG_NAME_SIZE 32
#define OS_FLAG_QUERY_EN 1
#define OS_FLAG_WAIT_CLR_EN 1
#define OS_LOWEST_PRIO 20
#define OS_MAX_EVENTS 60
#define OS_MAX_FLAGS 20
#define OS_MAX_MEM_PART 60
#define OS_MAX_QS 20
#define OS_MAX_TASKS 10
#define OS_MBOX_ACCEPT_EN 1
#define OS_MBOX_DEL_EN 1
#define OS_MBOX_EN 1
#define OS_MBOX_POST_EN 1
#define OS_MBOX_POST_OPT_EN 1
#define OS_MBOX_QUERY_EN 1
#define OS_MEM_EN 1
#define OS_MEM_NAME_SIZE 32
#define OS_MEM_QUERY_EN 1
#define OS_MUTEX_ACCEPT_EN 1
#define OS_MUTEX_DEL_EN 1
#define OS_MUTEX_EN 1
#define OS_MUTEX_QUERY_EN 1
#define OS_Q_ACCEPT_EN 1
#define OS_Q_DEL_EN 1
#define OS_Q_EN 1
#define OS_Q_FLUSH_EN 1
#define OS_Q_POST_EN 1
#define OS_Q_POST_FRONT_EN 1
#define OS_Q_POST_OPT_EN 1
#define OS_Q_QUERY_EN 1
#define OS_SCHED_LOCK_EN 1
#define OS_SEM_ACCEPT_EN 1
#define OS_SEM_DEL_EN 1
#define OS_SEM_EN 1
#define OS_SEM_QUERY_EN 1
#define OS_SEM_SET_EN 1
#define OS_TASK_CHANGE_PRIO_EN 1
#define OS_TASK_CREATE_EN 1
#define OS_TASK_CREATE_EXT_EN 1
#define OS_TASK_DEL_EN 1
#define OS_TASK_IDLE_STK_SIZE 512
#define OS_TASK_NAME_SIZE 32
#define OS_TASK_PROFILE_EN 1
#define OS_TASK_QUERY_EN 1
#define OS_TASK_STAT_EN 1
#define OS_TASK_STAT_STK_CHK_EN 1
#define OS_TASK_STAT_STK_SIZE 512
#define OS_TASK_SUSPEND_EN 1
#define OS_TASK_SW_HOOK_EN 1
#define OS_TASK_TMR_PRIO 0
#define OS_TASK_TMR_STK_SIZE 512
#define OS_THREAD_SAFE_NEWLIB 1
#define OS_TICKS_PER_SEC TIMER_TICKS_PER_SEC
#define OS_TICK_STEP_EN 1
#define OS_TIME_DLY_HMSM_EN 1
#define OS_TIME_DLY_RESUME_EN 1
#define OS_TIME_GET_SET_EN 1
#define OS_TIME_TICK_HOOK_EN 1
#define OS_TMR_CFG_MAX 16
#define OS_TMR_CFG_NAME_SIZE 16
#define OS_TMR_CFG_TICKS_PER_SEC 10
#define OS_TMR_CFG_WHEEL_SIZE 2
#define OS_TMR_EN 0

#endif /* __SYSTEM_H_ */
