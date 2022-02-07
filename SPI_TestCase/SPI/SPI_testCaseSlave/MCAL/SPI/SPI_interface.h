/*
 *  Author: Mina Mamdouh Youssef
 *  Driver: SPI
 *  Layer arch : MCAL
 *  Created on: Feb 6, 2022
 *	version:1
 *
 */


#ifndef	__SPI__INTERFACE__
#define __SPI__INTERFACE__



void SPI_voidInit(void) ; 
uint8_t SPI_voidTransever(uint8_t u8_dataSent) ;
void SPI_voidReceiveArr(uint8_t* pu8_dataReceive,uint8_t u8_arrSize) ; 
void SPI_voidSendArr(uint8_t* pu8_dataSent,uint8_t u8_arrSize) ; 



#endif
