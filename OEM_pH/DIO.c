/*
 * DIO.c
 *
 * Created: 4/22/2017 2:29:45 PM
 *  Author: A.Aboelmakarem
 */

#include "DIO.h"

void DIO_WritePortVal(char Port_Num,char Val)
{
	switch(Port_Num)
	{
		case 0:
		PORTA=Val;
		break;
		
		case 1:
		PORTB=Val;
		break;
		
		case 2:
		PORTC=Val;
		break;
		
		case 3:
		PORTD=Val;
		break;
		
		default:
		break;
	}
}

void DIO_WritePinVal(char Pin_Num, char Val)
{
	char Port_Num = Pin_Num/8;
	char Pin_Index = Pin_Num % 8;
	switch(Port_Num)
	{
		case 0:
		if(Val==0)
		CLR_BIT(PORTA,Pin_Index);
		else
		SET_BIT(PORTA,Pin_Index);
		break;
		
		case 1:
		if(Val==0)
		CLR_BIT(PORTB,Pin_Index);
		else
		SET_BIT(PORTB,Pin_Index);
		break;		

		case 2:
		if(Val==0)
		CLR_BIT(PORTC,Pin_Index);
		else
		SET_BIT(PORTC,Pin_Index);
		break;		

		case 3:
		if(Val==0)
		CLR_BIT(PORTD,Pin_Index);
		else
		SET_BIT(PORTD,Pin_Index);
		break;	
		
		default:
		break;
	}
}

void DIO_ReadPortVal(char Port_Num,char *Val)
{
	switch(Port_Num)
	{
		case 0:
		*Val=PINA;
		break;
		
		case 1:
		*Val=PINB;
		break;
		
		case 2:
		*Val=PINC;
		break;		
		
		case 3:
		*Val=PIND;
		break;		
		
		default:
		break;
	}
}


void DIO_ReadPinVal(char Pin_Num,char *Val)
{
	char Port_Num=Pin_Num/8;
	char Pin_Index=Pin_Num%8;
	switch(Port_Num)
	{
		case 0:
		*Val=GET_BIT(PINA,Pin_Index);
		
		#ifdef LONG_PRESS
		if(*Val==1)
		while(GET_BIT(PINA,Pin_Index));
		#endif		
		break;

		case 1:
		*Val=GET_BIT(PINB,Pin_Index);

		#ifdef LONG_PRESS
		if(*Val==1)
		while(GET_BIT(PINB,Pin_Index));
		#endif		
		break;
		
		case 2:
		*Val=GET_BIT(PINC,Pin_Index);
		
		#ifdef LONG_PRESS
		if(*Val==1)
		while(GET_BIT(PINC,Pin_Index));
		#endif		
		break;	
		
		case 3:
		*Val=GET_BIT(PIND,Pin_Index);
		
		#ifdef LONG_PRESS
		if(*Val==1)
		while(GET_BIT(PIND,Pin_Index));
		#endif
		break;			
		
		default:
		break;
	}
} 


void DIO_Init(char Pin_Num, PIN_DIRECTION_t pin_direction)
{
 char Port_Num=Pin_Num/8;
 char Pin_Index=Pin_Num%8;
 switch(Port_Num)
 {
  case 0:
   if (pin_direction == OUTPUT_DIR)
   {
	SET_BIT(DDRA,Pin_Index);   
   }
   else
   {
	CLR_BIT(DDRA,Pin_Index);   
   }
  break;
  case 1:
   if (pin_direction == OUTPUT_DIR)
   {
	SET_BIT(DDRB,Pin_Index);    
   }
   else
   {
	CLR_BIT(DDRB,Pin_Index);  
   }  
  break;
  case 2:
   if (pin_direction == OUTPUT_DIR)
   {
	SET_BIT(DDRC,Pin_Index); 
   }
   else
   {
	CLR_BIT(DDRC,Pin_Index);    
   }  
  break;
  case 3:
   if (pin_direction == OUTPUT_DIR)
   {
	SET_BIT(DDRD,Pin_Index); 
   }
   else
   {
	CLR_BIT(DDRD,Pin_Index);    
   }  
  break;	 
 }
 /*
	DDRA=DDRA_INIT;
	DDRB=DDRB_INIT;
	DDRC=DDRC_INIT;
	DDRD=DDRD_INIT;
	
	
	PORTA=PORTA_INIT;
	PORTB=PORTB_INIT;
	PORTC=PORTC_INIT;
	PORTD=PORTD_INIT;
 */
}