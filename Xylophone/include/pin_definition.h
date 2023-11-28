/**
 * @file pin_definition.h
 * @code #include <timer.h> @endcode
 * @author Miloslav Kužela (240648@vut.cz)
 * @brief Pin definition header file
 * Defining all pins used for the xylophone
 * @version 0.1
 * @date 2023-11-22
 * 
 * @copyright Copyright (c) 2023 Miloslav Kužela
 * 
 */
#ifndef PIN_DEF_H
# define PIN_DEF_H

//For AVR pin aliases
#include <avr/io.h>

/**
 * @brief Definition of keyboard buttons according to note
 */
#define C1  PB1
#define D   PB0
#define E   PD7
#define F   PD6
#define G   PD5
#define A   PD4
#define H   PD3
#define C2  PD2

/**
 * @brief Definition of interface buttons 
 */
#define left_btn    PC3
#define right_btn   PC2
#define enter_btn   PC1
#define switch_btn  PC0

#endif