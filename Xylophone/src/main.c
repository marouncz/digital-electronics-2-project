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
#include <stdio.h>
#include <string.h>
// Project specific library headers
#include "timer.h"          // Timer library for AVR-GCC
#include "gui.h"            // GUI library for oled display
#include "spi.h"
#include "gpio.h"           // Custom library for GPIO pin setup
#include "pin_definition.h" // Pin definitions
#include "uart.h"


uint8_t prevButtonState[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
uint8_t currButtonState[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
uint8_t *pPrevButtonState;
uint8_t *pCurrButtonState;

/* Function definitions ----------------------------------------------*/
int main(void)
{
    // Init GUI on oled display
    gui_init();
    GPIO_setup_xylophone(); // Pin direction setup
    SPI_init();
    GPIO_mode_input_pullup(&DDRD, 2);
    uart_init(UART_BAUD_SELECT(9600, F_CPU));


    TIM1_OVF_33MS;
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
    // static uint8_t tone = 0;

    // static uint8_t data = 0;
    // data = 1<<tone;
    
    // GPIO_write_low(&PORTB, 2);
    // transmitSPI(&data);   
    // GPIO_write_high(&PORTB, 2); 

    // tone++;
    // if(tone > 7) tone = 0;
    // uint8_t str[4];
    // itoa(data, &str, 10);
    // uart_puts(&str);

    //uart_puts(".\r\n");   
    GPIO_read_pins(&currButtonState);

    uart_putc(currButtonState[0]+48);
    // if(memcmp(currButtonState, prevButtonState, sizeof(prevButtonState)) != 0)
    // {
    //     uart_puts("butdiff\r\n");
    // }



    // memcpy(currButtonState, prevButtonState, sizeof(prevButtonState));



    


}