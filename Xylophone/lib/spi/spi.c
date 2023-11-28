#include "spi.h"

void initSPI(void)
{
    DDRB |= (1<<2); // set latch pin as output
    DDRB |= ((1<<3) | (1<<5)); //set SCLK and MOSI pins as outputs
    SPCR |= (1<<SPE)|(1<<MSTR)|(1<<DORD); //enable SPI peripheral as master with fclk/4 clock and LSB first

}

void transmitSPI(volatile uint8_t *data)
{
    SPDR = *data;
    while(!(SPSR & (1<<SPIF)));
}