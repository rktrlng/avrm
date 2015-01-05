#ifndef SPI_H
#define SPI_H

#define HI_NIBBLE(b) (((b) >> 4) & 0x0F)
#define LO_NIBBLE(b) ((b) & 0x0F)

void spi_init_master(void);
void spi_master_transmit(char data);

void spi_init_slave(void);
char spi_slave_receive(void);

#endif /* SPI_H */ 
