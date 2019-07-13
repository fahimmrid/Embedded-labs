/*
 * system.h - SOPC Builder system and BSP software package information
 *
 * Machine generated for CPU 'cpu2' in SOPC Builder design 'experiment3'
 * SOPC Builder design path: ../../experiment3.sopcinfo
 *
 * Generated: Wed Nov 21 18:30:27 EST 2012
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
#define ALT_CPU_BREAK_ADDR 0x10820
#define ALT_CPU_CPU_FREQ 50000000u
#define ALT_CPU_CPU_ID_SIZE 1
#define ALT_CPU_CPU_ID_VALUE 0x00000002
#define ALT_CPU_CPU_IMPLEMENTATION "tiny"
#define ALT_CPU_DATA_ADDR_WIDTH 0x15
#define ALT_CPU_DCACHE_LINE_SIZE 0
#define ALT_CPU_DCACHE_LINE_SIZE_LOG2 0
#define ALT_CPU_DCACHE_SIZE 0
#define ALT_CPU_EXCEPTION_ADDR 0x8020
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
#define ALT_CPU_INST_ADDR_WIDTH 0x11
#define ALT_CPU_NAME "cpu2"
#define ALT_CPU_RESET_ADDR 0x8000


/*
 * CPU configuration (with legacy prefix - don't use these anymore)
 *
 */

#define NIOS2_BIG_ENDIAN 0
#define NIOS2_BREAK_ADDR 0x10820
#define NIOS2_CPU_FREQ 50000000u
#define NIOS2_CPU_ID_SIZE 1
#define NIOS2_CPU_ID_VALUE 0x00000002
#define NIOS2_CPU_IMPLEMENTATION "tiny"
#define NIOS2_DATA_ADDR_WIDTH 0x15
#define NIOS2_DCACHE_LINE_SIZE 0
#define NIOS2_DCACHE_LINE_SIZE_LOG2 0
#define NIOS2_DCACHE_SIZE 0
#define NIOS2_EXCEPTION_ADDR 0x8020
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
#define NIOS2_INST_ADDR_WIDTH 0x11
#define NIOS2_RESET_ADDR 0x8000


/*
 * Define for each module class mastered by the CPU
 *
 */

#define __ALTERA_AVALON_MUTEX
#define __ALTERA_AVALON_ONCHIP_MEMORY2
#define __ALTERA_AVALON_PERFORMANCE_COUNTER
#define __ALTERA_AVALON_PIO
#define __ALTERA_AVALON_TIMER
#define __ALTERA_NIOS2_QSYS
#define __ALTERA_UP_AVALON_CHARACTER_LCD


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
#define ALT_STDERR "/dev/null"
#define ALT_STDERR_BASE 0x0
#define ALT_STDERR_DEV null
#define ALT_STDERR_TYPE ""
#define ALT_STDIN "/dev/null"
#define ALT_STDIN_BASE 0x0
#define ALT_STDIN_DEV null
#define ALT_STDIN_TYPE ""
#define ALT_STDOUT "/dev/null"
#define ALT_STDOUT_BASE 0x0
#define ALT_STDOUT_DEV null
#define ALT_STDOUT_TYPE ""
#define ALT_SYSTEM_NAME "experiment3"


/*
 * cpu2_LED_GREEN_O configuration
 *
 */

#define ALT_MODULE_CLASS_cpu2_LED_GREEN_O altera_avalon_pio
#define CPU2_LED_GREEN_O_BASE 0x11060
#define CPU2_LED_GREEN_O_BIT_CLEARING_EDGE_REGISTER 0
#define CPU2_LED_GREEN_O_BIT_MODIFYING_OUTPUT_REGISTER 0
#define CPU2_LED_GREEN_O_CAPTURE 0
#define CPU2_LED_GREEN_O_DATA_WIDTH 9
#define CPU2_LED_GREEN_O_DO_TEST_BENCH_WIRING 0
#define CPU2_LED_GREEN_O_DRIVEN_SIM_VALUE 0x0
#define CPU2_LED_GREEN_O_EDGE_TYPE "NONE"
#define CPU2_LED_GREEN_O_FREQ 50000000u
#define CPU2_LED_GREEN_O_HAS_IN 0
#define CPU2_LED_GREEN_O_HAS_OUT 1
#define CPU2_LED_GREEN_O_HAS_TRI 0
#define CPU2_LED_GREEN_O_IRQ -1
#define CPU2_LED_GREEN_O_IRQ_INTERRUPT_CONTROLLER_ID -1
#define CPU2_LED_GREEN_O_IRQ_TYPE "NONE"
#define CPU2_LED_GREEN_O_NAME "/dev/cpu2_LED_GREEN_O"
#define CPU2_LED_GREEN_O_RESET_VALUE 0x0
#define CPU2_LED_GREEN_O_SPAN 16
#define CPU2_LED_GREEN_O_TYPE "altera_avalon_pio"


