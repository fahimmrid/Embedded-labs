// Copyright by Adam Kinsman, Henry Ko and Nicola Nicolici
// Developed for the Embedded Systems course (COE4DS4)
// Department of Electrical and Computer Engineering
// McMaster University
// Ontario, Canada

#include <stdio.h>
#include "io.h"
#include "system.h"
#include "sys/alt_irq.h"
#include "sys/alt_stdio.h"
#include "priv/alt_busy_sleep.h"
#include <errno.h>
#include <priv/alt_file.h>
#include <string.h>
// #include "FAT32.h"
#include "SD_card_controller.h"
#include "PB_button.h"
#include "LCD_Camera_TouchPanel.h"
