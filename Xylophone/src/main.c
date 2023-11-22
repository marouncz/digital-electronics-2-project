// Main page of Doxygen manual
/**
 * @mainpage Electronically controlled xylophone
 * 
 * Firmware for controling xylophone, capable of producing different tones
 * and melodies. Consisting of oled display as GUI, 
 * shift register library for pin extension and user buttons handling.
 * 
 * Student project ran within a bachelor course Digital
 * Electronics 2 at Brno University of Technology, Czechia.
 * 
 * ATmega328P (Arduino Uno), 16 MHz, PlatformIO
 * 
 * @author Marek Coufal, Miloslav Kužela, Martin Ťavoda, Roman Vaněk (using dependencies created by Peter Fleury, Michael Köhler, Tomas Fryza) 
 * @copyright (c) 2023 Marek Coufal, Miloslav Kužela, Martin Ťavoda, Roman Vaněk, This work is licensed under 
 *                the terms of the MIT license
 */


/* Defines -----------------------------------------------------------*/
#ifndef F_CPU
# define F_CPU 16000000  // CPU frequency in Hz required for UART_BAUD_SELECT
#endif

/* Includes ----------------------------------------------------------*/
// System library headers
#include <avr/io.h>         // AVR device-specific IO definitions
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC
#include <stdlib.h>         // C library. Needed for number conversions
// Project specific library headers
#include "timer.h"          // Timer library for AVR-GCC
#include "gui.h"            // GUI library for oled display

/* Function definitions ----------------------------------------------*/
int main(void)
{

    // Main loop
    for(;;)
    {
        
    }

    // Will never reach this
    return 0;
}

/* Interrupt service routines ----------------------------------------*/
