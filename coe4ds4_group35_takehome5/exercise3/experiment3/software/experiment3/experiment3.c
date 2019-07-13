// Copyright by Adam Kinsman, Henry Ko and Nicola Nicolici
// Developed for the Embedded Systems course (COE4DS4)
// Department of Electrical and Computer Engineering
// McMaster University
// Ontario, Canada

// This is the embedded software for the
// LCD / Camera design

#include "define.h"



int height;
int width;

  const unsigned char bmp_header[] = {
    		0x42, 0x4d,
    		0x36, 0x10, 0x0e, 0x00,
    		0x00, 0x00,
    		0x00, 0x00,
    		0x36, 0x00, 0x00, 0x00,
    		0x28, 0x00, 0x00, 0x00,
    		0x40, 0x01, 0x00, 0x00,  //width changed to 320
    		0x10, 0xff, 0xff, 0xff,  //height changed to -240
    		0x01, 0x00,
    		0x18, 0x00,
    		0x00, 0x00, 0x00, 0x00,
    		0x00, 0x10, 0x0e, 0x00,
    		0x13, 0x0b, 0x00, 0x00,
    		0x13, 0x0b, 0x00, 0x00,
    		0x00, 0x00, 0x00, 0x00,
    		0x00, 0x10, 0x0e, 0x00,
    };

//since the read_data function returns 2 BYTES, the top byte shouldnt containing anything
//returning -1 if nothing is read which is FFFF
bool read_SD_int (short int file_handle, int *sd_info) {

    *sd_info = 0;
    unsigned short int read_data;

	//top byte error check
    if (((read_data = sd_card_read(file_handle)) >> 8) != 0)
    return false; //out of the 2 bytes sd_card_read returns, if top byte should be 0!!

    *sd_info = read_data |  *sd_info;

    if (((read_data = sd_card_read(file_handle)) >> 8) != 0)
    return false;

    *sd_info |= read_data << 8;

    if (((read_data = sd_card_read(file_handle)) >> 8) != 0)
    return false;
    *sd_info |= read_data << 16;

    if (((read_data = sd_card_read(file_handle)) >> 8) != 0)
    return false;
    *sd_info |= read_data << 24;

    return true;
}


bool bmp_function (short int file_handle, int *height, int *width) {

	int i;
    int header_num;
    int detect;
    bool bool_flag;

    for (i = 2; i < 10; i++) {
            if ((sd_card_read(file_handle) >> 8) != 0) return false;
        }

    if (sd_card_read(file_handle) != 'B') bool_flag = false;
    if (sd_card_read(file_handle) != 'M') bool_flag = false;


    // get offset to image data
    if (!read_SD_int(file_handle, &header_num)) return false;

    for (i = 14; i < 18; i++) // strip next 4 bytes
        if ((sd_card_read(file_handle) >> 8) != 0) return false;

    if (!read_SD_int(file_handle, width)) return false;
    if (!read_SD_int(file_handle, height)) return false;

	//get rid of the last bytes
    for (i = 26; i < header_num; i++)
        if ((sd_card_read(file_handle) >> 8) != 0) return false;

    return true;
}

