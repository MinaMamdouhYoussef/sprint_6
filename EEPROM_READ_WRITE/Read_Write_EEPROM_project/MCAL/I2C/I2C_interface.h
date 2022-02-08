#ifndef __I2C__INTERFACE__
#define __I2C__INTERFACE__
#include "I2C_private.h"

#define u8_I2C_START_FAILED 							10 
#define u8_I2C_START_DONE								11
#define u8_I2C_READ_DONE_SUCCESSFULLY					12
#define u8_I2C_READ_FAILED								13
#define u8_I2C_ARG_ERROR								14

#define u8_SENT_DATA_FAILED								15
#define u8_SENT_DATA_DONE								16


void I2C_voidMasterInit(void)  ;
uint8_t I2C_u8MasterStartReq(void)   ;
uint8_t I2C_u8MasterRepeatStart(void)  ;
void I2C_voidMasterSendSLAWrite(uint8_t u8_SLA) ;
void I2C_voidMasterSendSLARead(uint8_t u8_SLA) ;
uint8_t I2C_voidMasterWriteData(uint8_t u8_DataWantedToSend) ;
uint8_t I2C_u8MasterReadData(uint8_t* u8_ReadData,uint8_t u8_ReceiveAgain) ;
void I2C_voidMasterStop(void) ;




#endif
