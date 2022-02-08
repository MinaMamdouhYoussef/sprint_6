/*
 * EEPROM_main.c
 *
 *  Created on: Feb 5, 2022
 *      Author: CompuSity
 */
#include "LIBRARY/atmega32_registers.h"
#include"LIBRARY/BIT_MATH.h"
#include "LIBRARY/primitive_data_types.h"
#include "MCAL/TIMERS/timers_interface.h"
#include "MCAL/DIO/dio_interface.h"
#include "MCAL/I2C/I2C_interface.h"
#include "ECUAL/EEPROM/EEPROM_interface.h"
#include "MCAL/USART/usart_interface.h"
#include <string.h>

uint8_t u8_enterCheckPageVal(uint16_t* pu16_enteredPageNum) ;

#define FALSE 								0
#define TRUE 								1

#define u8_INTIAL_VAL						0
#define u8_BEGIN_WRITE_IN_BYTE_NUM0			0

#define u8_EQUAL_STR						0


#define u8_PAGE_VALID						2
#define u8_PAGE_INVALID						3
#define u8_INCREASE_PAGE_WEIGHT				10
#define bit7								7
#define u8_PAGE_STR_SIZE					6
#define u8_COMMAND_STR_SIZE					10

#define u8_MAX_INTERED_USER_DATA_SIZE		20

#define u8_MAX_PAGE_NUM						511

int main(void)
{
	uint16_t u16_enteredPageNum= u8_INTIAL_VAL 	 ;
	uint8_t u8_dataState  , u8_pageState = u8_INTIAL_VAL  ;
	uint8_t pu8_commandStr[u8_COMMAND_STR_SIZE] ;
	//uint8_t pu8_pageStr[u8_PAGE_STR_SIZE] ;
	uint8_t pu8_eepromDataStr[u8_MAX_INTERED_USER_DATA_SIZE] ;
	uint8_t pu8_userDataStr[u8_MAX_INTERED_USER_DATA_SIZE] ;

	SET_BIT(Ru8_SREG , bit7); // set global interrupt
	USART_voidInit() ;
	EEPROM_voidInit() ;


	while(1)
	{

		USART_u8TransStr((uint8_t*)"\rEnter READ or WRITE\r") ;

		do
		{
			u8_dataState = USART_u8ReceiveStr(pu8_commandStr,u8_COMMAND_STR_SIZE,'\r') ;

		}while(u8_dataState != u8_USART_RECEIVED_CORRECT) ;



		if(strcmp(pu8_commandStr,(uint8_t*)"WRITE")==u8_EQUAL_STR)
		{
			//Respond with OK
			USART_u8TransStr((uint8_t*)"ok \r") ;
			//take page number and check page validity
			u8_pageState =  u8_enterCheckPageVal((uint16_t*)(&u16_enteredPageNum)) ;
			if(u8_pageState == u8_PAGE_VALID)
			{
				USART_u8TransStr((uint8_t*)"ok \r") ;
				do
				{
					u8_dataState = USART_u8ReceiveStr(pu8_userDataStr,u8_MAX_INTERED_USER_DATA_SIZE,'\r') ;

				 }while(u8_dataState != u8_USART_RECEIVED_CORRECT) ;

				USART_u8TransStr((uint8_t*)"ok \r") ;
				//Write wanted page from EEPROM
				EEPROM_u8WriteNeededPartBlock(u16_enteredPageNum,u8_BEGIN_WRITE_IN_BYTE_NUM0,pu8_userDataStr,u8_MAX_INTERED_USER_DATA_SIZE) ;

			}
		}
		else if((strcmp(pu8_commandStr,(uint8_t*)"READ")==u8_EQUAL_STR ))
		{
			//Respond with OK
			USART_u8TransStr((uint8_t*)"ok \r") ;
			//take page number and check page validity and return in pointer number converted to u16
			u8_pageState = u8_enterCheckPageVal((uint16_t*)(&u16_enteredPageNum)) ;
			//read wanted page from EEPROM
			if(u8_pageState == u8_PAGE_VALID)
			{
				// read from EEPROM the written data
				EEPROM_u8ReadNeededPartBlock(u16_enteredPageNum,u8_BEGIN_WRITE_IN_BYTE_NUM0,pu8_eepromDataStr,u8_MAX_INTERED_USER_DATA_SIZE) ;
				USART_u8TransStr(pu8_eepromDataStr) ;
			}

		}
		else
		{
			USART_u8TransStr((uint8_t*)"Wrong input command \r") ;
		}
	}

}



//FUNCTION that take pointer to string to take the page number in,
uint8_t u8_enterCheckPageVal(uint16_t* pu16_enteredPageNum)
{
	uint8_t pu8_pageNumStr[u8_PAGE_STR_SIZE] ;
	uint8_t u8_inputPageState = u8_PAGE_INVALID , u8_indexArr = u8_INTIAL_VAL;
	*pu16_enteredPageNum = 	u8_I2C_INTIAL_VAL ;
	USART_u8TransStr((uint8_t*)"please Enter page number less than 511 \r ") ;

	//take a valid input from user (due to the time out that USART implemented with )
	do
	{
		u8_inputPageState = USART_u8ReceiveStr(pu8_pageNumStr,u8_PAGE_STR_SIZE,'\r') ;

	}while(u8_inputPageState != u8_USART_RECEIVED_CORRECT) ;

	// check the array taken by USART from user is digits and less than 511 (number of pages in EEPROM or not )
	while(pu8_pageNumStr[u8_indexArr]!=NULL_CHAR && u8_indexArr< (u8_PAGE_STR_SIZE))
	{
		if(pu8_pageNumStr[u8_indexArr]>='0' && pu8_pageNumStr[u8_indexArr]<='9' && (*pu16_enteredPageNum) < 511)
		{
			if(u8_indexArr== u8_INTIAL_VAL)
			{
				(*pu16_enteredPageNum) = (uint16_t)(pu8_pageNumStr[u8_indexArr] - '0');
				u8_indexArr++ ;
				u8_inputPageState = u8_PAGE_VALID ;

			}
			else if(u8_indexArr<=2)
			{
				(*pu16_enteredPageNum) = ((*pu16_enteredPageNum)*u8_INCREASE_PAGE_WEIGHT ) + (pu8_pageNumStr[u8_indexArr] - '0') ;
				u8_indexArr++ ;
				u8_inputPageState = u8_PAGE_VALID ;
			}
			else
			{
				USART_u8TransStr((uint8_t*)"Invalid Page number \r") ;
				break;
			}
		}
		else
		{
			USART_u8TransStr((uint8_t*)"Invalid Page number \r") ;
			break ;
		}
	}
	// check if the value choosen more than the page number or not
	if((*pu16_enteredPageNum)>u8_MAX_PAGE_NUM)
	{
		USART_u8TransStr((uint8_t*)"Invalid Page number \r") ;
		u8_inputPageState = u8_PAGE_INVALID ;
	}
	return u8_inputPageState ;
}
