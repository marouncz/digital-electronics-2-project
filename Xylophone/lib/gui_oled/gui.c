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

/* Local variables ---------------------------------------------------*/
const char* _button_Bstrs[] = {
    "1", "2", "3", "4", "5", "6", "7", "8"
};
const char* _button_strs[] = {
    "1", "2", "3", "4", "5", "6", "7", "8"
};

/* Function definitions ----------------------------------------------*/
void gui_init(void)
{
    twi_init();
    oled_init(OLED_DISP_ON);
    oled_clrscr();

    // Default look init
    // State buttons
    oled_gotoxy(3, GUI_DISP_STATES_ROW);
    oled_puts("PLAY");
    oled_gotoxy(13, GUI_DISP_STATES_ROW);
    oled_puts("RECORD");
    
    oled_drawLine(0, GUI_DISP_LINE1_POS, DISPLAY_WIDTH, GUI_DISP_LINE1_POS, WHITE);

    // Available tone resp. buttons on xylophone
    gui_clr_buttons();
    
    oled_drawLine(0, GUI_DISP_LINE2_POS, DISPLAY_WIDTH, GUI_DISP_LINE2_POS, WHITE);

    // Draw music sheet
    gui_clr_sheet();


    // Copy buffer to display RAM
    oled_display();
}

void gui_clr_records(void)
{
    oled_gotoxy(3, GUI_DISP_RECORDS_ROW);
    oled_puts("1 2 3 4 5 6 7 8");
}

void gui_clr_sheet(void)
{
    oled_gotoxy(0, GUI_DISP_SHEET_ROW);
    // First line 1/5
    oled_drawLine(0, GUI_DISP_SHEET_ROW, DISPLAY_WIDTH, GUI_DISP_SHEET_ROW, WHITE);
    // Second line 2/5
    oled_drawLine(0, GUI_DISP_SHEET_ROW, DISPLAY_WIDTH, GUI_DISP_SHEET_ROW, WHITE);
    // Third line 3/5
    oled_drawLine(0, GUI_DISP_SHEET_ROW, DISPLAY_WIDTH, GUI_DISP_SHEET_ROW, WHITE);
    // Fourth line 4/5
    oled_drawLine(0, GUI_DISP_SHEET_ROW, DISPLAY_WIDTH, GUI_DISP_SHEET_ROW, WHITE);
    // Fifth line 5/5
    oled_drawLine(0, GUI_DISP_SHEET_ROW, DISPLAY_WIDTH, GUI_DISP_SHEET_ROW, WHITE);
}

void gui_set_record(uint8_t button_num)
{
    oled_gotoxy(3 + button_num * 2, 2);
    oled_puts(_button_Bstrs[button_num]);
    oled_putc(" ");
    oled_display();
}