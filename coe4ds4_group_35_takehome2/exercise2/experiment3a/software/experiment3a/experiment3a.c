// Copyright by Adam Kinsman, Henry Ko and Nicola Nicolici
// Developed for the Embedded Systems course (COE4DS4)
// Department of Electrical and Computer Engineering
// McMaster University
// Ontario, Canada

/*
 * "Small Hello World" example.
 *
 * This example prints 'Hello from Nios II' to the STDOUT stream. It runs on
 * the Nios II 'standard', 'full_featured', 'fast', and 'low_cost' example
 * designs. It requires a STDOUT  device in your system's hardware.
 *
 * The purpose of this example is to demonstrate the smallest possible Hello
 * World application, using the Nios II HAL library.  The memory footprint
 * of this hosted application is ~332 bytes by default using the standard
 * reference design.  For a more fully featured Hello World application
 * example, see the example titled "Hello World".
 *
 * The memory footprint of this example has been reduced by making the
 * following changes to the normal "Hello World" example.
 * Check in the Nios II Software Developers Manual for a more complete
 * description.
 *
 * In the SW Application project (small_hello_world):
 *
 *  - In the C/C++ Build page
 *
 *    - Set the Optimization Level to -Os
 *
 * In System Library project (small_hello_world_syslib):
 *  - In the C/C++ Build page
 *
 *    - Set the Optimization Level to -Os
 *
 *    - Define the preprocessor option ALT_NO_INSTRUCTION_EMULATION
 *      This removes software exception handling, which means that you cannot
 *      run code compiled for Nios II cpu with a hardware multiplier on a core
 *      without a the multiply unit. Check the Nios II Software Developers
 *      Manual for more details.
 *
 *  - In the System Library page:
 *    - Set Periodic system timer and Timestamp timer to none
 *      This prevents the automatic inclusion of the timer driver.
 *
 *    - Set Max file descriptors to 4
 *      This reduces the size of the file handle pool.
 *
 *    - Check Main function does not exit
 *    - Uncheck Clean exit (flush buffers)
 *      This removes the unneeded call to exit when main returns, since it
 *      won't.
 *
 *    - Check Don't use C++
 *      This builds without the C++ support code.
 *
 *    - Check Small C library
 *      This uses a reduced functionality C library, which lacks
 *      support for buffering, file IO, floating point and getch(), etc.
 *      Check the Nios II Software Developers Manual for a complete list.
 *
 *    - Check Reduced device drivers
 *      This uses reduced functionality drivers if they're available. For the
 *      standard design this means you get polled UART and JTAG UART drivers,
 *      no support for the LCD driver and you lose the ability to program
 *      CFI compliant flash devices.
 *
 *    - Check Access device drivers directly
 *      This bypasses the device file system to access device drivers directly.
 *      This eliminates the space required for the device file system services.
 *      It also provides a HAL version of libc services that access the drivers
 *      directly, further reducing space. Only a limited number of libc
 *      functions are available in this configuration.
 *
 *    - Use ALT versions of stdio routines:
 *
 *           Function                  Description
 *        ===============  =====================================
 *        alt_printf       Only supports %s, %x, and %c ( < 1 Kbyte)
 *        alt_putstr       Smaller overhead than puts with direct drivers
 *                         Note this function doesn't add a newline.
 *        alt_putchar      Smaller overhead than putchar with direct drivers
 *        alt_getchar      Smaller overhead than getchar with direct drivers
 *
 */

#include "system.h"
#include <io.h>
#include "sys/alt_stdio.h"
#include "alt_types.h"
#include "altera_up_avalon_character_lcd.h"
#include <unistd.h>
#include <stdio.h>

char stringtb(alt_16 number) {
	if (number < 0) number = -number;
	switch(number) {
		case 1: return '1';
		case 2: return '2';
		case 3: return '3';
		case 4: return '4';
		case 5: return '5';
		case 6: return '6';
		case 7: return '7';
		case 8: return '8';
		case 9: return '9';
		default: return '0';
	}
}

alt_u16 disp_seven_seg(alt_u8 val) {
    switch (val) {
        case  0 : return 0x40;
        case  1 : return 0x79;
        case  2 : return 0x24;
        case  3 : return 0x30;
        case  4 : return 0x19;
        case  5 : return 0x12;
        case  6 : return 0x02;
        case  7 : return 0x78;
        case  8 : return 0x00;
        case  9 : return 0x18;
        case 10 : return 0x08;
        case 11 : return 0x03;
        case 12 : return 0x46;
        case 13 : return 0x21;
        case 14 : return 0x06;
        case 15 : return 0x0e;
        default : return 0x7f;
    }
}

