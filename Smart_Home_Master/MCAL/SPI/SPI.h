/*
 * SPI.h
 *
 *  Created on: Aug 31, 2023
 *      Author: user
 */

#ifndef SPI_H_
#define SPI_H_

#define SPI_SCK  7
#define SPI_MISO 6
#define SPI_MOSI 5
#define SPI_SS   4

//prototypes
void SPI_vInitMaster (void);
void SPI_vInitSlave (void);
u8 SPI_ui8TransmitRecive (u8 data);


#endif /* SPI_H_ */
