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
#define F_CPU 16000000 // CPU frequency in Hz required for UART_BAUD_SELECT
#endif

/* Includes ----------------------------------------------------------*/
// System library headers
#include <avr/interrupt.h> // Interrupts standard C library for AVR-GCC
#include <avr/io.h>        // AVR device-specific IO definitions
#include <stdio.h>
#include <stdlib.h> // C library. Needed for number conversions
#include <string.h>
// Project specific library headers
#include "gpio.h"           // Custom library for GPIO pin setup
#include "gui.h"            // GUI library for oled display
#include "pin_definition.h" // Pin definitions
#include "spi.h"
#include "timer.h" // Timer library for AVR-GCC
#include "uart.h"

#define DING_DUR 50

uint8_t prevButtonState[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
uint8_t currButtonState[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

/* Function definitions ----------------------------------------------*/
int main(void)
{
  // Init GUI on oled display
  gui_init();
  GPIO_setup_xylophone(); // Pin direction setup
  SPI_init();
  GPIO_mode_input_pullup(&DDRD, 2);
  uart_init(UART_BAUD_SELECT(9600, F_CPU));

  TIM1_OVF_4MS;
  TIM1_OVF_ENABLE;
  sei();

  // Main loop
  for (;;)
  {
  }

  // Will never reach this
  return 0;
}

/* Interrupt service routines ----------------------------------------*/
/**
 * @brief Construct a new ISR object
 * Overflow interupt rutine for button operating and recording of pressed notes.
 */
ISR(TIMER1_OVF_vect)
{
  static uint8_t dingTime[8] = {0, 0, 0, 0, 0, 0, 0, 0};
  static uint8_t regData = 0;

  GPIO_read_pins(&currButtonState);

  for (uint8_t i = 0; i < sizeof(dingTime); i++)
  {
    if (currButtonState[i] == 0 && prevButtonState[i] == 1)
    {
      dingTime[i] = DING_DUR;
    }
    if (dingTime[i] > 0)
    {
      regData |= (1 << i);
      dingTime[i]--;
    }
  }
  for (uint8_t i = 0; i < sizeof(currButtonState); i++)
  {
    prevButtonState[i] = currButtonState[i];
  }

  SPI_shift(regData);
  regData = 0;
}