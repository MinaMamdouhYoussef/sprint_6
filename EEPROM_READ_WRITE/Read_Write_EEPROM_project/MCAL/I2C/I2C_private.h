#ifndef __I2C__PRIVATE__
#define __I2C__PRIVATE__



//TWCR bit num. 
#define u8_I2C_TWINT									7
#define u8_I2C_TWEA									    6
#define u8_I2C_TWSTA									5
#define u8_I2C_TWSTO									4
#define u8_I2C_TWWC									    3
#define u8_I2C_TWEN									    2
#define u8_I2C_TWIE									    0


//TWSR bit num. 
#define u8_I2C_TWS7										7
#define u8_I2C_TWS6                                     6
#define u8_I2C_TWS5                                     5
#define u8_I2C_TWS4                                     4
#define u8_I2C_TWS3                                     3
#define u8_I2C_TWPS1                                    1
#define u8_I2C_TWPS0                                    0

//TWDR bit num. 
#define u8_I2C_TWD1										1
												

#define u8_I2C_MAX_WAIT_IN_MS							70
#define u8_I2C_MAX_REPEAT_START							100


#define u8_I2C_FLAG_SET									1
#define u8_I2C_FLAG_CLEAR								0

//VALUES OF STATUS REGISTERS flags.
#define u8_I2C_START_SEND_SUCCESSFULLY					0x08
#define u8_I2C_REPEAT_START_SEND_SUCCESSFULLY			0x10
#define u8_I2C_SLA_W_ACK_RECEIVED						0x18
#define u8_I2C_SLA_R_ACK_RECEIVED						0x40
#define u8_I2C_DATA_W_ACK_RECEIVED 						0x28
#define u8_I2C_DATA_R_ACK_RECEIVED_ACK_RETURN 			0x50
#define u8_I2C_DATA_R_ACK_RECEIVED_ACK_NOT_RETURN 		0x58

//MASKING THE Prescaler flag in the status register using this value 
#define u8_I2C_MASK_PRESCALE							0xF8
#define	u8_SET_READ_MODE								0x01 

//BIT names of TWGCE reg.
#define u8_I2C_TWA0										1


#define u8_I2C_SLAVE_SEND_DAT_ACK_RECEIVED				0xC8
#define u8_I2C_SLAVE_SEND_DAT_NOT_ACK_RECEIVED			0xC0
#define u8_I2C_SLAVE_ADDRESS_CALLED_SLAW				0x60
#define u8_I2C_DATA_RECEIVED_SLAVE_READ					0x80

#define u8_I2C_SET_BIT_TO_ONE							1
#define	u8_I2C_INTIAL_VAL								0
#define u8_I2C_MAXIMUM_REPEAT_SEND						3 

#define u8_I2C_RECEIVE_COMPLETE							10
#define u8_I2C_RECEIVE_MORE_WORDS						11

#endif
