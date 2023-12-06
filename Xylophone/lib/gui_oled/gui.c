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
#include <string.h>

/* Local variables ---------------------------------------------------*/
static uint8_t record_selected = 0;
char* const records_str_p[] PROGMEM = {"1 ", "2 ", "3 ", "4 "};

static uint8_t button_selected[] = {0, 1, 0};
char* const modes_str_p[] = {"PLAY", "STOP", "RECORD"};

struct GUISheetRow_t
{
    uint8_t row_register;
    
};

const char tones[] = {'C', 'D', 'E', 'F', 'G', 'A', 'H', 'C'};
static uint8_t sheet_row_regs[5] = {0, 0, 0, 0, 0};


/* Local function declarations ---------------------------------------*/

/**
 * @brief Inverts color within specific section of buffer
 *        Call oled_display() to see changes on display
 * 
 * @param y_pos Start pixel in y axes
 * @param row_n Row number = <0, 7>
 * @param px_length Number of pixel colums to invert
 * @return none
 */
static void gui_buffer_invert_section(uint8_t y_pos, uint8_t row_n, uint8_t px_length);

/* Function definitions ----------------------------------------------*/
void gui_init(void)
{
    twi_init();
    oled_init(OLED_DISP_ON);
    oled_clrscr();

    // State buttons
    gui_button_clear(DISPLAY);
    // Invert all elements in the button_selected array to toggle them
    for (uint8_t i = 0; i < sizeof(button_selected); i++) {
        button_selected[i] = !button_selected[i];
    }
    gui_botton_toggle(PLAY);
    gui_botton_toggle(STOP);
    gui_botton_toggle(RECORD);

    // Available tone resp. buttons on xylophone
    gui_record_clear(DISPLAY);
    gui_record_set(record_selected);
    
    // Draw music sheet
    gui_lines();

    oled_display();
}

void gui_button_clear(enum GUIDisplayUpdate change)
{
    oled_gotoxy(2, GUI_DISP_MODES_ROW);
    for(uint8_t i = 0; i < sizeof(modes_str_p) / sizeof(modes_str_p[0]); i++)
    {
        // Display default string
        oled_puts(modes_str_p[i]);
        oled_puts("  ");
    }
    // Copy buffer to display RAM
    if(change == DISPLAY) oled_display();
}

void gui_botton_toggle(enum GUIButton button)
{
    enum GUIButtonValue value_play, value_stop, value_record;
    value_play = button_selected[PLAY];
    value_stop = button_selected[STOP];
    value_record = button_selected[RECORD];
    if(button == PLAY) value_play = !button_selected[button];
    if(button == STOP) value_stop = !button_selected[button];
    if(button == RECORD) value_record = !button_selected[button];
    gui_botton_set(value_play, value_stop, value_record);
}

void gui_botton_set(enum GUIButtonValue value_play, enum GUIButtonValue value_stop, enum GUIButtonValue value_record)
{
    button_selected[PLAY] = value_play;
    button_selected[STOP] = value_stop;
    button_selected[RECORD] = value_record;
    // Crawing potantiali momorized content to display
    oled_display();
    // Clearing modes section, but not diplaying it yet
    // That way at least one selection of record is displayed
    gui_button_clear(MEMORIZE);

    // Select mode by inverting pixel at its position
    for(uint8_t i = 0; i < sizeof(button_selected); i++)
    {
        if(button_selected[i])
        {
            uint8_t string_length = strlen(modes_str_p[i]);
            switch(i)
            {
            case PLAY:
                gui_buffer_invert_section(2 * _GUI_FONT_WIDTH, GUI_DISP_MODES_ROW, string_length * _GUI_FONT_WIDTH + 1);
                break;
            case STOP:
                gui_buffer_invert_section(8 * _GUI_FONT_WIDTH, GUI_DISP_MODES_ROW, string_length * _GUI_FONT_WIDTH + 1);
                break;
            case RECORD:
                gui_buffer_invert_section(14 * _GUI_FONT_WIDTH, GUI_DISP_MODES_ROW, string_length * _GUI_FONT_WIDTH + 1);
                break;
            default:
                break;
            }
        }
    }
    // Copy buffer to display RAM
    oled_display();
}