/*
 * cpu2_PB_BUTTON_I configuration
 *
 */

#define ALT_MODULE_CLASS_cpu2_PB_BUTTON_I altera_avalon_pio
#define CPU2_PB_BUTTON_I_BASE 0x11080
#define CPU2_PB_BUTTON_I_BIT_CLEARING_EDGE_REGISTER 0
#define CPU2_PB_BUTTON_I_BIT_MODIFYING_OUTPUT_REGISTER 0
#define CPU2_PB_BUTTON_I_CAPTURE 1
#define CPU2_PB_BUTTON_I_DATA_WIDTH 2
#define CPU2_PB_BUTTON_I_DO_TEST_BENCH_WIRING 0
#define CPU2_PB_BUTTON_I_DRIVEN_SIM_VALUE 0x0
#define CPU2_PB_BUTTON_I_EDGE_TYPE "RISING"
#define CPU2_PB_BUTTON_I_FREQ 50000000u
#define CPU2_PB_BUTTON_I_HAS_IN 1
#define CPU2_PB_BUTTON_I_HAS_OUT 0
#define CPU2_PB_BUTTON_I_HAS_TRI 0
#define CPU2_PB_BUTTON_I_IRQ 1
#define CPU2_PB_BUTTON_I_IRQ_INTERRUPT_CONTROLLER_ID 0
#define CPU2_PB_BUTTON_I_IRQ_TYPE "EDGE"
#define CPU2_PB_BUTTON_I_NAME "/dev/cpu2_PB_BUTTON_I"
#define CPU2_PB_BUTTON_I_RESET_VALUE 0x0
#define CPU2_PB_BUTTON_I_SPAN 16
#define CPU2_PB_BUTTON_I_TYPE "altera_avalon_pio"


/*
 * cpu2_SWITCH_I configuration
 *
 */

#define ALT_MODULE_CLASS_cpu2_SWITCH_I altera_avalon_pio
#define CPU2_SWITCH_I_BASE 0x11070
#define CPU2_SWITCH_I_BIT_CLEARING_EDGE_REGISTER 0
#define CPU2_SWITCH_I_BIT_MODIFYING_OUTPUT_REGISTER 0
#define CPU2_SWITCH_I_CAPTURE 0
#define CPU2_SWITCH_I_DATA_WIDTH 8
#define CPU2_SWITCH_I_DO_TEST_BENCH_WIRING 0
#define CPU2_SWITCH_I_DRIVEN_SIM_VALUE 0x0
#define CPU2_SWITCH_I_EDGE_TYPE "NONE"
#define CPU2_SWITCH_I_FREQ 50000000u
#define CPU2_SWITCH_I_HAS_IN 1
#define CPU2_SWITCH_I_HAS_OUT 0
#define CPU2_SWITCH_I_HAS_TRI 0
#define CPU2_SWITCH_I_IRQ -1
#define CPU2_SWITCH_I_IRQ_INTERRUPT_CONTROLLER_ID -1
#define CPU2_SWITCH_I_IRQ_TYPE "NONE"
#define CPU2_SWITCH_I_NAME "/dev/cpu2_SWITCH_I"
#define CPU2_SWITCH_I_RESET_VALUE 0x0
#define CPU2_SWITCH_I_SPAN 16
#define CPU2_SWITCH_I_TYPE "altera_avalon_pio"


/*
 * cpu2_character_lcd_0 configuration
 *
 */

