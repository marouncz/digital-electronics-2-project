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

/**
 * @file 
 * @defgroup vanek_gui GUI Library <gui.h>
 * @code #include <gui.h> @endcode
 *
 * @brief Graphical user interface library for oled display.
 *
 * The library contains functions for contoling gui for xylophone.
 *
 * @note Depended on twi.h - I2C/TWI library for AVR-GCC by Tomas Fryza
 *       and oled.h - Michael Köhler's OLED librar.
 * @author Roman Vaněk, Brno University of Technology, Czechia
 * 
 * @copyright (c) 2023 Roman Vaněk, This work is licensed under 
 *                the terms of the MIT license
 * @{
 */

/* Includes ----------------------------------------------------------*/
#include "twi.h"            // I2C/TWI library for AVR-GCC
#include "oled.h"           // Michael Köhler's OLED library

/* Defines -----------------------------------------------------------*/
#define GUI_DISP_STATES_ROW 0 // position of PLAY, STOP and RECORD buttons
#define GUI_DISP_RECORDS_ROW 2 // position of available records of xylophone
#define GUI_DISP_LINE1_POS 24 // position of line
#define GUI_DISP_LINE2_POS 25 // position of line
#define GUI_DISP_SHEET_POS 5 // start position of musical sheet

/* Function prototypes -----------------------------------------------*/
/**
 * @brief Initalize graphical user interface on oled
 * @return none
 * @par Implementation notes:
 *           - Init I2C and OLED
 */
void gui_init(void);

/**
 * @brief Clears row for displaying available record sections
 * @return none
 */
void gui_records_clr(void);

/**
 * @brief Clears all lines of musical sheet
 * @return none
 */
void gui_sheet_clr(void);

/**
 * @brief Display selected record on display
 * 
 * @param button_num button number = <0, 7>
 * @return none
 */
void gui_records_set(uint8_t button_num);

/**
 * @brief Selects next record 
 * 
 * @param button_num button number = <0, 7>
 * @return none
 */
void gui_records_shift(uint8_t button_num);