/*
 * system.h - SOPC Builder system and BSP software package information
 *
 * Machine generated for CPU 'cpu_0' in SOPC Builder design 'experiment3b'
 * SOPC Builder design path: ../../experiment3b.sopcinfo
 *
 * Generated: Tue Oct 30 17:21:25 EDT 2012
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
#define ALT_CPU_BREAK_ADDR 0x8820
#define ALT_CPU_CPU_FREQ 50000000u
#define ALT_CPU_CPU_ID_SIZE 1
#define ALT_CPU_CPU_ID_VALUE 0x00000000
#define ALT_CPU_CPU_IMPLEMENTATION "tiny"
#define ALT_CPU_DATA_ADDR_WIDTH 0x10
#define ALT_CPU_DCACHE_LINE_SIZE 0
#define ALT_CPU_DCACHE_LINE_SIZE_LOG2 0
#define ALT_CPU_DCACHE_SIZE 0
#define ALT_CPU_EXCEPTION_ADDR 0x4020
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
#define ALT_CPU_INST_ADDR_WIDTH 0x10
#define ALT_CPU_NAME "cpu_0"
#define ALT_CPU_RESET_ADDR 0x4000


/*
 * CPU configuration (with legacy prefix - don't use these anymore)
 *
 */

#define NIOS2_BIG_ENDIAN 0
#define NIOS2_BREAK_ADDR 0x8820
#define NIOS2_CPU_FREQ 50000000u
#define NIOS2_CPU_ID_SIZE 1
#define NIOS2_CPU_ID_VALUE 0x00000000
#define NIOS2_CPU_IMPLEMENTATION "tiny"
#define NIOS2_DATA_ADDR_WIDTH 0x10
#define NIOS2_DCACHE_LINE_SIZE 0
#define NIOS2_DCACHE_LINE_SIZE_LOG2 0
#define NIOS2_DCACHE_SIZE 0
#define NIOS2_EXCEPTION_ADDR 0x4020
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
#define NIOS2_INST_ADDR_WIDTH 0x10
#define NIOS2_RESET_ADDR 0x4000


/*
 * Define for each module class mastered by the CPU
 *
 */

#define __ALTERA_AVALON_JTAG_UART
#define __ALTERA_AVALON_ONCHIP_MEMORY2
#define __ALTERA_AVALON_PIO
#define __ALTERA_NIOS2_QSYS
#define __ALTERA_UP_AVALON_CHARACTER_LCD


/*
 * LED_GREEN_O configuration
 *
 */

#define ALT_MODULE_CLASS_LED_GREEN_O altera_avalon_pio
#define LED_GREEN_O_BASE 0x9010
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
#define LED_RED_O_BASE 0x9000
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
 * SEVEN_SEGMENT_N_O_0 configuration
 *
 */

#define ALT_MODULE_CLASS_SEVEN_SEGMENT_N_O_0 altera_avalon_pio
#define SEVEN_SEGMENT_N_O_0_BASE 0x9020
#define SEVEN_SEGMENT_N_O_0_BIT_CLEARING_EDGE_REGISTER 0
#define SEVEN_SEGMENT_N_O_0_BIT_MODIFYING_OUTPUT_REGISTER 0
#define SEVEN_SEGMENT_N_O_0_CAPTURE 0
#define SEVEN_SEGMENT_N_O_0_DATA_WIDTH 7
#define SEVEN_SEGMENT_N_O_0_DO_TEST_BENCH_WIRING 0
#define SEVEN_SEGMENT_N_O_0_DRIVEN_SIM_VALUE 0x0
#define SEVEN_SEGMENT_N_O_0_EDGE_TYPE "NONE"
#define SEVEN_SEGMENT_N_O_0_FREQ 50000000u
#define SEVEN_SEGMENT_N_O_0_HAS_IN 0
#define SEVEN_SEGMENT_N_O_0_HAS_OUT 1
#define SEVEN_SEGMENT_N_O_0_HAS_TRI 0
#define SEVEN_SEGMENT_N_O_0_IRQ -1
#define SEVEN_SEGMENT_N_O_0_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SEVEN_SEGMENT_N_O_0_IRQ_TYPE "NONE"
#define SEVEN_SEGMENT_N_O_0_NAME "/dev/SEVEN_SEGMENT_N_O_0"
#define SEVEN_SEGMENT_N_O_0_RESET_VALUE 0x0
#define SEVEN_SEGMENT_N_O_0_SPAN 16
#define SEVEN_SEGMENT_N_O_0_TYPE "altera_avalon_pio"


/*
 * SEVEN_SEGMENT_N_O_1 configuration
 *
 */