void number_to_string(alt_16 number, char *str) {
	alt_8 i;
	//alt_8 i_2=0;
	alt_8 i_1=0;
	alt_8 n=16;
	alt_8 sign_flag = 0;
	alt_8 neg = (number < 0);
	//char* str_pt= &str[0];
	//alt_u8 blank=0;
	char temp=' ';
	char temp_str[16] = "                ";

	for (i = 0; i < 16; i++) {
		str[15-i] = stringtb(number % 10);
		temp_str[i]=str[15-i];
		if ((number == 0) && (i > 0)) {
			str[15-i] = ' ';
			temp_str[i]=str[15-i];
			if (sign_flag == 0) {
				 sign_flag = 1;
				if (neg) {
					str[15-i] = '-';
					temp_str[i]=str[15-i];}
			}
		}
		number /= 10;


	}

	for(i=15;i>=0;i--){
		if(temp_str[i]!=' '){
			str[i_1]=temp_str[i];
			i_1++;
		}else{
			str[i]=temp_str[i];
		}

	}


	/*
	temp_str[0]=str[0];
	temp_str[1]=str[1];
	temp_str[2]=str[2];
	temp_str[3]=str[3];
	temp_str[4]=str[4];
	temp_str[5]=str[5];
	temp_str[6]=str[6];
	temp_str[7]=str[7];
	temp_str[8]=str[8];
	temp_str[9]=str[9];
	temp_str[10]=str[10];
	temp_str[11]=str[11];
	temp_str[12]=str[12];
	temp_str[13]=str[13];
	temp_str[14]=str[14];
	temp_str[15]=str[15];
   */

   /*
	str[0]=temp_str[0];
	str[1]=temp_str[1];
	str[2]=temp_str[2];
	str[3]=temp_str[3];
	str[4]=temp_str[4];
	str[5]=temp_str[5];
	str[6]=temp_str[6];
	str[7]=temp_str[7];
	str[8]=temp_str[8];
	str[9]=temp_str[9];
	str[10]=temp_str[10];
	str[11]=temp_str[11];
	str[12]=temp_str[12];
	str[13]=temp_str[13];
	str[14]=temp_str[14];
	str[15]=temp_str[15];
*/

}





