#ifndef SPI_H
# define SPI_H

#include <avr/io.h>

void initSPI(void);

void transmitSPI(volatile uint8_t *data);

#endif