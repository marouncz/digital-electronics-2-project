/**
 * @file 
 * @defgroup spi peripheral library <spi.h>
 * @code #include <spi.h> @endcode
 *
 * @brief Library for spi init and data transmit for shift registers
 *
 * The library contains functions for contoling gui for xylophone.
 *
 * @author Marek Coufal, Martin Tavoda, Brno University of Technology, Czechia
 * 
 * @copyright (c) 2023 Marek Coufal, Martin Tavoda, This work is licensed under 
 *                the terms of the MIT license
 * @{
 */


#ifndef SPI_H
# define SPI_H

#include <avr/io.h>

/**
 * @brief  Iitialize SPI peripheral for use with shift registers
 * @return none 
 */
void SPI_init(void);

/**
 * @brief  Transmit data over SPI in blocking mode
 * @param  data pointer to data to transmit
 * @return none 
 */
void SPI_transmit(volatile uint8_t *data);

/**
 * @brief  Transmit data over SPI in blocking mode and handles latch pin
 * @param  data pointer to data to transmit
 * @return none 
 */
void SPI_shift(volatile uint8_t *data);

#endif