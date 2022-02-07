/*
 * EEPROM_main.c
 *
 *  Created on: Feb 5, 2022
 *      Author: CompuSity
 */
#include "LIBRARY/atmega32_registers.h"
#include "LIBRARY/primitive_data_types.h"
#include "MCAL/DIO/dio_interface.h"
#include "MCAL/I2C/I2C_interface.h"


#define u8_I2C_MCU_SLAVE_ADDRESS			0x51

int main(void)
{

	uint8_t u8_dataRead ;
	//initializing the slave
	I2C_voidSlaveInit(u8_I2C_MCU_SLAVE_ADDRESS) ;
	//send ack from slave that the master's write request happened
	I2C_slaveAckRead() ;
	//get the returned data
	u8_dataRead = I2C_slaveReadAckReturned() ;
	//initialize the PORTA to be output port
	DIO_u8SetPortDir(u8_DIO_PORTA,u8_DIO_OUTPUT_PORT) ;
	//set the port with the returned value (value sent from master )
	DIO_u8SetPortVal(u8_DIO_PORTA,u8_dataRead) ;

	while(1)
	{

	}

}

