// Copyright by Adam Kinsman, Henry Ko and Nicola Nicolici
// Developed for the Embedded Systems course (COE4DS4)
// Department of Electrical and Computer Engineering
// McMaster University
// Ontario, Canada

// This is the embedded software for the
// LCD / Camera design

#include "define.h"

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

                    // take out header from PPM
                    for (i = 0; i < 15; i++) {
                        data = sd_card_read(file_handle);
                        if ((data >> 8) != 0) printf("eof reached in header\n");                        
                    }
                    LTC_Switch_Nios_Mode(1);
                    
                    for (i = 0; i < NUM_LINES; i++) {
                        for (j = 0; j < LINE_LEN; j++) {
                            IOWR(LED_RED_O_BASE, 0, i*640+j);
                            data = sd_card_read(file_handle);
                            if ((data >> 8) != 0) printf("R eof reached: %d, %d\n", i, j);
                            R_vals[j] = data & 0xFF;

                            data = sd_card_read(file_handle);
                            if ((data >> 8) != 0) printf("G eof reached: %d, %d\n", i, j);
                            G_vals[j] = data & 0xFF;

                            data = sd_card_read(file_handle);
                            if ((data >> 8) != 0) printf("B eof reached: %d, %d\n", i, j);
                            B_vals[j] = data & 0xFF;
                        }                        
                        LTC_Write_Image_Line(R_vals, G_vals, B_vals);
                    }                                       
                    LTC_Switch_HW_Mode();
                    
                    sd_card_fclose(file_handle);
                }
                
                PB_irq_data.load_img_flag = 0;
            }
            
            if (PB_irq_data.save_img_flag == 1) {
                // stop the camera
                IOWR(NIOS_LCD_CAMERA_COMPONENT_0_CAMERA_BASE, 1, 0x8);
                
                sprintf(filename, "file%d.ppm", file_number++);
                
                while ((file_handle = sd_card_fopen(filename, 1)) < 0) {
                    sprintf(filename, "file%d.ppm", file_number++);                 
                }
                
                printf("Saving image to file (%s)...\n", filename);
                LTC_Switch_Nios_Mode(0);

                // PPM header
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
                for (i = 0; i < NUM_LINES; i++) {
                    LTC_Read_Image_Line(R_vals, G_vals, B_vals);
                    for (j = 0; j < LINE_LEN; j++) {
                        IOWR(LED_RED_O_BASE, 0, i*640+j);
                        status = sd_card_write(file_handle, R_vals[j]);
                        if (!status) printf("Write fail: R %d %d\n", i, j);
                        status = sd_card_write(file_handle, G_vals[j]);
                        if (!status) printf("Write fail: G %d %d\n", i, j);
                        status = sd_card_write(file_handle, B_vals[j]);
                        if (!status) printf("Write fail: B %d %d\n", i, j);
                    }
                }                                       
                LTC_Switch_HW_Mode();
                
                sd_card_fclose(file_handle);

                PB_irq_data.save_img_flag = 0;
            }
        }
    
    return 0;
}
