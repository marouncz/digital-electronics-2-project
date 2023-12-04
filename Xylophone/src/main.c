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
#include "songs.h"

#define DING_DUR 10
#define MEM_LEN 40

uint8_t prevButtonState[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
uint8_t currButtonState[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
volatile uint16_t timeStamp = 0;
volatile uint8_t recFlag = 0;
volatile uint16_t memory_timeStamp[MEM_LEN] = {0};
volatile uint8_t memory_note[MEM_LEN] = {0};
volatile uint8_t memoryCounter = 0;
volatile uint8_t playbackFlag = 0;
volatile uint8_t mem_debug = 0;
volatile uint8_t trackNumber = 1;

/* Function definitions ----------------------------------------------*/
int main(void)
{
  // Init GUI on oled display
  gui_init();
  GPIO_setup_xylophone(); // Pin direction setup
  SPI_init();
  GPIO_mode_input_pullup(&DDRD, 2);
  uart_init(UART_BAUD_SELECT(115200, F_CPU));

  TIM1_OVF_4MS;
  TIM1_OVF_ENABLE;
  sei();

  // Main loop
  while (1)
  {
    if (mem_debug)
    {
      uart_puts("Memory content\n");
      for (uint8_t i = 0; i < MEM_LEN; i++)
      {
        uart_putc(memory_note[i] + 48);
        uart_puts("   ");
        char str[8];
        uart_puts(itoa(memory_timeStamp[i], str, 10));
        uart_puts("\n");
      }
      mem_debug = 0;
    }
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
      if (recFlag)
      {
        memory_note[memoryCounter] = i;
        memory_timeStamp[memoryCounter] = timeStamp;
        memoryCounter++;
        uart_putc(memoryCounter + 48);
      }

    }
    if (dingTime[i] > 0)
    {
      regData |= (1 << i);
      dingTime[i]--;
    }
  }

  if(playbackFlag)
  {
    if(memory_timeStamp[memoryCounter] == timeStamp)
    {
      dingTime[memory_note[memoryCounter]] = DING_DUR; 
      memoryCounter++;
    }
    if(memory_timeStamp[memoryCounter] == 0)
    {
      playbackFlag = 0;
    }
  }

  // TODO: find space in code for wrinting to display
  uint8_t changed = 0;
  for (uint8_t i = 0; i < sizeof(dingTime); i++)
  {
    if (currButtonState[i] == 0 && prevButtonState[i] == 1)
    {
      changed = 1;
    }
  }
  if(changed)
  {
    gui_sheet_set(regData);
  }
  else
  {
    gui_sheet_update();
  }
  

  SPI_shift(regData);
  regData = 0;

  if (currButtonState[11] == 0 && prevButtonState[11] == 1)
  { // Shift record
    uart_puts("Select next record\n");
    gui_record_shift();
  }
  if (currButtonState[10] == 0 && prevButtonState[10] == 1)
  { // Record
    timeStamp = 0;
    recFlag = 1;
    memoryCounter = 0;
    uart_puts("Recording started\n");
    gui_botton_toggle(RECORD);
  }
  if (currButtonState[9] == 0 && prevButtonState[9] == 1)
  { // Stop
    uart_puts("Recording stoped\n");
    gui_botton_toggle(RECORD);
    recFlag = 0;
    mem_debug = 1;
    memory_timeStamp[memoryCounter] = 0;
  }
  if (currButtonState[8] == 0 && prevButtonState[8] == 1)
  { // Play
    uart_puts("Playback started\n");
    gui_botton_toggle(PLAY);
    playbackFlag = 1;
    timeStamp = 0;
    memoryCounter = 0;
  }

  for (uint8_t i = 0; i < sizeof(currButtonState); i++)
  {
    prevButtonState[i] = currButtonState[i];
  }

  timeStamp++;
}