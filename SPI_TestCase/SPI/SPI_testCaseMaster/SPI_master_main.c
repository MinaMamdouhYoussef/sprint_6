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


//sending from master 0xFF to make slave output port high when set this data in PORT
#define u8_MAKE_SLAVE_PORT_HIGH					0xFF


int main(void)
{
	uint8_t u8_dummy ;
	//SPI intialization
	SPI_voidInit() ;
	//send the wanted data to slave and receive dummy value from slave
	u8_dummy = SPI_voidTransever(u8_MAKE_SLAVE_PORT_HIGH) ;

	while(1)
	{

	}
}
