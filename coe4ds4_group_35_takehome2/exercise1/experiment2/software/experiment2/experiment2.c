// Copyright by Adam Kinsman, Henry Ko and Nicola Nicolici
// Developed for the Embedded Systems course (COE4DS4)
// Department of Electrical and Computer Engineering
// McMaster University
// Ontario, Canada

#include "io.h"
#include "system.h"
#include "alt_types.h"
#include "sys/alt_stdio.h"

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


int main()
{
    alt_8 i;
    alt_u32 switch_val;
  //  alt_8 new_or;
   // alt_8 new_two;
    alt_u32 number;
    alt_u32 number2;
    alt_8 number3 ;
    alt_8 on_off_count;
    alt_8 number4;
    alt_8 flag;
    alt_u32 result;
    alt_u32 result_two;

    alt_u16 green;//hgreen led 8 bits
 /*   alt_8 binary_set;
    alt_8 ex17;
    alt_8 ex16;
    alt_8 ex15;
    alt_8 ex14;
    alt_8 ex13;*/

  //  char new17 = (switch_val >> 17) & 0x1;
   // char new16 = (switch_val >> 16) & 0x1;
   // new = (new16 && new17);

    alt_putstr("Experiment 2!\n");
    alt_printf ("%x",number3);
    
    /* Event loop never exits. */
    while (1) {
        switch_val = IORD(SWITCH_I_BASE, 0);

     IOWR(LED_GREEN_O_BASE, 0, green);  //green

       // result = (number<<13 | number2<<8|number3<<3) ;
     //result = (number | number2 ) ;
      // number3 = (number3 << 3);
     //    result |= number4;


	 	number3 = 0x0;
	 	on_off_count = 0x0;
	 	green = 0x100; //256 so the 9th bit  one (LED 8)


         IOWR(LED_RED_O_BASE, 0, number);


        if  (switch_val == 0) {
              //number2 = 31;
             //number2 = (number2 << 8);
               number = 2047;
               number = (number <<8);
             //number = 31;
               //number=(number<<13);
             //  result = 2047;

       } else {
     	for (i = 17; i >= 0; i--) {
                 if ((switch_val >> i ) != 0) {
                	 number = (i << 13); // in the first case when i = 17, number is 17 shifted by 13
                              i = 0;
                          }

               }


        	for ( i = 0; i <= 17; i++)  {
        		 if ((switch_val >> i ) &(0x1)!= 0) {
        			 number |= (i << 8);
        		            i = 17;
        		                          }
        		}


        	number |= number;

        /*	flag = 0x0;
        	for ( i = 17; i >= 0; i--)  {
        		 if (((switch_val >> i ) &(0x1)) != 0) {
        			 number3 += 1;
        			 flag = 0x1;
        			 if (flag == 0x1) {
        			               			 on_off_count += 1; }
        		 }

        	}

        	*/

        	for ( i = 17; i >= 0; i--)  {
        		 if (((switch_val >> i ) &(0x1)) != 0) {
        			 number3 += 1; // in the first case when i = 17, number is 17 shifted by 13
        			    if ((~(switch_val >> i-1 ) &(0x1)) != 0) {
        			           			 on_off_count += 1; }
        		 }

        	}

        	 number= number| (number3 <<3) ;
        //	number4 = (number3 << 3);
        /*	 	for ( i = 17; i >= 0; i--)  {
        	 		if (~(switch_val >> i-1 ) &(0x1) != 0) {
        	             			 number3_off += 1; }*/




              if (number3 > 0x9) {
        	         number |=(0x1 <<2); //number = number | ...
              }

              if (number3 < 0x9) {
            	     number |= (0x1 <<1);
              }

              if (number3 == 0x9) {
            	  number |=  (0x1 <<0);
              }


              green = (on_off_count << 4)| green ;

              if (((number3)&(1))== 1)  { //first bit for odd is always a 1, so if it isnt 0, light up led0, use % as well
            		//  green |= green <<0 ;
                green  |= 0x1; //if you dont make green = green | new then problems
              }


       }

        /*       char new17 = (switch_val >> 17) & 0x1;
        	        char new16 = (switch_val >> 16) & 0x1;
        	        char new15 = (switch_val >> 15) & 0x1;
        	        char new14 = (switch_val >> 14) & 0x1;
        	        char new13 = (switch_val >> 13) & 0x1;

        	      alt_printf ("%x",ex17);

        	        if ((switch_val >> 17) & 0x1)
        	        ex17 = ((new17 && ~new16 && ~new15 && ~new14 && new13)>>3);
        	        else if ((switch_val >> 16) & 0x1)
        	        ex16 = (new17 && ~new16 && ~new15 && ~new14 && ~new13);
        	        else if ((switch_val >> 15) & 0x1)
        	        ex15 = (~new17 && new16 && new15 && new14 && new13);
        	        else if ((switch_val >> 14) & 0x1)
        	        ex14 = (~new17 && new16 && new15 && new14 && ~new13);
        	        else if ((switch_val >> 13) & 0x1)
        	        ex13 = (~new17 && new16 && new15 && ~new14 && new13);

        	        IOWR(LED_RED_O_BASE, 0, ex17);
        	        IOWR(LED_RED_O_BASE, 0, ex16>>3);
        	        IOWR(LED_RED_O_BASE, 0, ex15>>3);
        	        IOWR(LED_RED_O_BASE, 0, ex14>>3);
        	        IOWR(LED_RED_O_BASE, 0, ex13>>3);

        	       // i = 17;
        	        //}
        	*/




    }
        return 0;

}
