/*
 * LightTraffic_main.c
 *
 *  Created on: Feb 6, 2022
 */
#include "LIBRARY/BIT_MATH.h"
#include "LIBRARY/primitive_data_types.h"
#include "MCAL/USART/usart_interface.h"
#include "MCAL/DIO/dio_interface.h"
#include "ECUAL/LED/led_interface.h"
#include <string.h>


#define u8_EQUAL_STR						0
#define u8_COMMAND_STR_SIZE					10
#define u8_LAST_STR_COMMAND_INDEX			9
#define u8_TERMINATE_STR_ASCII				'\r'
#define GREEN_LED_ON_STR					(uint8_t*)"Green LED is on\r"
#define RED_LED_ON_STR						(uint8_t*)"Red LED is on\r"
#define YELLOW_LED_ON_STR					(uint8_t*)"Yellow LED is on\r"
#define WRONG_COMMAND_STR					(uint8_t*)"wrong Entered Command\r"
#define RESPOND_STR							(uint8_t*)"OK\r"
#define START_COMMAND_STR					"START"
#define WAIT_COMMAND_STR					"WAIT"
#define STOP_COMMAND_STR					"STOP"
#define ATTENTION_COMMAND_STR				"AT"


int main(void )
{
	USART_voidInit() ;
	LED_voidInit() ;
	uint8_t pu8_commandStr[u8_COMMAND_STR_SIZE] , u8_dataState ;


	while(1)
	{
		//get input from user and due to the USART is based on Time out so looping take place until the input entered
		do
		{
			u8_dataState = USART_u8ReceiveStr(pu8_commandStr,u8_LAST_STR_COMMAND_INDEX,u8_TERMINATE_STR_ASCII) ;

		}while(u8_dataState != u8_USART_RECEIVED_CORRECT) ;

		//if START command written, Green LED on and the response given back on terminal
		if(strcmp(pu8_commandStr,START_COMMAND_STR)==u8_EQUAL_STR)
		{
			LED_u8On(u8_LED0) ;
			LED_u8Off(u8_LED1) ;
			LED_u8Off(u8_LED2) ;
			USART_u8TransStr(GREEN_LED_ON_STR);
		}
		//if WAIT command written, Yellow LED on and the response given back on terminal
		else if (strcmp(pu8_commandStr,WAIT_COMMAND_STR)==u8_EQUAL_STR)
		{
			LED_u8Off(u8_LED0) ;
			LED_u8On(u8_LED1) ;
			LED_u8Off(u8_LED2) ;
			USART_u8TransStr(YELLOW_LED_ON_STR);
		}
		//if STOP command written, Red LED on and the response given back on terminal
		else if(strcmp(pu8_commandStr,STOP_COMMAND_STR)==u8_EQUAL_STR)
		{
			LED_u8Off(u8_LED0) ;
			LED_u8Off(u8_LED1) ;
			LED_u8On(u8_LED2) ;
			USART_u8TransStr(RED_LED_ON_STR) ;
		}
		//if At command written, ok response given back
		else if (strcmp(pu8_commandStr,ATTENTION_COMMAND_STR)==u8_EQUAL_STR)
		{
			USART_u8TransStr(RESPOND_STR);
		}
		//if the command entered is incorrect, incorrect state will given
		else
		{
			USART_u8TransStr(WRONG_COMMAND_STR) ;
		}
	}
}