#define ALT_MODULE_CLASS_SEVEN_SEGMENT_N_O_1 altera_avalon_pio
#define SEVEN_SEGMENT_N_O_1_BASE 0x9030
#define SEVEN_SEGMENT_N_O_1_BIT_CLEARING_EDGE_REGISTER 0
#define SEVEN_SEGMENT_N_O_1_BIT_MODIFYING_OUTPUT_REGISTER 0
#define SEVEN_SEGMENT_N_O_1_CAPTURE 0
#define SEVEN_SEGMENT_N_O_1_DATA_WIDTH 7
#define SEVEN_SEGMENT_N_O_1_DO_TEST_BENCH_WIRING 0
#define SEVEN_SEGMENT_N_O_1_DRIVEN_SIM_VALUE 0x0
#define SEVEN_SEGMENT_N_O_1_EDGE_TYPE "NONE"
#define SEVEN_SEGMENT_N_O_1_FREQ 50000000u
#define SEVEN_SEGMENT_N_O_1_HAS_IN 0
#define SEVEN_SEGMENT_N_O_1_HAS_OUT 1
#define SEVEN_SEGMENT_N_O_1_HAS_TRI 0
#define SEVEN_SEGMENT_N_O_1_IRQ -1
#define SEVEN_SEGMENT_N_O_1_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SEVEN_SEGMENT_N_O_1_IRQ_TYPE "NONE"
#define SEVEN_SEGMENT_N_O_1_NAME "/dev/SEVEN_SEGMENT_N_O_1"
#define SEVEN_SEGMENT_N_O_1_RESET_VALUE 0x0
#define SEVEN_SEGMENT_N_O_1_SPAN 16
#define SEVEN_SEGMENT_N_O_1_TYPE "altera_avalon_pio"


/*
 * SWITCH_GrpA_I configuration
 *
 */

#define ALT_MODULE_CLASS_SWITCH_GrpA_I altera_avalon_pio
#define SWITCH_GRPA_I_BASE 0x9040
#define SWITCH_GRPA_I_BIT_CLEARING_EDGE_REGISTER 0
#define SWITCH_GRPA_I_BIT_MODIFYING_OUTPUT_REGISTER 0
#define SWITCH_GRPA_I_CAPTURE 1
#define SWITCH_GRPA_I_DATA_WIDTH 9
#define SWITCH_GRPA_I_DO_TEST_BENCH_WIRING 0
#define SWITCH_GRPA_I_DRIVEN_SIM_VALUE 0x0
#define SWITCH_GRPA_I_EDGE_TYPE "ANY"
#define SWITCH_GRPA_I_FREQ 50000000u
#define SWITCH_GRPA_I_HAS_IN 1
#define SWITCH_GRPA_I_HAS_OUT 0
#define SWITCH_GRPA_I_HAS_TRI 0
#define SWITCH_GRPA_I_IRQ 1
#define SWITCH_GRPA_I_IRQ_INTERRUPT_CONTROLLER_ID 0
#define SWITCH_GRPA_I_IRQ_TYPE "EDGE"
#define SWITCH_GRPA_I_NAME "/dev/SWITCH_GrpA_I"
#define SWITCH_GRPA_I_RESET_VALUE 0x0
#define SWITCH_GRPA_I_SPAN 16
#define SWITCH_GRPA_I_TYPE "altera_avalon_pio"


/*
 * SWITCH_GrpB_I configuration
 *
 */

#define ALT_MODULE_CLASS_SWITCH_GrpB_I altera_avalon_pio
#define SWITCH_GRPB_I_BASE 0x9050
#define SWITCH_GRPB_I_BIT_CLEARING_EDGE_REGISTER 0
#define SWITCH_GRPB_I_BIT_MODIFYING_OUTPUT_REGISTER 0
#define SWITCH_GRPB_I_CAPTURE 1
#define SWITCH_GRPB_I_DATA_WIDTH 9
#define SWITCH_GRPB_I_DO_TEST_BENCH_WIRING 0
#define SWITCH_GRPB_I_DRIVEN_SIM_VALUE 0x0
#define SWITCH_GRPB_I_EDGE_TYPE "ANY"
#define SWITCH_GRPB_I_FREQ 50000000u
#define SWITCH_GRPB_I_HAS_IN 1
#define SWITCH_GRPB_I_HAS_OUT 0
#define SWITCH_GRPB_I_HAS_TRI 0
#define SWITCH_GRPB_I_IRQ 2
#define SWITCH_GRPB_I_IRQ_INTERRUPT_CONTROLLER_ID 0
#define SWITCH_GRPB_I_IRQ_TYPE "EDGE"
#define SWITCH_GRPB_I_NAME "/dev/SWITCH_GrpB_I"
#define SWITCH_GRPB_I_RESET_VALUE 0x0
#define SWITCH_GRPB_I_SPAN 16
#define SWITCH_GRPB_I_TYPE "altera_avalon_pio"


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
#define ALT_STDERR_BASE 0x9060
#define ALT_STDERR_DEV jtag_uart_0
#define ALT_STDERR_IS_JTAG_UART
#define ALT_STDERR_PRESENT
#define ALT_STDERR_TYPE "altera_avalon_jtag_uart"
#define ALT_STDIN "/dev/jtag_uart_0"
#define ALT_STDIN_BASE 0x9060
#define ALT_STDIN_DEV jtag_uart_0
#define ALT_STDIN_IS_JTAG_UART
#define ALT_STDIN_PRESENT
#define ALT_STDIN_TYPE "altera_avalon_jtag_uart"
#define ALT_STDOUT "/dev/jtag_uart_0"
#define ALT_STDOUT_BASE 0x9060
#define ALT_STDOUT_DEV jtag_uart_0
#define ALT_STDOUT_IS_JTAG_UART
#define ALT_STDOUT_PRESENT
#define ALT_STDOUT_TYPE "altera_avalon_jtag_uart"
#define ALT_SYSTEM_NAME "experiment3b"


