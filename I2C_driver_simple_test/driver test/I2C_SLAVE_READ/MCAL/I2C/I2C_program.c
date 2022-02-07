/*
 * EEPROM_main.c
 * layer : MCAL
 * DRIVER: I2C
 *  Created on: Feb 1, 2022
 *      Author: mina mamdouh
 *      version: 1
 */

#include "../../LIBRARY/BIT_MATH.h"
#include "../../LIBRARY/primitive_data_types.h"
#include "../../LIBRARY/atmega32_registers.h"
#include "I2C_private.h"
#include "I2C_interface.h"


void I2C_voidMasterInit(void) 
{

		Ru8_TWBR = 0x70 ;
		CLR_BIT(Ru8_TWSR,u8_I2C_TWPS1) ;
		CLR_BIT(Ru8_TWSR,u8_I2C_TWPS0) ;

		Ru8_TWCR = ((u8_I2C_SET_BIT_TO_ONE<<u8_I2C_TWEA)|(u8_I2C_SET_BIT_TO_ONE<<u8_I2C_TWEN)) ; 
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//return start state if it done successfully or not 
uint8_t I2C_u8MasterStartReq(void)  
{
	uint8_t u8_StartState = u8_I2C_START_FAILED ;  
	/*set start condion to begin the start req., make I2C Enable, and Clear int flag 
	 *so that we can send start condition (no operation can done without clearing int flag )
	 */
	Ru8_TWCR = ((u8_I2C_SET_BIT_TO_ONE<<u8_I2C_TWSTA)|(u8_I2C_SET_BIT_TO_ONE<<u8_I2C_TWEN)|(u8_I2C_SET_BIT_TO_ONE<<u8_I2C_TWINT)
				|(u8_I2C_SET_BIT_TO_ONE<<u8_I2C_TWEA)) ;

	while(GET_BIT(Ru8_TWCR,u8_I2C_TWINT) != u8_I2C_FLAG_SET) ;

	if((Ru8_TWSR & u8_I2C_MASK_PRESCALE)==u8_I2C_START_SEND_SUCCESSFULLY)  //start send successfully
	{
		u8_StartState = u8_I2C_START_DONE ;
	}

	return u8_StartState ; 
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

uint8_t I2C_u8MasterRepeatStart(void) 
{
	uint8_t u8_StartState = u8_I2C_START_FAILED ;
	/*
	 * Repeat start to the last address by clearing TWINT , make a start condition ,and make I2C enabled 
	 */
	Ru8_TWCR = ((u8_I2C_SET_BIT_TO_ONE<<u8_I2C_TWSTA)|(u8_I2C_SET_BIT_TO_ONE<<u8_I2C_TWEN)|(u8_I2C_SET_BIT_TO_ONE<<u8_I2C_TWINT)
			   |(u8_I2C_SET_BIT_TO_ONE<<u8_I2C_TWEA)) ;
	while(GET_BIT(Ru8_TWCR,u8_I2C_TWINT) != u8_I2C_FLAG_SET) ;
	if((Ru8_TWSR & u8_I2C_MASK_PRESCALE)==u8_I2C_REPEAT_START_SEND_SUCCESSFULLY)  //start send successfully
	{
		u8_StartState = u8_I2C_START_DONE ;
	}

	return u8_StartState ; 
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// master send a slave address and wanted to read from the SLA
void I2C_voidMasterSendSLAWrite(uint8_t u8_SLA)
{
	//make TWDR set with wanted slave address and make LSB = 0 to be in write operation 
	Ru8_TWDR = (u8_SLA<<u8_I2C_TWD1)  ;
	/*make I2C Enable and Clear int flag so that we can load TWDR (no operation can done without clearing int flag) 
	 *and clear condition start bit */
	Ru8_TWCR = ((u8_I2C_SET_BIT_TO_ONE<<u8_I2C_TWEN) |(u8_I2C_SET_BIT_TO_ONE<<u8_I2C_TWINT)|(u8_I2C_SET_BIT_TO_ONE<<u8_I2C_TWEA)) ;
	
	// wait until the Master sends the SLA address with write operation 
	while(GET_BIT(Ru8_TWCR,u8_I2C_TWINT) != u8_I2C_FLAG_SET) ; 
	
	// wait until Ack. is received and if Ack is not received repeat start and send address again until the Ack is received. 
	while(((Ru8_TWSR & u8_I2C_MASK_PRESCALE)!=u8_I2C_SLA_W_ACK_RECEIVED))
	{
		// master will repeat start in case ACK is not reached.  
		I2C_u8MasterRepeatStart() ;
		
  	   //make TWDR set with wanted slave address and make LSB = 0 to be in write operation 
		Ru8_TWDR = (u8_SLA<<u8_I2C_SET_BIT_TO_ONE)  ;
		
	/*make I2C Enable and Clear int flag so that we can load TWDR (no operation can done without clearing int flag) 
	 *and clear condition start bit */
	 Ru8_TWCR = ((u8_I2C_SET_BIT_TO_ONE<<u8_I2C_TWEN) |(u8_I2C_SET_BIT_TO_ONE<<u8_I2C_TWINT)) ;
	
		// wait until the Master sends the SLA address with write operation 
		while(GET_BIT(Ru8_TWCR,u8_I2C_TWINT) != u8_I2C_FLAG_SET) ;
	}

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// master send a slave address and wanted to read from the SLA
void I2C_voidMasterSendSLARead(uint8_t u8_SLA)
{
	//make TWDR set with wanted slave address and make LSB = 1 to be in read operation 
	Ru8_TWDR = (u8_SLA<<u8_I2C_TWD1)| u8_SET_READ_MODE  ;
	
	//make I2C Enable and Clear int flag so that we can load TWDR (no operation can done without clearing int flag)
	Ru8_TWCR = ((u8_I2C_SET_BIT_TO_ONE<<u8_I2C_TWEN) |(u8_I2C_SET_BIT_TO_ONE<<u8_I2C_TWINT) |(u8_I2C_SET_BIT_TO_ONE<<u8_I2C_TWEA)) ;
	
	// wait until the Master sends the SLA address with read operation 
	while(GET_BIT(Ru8_TWCR,u8_I2C_TWINT) != u8_I2C_FLAG_SET) ; 
	
	// wait until Ack. is received and if Ack is not received repeat start and send address again until the Ack is received. 
	while((Ru8_TWSR & u8_I2C_MASK_PRESCALE)!=u8_I2C_SLA_R_ACK_RECEIVED)
	{
		// master will repeat start in case ACK is not reached.  
		I2C_u8MasterRepeatStart() ; 

		//make TWDR set with wanted slave address and make LSB = 1 to be in read operation 
		Ru8_TWDR = (u8_SLA<<u8_I2C_TWD1)| u8_SET_READ_MODE  ;
		
		//make I2C Enable and Clear int flag so that we can load TWDR (no operation can done without clearing int flag)
		Ru8_TWCR = ((u8_I2C_SET_BIT_TO_ONE<<u8_I2C_TWEN) |(u8_I2C_SET_BIT_TO_ONE<<u8_I2C_TWINT)) ; 
	
		// wait until the Master sends the SLA address with read operation 
		while(GET_BIT(Ru8_TWCR,u8_I2C_TWINT) != u8_I2C_FLAG_SET) ; 
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

uint8_t I2C_voidMasterWriteData(uint8_t u8_DataWantedToSend)
{
	uint8_t u8_ErrorState = u8_I2C_INTIAL_VAL ;
	// put the data needed to send in the send reg. 
	Ru8_TWDR = u8_DataWantedToSend ; 
	
	//make I2C Enable and Clear int flag so that we can load TWDR (no operation can done without clearing int flag)
	Ru8_TWCR = ((u8_I2C_SET_BIT_TO_ONE<<u8_I2C_TWEN) |(u8_I2C_SET_BIT_TO_ONE<<u8_I2C_TWINT)|(u8_I2C_SET_BIT_TO_ONE<<u8_I2C_TWEA)) ;
	
	// wait until the Master sends the data send .
	while(GET_BIT(Ru8_TWCR,u8_I2C_TWINT) != u8_I2C_FLAG_SET) ; 
	
	if((Ru8_TWSR & u8_I2C_MASK_PRESCALE)== u8_I2C_DATA_W_ACK_RECEIVED)
	{
		u8_ErrorState = u8_SENT_DATA_DONE ;
	}
	else
	{
		u8_ErrorState = u8_SENT_DATA_FAILED ;
	}
	return u8_ErrorState ;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//function that read from slave and return error state if the argument is wrong
uint8_t I2C_u8MasterReadData(uint8_t* u8_ReadData,uint8_t u8_ReceiveAgain)
{
	uint8_t u8_ErrorState = u8_I2C_INTIAL_VAL ;
	if((u8_ReceiveAgain==u8_I2C_RECEIVE_MORE_WORDS || u8_ReceiveAgain==u8_I2C_RECEIVE_COMPLETE) && u8_ReadData!=NULL_POINTER )
	{
		if(u8_ReceiveAgain==u8_I2C_RECEIVE_MORE_WORDS)
		{
			/*make I2C Enable and Clear int flag so that we can load TWDR (no operation can done without clearing int flag)
			 *and make the slave ACK when the data received*/
			Ru8_TWCR = (u8_I2C_SET_BIT_TO_ONE<<u8_I2C_TWEN) |(u8_I2C_SET_BIT_TO_ONE<<u8_I2C_TWINT)|(u8_I2C_SET_BIT_TO_ONE<<u8_I2C_TWEA) ; 
			// wait until the Master Receive the data sent .
			while(GET_BIT(Ru8_TWCR,u8_I2C_TWINT) != u8_I2C_FLAG_SET) ; 

			if((Ru8_TWSR & u8_I2C_MASK_PRESCALE)== u8_I2C_DATA_R_ACK_RECEIVED_ACK_RETURN)
			{
				u8_ErrorState =u8_I2C_READ_DONE_SUCCESSFULLY ; 
				*u8_ReadData = Ru8_TWDR ;
			}
			else 
			{
				u8_ErrorState =u8_I2C_READ_FAILED; 
			}
		}
		else 
		{
			//make I2C Enable and Clear int flag so that we can load TWDR (no operation can done without clearing int flag)
			Ru8_TWCR = (u8_I2C_SET_BIT_TO_ONE<<u8_I2C_TWEN) |(u8_I2C_SET_BIT_TO_ONE<<u8_I2C_TWINT) ; 
			while(GET_BIT(Ru8_TWCR,u8_I2C_TWINT) != u8_I2C_FLAG_SET) ; 
			if((Ru8_TWSR & u8_I2C_MASK_PRESCALE)== u8_I2C_DATA_R_ACK_RECEIVED_ACK_NOT_RETURN)
			{
				u8_ErrorState =u8_I2C_READ_DONE_SUCCESSFULLY ; 
				*u8_ReadData = Ru8_TWDR ;
			}
			else 
			{
				u8_ErrorState =u8_I2C_READ_FAILED; 
			}
		}


	}
	else 
	{
		u8_ErrorState = u8_I2C_ARG_ERROR ; 
	}
	return u8_ErrorState ;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void I2C_voidMasterStop(void)
{	
	/*make I2C Enable and Clear int flag so that we can load TWDR (no operation can done without clearing int flag)
	 * and set condion stop bit to stop sending */
	Ru8_TWCR = (u8_I2C_SET_BIT_TO_ONE<<u8_I2C_TWEN) |(u8_I2C_SET_BIT_TO_ONE<<u8_I2C_TWINT) | (u8_I2C_SET_BIT_TO_ONE<<u8_I2C_TWSTO) ; 	
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void I2C_voidSlaveInit(uint8_t u8_SlaveAddress)
{
	// make general call off and set slave address to intiate the slave mode of I2C
	Ru8_TWAR = u8_SlaveAddress << u8_I2C_TWA0 ;
	// initialize tWCR by setting TWEN to 1 to ENABLE the two wire interface and setting TWEA to 1 to Enable the slave to receive ack.
	Ru8_TWCR = ((u8_I2C_SET_BIT_TO_ONE<<u8_I2C_TWEN) |(u8_I2C_SET_BIT_TO_ONE<<u8_I2C_TWEA)) ;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                //
uint8_t I2C_slaveReadAckReturned(void)
{
	//set ack. , clear TWINT to wait the new actio and make the I2C enabled
	Ru8_TWCR = ((u8_I2C_SET_BIT_TO_ONE << u8_I2C_TWINT) | (u8_I2C_SET_BIT_TO_ONE<< u8_I2C_TWEA) | (u8_I2C_SET_BIT_TO_ONE << u8_I2C_TWEN));
	//wait until data received
	while(GET_BIT(Ru8_TWCR,u8_I2C_TWINT) != u8_I2C_FLAG_SET);
	//return the data received
	return Ru8_TWDR;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void I2C_slaveAckRead(void)
{
	//wait until the SLW+W received by slave
	while((Ru8_TWSR & 0xF8) != u8_I2C_SLAVE_ADDRESS_CALLED_SLAW) ;
	//set ack. , clear TWINT to wait the new action and make the I2C enabled
	Ru8_TWCR = ((u8_I2C_SET_BIT_TO_ONE << u8_I2C_TWINT) | (u8_I2C_SET_BIT_TO_ONE<< u8_I2C_TWEA) | (u8_I2C_SET_BIT_TO_ONE << u8_I2C_TWEN));
	//wait until master receive the ACK.
	while  (GET_BIT(Ru8_TWCR,u8_I2C_TWINT) != u8_I2C_FLAG_SET);

}