int main()
{ 
	alt_u32 switch_val= 0;
	alt_u32 switch_val2= 0;
	alt_u8 prev_switch_flag17= 0;  // Stores the prev value of switch 16
	alt_u8 prev_switch_flag16= 0;
	alt_u8 empty_flag= 0;
	alt_16 ring_buffer[9] = {0x8000,0x8000,0x8000,0x8000,0x8000,0x8000,0x8000,0x8000,0x8000};
	//alt_16 ring_buffer[9];
	alt_16 max=0x8000;
	char lcd_str[17] = "                ";
	char lcd_str2[17] = "                ";
	char lcd_str3[17] = "                ";
	alt_u16 write = 0;
	alt_u16 read = 0;
	alt_u16 counter = 0;
	alt_u8	i;

	//max = 0x8000;

	alt_up_character_lcd_dev *lcd_0;

    alt_printf("Exercise 2:\n");
    
    lcd_0 = alt_up_character_lcd_open_dev(CHARACTER_LCD_0_NAME);
    
    if (lcd_0 == NULL) alt_printf("Error opening LCD device\n");
    else alt_printf("LCD device opened.\n");
    
    alt_up_character_lcd_init(lcd_0);

    //alt_up_character_lcd_string(lcd_0, "Experiment 3a");

    //alt_up_character_lcd_set_cursor_pos(lcd_0, 0, 1);

    //alt_up_character_lcd_string(lcd_0, "Welcome");
    

  /* Event loop never exits. */
  while (1) {
	  if ((switch_val= (IORD(SWITCH_I_BASE, 0) >> 17) & 0x1) != prev_switch_flag17) {
		  empty_flag=0;
		  counter=counter+1;
		  printf("counter=%d\n",counter);
		  switch_val2 = IORD(SWITCH_I_BASE, 0);
		  ring_buffer[write % 9] = (switch_val2 & 0xFFFF);
		  //printf("%d\n",write);
		  //printf("test 0 %d\n",write % 9);
		  //printf("%d\n",list[write % 9] );
		  //printf("%d\n",(switch_val2 & 0xFFFF) );
		  //printf("%d\n",list[write % 9] );
		  //printf("%d\n",list[0]);
		  //printf("%d\n",list[1]);
		  //printf("%d\n",list[2]);
		  write= write+1;
		  //printf("%d\n",max);
		  for (i = 0; i < 9; i++){
		  		if (ring_buffer[i] > max) {
		  			max = ring_buffer[i];

		  		}
		  printf("%d ",ring_buffer[i]);
		  		}
		  printf("\n ");
		  //printf("%d\n",max);
		  //printf("%d\n",write % 9);
		  //max_number(list,max);
		  number_to_string(max,lcd_str);
		  //printf("%s\n",lcd_str);
		  alt_up_character_lcd_set_cursor_pos(lcd_0, 0, 1);
		  alt_up_character_lcd_string(lcd_0, lcd_str);
		  prev_switch_flag17 = switch_val;
		  max=0x8000;
		  if((write>8)&&(counter>9)){
			  read=write%9;
			  //read=write;
			  counter=9;
		  }else{
			  read=write-counter;
		  }
		  printf("write#=%d\n",write);
	  }
	  if ((switch_val= (IORD(SWITCH_I_BASE, 0) >> 16) & 0x1) != prev_switch_flag16) {
		  printf("SWITCH 16 REACHED\n");
		  //printf("counter = %d\n",counter);
		  //write= write-1;
		  //stay_flag= prev_switch_flag17;
		  if(empty_flag){
		  				  printf("lempty REACHED\n");
		  				  alt_up_character_lcd_set_cursor_pos(lcd_0, 0, 1);
		  				  alt_up_character_lcd_string(lcd_0, "                 ");
		  				  prev_switch_flag16= switch_val;
		  				  alt_up_character_lcd_set_cursor_pos(lcd_0, 0, 0);
		  				  alt_up_character_lcd_string(lcd_0, "Empty");
		  				  prev_switch_flag16= switch_val;
		  				  read=0;
		  				  write=0;
		  				  counter=0;
		  				  printf("counter = %d\n",counter);
		  				  }
		  else if(read==(write-1)){
			  alt_up_character_lcd_set_cursor_pos(lcd_0, 0, 1);
			  alt_up_character_lcd_string(lcd_0, "                 ");
			  prev_switch_flag16= switch_val;
			  number_to_string(ring_buffer[read%9],lcd_str2);
			  alt_up_character_lcd_set_cursor_pos(lcd_0, 0, 0);
			  alt_up_character_lcd_string(lcd_0, lcd_str2);
			  ring_buffer[read%9]= 0x8000;
			  read=read+1;
			  counter=counter-1;
			  printf("counter = %d\n",counter);
			  printf("%d ",ring_buffer[0]);
			  printf("%d ",ring_buffer[1]);
			  printf("%d ",ring_buffer[2]);
			  printf("%d ",ring_buffer[3]);
			  printf("%d ",ring_buffer[4]);
			  printf("%d ",ring_buffer[5]);
			  printf("%d ",ring_buffer[6]);
			  printf("%d ",ring_buffer[7]);
			  printf("%d ",ring_buffer[8]);
			  printf("\n ");
			  empty_flag=1;
			  //write= write-1;
			  //printf("test 1 %d\n",write);
			  //write = 1;
			  //prev_switch_flag16= switch_val;
			  //max=0x8000;
			  //printf("%d\n",max);

		  }else{
		  printf("read = %d\n",read);
		  number_to_string(ring_buffer[read%9],lcd_str2);
		  alt_up_character_lcd_set_cursor_pos(lcd_0, 0, 0);
		  alt_up_character_lcd_string(lcd_0, lcd_str2);
		  ring_buffer[read%9]= 0x8000;
		  //write= write-1;
		  read=read+1;
		  counter=counter-1;
		  printf("counter = %d\n",counter);
		  printf("%d ",ring_buffer[0]);
		  printf("%d ",ring_buffer[1]);
		  printf("%d ",ring_buffer[2]);
		  printf("%d ",ring_buffer[3]);
		  printf("%d ",ring_buffer[4]);
		  printf("%d ",ring_buffer[5]);
		  printf("%d ",ring_buffer[6]);
		  printf("%d ",ring_buffer[7]);
		  printf("%d ",ring_buffer[8]);
		  printf("\n ");

		  //write= write-1;
		  //printf("test %d\n",write % 9);
		  //ring_buffer[0] = ring_buffer[1];
		  //ring_buffer[1] = ring_buffer[2];
		  //ring_buffer[2] = ring_buffer[3];
		  //ring_buffer[3] = ring_buffer[4];
		  //ring_buffer[4] = ring_buffer[5];
		  //ring_buffer[5] = ring_buffer[6];
		  //ring_buffer[6] = ring_buffer[7];
		  //ring_buffer[7] = ring_buffer[8];
		  //ring_buffer[8] = 0x8000;

		  for (i = 0; i < 9; i++){
			  if (ring_buffer[i] > max) {
		  		  max = ring_buffer[i];
		  		  		}
		  		  //printf("%d  ",list[i]);
		  		  		}
		  //printf("%d\n",max);
		  //max_number(list,max);
		  number_to_string(max,lcd_str3);
	      alt_up_character_lcd_set_cursor_pos(lcd_0, 0, 1);
	  	  alt_up_character_lcd_string(lcd_0, lcd_str3);
	  	  prev_switch_flag16= switch_val;
	  	  max=0x8000;
	  	  }
	  }

	  IOWR(SEVEN_SEGMENT_N_O_0_BASE, 0,
	    disp_seven_seg((counter) & 0xF));

  }

  return 0;
}
