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
    oled_charMode(DOUBLESIZE);
    oled_gotoxy(0, 2);
    oled_puts("PLAY");
    oled_gotoxy(0, 10);
    oled_puts("RECORD");
}