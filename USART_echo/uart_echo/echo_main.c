/*
 * echo_main.c
 *
 *  Created on: Feb 5, 2022
 *      Author: CompuSity
 */


#include "LIBRARY/primitive_data_types.h"
#include "LIBRARY/BIT_MATH.h"
#include "LIBRARY/atmega32_registers.h"
#include "MCAL/USART/usart_interface.h"
#include "MCAL/DIO/dio_interface.h"
//#include <string.h>

#define bit7 			7
int main(void )
{
	USART_voidInit()  ;
	SET_BIT(Ru8_SREG , bit7); // set global interrupt

	uint8_t pu8_Packet[30] ;
	uint8_t u8_dataState =  u8_USART_DATA_SENT;
	u8_dataState = USART_u8ReceiveStr(pu8_Packet,30,'\r') ;
	u8_dataState = USART_u8TransStr(pu8_Packet) ;

	while (1)
	{
	}
	return 0 ;
}
