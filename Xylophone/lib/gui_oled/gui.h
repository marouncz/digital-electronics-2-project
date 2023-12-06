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
#if defined(SSD1309)
    /**
     * @brief Value added to certain GUI positions when SSD1309 is defined.
     *        This is necessary because SSD1309 lists rows from 1 instead of 0.
     */
    #define GUI_ADD_ONE 1
#else
    /**
     * @brief Value added to certain GUI positions when SSD1309 is not defined.
     */
    #define GUI_ADD_ONE 0
#endif

#define _GUI_FONT_WIDTH 6    /**< Font width in pixels */
#define _GUI_ROW_HEIGHT 8    /**< Row height in pixels */

#define GUI_DISP_MODES_ROW     (uint8_t)(0 + GUI_ADD_ONE)               /**< Row number where PLAY, STOP, and RECORD buttons will be displayed */
#define GUI_DISP_RECORDS_ROW    (uint8_t)(1 + GUI_ADD_ONE)              /**< Row number where available records of xylophone will be displayed */                     
#define GUI_DISP_SHEET_POS      (uint8_t)((2 + GUI_ADD_ONE) * _GUI_ROW_HEIGHT)    /**< Start position [px] axis where the musical sheet will be displayed */

// Change to shift records display positon 
#define GUI_DISP_RECORDS_COL (uint8_t)7       /**< Start column number where available records of xylophone will be displayed */

/** Types ------------------------------------------------------------*/

/**
 * @brief Either MEMORIZE or DISPLAY
 *        Used as parameter of function for immediate changes option
 */
enum GUIDisplayUpdate
{
    DISPLAY = 1,
    MEMORIZE = 0
};

/**
 * @brief Available buttons on GUI
 *        Used as parameter of function gui_record_toggle()
 */
enum GUIButton
{
    PLAY,
    STOP,
    RECORD
};

/**
 * @brief Button toggle values
 *        Used as parameter of function gui_botton_set()
 */
enum GUIButtonValue
{
    RESET,
    SET
};


/* Function prototypes -----------------------------------------------*/
/**
 * @brief Initalize graphical user interface on oled
 * @return none
 * @par Implementation notes:
 *           - Init I2C and OLED
 */
void gui_init(void);

/**
 * @brief Clears row for displaying selected buttons
 * @return none
 * @param change either MEMORIZE or DISPLAY display changes immediately
 */
void gui_button_clear(enum GUIDisplayUpdate change);

/**
 * @brief Show selected record on display
 * 
 * @param button either PLAY, SELECT or RECORD, refer to GUIButtons enum
 * @return none
 */
void gui_botton_toggle(enum GUIButton button);

/**
 * @brief Show / clear selected buttons on display
 * 
 * @param value either SET or RESET, refer to GUIButtonValue enum
 * @return none
 */
void gui_botton_set(enum GUIButtonValue value_play, enum GUIButtonValue value_stop, enum GUIButtonValue value_record);

/**
 * @brief Clears row for displaying available record sections
 * @return none
 * @param update either MEMORIZE or DISPLAY display changes immediately
 */
void gui_record_clear(enum GUIDisplayUpdate change);

/**
 * @brief Display selected record on display
 * 
 * @param record_num record number = <0, 3>
 * @return none
 */
void gui_record_set(uint8_t record_num);

/**
 * @brief Selects next record 
 * @return selected record number = <0, 3>
 */
uint8_t gui_record_shift(void);

/**
 * @brief Clears all lines of musical sheet
 * @return none
 */
void gui_sheet_clear(void);

/**
 * @brief Draw tones to musical sheet
 * @param tone_register each bit represents tone
 * @return none
 */
void gui_sheet_set(uint8_t tone_register);

/**
 * @brief Shifts all conten on sheet upwards
 * @return none
 */
void gui_sheet_update();
