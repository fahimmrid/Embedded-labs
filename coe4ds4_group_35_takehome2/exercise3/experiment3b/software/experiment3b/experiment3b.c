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

#include "io.h"
#include "system.h"
#include "alt_types.h"
#include "sys/alt_stdio.h"
#include "sys/alt_irq.h"
#include "altera_up_avalon_character_lcd.h"

#include <stdio.h>
#include <unistd.h> //sleep



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






alt_u32 switch_val_a;
alt_u32 switch_val_b;



void SW_GRPA_interrupt(int *amount) {

   // alt_printf("Switches GRPA changed\n");



	switch_val_a  = (IORD(SWITCH_GRPA_I_BASE, 3) & 0x1F);
    IOWR(SWITCH_GRPA_I_BASE, 3, 0x0);



    if (switch_val_a == 0x1){
    	if ((*amount +5)  <= 1200 ){
    	*amount = *amount + 5;
    	} if (*amount >= 1200 ){
    		IOWR(LED_RED_O_BASE, 0, (0x20000 |*amount));
    		//IOWR(LED_RED_O_BASE, 0, number);
    		usleep(1000000);}

    }



     if (switch_val_a == 0x2)
    {
    	if ((*amount + 10) <= 1200 ){
    	*amount = *amount + 10;
    	}  if (*amount >= 1200 ){
    	    	IOWR(LED_RED_O_BASE, 0, (0x20000 |*amount));
    	    		//IOWR(LED_RED_O_BASE, 0, number);
    	    	usleep(1000000);}
    }


     if (switch_val_a == 0x4)
    {
    	if ((*amount + 25)<= 1200 ){
      	*amount = *amount + 25;
    	}  if (*amount >= 1200 ){
      		IOWR(LED_RED_O_BASE, 0, (0x20000 |*amount));
      		//IOWR(LED_RED_O_BASE, 0, number);
      		usleep(1000000);}

      }

     if (switch_val_a == 0x8){
    	if ((*amount + 100 )<= 1200 ){
         	*amount = *amount + 100;
    	} if (*amount >= 1200 ){
         		IOWR(LED_RED_O_BASE, 0, (0x20000 |*amount));
         		//IOWR(LED_RED_O_BASE, 0, number);
         		usleep(1000000);}

         }

     if (switch_val_a == 0x10){
    	if ((*amount + 200)<= 1200 ){
         	*amount = *amount + 200;
    	}  if (*amount >= 1200 ){
         		IOWR(LED_RED_O_BASE, 0, (0x20000 |*amount));
         		//IOWR(LED_RED_O_BASE, 0, number);= 0x0;
         		usleep(1000000);}
         }

     IOWR(LED_GREEN_O_BASE, 0, 0x8);


     IOWR(LED_RED_O_BASE, 0, *amount);

     printf("total amount = %d.%02d\n",*amount/100,  *amount%100);
}



