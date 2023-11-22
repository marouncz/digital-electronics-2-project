#include "spi.h"

void initSPI(void)
{

}

void transmitSPI(volatile uint8_t *data)
{
    SPDR = data;
    while(!(SPSR & (1<<SPIF)));
}