#define ALT_MODULE_CLASS_cpu2_character_lcd_0 altera_up_avalon_character_lcd
#define CPU2_CHARACTER_LCD_0_BASE 0x11090
#define CPU2_CHARACTER_LCD_0_IRQ -1
#define CPU2_CHARACTER_LCD_0_IRQ_INTERRUPT_CONTROLLER_ID -1
#define CPU2_CHARACTER_LCD_0_NAME "/dev/cpu2_character_lcd_0"
#define CPU2_CHARACTER_LCD_0_SPAN 2
#define CPU2_CHARACTER_LCD_0_TYPE "altera_up_avalon_character_lcd"


/*
 * cpu2_onchip_ram configuration
 *
 */

#define ALT_MODULE_CLASS_cpu2_onchip_ram altera_avalon_onchip_memory2
#define CPU2_ONCHIP_RAM_ALLOW_IN_SYSTEM_MEMORY_CONTENT_EDITOR 0
#define CPU2_ONCHIP_RAM_ALLOW_MRAM_SIM_CONTENTS_ONLY_FILE 0
#define CPU2_ONCHIP_RAM_BASE 0x8000
#define CPU2_ONCHIP_RAM_CONTENTS_INFO ""
#define CPU2_ONCHIP_RAM_DUAL_PORT 0
#define CPU2_ONCHIP_RAM_GUI_RAM_BLOCK_TYPE "Automatic"
#define CPU2_ONCHIP_RAM_INIT_CONTENTS_FILE "cpu2_onchip_ram"
#define CPU2_ONCHIP_RAM_INIT_MEM_CONTENT 1
#define CPU2_ONCHIP_RAM_INSTANCE_ID "NONE"
#define CPU2_ONCHIP_RAM_IRQ -1
#define CPU2_ONCHIP_RAM_IRQ_INTERRUPT_CONTROLLER_ID -1
#define CPU2_ONCHIP_RAM_NAME "/dev/cpu2_onchip_ram"
#define CPU2_ONCHIP_RAM_NON_DEFAULT_INIT_FILE_ENABLED 0
#define CPU2_ONCHIP_RAM_RAM_BLOCK_TYPE "Auto"
#define CPU2_ONCHIP_RAM_READ_DURING_WRITE_MODE "DONT_CARE"
#define CPU2_ONCHIP_RAM_SINGLE_CLOCK_OP 0
#define CPU2_ONCHIP_RAM_SIZE_MULTIPLE 1
#define CPU2_ONCHIP_RAM_SIZE_VALUE 32768u
#define CPU2_ONCHIP_RAM_SPAN 32768
#define CPU2_ONCHIP_RAM_TYPE "altera_avalon_onchip_memory2"
#define CPU2_ONCHIP_RAM_WRITABLE 1


/*
 * cpu2_performance_counter configuration
 *
 */

#define ALT_MODULE_CLASS_cpu2_performance_counter altera_avalon_performance_counter
#define CPU2_PERFORMANCE_COUNTER_BASE 0x11000
#define CPU2_PERFORMANCE_COUNTER_HOW_MANY_SECTIONS 3
#define CPU2_PERFORMANCE_COUNTER_IRQ -1
#define CPU2_PERFORMANCE_COUNTER_IRQ_INTERRUPT_CONTROLLER_ID -1
#define CPU2_PERFORMANCE_COUNTER_NAME "/dev/cpu2_performance_counter"
#define CPU2_PERFORMANCE_COUNTER_SPAN 64
#define CPU2_PERFORMANCE_COUNTER_TYPE "altera_avalon_performance_counter"


/*
 * cpu2_timer configuration
 *
 */