void SW_GRPB_interrupt(int *amount) {

   // alt_printf("Switches GRPA changed\n");


	switch_val_b  = (IORD(SWITCH_GRPB_I_BASE, 3) & 0x1F);
    IOWR(SWITCH_GRPB_I_BASE, 3, 0x0);
    IOWR(LED_RED_O_BASE, 0, *amount);

  //  if (*amount == 0x0){
 //   	IOWR(LED_GREEN_O_BASE, 0, 0x8);
  //  }

    if (*amount >0){


    if (switch_val_b == 0x1){
    	if (*amount>= 305){
    	*amount = *amount - 305;
    	 if (*amount == 0)
    	 {
    	  IOWR(LED_GREEN_O_BASE, 0, 0xA);
    	  usleep(1000000);//1010
    	  IOWR(LED_GREEN_O_BASE, 0, 0x0);
    	 }
    	}
    	else  {
    		IOWR(LED_GREEN_O_BASE, 0, 0x9);
    		usleep(1000000);
    		IOWR(LED_GREEN_O_BASE, 0, 0x8);
        }

    }

    if (switch_val_b == 0x2){
    	if (*amount>= 430){
    	*amount = *amount - 430;
    	 if (*amount == 0)
    	    	 {
    	    	  IOWR(LED_GREEN_O_BASE, 0, 0xA);
    	    	  usleep(1000000);//1010
    	    	  IOWR(LED_GREEN_O_BASE, 0, 0x0);
    	    	 }
    	}
    	else  {
    	    		IOWR(LED_GREEN_O_BASE, 0, 0x9);
    	    		usleep(1000000);
    	    		IOWR(LED_GREEN_O_BASE, 0, 0x8);
    	        }
    }

    if (switch_val_b == 0x4){
    	if (*amount>= 190){
    	*amount = *amount - 190;
    	 if (*amount == 0)
    	    	 {
    	    	  IOWR(LED_GREEN_O_BASE, 0, 0xA);
    	    	  usleep(1000000);//1010
    	    	  IOWR(LED_GREEN_O_BASE, 0, 0x0);
    	    	 }
    	}
    	else  {
    	    		IOWR(LED_GREEN_O_BASE, 0, 0x9);
    	    		usleep(1000000);
    	    		IOWR(LED_GREEN_O_BASE, 0, 0x8);
    	        }

        }

    if (switch_val_b == 0x8){
    	if (*amount>= 255){
    	*amount = *amount - 255;
    	 if (*amount == 0)
    	    	 {
    	    	  IOWR(LED_GREEN_O_BASE, 0, 0xA);
    	    	  usleep(1000000);//1010
    	    	  IOWR(LED_GREEN_O_BASE, 0, 0x0);
    	    	 }
    	}
    	else  {
    	    		IOWR(LED_GREEN_O_BASE, 0, 0x9);
    	    		usleep(1000000);
    	    		IOWR(LED_GREEN_O_BASE, 0, 0x8);
    	        }
        }

    if (switch_val_b == 0x10){
    	//IOWR(LED_GREEN_O_BASE, 0, 0x9);
    	IOWR(LED_GREEN_O_BASE, 0, 0xC); //complete with a cancel so led2!!
    	usleep(1000000);
    	IOWR(LED_GREEN_O_BASE, 0, 0x0);
    	*amount = 0;// when complete set it to zero


        }
    }
    else
    	{
    	IOWR(LED_GREEN_O_BASE, 0, 0x0);
    	usleep(1000000);
        IOWR(LED_GREEN_O_BASE, 0, 0x8);

    	}

    IOWR(LED_RED_O_BASE, 0, *amount);

	printf("total amount = %d.%02d\n",*amount/100,  *amount%100);

    }

int main (void)
{

    	volatile int amount = 0;

		IOWR(SWITCH_GRPA_I_BASE, 3, 0x0); // edge capture register
	    IOWR(SWITCH_GRPA_I_BASE, 2, 0x1F); // IRQ mask
	    alt_irq_register(SWITCH_GRPA_I_IRQ, &amount, (void*)SW_GRPA_interrupt);

	    IOWR(SWITCH_GRPB_I_BASE, 3, 0x0); // edge capture register
	    IOWR(SWITCH_GRPB_I_BASE, 2, 0x1F); // IRQ mask
	    alt_irq_register(SWITCH_GRPB_I_IRQ, &amount, (void*)SW_GRPB_interrupt);

	    IOWR(LED_GREEN_O_BASE, 0, 0x0);

	    while (1);

	    return 0;
}


/*
int main()
{
    alt_u32 sw_grp_a;
    alt_up_character_lcd_dev *lcd_0;



    alt_printf("Experiment 3b:\n");

    lcd_0 = alt_up_character_lcd_open_dev(CHARACTER_LCD_0_NAME);

    if (lcd_0 == NULL) alt_printf("Error opening LCD device\n");
    else alt_printf("LCD device opened.\n");

    alt_up_character_lcd_init(lcd_0);

    alt_up_character_lcd_string(lcd_0, "Experiment 3b");

    alt_up_character_lcd_set_cursor_pos(lcd_0, 0, 1);

    alt_up_character_lcd_string(lcd_0, "Welcome");


    /* Event loop never exits. */
    //IOWR(SEVEN_SEGMENT_N_O_0_BASE, 0, 16);

    /* Event loop never exits. */
/*
    while (1) {
        sw_grp_a = IORD(SWITCH_GRPA_I_BASE, 0);
        IOWR(SEVEN_SEGMENT_N_O_0_BASE, 0,
        disp_seven_seg(sw_grp_a & 0xF));
    }

  return 0;
}
*/
