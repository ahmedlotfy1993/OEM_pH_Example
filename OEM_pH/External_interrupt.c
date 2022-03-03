/*
 * External_interrupt.c
 *
 * Created: 1/24/2018 4:23:34 PM
 * Author : iti
 */ 

#include <avr/interrupt.h>
#include "External_interrupt.h"
#include "DIO.h"
void(*ptr)(void); //global pointer to function
void Externalnterrupt_gInit(INT_TYPE_t int_type, EDGE_TYPE_t edge_type, void(*pfunc)(void))
{
 switch (int_type)
 {
  case INT00:
   DIO_Init(PB02_PIN_NUM, INPUT_DIR);
   MCUCR &= (uint8_t)0xFC;
   if (edge_type == RISING_EDGE)
   {
	 MCUCR |= (uint8_t)0x03;   
   }else if(edge_type == FALLING_EDGE)
   {
	MCUCR |= (uint8_t)0x02;   
   }else if (edge_type == LOGICAL_CHANGE)
   {
	MCUCR |= (uint8_t)0x01;   
   }else
   {
	   
   }
   GICR|= (uint8_t)0x40;
  break;
  case INT01:
   DIO_Init(PD02_PIN_NUM, INPUT_DIR);
   MCUCR &= (uint8_t)0xF3;
   if (edge_type == RISING_EDGE)
   {
	MCUCR |= (uint8_t)0x0C;
   }else if(edge_type == FALLING_EDGE)
   {
	MCUCR |= (uint8_t)0x08;
   }else if (edge_type == LOGICAL_CHANGE)
   {
	MCUCR |= (uint8_t)0x04;
   }else
   {
	   
   }
   GICR|= (uint8_t)0x80;
  break;
  case INT02:
   DIO_Init(PD03_PIN_NUM, INPUT_DIR);
   MCUCR &= (uint8_t)0xF3;
   if (edge_type == RISING_EDGE)
   {
	MCUCSR |= (uint8_t)0x40;
   }else if(edge_type == FALLING_EDGE)
   {
	MCUCR &= (uint8_t)0xBF;
   }
   GICR|= (uint8_t)0x20;
  break;	 
 }	
 ptr=pfunc;
}
void SET_int0(void(*pfunc)(void))
{
 ptr=pfunc;	
}
ISR(INT0_vect)
{
	(ptr)();
}