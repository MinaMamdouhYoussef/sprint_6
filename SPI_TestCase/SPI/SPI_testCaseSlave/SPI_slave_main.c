/*
 * SPI_master_main.c
 *
 *  Created on: Feb 6, 2022
 *      Author: CompuSity
 */

#include "LIBRARY/BIT_MATH.h"
#include "LIBRARY/atmega32_registers.h"
#include "LIBRARY/primitive_data_types.h"
#include "MCAL/DIO/dio_interface.h"
#include "MCAL/SPI/SPI_interface.h"




int main(void)
{
	uint8_t u8_receiveData ,u8_dummy ;
	SPI_voidInit() ;
	//receive data and send dummy byte
	u8_receiveData = SPI_voidTransever(u8_dummy) ;
	//make DIO port A output port
	DIO_u8SetPortDir(u8_DIO_PORTA,u8_DIO_OUTPUT_PORT) ;
	//Set the received value on slave port A
	DIO_u8SetPortVal(u8_DIO_PORTA,u8_receiveData) ;
	while(1)
	{

	}
}
