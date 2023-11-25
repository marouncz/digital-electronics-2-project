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
 * @defgroup gui GPIO Library <gui.h>
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
#define GUI_DISP_STATES_POS 0
#define GUI_DISP_LINE1_POS 11
#define GUI_DISP_LINE2_POS 25

/* Function prototypes -----------------------------------------------*/
/**
 * @brief Initalize graphical user interface on oled
 * @return none
 * @par Implementation notes:
 *           - Init I2C and OLED
 */
void gui_init(void);

/**
 * @brief Resets line for displaying presed tone buttons
 * @return none
 */
void gui_clr_buttons(void);

/**
 * @brief Display pressed button on display
 * 
 * @param button_num button number = <0, 7>
 * @return none
 */
void gui_set_button(uint8_t button_num);