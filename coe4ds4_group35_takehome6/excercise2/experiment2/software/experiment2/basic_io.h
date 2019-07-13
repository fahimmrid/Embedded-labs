// Copyright by Adam Kinsman, Henry Ko and Nicola Nicolici
// Developed for the Embedded Systems course (COE4DS4)
// Department of Electrical and Computer Engineering
// McMaster University
// Ontario, Canada

#ifndef   __basic_io_H__
#define   __basic_io_H__

#include <io.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "system.h"
#include "sys/alt_irq.h"

#define SEG7_VALUE        0x11111111
#define LED_GREEN_VALUE   0x0
#define LED_RED_VALUE     0x0

//  for GPIO
#define inport(base)                                  IORD(base, 0)
#define outport(base, data)                           IOWR(base, 0, data)
#define get_pio_dir(base)                             IORD(base, 1)
#define set_pio_dir(base, data)                       IOWR(base, 1, data)
#define get_pio_irq_mask(base)                        IORD(base, 2)
#define set_pio_irq_mask(base, data)                  IOWR(base, 2, data)
#define get_pio_edge_cap(base)                        IORD(base, 3)
#define set_pio_edge_cap(base, data)                  IOWR(base, 3, data)

//  for SEG7 Display
#define seg7_show(base,data)                          IOWR(base, 0, data)

#endif
