#ifndef SPI_H
# define SPI_H

#include <avr/io.h>

void SPI_init(void);

void SPI_transmit(volatile uint8_t *data);

void SPI_shift(volatile uint8_t *data);

#endif