#define ALT_MODULE_CLASS_cpu2_timer altera_avalon_timer
#define CPU2_TIMER_ALWAYS_RUN 0
#define CPU2_TIMER_BASE 0x11040
#define CPU2_TIMER_COUNTER_SIZE 32
#define CPU2_TIMER_FIXED_PERIOD 0
#define CPU2_TIMER_FREQ 50000000u
#define CPU2_TIMER_IRQ 0
#define CPU2_TIMER_IRQ_INTERRUPT_CONTROLLER_ID 0
#define CPU2_TIMER_LOAD_VALUE 499999ull
#define CPU2_TIMER_MULT 0.0010
#define CPU2_TIMER_NAME "/dev/cpu2_timer"
#define CPU2_TIMER_PERIOD 10.0
#define CPU2_TIMER_PERIOD_UNITS "ms"
#define CPU2_TIMER_RESET_OUTPUT 0
#define CPU2_TIMER_SNAPSHOT 1
#define CPU2_TIMER_SPAN 32
#define CPU2_TIMER_TICKS_PER_SEC 100u
#define CPU2_TIMER_TIMEOUT_PULSE_OUTPUT 0
#define CPU2_TIMER_TYPE "altera_avalon_timer"


/*
 * hal configuration
 *
 */

#define ALT_MAX_FD 4
#define ALT_SYS_CLK CPU2_TIMER
#define ALT_TIMESTAMP_CLK none


/*
 * message_buffer_mutex configuration
 *
 */

#define ALT_MODULE_CLASS_message_buffer_mutex altera_avalon_mutex
#define MESSAGE_BUFFER_MUTEX_BASE 0x1020d0
#define MESSAGE_BUFFER_MUTEX_IRQ -1
#define MESSAGE_BUFFER_MUTEX_IRQ_INTERRUPT_CONTROLLER_ID -1
#define MESSAGE_BUFFER_MUTEX_NAME "/dev/message_buffer_mutex"
#define MESSAGE_BUFFER_MUTEX_OWNER_INIT 0
#define MESSAGE_BUFFER_MUTEX_OWNER_WIDTH 16
#define MESSAGE_BUFFER_MUTEX_SPAN 8
#define MESSAGE_BUFFER_MUTEX_TYPE "altera_avalon_mutex"
#define MESSAGE_BUFFER_MUTEX_VALUE_INIT 0
#define MESSAGE_BUFFER_MUTEX_VALUE_WIDTH 16


/*
 * message_buffer_ram configuration
 *
 */

#define ALT_MODULE_CLASS_message_buffer_ram altera_avalon_onchip_memory2
#define MESSAGE_BUFFER_RAM_ALLOW_IN_SYSTEM_MEMORY_CONTENT_EDITOR 0
#define MESSAGE_BUFFER_RAM_ALLOW_MRAM_SIM_CONTENTS_ONLY_FILE 0
#define MESSAGE_BUFFER_RAM_BASE 0x100000
#define MESSAGE_BUFFER_RAM_CONTENTS_INFO ""
#define MESSAGE_BUFFER_RAM_DUAL_PORT 0
#define MESSAGE_BUFFER_RAM_GUI_RAM_BLOCK_TYPE "Automatic"
#define MESSAGE_BUFFER_RAM_INIT_CONTENTS_FILE "message_buffer_ram"
#define MESSAGE_BUFFER_RAM_INIT_MEM_CONTENT 1
#define MESSAGE_BUFFER_RAM_INSTANCE_ID "NONE"
#define MESSAGE_BUFFER_RAM_IRQ -1
#define MESSAGE_BUFFER_RAM_IRQ_INTERRUPT_CONTROLLER_ID -1
#define MESSAGE_BUFFER_RAM_NAME "/dev/message_buffer_ram"
#define MESSAGE_BUFFER_RAM_NON_DEFAULT_INIT_FILE_ENABLED 0
#define MESSAGE_BUFFER_RAM_RAM_BLOCK_TYPE "Auto"
#define MESSAGE_BUFFER_RAM_READ_DURING_WRITE_MODE "DONT_CARE"
#define MESSAGE_BUFFER_RAM_SINGLE_CLOCK_OP 0
#define MESSAGE_BUFFER_RAM_SIZE_MULTIPLE 1
#define MESSAGE_BUFFER_RAM_SIZE_VALUE 4096u
#define MESSAGE_BUFFER_RAM_SPAN 4096
#define MESSAGE_BUFFER_RAM_TYPE "altera_avalon_onchip_memory2"
#define MESSAGE_BUFFER_RAM_WRITABLE 1

#endif /* __SYSTEM_H_ */
