// Copyright by Adam Kinsman, Henry Ko and Nicola Nicolici
// Developed for the Embedded Systems course (COE4DS4)
// Department of Electrical and Computer Engineering
// McMaster University
// Ontario, Canada

#ifndef __LTC_H__
#define __LTC_H__

#define NUM_LINES 480
#define LINE_LEN 640

alt_u8 R_vals[LINE_LEN], G_vals[LINE_LEN], B_vals[LINE_LEN];

void LTC_Switch_Nios_Mode(int);
void LTC_Switch_HW_Mode();
void LTC_Read_Image_Line(alt_u8 *, alt_u8 *, alt_u8 *);
void LTC_Write_Image_Line(alt_u8 *, alt_u8 *, alt_u8 *);
void LTC_TouchPanel_int(void);

#endif
