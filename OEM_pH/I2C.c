
#include "I2C.h"
void TWI_init(uint32_t clk_val)
{
	TWSR=0x00;
	uint8_t prescaler_val = 1;
	uint32_t TWBR_Val = 0;

	 TWBR_Val = ((F_CPU / clk_val) - 16 ) / (2 * prescaler_val);
	 while ((TWBR_Val > (uint8_t)0xff) && (prescaler_val <= (uint8_t)64))
	 {
	  prescaler_val = prescaler_val * 4;
	  TWBR_Val = ((F_CPU / clk_val) - 16 ) / (2 * prescaler_val);	 
	 }
	 switch (prescaler_val)
	 {
	  case 1:
	   TWSR |= TWI_OVER_01_PRESCALER_VAL;
	  break;
	  
	  case 4:
	   TWSR |= TWI_OVER_04_PRESCALER_VAL;
	  break;
	  
	  case 16:
	   TWSR |= TWI_OVER_16_PRESCALER_VAL;
	  break;
	  
	  case 64:
	   TWSR |= TWI_OVER_64_PRESCALER_VAL;
	  break;
	  	 
	 }
	 TWBR= (uint8_t) TWBR_Val; 
	
	TWCR=(1<<TWEN);
}

void TWI_Start()
{
	TWCR=(1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while((TWCR & (1<<TWINT))==0);
}

void TWI_Stop()
{
	TWCR=(1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
}
/*
unsigned char TWI_GetStatus()
{
	unsigned char status;
	status = TWSR & 0xF8;
	return status;
}
*/
void TWI_Write(unsigned char u8data)
{
	TWDR=u8data;
	TWCR=(1<<TWINT)|(1<<TWEN);
	while((TWCR & (1<<TWINT))==0);
}
/*
unsigned char TWI_ReadACK()
{
	TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWEA);
	while((TWCR & (1<<TWINT))==0);
	return TWDR;
}
*/
unsigned char TWI_ReadNACK()
{
	TWCR=(1<<TWINT)|(1<<TWEN);
	while((TWCR & (1<<TWINT))==0);
	return TWDR;
}
