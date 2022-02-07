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
#define u8_SEND_DATA						0xFF
int main(void)
{
	//initializing the master
	I2C_voidMasterInit() ;
	//begin start condition
	I2C_u8MasterStartReq() ;
	//send a write request to slave
	I2C_voidMasterSendSLAWrite(u8_I2C_MCU_SLAVE_ADDRESS) ;
	//SEND 0xFF to the slave so that the slave will
	I2C_voidMasterWriteData(u8_SEND_DATA) ;
	//end of transaction
	I2C_voidMasterStop() ;
	while(1)
	{

	}

}

