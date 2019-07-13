// Copyright by Adam Kinsman, Henry Ko and Nicola Nicolici
// Developed for the Embedded Systems course (COE4DS4)
// Department of Electrical and Computer Engineering
// McMaster University
// Ontario, Canada

// This is the embedded software for the LCD design

#include <stdio.h>
#include "io.h"
#include "system.h"
#include "sys/alt_irq.h"
#include "sys/alt_stdio.h"
#include "priv/alt_busy_sleep.h"

int RGB_colour(int colour) {
    switch (colour & 0x7) {
        case 0 : return 0x00000000; // black 
        case 1 : return 0x000003FF; // red
        case 2 : return 0x7C007C00; // green 
        case 3 : return 0x7C007FFF; // yellow
        case 4 : return 0x03FF0000; // blue
        case 5 : return 0x03FF03FF; // magenta
        case 6 : return 0x7FFF7C00; // cyan
        case 7 : return 0x7FFF7FFF; // white
    }
    return 0x00000000;
}    


int cursur_size = 16;
int cursur_y_pos = 0;
int cursur_x_pos = 0;
int color_block[15][20]; //for each color block, since its 15 by 20 for whole grid,


void draw_horizontal_bars(int width);

//void cursur(int size);


void TouchPanel_int(void) {
    static int width = 32;
    int TP_val, x_val, y_val, key = 6;

    TP_val = IORD(NIOS_LCD_COMPONENT_0_TOUCHPANEL_BASE, 0);
    x_val = (TP_val >> 20) & 0xFF; y_val = (TP_val >> 4) & 0xFF;

    if (((TP_val >> 31) & 0x1) && (x_val >= 0xC9) && (x_val <= 0xF1)) {
        if ((y_val >= 0x17) && (y_val <= 0x33)) { // Key 0
            key = 0;
            IOWR(NIOS_LCD_COMPONENT_0_CONSOLE_BASE, 0, 0x1);
        }
        if ((y_val >= 0x3D) && (y_val <= 0x58)) { // Key 1
            key = 1;
            IOWR(NIOS_LCD_COMPONENT_0_CONSOLE_BASE, 0, 0x2);
        }
        if ((y_val >= 0x62) && (y_val <= 0x7E)) { // Key 2
            key = 2;
            IOWR(NIOS_LCD_COMPONENT_0_CONSOLE_BASE, 0, 0x4);
        }
        if ((y_val >= 0x88) && (y_val <= 0xA4)) { // Key 3
            key = 3;
            IOWR(NIOS_LCD_COMPONENT_0_CONSOLE_BASE, 0, 0x8);
        }
        if ((y_val >= 0xAE) && (y_val <= 0xC9)) { // Key 4
            key = 4;
            IOWR(NIOS_LCD_COMPONENT_0_CONSOLE_BASE, 0, 0x10);
        }
        if ((y_val >= 0xD3) && (y_val <= 0xEF)) { // Key 5
            key = 5;
            IOWR(NIOS_LCD_COMPONENT_0_CONSOLE_BASE, 0, 0x20);
        }
    } else IOWR(NIOS_LCD_COMPONENT_0_CONSOLE_BASE, 0, 0x0);
        
    if (IORD(NIOS_LCD_COMPONENT_0_TOUCHPANEL_BASE, 2) & 0x2) { // posedge
        if (key == 0)  {
        	if (cursur_y_pos > 0){
        		cursur_y_pos -= 1;
        	}
        }
        else if (key == 1)  {
                if (cursur_y_pos < 14){
                cursur_y_pos = cursur_y_pos + 1;
                	}
                }

        else if (key == 2)  {
                    if (cursur_x_pos > 0){
                       cursur_x_pos = cursur_x_pos - 1;
                        	}
                        }
        else if (key == 3)  {
                 	if (cursur_x_pos < 19){
                        cursur_x_pos = cursur_x_pos + 1;
                        	}
                        }
        else if (key == 4)  {
                    if (cursur_size < 32){
                        cursur_size = cursur_size + 4;
                        	}
                        }
        else if (key == 5)  {
                   	if (cursur_size > 4){
                        cursur_size = cursur_size - 4;
                               	}
                               }

        draw_horizontal_bars(width);
    }

    IOWR(NIOS_LCD_COMPONENT_0_CONSOLE_BASE, 0, 0x0);
    TP_val = IORD(NIOS_LCD_COMPONENT_0_TOUCHPANEL_BASE, 2);
    IOWR(NIOS_LCD_COMPONENT_0_TOUCHPANEL_BASE, 2, TP_val & 0x30);
}




