#ifndef I2C_H_
#define I2C_H_

#include "My_lib.h"
#include <avr/io.h>



/*
//I2C status
#define RESTART_STATUS     					(0x10)
#define START_STATUS	   					(0x08)
#define SLAVE_ADDRESS_WRITE_ACK_STATUS		(0x18)
#define SLAVE_ADDRESS_READ_ACK_STATUS		(0x40)
#define DATA_SEND_ACK_STATUS				(0x28)
#define DATA_READ_NACK_STATUS				(0x58)
#define DATA_READ_ACK_STATUS				(0x50)
*/

#define TWI_OVER_01_PRESCALER_VAL           (uint8_t)0x00
#define TWI_OVER_04_PRESCALER_VAL           (uint8_t)0x01
#define TWI_OVER_16_PRESCALER_VAL           (uint8_t)0x02
#define TWI_OVER_64_PRESCALER_VAL           (uint8_t)0x03
void TWI_init(uint32_t clk_val);
void TWI_Start();
void TWI_Stop();
//unsigned char TWI_GetStatus();
void TWI_Write(unsigned char u8data);
unsigned char TWI_ReadNACK();






#endif    //I2C_H_
