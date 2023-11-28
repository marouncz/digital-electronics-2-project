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
#include "spi.h"
#include "gpio.h"           // Custom library for GPIO pin setup
#include "pin_definition.h" // Pin definitions
#include "uart.h"

/* Function definitions ----------------------------------------------*/
int main(void)
{
    // Init GUI on oled display
    gui_init();
    GPIO_setup_xylophone(); // Pin direction setup
    SPI_init();

    uart_init(UART_BAUD_SELECT(9600, F_CPU));

    TIM1_OVF_1SEC;
    TIM1_OVF_ENABLE;
    sei();

    // Main loop
    for(;;)
    {
        
    }

    // Will never reach this
    return 0;
}

/* Interrupt service routines ----------------------------------------*/
ISR(TIMER1_OVF_vect)
{
    static uint8_t tone = 0;

    static uint8_t data = 0;
    data = 1<<tone;
    
    SPI_shift(&data);   

    tone++;
    if(tone > 7) tone = 0;
    uint8_t str[4];
    itoa(data, &str, 10);
    uart_puts(&str);
}