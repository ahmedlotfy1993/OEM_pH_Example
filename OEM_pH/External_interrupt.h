/*
 * External_interrupt.h
 *
 * Created: 1/24/2018 4:23:34 PM
 * Author : iti
 */ 
#include "My_lib.h"
#define PB02_PIN_NUM  (uint8_t)10
#define PD02_PIN_NUM  (uint8_t)24
#define PD03_PIN_NUM  (uint8_t)25
typedef enum
{
 INT00 = (uint8_t)0x00,
 INT01 = (uint8_t)0x01,	
 INT02 = (uint8_t)0x02,		
}INT_TYPE_t;

typedef enum
{
 LOW_LEVEL       = (uint8_t)0x00,
 LOGICAL_CHANGE  = (uint8_t)0x01,
 FALLING_EDGE    = (uint8_t)0x02, 
 RISING_EDGE     = (uint8_t)0x03	
}EDGE_TYPE_t;
void Externalnterrupt_gInit(INT_TYPE_t int_type, EDGE_TYPE_t edge_type, void(*pfunc)(void));