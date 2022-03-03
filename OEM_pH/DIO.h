/*
 * DIO.h
 *
 * Created: 4/22/2017 2:30:13 PM
 *  Author: A.Aboelmakarem
 */ 

#include <avr/io.h>
#include "My_lib.h"

typedef enum
{
 INPUT_DIR  = (uint8_t)0x00,
 OUTPUT_DIR	= (uint8_t)0x01,
	
}PIN_DIRECTION_t;

void DIO_WritePortVal(char Port_Num,char Val);
void DIO_WritePinVal(char Pin_Num, char Val);
void DIO_ReadPortVal(char Port_Num,char *Val);
void DIO_ReadPinVal(char Pin_Num,char *Val);
void DIO_Init(char Pin_Num, PIN_DIRECTION_t pin_direction);

/**********************Configuration****************/
#define DDRA_INIT    0b00000000
#define DDRB_INIT    0b01000000
#define DDRC_INIT    0b11111100
#define DDRD_INIT    0b00000000

#define PORTA_INIT   0b00000000
#define PORTB_INIT   0b00000000
#define PORTC_INIT   0b00000000
#define PORTD_INIT   0b00000000

#define LONG_PRESS

