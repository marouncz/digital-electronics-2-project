#include "spi.h"

void SPI_init(void)
{
    DDRB |= (1<<2); // set latch pin as output
    DDRB |= ((1<<3) | (1<<5)); //set SCLK and MOSI pins as outputs
    SPCR |= (1<<SPE)|(1<<MSTR)|(1<<DORD); //enable SPI peripheral as master with fclk/4 clock and LSB first

}

void SPI_transmit(volatile uint8_t *data)
{
    SPDR = *data;
    while(!(SPSR & (1<<SPIF)));
}

void SPI_shift(volatile uint8_t *data){
    GPIO_write_low(&PORTB, 2);
    SPI_transmit(&data);   
    GPIO_write_high(&PORTB, 2); 
}