void draw_horizontal_bars(int width) {

    int i, j, colour = 0;
    int width_counter = 0;
    int height;
    height = width;
    int height_counter = 0;
    int last_color = 0;
    int reset_color = 0;
    int final_color = 0;


  //  int RGB = RGB_colour(last_color);
    // int RGB2 = RGB_colour(colour);
    int RGB = RGB_colour(color_block[0][0]);
    int RGB_negative = ~RGB_colour(color_block[0][0]);
    int cursur_square;
    cursur_square = (width - cursur_size) >> 1; //(32 - size)/2

    // Set pixel position to top-left corner
    IOWR(NIOS_LCD_COMPONENT_0_IMAGE_BASE, 2, 0x1);

    for (i = 0; i < 480; i++) {
        for (j = 0; j < 640; j++) {
        	//IOWR(NIOS_LCD_COMPONENT_0_IMAGE_BASE, 0, RGB);
        	if ((last_color == cursur_y_pos) && (colour == cursur_x_pos) && (height_counter >= cursur_square) && (width_counter >= cursur_square) &&
        		(width_counter < (width -cursur_square)) && (height_counter < (width -cursur_square))) {

        		IOWR(NIOS_LCD_COMPONENT_0_IMAGE_BASE, 0, ~RGB);
        		//IOWR(NIOS_LCD_COMPONENT_0_IMAGE_BASE, 0, RGB_negative);
        		//RGB_negative = ~(RGB_colour(color_block[last_color][colour]));
        				}
        	else {
        		IOWR(NIOS_LCD_COMPONENT_0_IMAGE_BASE, 0, RGB);
        	}

            height_counter++;
            if (height_counter == height) {
               colour++;
               height_counter = 0;
             //  RGB = RGB_colour(last_color);
             //  RGB2 = RGB_colour(colour);
               RGB = RGB_colour(color_block[last_color][colour]);
               }
          //  last_color = colour;
        }
       // colour = reset_color;
       // RGB = RGB_colour(colour);
            width_counter++;
                 if (width_counter == width) {
                       //lastcc++;
                	   //reset_color = last_color;
                       width_counter = 0;
                       last_color++;
                       RGB = RGB_colour(color_block[last_color][colour]);
                      // RGB = RGB_colour(last_color);
                      // RGB2 = RGB_colour(colour);

                   }
              colour = 0;
             // RGB = RGB_colour(last_color);
            //  RGB2 = RGB_colour(colour);
              RGB = RGB_colour(color_block[last_color][colour]);
              //height_counter = 0;
              //width_counter = 0;



        }


    }


int main()
{

    printf("Experiment 1!\n");
    alt_irq_register(NIOS_LCD_COMPONENT_0_TOUCHPANEL_IRQ, NULL, (void *)TouchPanel_int);

    // Turn button indicators off
    IOWR(NIOS_LCD_COMPONENT_0_CONSOLE_BASE, 0, 0x0);

    int row, col, colour_counter = 0;

    for (row = 0; row < 15; row++) {
    		for (col = 0; col < 20; col++) {
    			color_block[row][col] = colour_counter % 8;
    			//last_color = colour_counter % 8;
    			colour_counter++;
    			printf("cc:   %i\n", colour_counter%8);//goes 0 to 7 as incremented
    		}


    		//printf("cc:   %i\n", colour_counter%8);
    	}

    draw_horizontal_bars(32);

 // cursur(16);

    while (1);        

    return 0;
}
