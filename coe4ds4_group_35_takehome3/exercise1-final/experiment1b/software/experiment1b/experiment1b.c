/*
 * "Hello World" example.
 *
 * This example prints 'Hello from Nios II' to the STDOUT stream. It runs on
 * the Nios II 'standard', 'full_featured', 'fast', and 'low_cost' example
 * designs. It runs with or without the MicroC/OS-II RTOS and requires a STDOUT
 * device in your system's hardware.
 * The memory footprint of this hosted application is ~69 kbytes by default
 * using the standard reference design.
 *
 * For a reduced footprint version of this template, and an explanation of how
 * to reduce the memory footprint for a given application, see the
 * "small_hello_world" template.
 *
 */

#include <stdio.h>
#include "define.h"

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
    elevator data;
	data.door_open = 0;
	data.door_hold = 0;
	data.drc = 0;
	data.instruction = 0;
	data.cur_flo = 0;
	data.betweenflo = 0;



    init_button_irq(&data);
	init_counter_0_irq(&data);
	init_counter_1_irq(&data);
    init_switch_irq(&data);
	printf("elevator is ready to use\n");



	while(1){
		IOWR(LED_RED_O_BASE, 0, data.instruction);
		IOWR(SEVEN_SEGMENT_N_O_BASE, 0, disp_seven_seg(data.cur_flo));

		if(data.betweenflo==0){
			if(data.drc==0){
				if(data.door_open==0&&data.door_hold==0){
					if(data.instruction!=0){
						if((data.instruction>>data.cur_flo)==0){
							//printf("elevator start going down\n");
							data.drc=-1;
						}else{
							//printf("elevator start going up\n");
							data.drc=1;
						}
						data.betweenflo=1;
						reset_counter_0();

					}

				}
			}else{
				if (((data.instruction >> data.cur_flo) & 0x1) == 1) {
					data.instruction = data.instruction & ~(0x1 << data.cur_flo);

					data.door_open = 1;
					printf("elevator at floor %d, door open\n",data.cur_flo);
					reset_counter_1();
				} else {
					if(data.door_open==0 && data.door_hold==0){
						if(data.drc==1){
							if(data.cur_flo<11){
								if((data.instruction>>data.cur_flo)!=0){
									printf("elevator at floor %d, keeps going up\n",data.cur_flo);
								    data.betweenflo=1;
								    reset_counter_0();
							    }else{
									if(data.instruction==0){
										//printf("elevator at floor %d,elevator stopped\n",data.cur_flo);
									    data.drc=0;
								    }else{
										//printf("elevator at floor %d, and going down\n",data.cur_flo);
									    data.drc=-1;
									    data.betweenflo=1;
									    reset_counter_0();
								         }
							        }
						       }else{
								   if(data.instruction==0){
									   //printf("elevator stopped at the top floor\n");
									   data.drc=0;
									   }else{
										   //printf("elevator reach the top floor\n");
									       data.drc=-1;
									       data.betweenflo=1;
									       reset_counter_0();}
						        }
							}else{
								if (data.cur_flo > 0) {
									if ((data.instruction & ((~(0xFFF << data.cur_flo)) & 0xFFF)) != 0) {
								    printf("elevator at floor %d, keeps going down\n", data.cur_flo);
								    data.betweenflo = 1;
								    reset_counter_0();
									} else {
										if (data.instruction != 0) {
											//printf("elevator at floor %d, now goes up\n", data.cur_flo);
										    data.drc = 1;
										    data.betweenflo = 1;
										    reset_counter_0();
											} else {
												//printf("elevator stopped\n");
		                                        data.drc = 0;}
											}
								} else {
								    if (data.instruction != 0) {
										//printf("elevator reach the bottom floor\n");
									    data.drc = 1;
									    data.betweenflo = 1;
									    reset_counter_0();
										} else {
											//printf("elevator stop at the bottom floor\n");
									        // no more request
									        data.drc = 0;}
							            }
						            }

					    }
				    }

			    }

		}


	}
}
