// Copyright by Adam Kinsman, Henry Ko and Nicola Nicolici
// Developed for the Embedded Systems course (COE4DS4)
// Department of Electrical and Computer Engineering
// McMaster University
// Ontario, Canada

#include "define.h"


void translate_PS2_code(PS2_buffer_struct *PS2_buffer_data, int PS2_code ) {
	// (*PS2).cur_buf //


	if (PS2_buffer_data->cur_buf_length >= MAX_STRING_LENGTH-2) {
		printf("buffer overflow\n");
	} else

		{
		switch (PS2_code) {
			case 0x0E: PS2_buffer_data->string_buffer[PS2_buffer_data->cur_buf_length++] = '`'; break;
			case 0x16: PS2_buffer_data->string_buffer[PS2_buffer_data->cur_buf_length++] = '1'; break;
			case 0x1E: PS2_buffer_data->string_buffer[PS2_buffer_data->cur_buf_length++] = '2'; break;
			case 0x26: PS2_buffer_data->string_buffer[PS2_buffer_data->cur_buf_length++] = '3'; break;
			case 0x25: PS2_buffer_data->string_buffer[PS2_buffer_data->cur_buf_length++] = '4'; break;
			case 0x2E: PS2_buffer_data->string_buffer[PS2_buffer_data->cur_buf_length++] = '5'; break;
			case 0x36: PS2_buffer_data->string_buffer[PS2_buffer_data->cur_buf_length++] = '6'; break;
			case 0x3D: PS2_buffer_data->string_buffer[PS2_buffer_data->cur_buf_length++] = '7'; break;
			case 0x3E: PS2_buffer_data->string_buffer[PS2_buffer_data->cur_buf_length++] = '8'; break;
			case 0x46: PS2_buffer_data->string_buffer[PS2_buffer_data->cur_buf_length++] = '9'; break;
			case 0x45: PS2_buffer_data->string_buffer[PS2_buffer_data->cur_buf_length++] = '0'; break;
			case 0x4E: PS2_buffer_data->string_buffer[PS2_buffer_data->cur_buf_length++] = '-'; break;
			case 0x55: PS2_buffer_data->string_buffer[PS2_buffer_data->cur_buf_length++] = '='; break;

			case 0x5D: PS2_buffer_data->string_buffer[PS2_buffer_data->cur_buf_length++] = '\\'; break;
			case 0x15: PS2_buffer_data->string_buffer[PS2_buffer_data->cur_buf_length++] = (PS2_buffer_data->caps_lock) ? 'Q' : 'q'; break;
			case 0x1D: PS2_buffer_data->string_buffer[PS2_buffer_data->cur_buf_length++] = (PS2_buffer_data->caps_lock) ? 'W' : 'w'; break;
			case 0x24: PS2_buffer_data->string_buffer[PS2_buffer_data->cur_buf_length++] = (PS2_buffer_data->caps_lock) ? 'E' : 'e'; break;
			case 0x2D: PS2_buffer_data->string_buffer[PS2_buffer_data->cur_buf_length++] = (PS2_buffer_data->caps_lock) ? 'R' : 'r'; break;
			case 0x2C: PS2_buffer_data->string_buffer[PS2_buffer_data->cur_buf_length++] = (PS2_buffer_data->caps_lock) ? 'T' : 't'; break;
			case 0x35: PS2_buffer_data->string_buffer[PS2_buffer_data->cur_buf_length++] = (PS2_buffer_data->caps_lock) ? 'Y' : 'y'; break;
			case 0x3C: PS2_buffer_data->string_buffer[PS2_buffer_data->cur_buf_length++] = (PS2_buffer_data->caps_lock) ? 'U' : 'u'; break;
			case 0x43: PS2_buffer_data->string_buffer[PS2_buffer_data->cur_buf_length++] = (PS2_buffer_data->caps_lock) ? 'I' : 'i'; break;
			case 0x44: PS2_buffer_data->string_buffer[PS2_buffer_data->cur_buf_length++] = (PS2_buffer_data->caps_lock) ? 'O' : 'o'; break;
			case 0x4D: PS2_buffer_data->string_buffer[PS2_buffer_data->cur_buf_length++] = (PS2_buffer_data->caps_lock) ? 'P' : 'p'; break;
			case 0x54: PS2_buffer_data->string_buffer[PS2_buffer_data->cur_buf_length++] = '['; break;
			case 0x5B: PS2_buffer_data->string_buffer[PS2_buffer_data->cur_buf_length++] = ']'; break;

			case 0x1C: PS2_buffer_data->string_buffer[PS2_buffer_data->cur_buf_length++] = (PS2_buffer_data->caps_lock) ? 'A' :'a'; break;
			case 0x1B: PS2_buffer_data->string_buffer[PS2_buffer_data->cur_buf_length++] = (PS2_buffer_data->caps_lock) ? 'S' :'s'; break;
			case 0x23: PS2_buffer_data->string_buffer[PS2_buffer_data->cur_buf_length++] = (PS2_buffer_data->caps_lock) ? 'D' :'d'; break;
			case 0x2B: PS2_buffer_data->string_buffer[PS2_buffer_data->cur_buf_length++] = (PS2_buffer_data->caps_lock) ? 'F' :'f'; break;
			case 0x34: PS2_buffer_data->string_buffer[PS2_buffer_data->cur_buf_length++] = (PS2_buffer_data->caps_lock) ? 'G' :'g'; break;
			case 0x33: PS2_buffer_data->string_buffer[PS2_buffer_data->cur_buf_length++] = (PS2_buffer_data->caps_lock) ? 'H' :'h'; break;
			case 0x3B: PS2_buffer_data->string_buffer[PS2_buffer_data->cur_buf_length++] = (PS2_buffer_data->caps_lock) ? 'J' :'j'; break;
			case 0x42: PS2_buffer_data->string_buffer[PS2_buffer_data->cur_buf_length++] = (PS2_buffer_data->caps_lock) ? 'K' :'k'; break;
			case 0x4B: PS2_buffer_data->string_buffer[PS2_buffer_data->cur_buf_length++] = (PS2_buffer_data->caps_lock) ? 'L' :'l'; break;
			case 0x4C: PS2_buffer_data->string_buffer[PS2_buffer_data->cur_buf_length++] = ';'; break;
			case 0x52: PS2_buffer_data->string_buffer[PS2_buffer_data->cur_buf_length++] = '\''; break;
			case 0x1A: PS2_buffer_data->string_buffer[PS2_buffer_data->cur_buf_length++] = (PS2_buffer_data->caps_lock) ? 'Z' :'z'; break;
			case 0x22: PS2_buffer_data->string_buffer[PS2_buffer_data->cur_buf_length++] = (PS2_buffer_data->caps_lock) ? 'X' :'x'; break;


			case 0x21: PS2_buffer_data->string_buffer[PS2_buffer_data->cur_buf_length++] = (PS2_buffer_data->caps_lock) ? 'C' :'c'; break;
			case 0x2A: PS2_buffer_data->string_buffer[PS2_buffer_data->cur_buf_length++] = (PS2_buffer_data->caps_lock) ? 'V' :'v'; break;
			case 0x32: PS2_buffer_data->string_buffer[PS2_buffer_data->cur_buf_length++] = (PS2_buffer_data->caps_lock) ? 'B' :'b'; break;
			case 0x31: PS2_buffer_data->string_buffer[PS2_buffer_data->cur_buf_length++] = (PS2_buffer_data->caps_lock) ? 'N' :'n'; break;
			case 0x3A: PS2_buffer_data->string_buffer[PS2_buffer_data->cur_buf_length++] = (PS2_buffer_data->caps_lock) ? 'M' :'m'; break;
			case 0x41: PS2_buffer_data->string_buffer[PS2_buffer_data->cur_buf_length++] = ','; break;
			case 0x49: PS2_buffer_data->string_buffer[PS2_buffer_data->cur_buf_length++] = '.'; break;
			case 0x4A: PS2_buffer_data->string_buffer[PS2_buffer_data->cur_buf_length++] = '/'; break;
			case 0x29: PS2_buffer_data->string_buffer[PS2_buffer_data->cur_buf_length++] = ' '; break;
			case 0x5A: PS2_buffer_data->string_buffer[PS2_buffer_data->cur_buf_length++] = '\n'; break;
			//case 0x58: PS2_buffer_data->caps_lock =  !(PS2_buffer_data->caps_lock); break;
		}
	
		//PS2_buffer_data->cur_buf_length++;
		PS2_buffer_data->string_buffer[PS2_buffer_data->cur_buf_length] = '\0';

		//PS2_buffer_data->buffer_flush = 1;


	}
}