/*
 * character_lcd_0 configuration
 *
 */

#define ALT_MODULE_CLASS_character_lcd_0 altera_up_avalon_character_lcd
#define CHARACTER_LCD_0_BASE 0x9068
#define CHARACTER_LCD_0_IRQ -1
#define CHARACTER_LCD_0_IRQ_INTERRUPT_CONTROLLER_ID -1
#define CHARACTER_LCD_0_NAME "/dev/character_lcd_0"
#define CHARACTER_LCD_0_SPAN 2
#define CHARACTER_LCD_0_TYPE "altera_up_avalon_character_lcd"


/*
 * hal configuration
 *
 */

#define ALT_MAX_FD 4
#define ALT_SYS_CLK none
#define ALT_TIMESTAMP_CLK none


/*
 * jtag_uart_0 configuration
 *
 */

#define ALT_MODULE_CLASS_jtag_uart_0 altera_avalon_jtag_uart
#define JTAG_UART_0_BASE 0x9060
#define JTAG_UART_0_IRQ 0
#define JTAG_UART_0_IRQ_INTERRUPT_CONTROLLER_ID 0
#define JTAG_UART_0_NAME "/dev/jtag_uart_0"
#define JTAG_UART_0_READ_DEPTH 64
#define JTAG_UART_0_READ_THRESHOLD 8
#define JTAG_UART_0_SPAN 8
#define JTAG_UART_0_TYPE "altera_avalon_jtag_uart"
#define JTAG_UART_0_WRITE_DEPTH 64
#define JTAG_UART_0_WRITE_THRESHOLD 8


/*
 * onchip_memory2_0 configuration
 *
 */

#define ALT_MODULE_CLASS_onchip_memory2_0 altera_avalon_onchip_memory2
#define ONCHIP_MEMORY2_0_ALLOW_IN_SYSTEM_MEMORY_CONTENT_EDITOR 0
#define ONCHIP_MEMORY2_0_ALLOW_MRAM_SIM_CONTENTS_ONLY_FILE 0
#define ONCHIP_MEMORY2_0_BASE 0x4000
#define ONCHIP_MEMORY2_0_CONTENTS_INFO ""
#define ONCHIP_MEMORY2_0_DUAL_PORT 0
#define ONCHIP_MEMORY2_0_GUI_RAM_BLOCK_TYPE "Automatic"
#define ONCHIP_MEMORY2_0_INIT_CONTENTS_FILE "onchip_memory2_0"
#define ONCHIP_MEMORY2_0_INIT_MEM_CONTENT 1
#define ONCHIP_MEMORY2_0_INSTANCE_ID "NONE"
#define ONCHIP_MEMORY2_0_IRQ -1
#define ONCHIP_MEMORY2_0_IRQ_INTERRUPT_CONTROLLER_ID -1
#define ONCHIP_MEMORY2_0_NAME "/dev/onchip_memory2_0"
#define ONCHIP_MEMORY2_0_NON_DEFAULT_INIT_FILE_ENABLED 0
#define ONCHIP_MEMORY2_0_RAM_BLOCK_TYPE "Auto"
#define ONCHIP_MEMORY2_0_READ_DURING_WRITE_MODE "DONT_CARE"
#define ONCHIP_MEMORY2_0_SINGLE_CLOCK_OP 0
#define ONCHIP_MEMORY2_0_SIZE_MULTIPLE 1
#define ONCHIP_MEMORY2_0_SIZE_VALUE 16384u
#define ONCHIP_MEMORY2_0_SPAN 16384
#define ONCHIP_MEMORY2_0_TYPE "altera_avalon_onchip_memory2"
#define ONCHIP_MEMORY2_0_WRITABLE 1

#endif /* __SYSTEM_H_ */
