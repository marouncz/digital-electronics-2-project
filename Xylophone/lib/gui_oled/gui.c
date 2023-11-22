/***********************************************************************
 * 
 * GUI library for Xylophone oled display.
 * 
 * ATmega328P (Arduino Uno), 16 MHz, PlatformIO
 *
 * Copyright (c) 2023 Roman Vaněk
 * Dept. of Radio Electronics, Brno University of Technology, Czechia
 * This work is licensed under the terms of the MIT license.
 *
 **********************************************************************/


/* Includes ----------------------------------------------------------*/
#include "gui.h"

/* Function definitions ----------------------------------------------*/
void gui_init(void)
{
    twi_init();
    oled_init(OLED_DISP_ON);
    oled_clrscr();

    // Default look init
    // User buttons
    oled_gotoxy(3, 0);
    oled_puts("PLAY");
    oled_gotoxy(13, 0);
    oled_puts("RECORD");
    
    oled_drawLine(0, 11, DISPLAY_WIDTH, 11, WHITE);

    // Available tone on xylophone
    oled_gotoxy(3, 2);
    oled_puts("1 ");
    oled_puts("2 ");
    oled_puts("3 ");
    oled_puts("4 ");
    oled_puts("5 ");
    oled_puts("6 ");
    oled_puts("7 ");
    oled_puts("8 ");
    
    oled_drawLine(0, 3 + 2*11, DISPLAY_WIDTH, 3 + 2*11, WHITE);

    // Copy buffer to display RAM
    oled_display();
}