/*
 * My_lib.h
 *
 * Created: 7/25/2018 10:21:31 PM
 *  Author: Ahmed Lotfy
 */ 


#ifndef MY_LIB_H_
#define MY_LIB_H_
#define F_CPU 8000000UL
typedef unsigned char     uint8;       //0-255
typedef unsigned int      uint16;     //0-65535
typedef signed char       sint8;     // (-128)-127
typedef signed int        sint16;   //(-32768)-32767
typedef unsigned long int uint32;  //0-4294967295
typedef signed long int   sint32; //(-2147483648)-2147483647

#define SET_BIT(reg,bitnum) reg|=(1<<bitnum)
#define CLR_BIT(reg,bitnum) reg&=~(1<<bitnum)
#define GET_BIT(reg,bitnum) (reg & (1<<bitnum))>>bitnum //((PINA & (1<<PA0))>>PA0)
#define TOOGLE_BIT(reg,bitnum) reg^=(1<<bitnum)



#endif /* MY_LIB_H_ */