void gui_record_clear(enum GUIDisplayUpdate change)
{
    oled_gotoxy(GUI_DISP_RECORDS_COL, GUI_DISP_RECORDS_ROW);
    for(uint8_t i = 0; i < sizeof(records_str_p) / sizeof(records_str_p[0]); i++)
    {
        // Display default string
        oled_puts(records_str_p[i]);
    }
    // Copy buffer to display RAM
    if(change == DISPLAY) oled_display();
}

void gui_record_set(uint8_t record_num)
{
    // Crawing potantiali momorized content to display
    oled_display();
    // Clearing records section, but not diplaying it yet
    // That way at least one selection of record is displayed
    gui_record_clear(MEMORIZE);
    // Select recerd by inverting pixel at its position
    gui_buffer_invert_section((GUI_DISP_RECORDS_COL + record_num * 2) * _GUI_FONT_WIDTH, GUI_DISP_RECORDS_ROW, _GUI_FONT_WIDTH + 1);
    // Copy buffer to display RAM
    oled_display();
    record_selected = record_num;
}

uint8_t gui_record_shift()
{
    // Overflow to first item if greater then max
    if(record_selected >= (sizeof(records_str_p) / sizeof(records_str_p[0])) - 1) record_selected = 0;
    else record_selected++;
    // Display next
    gui_record_set(record_selected);
    return record_selected;
}

static void gui_buffer_invert_section(uint8_t y_pos, uint8_t row_n, uint8_t px_length)
{
    // Accesing display buffer from oled.h 
    extern uint8_t displayBuffer[DISPLAY_HEIGHT/8][DISPLAY_WIDTH];
    // Inverting bytes of pixels within buffer one by one
    for (int j = y_pos; j < px_length + y_pos; j++) {
        displayBuffer[row_n][j] = ~displayBuffer[row_n][j];
    }
}

void gui_lines()
{
    // Draw lines for better visuals of gui sections
    oled_drawLine(0, GUI_DISP_SHEET_POS, DISPLAY_WIDTH, GUI_DISP_SHEET_POS, BLACK);
    oled_drawLine(0, GUI_DISP_SHEET_POS + 1, DISPLAY_WIDTH, GUI_DISP_SHEET_POS + 1, WHITE);
    oled_drawLine(0, GUI_DISP_SHEET_POS + 2, DISPLAY_WIDTH, GUI_DISP_SHEET_POS + 2, WHITE);
}

void gui_sheet_set(uint8_t tone_register)
{
    gui_sheet_update();
    sheet_row_regs[sizeof(sheet_row_regs) - 1] = tone_register;
    for(uint8_t i = 0; i < 8; i++)
    {
        oled_gotoxy(3 + i * 2, GUI_DISP_SHEET_POS / _GUI_ROW_HEIGHT + (sizeof(sheet_row_regs) - 1));
        if((tone_register >> i) & 1)
        {
            oled_putc(tones[i]);
        }
        else
        {
            oled_putc(' ');
        }
    }
    // Draw lines for better visuals, hiding first charactes
    gui_lines();
    oled_display();
}

void gui_sheet_update()
{
    // Shift all items in sheet rows up
    for(uint8_t j = 1; j < sizeof(sheet_row_regs); j++)
    {
        // Starting with first item
        sheet_row_regs[j - 1] = sheet_row_regs[j];

        // Writing row acording to bites in sheet register
        for(uint8_t i = 0; i < 8; i++)
        {
            oled_gotoxy(3 + i * 2, GUI_DISP_SHEET_POS / _GUI_ROW_HEIGHT + j - 1);
            // Write
            if((sheet_row_regs[j - 1] >> i) & 1)
            {
                oled_putc(tones[i]);
            }
            // Erase
            else
            {
                oled_putc(' ');
            }
        }
    }
    // Destroying first item
    gui_lines();
    // Destroying last item
    sheet_row_regs[sizeof(sheet_row_regs) - 1] = 0;
}