void read_PS2_data(int *make_code_flag, int *PS2_code) {
	int data;
	
	data = IORD(PS2_CONTROLLER_COMPONENT_0_BASE, 0);
	*make_code_flag = (data >> 8) & 0x1;
	*PS2_code = data & 0xFF; //value at , wirting
}



// ISR when the a PS2 code is acquired
void handle_PS2_interrupts(PS2_buffer_struct *PS2_buffer_data)
{
	int make_code_flag, PS2_code;
	int make_code_flag_buf ;
	int PS2_code_buf ;
	int array[200];
	int release_array[200];
		int press = 0;
	    int key = 0;
	    int max = 200;
	    int flag;
	    int release_flag = 0;


	make_code_flag_buf = make_code_flag;
	PS2_code_buf= PS2_code;


	read_PS2_data(&make_code_flag, &PS2_code); //giving address
      //array[PS2_code], w.e elsement ++ //having 26 element to check.


	if (array[key] == PS2_code && press == max) {

		flag = 0;
	    release_flag = 1;
	}
	else {
		   if (array[key] !=  PS2_code) {
			    release_flag = 1;
			    flag = 1;
			    release_flag = 0;
				array[press] = PS2_code;
			    press++;


		    for(key = 0; key<press; key++)
			{
				if (array[key] == PS2_code){
				 array[press] = PS2_code;}
				break;
				if (array[key] == PS2_code){

				array[press] = PS2_code;
				flag=1;
			    release_flag = 0;}
				else {
				//array[key] != PS2_code;
				//flag = 0;
				flag= 0;
			    release_flag = 1;
			     press--;
			    // make_code_flag == 0;

			     break;
			    // release_flag = 0;

				}
			}
			//}
		 }

	}

	   // printf ("val:  %x",  array[i] );

		if ((make_code_flag) && (flag ==1 ) && (release_flag != 1)) {
			//if (PS2_code_buf != PS2_code) {
			translate_PS2_code(PS2_buffer_data, PS2_code);
			PS2_buffer_data->buffer_flush = 1;

			flag = 0;
		//	release_flag = 1;
		}
		//make_code_flag_buf = make_code_flag;

		if ((make_code_flag == 1) && (make_code_flag_buf == 0)) {
			make_code_flag_buf = make_code_flag;
		}

	//	make_code_flag_buf = make_code_flag;
	//	if (make_code_flag == 0)
			//((PS2_buffer_struct *)PS2_buffer_data)-> (PS2_code >> 4);
			//PS2_buffer_data->caps_lock =  !(PS2_buffer_data->caps_lock);
		//	 translate_PS2_code(PS2_code, (PS2_buffer_struct *)PS2_buffer_data);

// make_code && ps2_buffer_data->flag

	  if ((make_code_flag == 0) && ((PS2_code==0x58))) {//PS2_code == 0x58

		  PS2_buffer_data->caps_lock = !(PS2_buffer_data->caps_lock);
		//   translate_PS2_code(PS2_buffer_data, PS2_code);
		 //  translate_PS2_code(PS2_code, (PS2_buffer_struct *)PS2_buffer_data);
		//  (*PS2_buffer_data).caps_lock =  !(*PS2_buffer_data).caps_lock;
	  }


	IOWR(PS2_CONTROLLER_COMPONENT_0_BASE, 0, 0);
}

// Function for initializing the ISR of the PS2_controller
void init_PS2_irq(PS2_buffer_struct *PS2_buffer_data) {
	IOWR(PS2_CONTROLLER_COMPONENT_0_BASE, 0, 0);

	alt_irq_register(PS2_CONTROLLER_COMPONENT_0_IRQ, (void *)PS2_buffer_data, (void*)handle_PS2_interrupts );
}