int main()
{
    // alt_up_sd_card_dev *sd_card_dev = NULL;
    PB_irq_data_struct PB_irq_data;
    short int file_handle;
    int i, j;
    int connected = 0;
    int status;
    unsigned short int data;
    char filename[13];
    int file_number = 0;
//    int height;
 //   int width;

    alt_u8 full_R[LINE_LEN], full_G[LINE_LEN], full_B[LINE_LEN];

    PB_irq_data.load_img_flag = 0;
    PB_irq_data.save_img_flag = 0;
    
    // sd_card_dev = alt_up_sd_card_open_dev("/dev/SD_card_0");
    sd_card_open_dev();
    
    alt_irq_register(NIOS_LCD_CAMERA_COMPONENT_0_TOUCHPANEL_IRQ, NULL, (void *)LTC_TouchPanel_int);
    init_button_irq(&PB_irq_data);
    
    printf("Experiment 3!\n");

    // initialize the touch panel
    IOWR(NIOS_LCD_CAMERA_COMPONENT_0_TOUCHPANEL_BASE, 2, 0x0);
    IOWR(NIOS_LCD_CAMERA_COMPONENT_0_TOUCHPANEL_BASE, 1, 0x400000);

    // initialize the camera
    IOWR(NIOS_LCD_CAMERA_COMPONENT_0_CAMERA_BASE, 0, 0x0400);
    IOWR(NIOS_LCD_CAMERA_COMPONENT_0_CAMERA_BASE, 1, 0x2);
    while ((IORD(NIOS_LCD_CAMERA_COMPONENT_0_CAMERA_BASE, 1) & 0x1) == 0);
    IOWR(NIOS_LCD_CAMERA_COMPONENT_0_CAMERA_BASE, 1, 0x4);

    // initialize the buttons
    IOWR(NIOS_LCD_CAMERA_COMPONENT_0_CONSOLE_BASE, 1, 0x0);
    
    // initialize the filter pipe
    IOWR(NIOS_LCD_CAMERA_COMPONENT_0_IMAGELINE_BASE, 4, 0);

        while(1) { 
            if ((connected == 0) && (sd_card_is_Present())) {
                printf("Card connected.\n"); 
                connected = 1; 
                if (sd_card_is_FAT16()) {
                    printf("Valid file system detected.\n"); 
                } else {
                    printf("Unknown file system.\n");
                }
                status = sd_card_find_first(".", PB_irq_data.filename);
                
                switch (status) {
                    case 0: printf("Success\n"); break;
                    case 1: printf("Invalid directory\n"); break;
                    case 2: printf("No card or incorrect FS\n"); break;
                }
            } else if ((connected == 1) && (sd_card_is_Present() == false)) {
                printf("Card disconnected.\n"); connected = 0;
            }
            
            if (PB_irq_data.load_img_flag == 1) {
                // stop the camera
                IOWR(NIOS_LCD_CAMERA_COMPONENT_0_CAMERA_BASE, 1, 0x8);
                
                file_handle = sd_card_fopen(PB_irq_data.filename, false);
                
                if (status < 0) printf("Error opening file \"%s\"\n", PB_irq_data.filename);
                else {
                    printf("Loading image data from file \"%s\"\n", PB_irq_data.filename);

		    // parse BMP header
		    if (!bmp_function(file_handle, &height, &width))
			    printf("BMP formatting is Incorrect, try again\n");
		    else if (((height != 240) && (height != -240)) || (width != 320))
			    printf("Size is Incorrect\n");
		    else {
                        if (height > 0) {
                        	printf("This displaying image is inverted picture\n");}
                        	 else if (height < 0){
                        		 printf("This displaying image is inverted picture");
                      }

                        LTC_Switch_Nios_Mode(1);

                 for (i = 0; i < LINE_LEN; i++)
                       full_R[i] = full_G[i] = full_B[i] = 0;
                    for (i = 0; i < NUM_LINES/4; i++)
                       LTC_Write_Image_Line(full_R,full_G,full_B);


                        for (i = 0; i < NUM_LINES/2; i++) {
                            IOWR(LED_RED_O_BASE, 0, i);
                            for (j = 0; j < LINE_LEN/2; j++) {
                            	//IOWR(LED_RED_O_BASE, 0, i*640+j);
                                data = sd_card_read(file_handle);
                                /*data = sd_card_read(file_handle);
								B_vals[j] = data & 0xFF;
								data = sd_card_read(file_handle);
								G_vals[j] = data & 0xFF;
								data = sd_card_read(file_handle);
								R_vals[j] = data & 0xFF;*/
                                if ((data >> 8) != 0) printf("B eof reached: %d, %d\n", i, j);
                                if (height < 0)
                                	full_B[j + LINE_LEN/4] = data & 0xff;
                                else B_vals[i][j] = data & 0xFF;

                                data = sd_card_read(file_handle);
                                if ((data >> 8) != 0) printf("G eof reached: %d, %d\n", i, j);
                                if (height < 0)
                                	full_G[j + LINE_LEN/4] = data & 0xff;
                                else G_vals[i][j] = data & 0xFF;

                                data = sd_card_read(file_handle);
                                if ((data >> 8) != 0) printf("R eof reached: %d, %d\n", i, j);
                                if (height < 0)
                                	full_R[j + LINE_LEN/4] = data & 0xff;
                                else R_vals[i][j] = data & 0xFF;
                            }
                            if (height < 0)
                            	{
                            	LTC_Write_Image_Line(full_R, full_G, full_B);
                            	}
                        }


                        if (height > 0)
                            for (i = NUM_LINES/2 - 1; i >= 0; i--) {
                            	//inverted image
                               for (j = 0; j < LINE_LEN/2; j++) {
                                  full_R[j + LINE_LEN/4] = R_vals[i][j];
                                  full_G[j + LINE_LEN/4] = G_vals[i][j];
                                  full_B[j + LINE_LEN/4] = B_vals[i][j];
                               }
                               LTC_Write_Image_Line(full_R, full_G, full_B);
    			            }


                        for (i = 0; i < LINE_LEN; i++)
                            full_R[i] = full_G[i] = full_B[i] = 0;
                          for (i = 0; i < NUM_LINES/4; i++)
                            LTC_Write_Image_Line(full_R,full_G,full_B);

                        LTC_Switch_HW_Mode();
		    }

                    sd_card_fclose(file_handle);

                }
                
                PB_irq_data.load_img_flag = 0;
            }
            
            if (PB_irq_data.save_img_flag == 1) {
                // stop the camera
                IOWR(NIOS_LCD_CAMERA_COMPONENT_0_CAMERA_BASE, 1, 0x8);
                
                sprintf(filename, "file%d.bmp", file_number++);
                
                while ((file_handle = sd_card_fopen(filename, 1)) < 0) {
                    sprintf(filename, "file%d.bmp", file_number++);
                }
                
                printf("Saving image to file (%s)...\n", filename);
                LTC_Switch_Nios_Mode(0);

				for (i = 0, status = true; i < 54; i++) {
					status = status && sd_card_write(file_handle, bmp_header[i]);
				if (!status) printf("Write fail in header!\n");
				}

				/*
                status = sd_card_write(file_handle, 'P');
                status = sd_card_write(file_handle, '6');
                status = sd_card_write(file_handle, '\n');
                status = sd_card_write(file_handle, '6');
                status = sd_card_write(file_handle, '4');
                status = sd_card_write(file_handle, '0');
                status = sd_card_write(file_handle, ' ');
                status = sd_card_write(file_handle, '4');
                status = sd_card_write(file_handle, '8');
                status = sd_card_write(file_handle, '0');
                status = sd_card_write(file_handle, '\n');
                status = sd_card_write(file_handle, '2');
                status = sd_card_write(file_handle, '5');
                status = sd_card_write(file_handle, '5');
                status = sd_card_write(file_handle, '\n');
               */

                for (i = 0; i < NUM_LINES / 2; i++) {
                    IOWR(LED_RED_O_BASE, 0, i);
                    LTC_Read_Image_Line(full_R, full_G, full_B);
                    for (j = 0; j < LINE_LEN; j+=2) {  // now so odd is removed, BGR order
                        status = sd_card_write(file_handle, full_B[j]);
                        if (!status) printf("Write fail: B %d %d\n", i, j);
                        status = sd_card_write(file_handle, full_G[j]);
                        if (!status) printf("Write fail: G %d %d\n", i, j);
                        status = sd_card_write(file_handle, full_R[j]);
                        if (!status) printf("Write fail: R %d %d\n", i, j);
                    }
                    LTC_Read_Image_Line(full_R, full_G, full_B);
                }

                LTC_Switch_HW_Mode();

                sd_card_fclose(file_handle);

                PB_irq_data.save_img_flag = 0;
            }
        }
    
    return 0;
}


