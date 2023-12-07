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
#define MEM_LEN 70

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
volatile uint8_t playbackNum;

volatile uint8_t dingTime[8] = {0};
volatile uint8_t regData_d = 0;

/* Function definitions ----------------------------------------------*/
int main(void)
{
  GPIO_setup_xylophone(); // Pin direction setup
  SPI_init();
  GPIO_mode_input_pullup(&DDRD, 2);
  uart_init(UART_BAUD_SELECT(115200, F_CPU));

  // Init GUI on oled display
  gui_init();

  TIM1_OVF_4MS;
  TIM1_OVF_ENABLE;
  sei();

  // Main loop
  while (1)
  {
    // UI
    if (regData_d > 0)
    {
      gui_sheet_set(regData_d);
      regData_d = 0;
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
  static uint8_t regData = 0;
  regData = 0;

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
  regData_d = regData;

  if (playbackFlag)
  {
    switch (playbackNum)
    {
    case 0:
    //Playback of user rewriteable song stored in RAM
      if (memory_timeStamp[memoryCounter] == timeStamp)
      {
        dingTime[memory_note[memoryCounter]] = DING_DUR;
        memoryCounter++;
      }
      if (memory_timeStamp[memoryCounter] == 0)
      {
        playbackFlag = 0;
        gui_botton_set(RESET, SET, RESET);
      }
      break;

    case 1:
    //Playback of first song stored in FLASH
      if (pgm_read_word(&flashSongsTimeStamp1[memoryCounter]) == timeStamp)
      {
        dingTime[pgm_read_byte(&flashSongsNote1[memoryCounter])] = DING_DUR;
        memoryCounter++;
      }
      if (pgm_read_word(&flashSongsTimeStamp1[memoryCounter]) == 0)
      {
        playbackFlag = 0;
        gui_botton_set(RESET, SET, RESET);
      }
      break;

    case 2:
    //Playback of second song stored in FLASH
      if (pgm_read_word(&flashSongsTimeStamp2[memoryCounter]) == timeStamp)
      {
        dingTime[pgm_read_byte(&flashSongsNote2[memoryCounter])] = DING_DUR;
        memoryCounter++;
      }
      if (pgm_read_word(&flashSongsTimeStamp2[memoryCounter]) == 0)
      {
        playbackFlag = 0;
        gui_botton_set(RESET, SET, RESET);
      }
      break;

    case 3:
    //Playback of third song stored in FLASHw
      if (pgm_read_word(&flashSongsTimeStamp3[memoryCounter]) == timeStamp)
      {
        dingTime[pgm_read_byte(&flashSongsNote3[memoryCounter])] = DING_DUR;
        memoryCounter++;
      }
      if (pgm_read_word(&flashSongsTimeStamp3[memoryCounter]) == 0)
      {
        playbackFlag = 0;
        gui_botton_set(RESET, SET, RESET);
      }
      break;

    default:
      break;
    }
  }

  SPI_shift(regData);

  if (currButtonState[11] == 0 && prevButtonState[11] == 1)
  { //4th button pressed 
    // Shift playback
    uart_puts("Select next record\n");
    playbackNum = gui_record_shift();
  }
  if (currButtonState[10] == 0 && prevButtonState[10] == 1)
  { //3rd button pressed
    // Record
    timeStamp = 0;
    recFlag = 1;
    memoryCounter = 0;
    uart_puts("Recording started\n");
    gui_botton_set(RESET, RESET, SET);
  }
  if (currButtonState[9] == 0 && prevButtonState[9] == 1)
  { //2nd button pressed
    // Stop
    uart_puts("Recording stoped\n");
    gui_botton_set(RESET, SET, RESET);
    recFlag = 0;
    mem_debug = 1;
    memory_timeStamp[memoryCounter] = 0;
    playbackFlag = 0;
  }
  if (currButtonState[8] == 0 && prevButtonState[8] == 1)
  { //1st button pressed
    // Play
    uart_puts("Playback started\n");
    gui_botton_set(SET, RESET, RESET);
    playbackFlag = 1;
    timeStamp = 0;
    memoryCounter = 0;
  }
  //copy button state to prevButtonState
  for (uint8_t i = 0; i < sizeof(currButtonState); i++)
  {
    prevButtonState[i] = currButtonState[i];
  }
  //increase timestamp for song time tracking
  timeStamp++;
}