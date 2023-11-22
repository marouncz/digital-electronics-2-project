#ifndef SPI_H
# define SPI_H

#include <avr/io.h>

void initSPI(void);

void transmitSPI(volatile unit8_t *data);

#endif