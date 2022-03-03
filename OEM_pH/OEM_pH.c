/*
 * OEM_pH.c
 *
 * Created: 30-Nov-21 12:07:37 AM
 *  Author: Ahmed Lotfy
 */
/* ==============================================================================================================
                                             Include files
   ==============================================================================================================*/
//#include <util/delay.h> 
#include "My_lib.h"
#include "I2C.h"
//#include "DIO.h"
#include "External_interrupt.h"
#include "OEM_pH.h"

/* ==============================================================================================================
                                             Local Macros
   ==============================================================================================================*/
 /*!
  * This Macros depends on MC and can be modified for easy portability.
 */
#define OEM_pH_INITIALIZE_CLK_RATE(CLK_SPEED)                TWI_init(CLK_SPEED)
#define OEM_pH_GENREATE_START_BIT()                          TWI_Start()
#define OEM_pH_OPEN_WRITE_SESSION(ADDRESS)                   TWI_Write((uint8_t)(ADDRESS & (uint8_t)0xFE))
#define OEM_pH_OPEN_READ_SESSION(ADDRESS)                    TWI_Write((uint8_t)(ADDRESS | (uint8_t)0x01))
#define OEM_pH_SEND_REG_ADDRESS(REG_ADDR)                    TWI_Write(REG_ADDR)
#define OEM_pH_WRITE_REG_DATA(DATA)                          TWI_Write(DATA)
#define OEM_pH_READ_REG_DATA()                               TWI_ReadNACK()
#define OEM_pH_GENREATE_STOP_BIT()                           TWI_Stop()

#define OEM_pH_INTERRUPT_NUMBER                              INT00

/* ==============================================================================================================
                                             Variables deceleration
   ==============================================================================================================*/
static uint8_t device_address = DEFAULT_DEVICE_ADDRESS;
volatile float pH_level = 0.00;

/* ==============================================================================================================
                                             Static function prototypes
   ==============================================================================================================*/
/**
* This method used to write one byte value in a specific register .
* @author Ahmed Lotfy
* @param  reg_address: physical address of register 
* @param  reg_data   : data to be written.
* @return NONE
* @date   11/29/2021
*/
static void OEM_pH_iWriteReg_OneByte(uint8_t reg_address,uint8_t reg_data);
/**
* This method used to write four byte value in a specific register .
* @author Ahmed Lotfy
* @param  reg_address: physical address of register
* @param  reg_data   : data to be written.
* @return NONE
* @date   11/29/2021
*/
static void OEM_pH_iWriteReg_FourByte(uint8_t reg_address,uint32_t reg_data);
/**
* This method used to read one byte value from a specific register .
* @author Ahmed Lotfy
* @param  reg_address: physical address of register
* @return reg_data   : value of data after been read. 
* @date   11/29/2021
*/
static uint8_t OEM_pH_iReadReg_OneByte(uint8_t reg_address);
/**
* This method used to read four byte value from a specific register .
* @author Ahmed Lotfy
* @param  reg_address: physical address of register
* @return reg_data   : value of data after been read.
* @date   11/29/2021
*/
static uint32_t OEM_pH_iReadReg_FourByte(uint8_t reg_address);
/**
* This method used as a handler when the interrupt pin set to high .
* @author Ahmed Lotfy
* @param  reg_address: NONE
* @return reg_data   : NONE.
* @date   11/29/2021
*/
static void OEM_pH_iHandler_Highlevel_InterruptPin(void);
/**
* This method used as a handler when the interrupt pin set to low .
* @author Ahmed Lotfy
* @param  reg_address: NONE
* @return reg_data   : NONE.
* @date   11/29/2021
*/
static void OEM_pH_iHandler_Lowlevel_InterruptPin(void);
/**
* This method used as a handler when the interrupt pin invert the level .
* @author Ahmed Lotfy
* @param  reg_address: NONE
* @return reg_data   : NONE.
* @date   11/29/2021
*/
static void OEM_pH_iHandler_Invertlevel_InterruptPin(void);
/* ==============================================================================================================
                                             Global function definitions
   ==============================================================================================================*/
/**
* This method used to initialize OEM_pH sensor.
* @author Ahmed Lotfy
* @param  NONE.
* @return NONE.
* @date   11/29/2021
*/
void OEM_pH_gInit(void)
{
 OEM_pH_INITIALIZE_CLK_RATE(OEM_pH_SENSOR_CLK_RATE);
}
/**
* This method used to get the device type data.
* @author Ahmed Lotfy
* @param  NONE
* @return device type
* @date   11/29/2021
*/
uint8_t OEM_pH_gRead_DeviceType(void)
{
 uint8_t device_type = 0;
 device_type = OEM_pH_iReadReg_OneByte(DEVICE_TYPE_REG);		
 return device_type;	
}
/**
* This method used to get the firmware version number.
* @author Ahmed Lotfy
* @param  NONE
* @return FW version number
* @date   11/29/2021
*/
uint8_t OEM_pH_gRead_FW_VERSION(void)
{
 uint8_t fw_version = 0;
 fw_version = OEM_pH_iReadReg_OneByte(FIRMWARE_VERSION_REG);
 return fw_version;
}

/**
* This method used to handle the process of changing physical device address.
* @author Ahmed Lotfy
* @param  new_addr : value to be changed.
* @return Status for operation
* @date   11/29/2021
*/
STATUS_t OEM_pH_gModify_DeviceAddress(uint8_t new_addr)
{
 STATUS_t operation_status = SUCCESS;	
 uint8_t lock_status = LOCKED;
 
 new_addr = (uint8_t)(new_addr & (uint8_t)0x7f);
 OEM_pH_iWriteReg_OneByte(ADDRESS_LOCK_UNLOCK_REG,0x55);
 OEM_pH_iWriteReg_OneByte(ADDRESS_LOCK_UNLOCK_REG,0xAA);
 lock_status = OEM_pH_iReadReg_OneByte(ADDRESS_LOCK_UNLOCK_REG);
 if (lock_status == UNLOCKED)
 {
  OEM_pH_iWriteReg_OneByte(ADDRESS_REG,new_addr);	
  lock_status = OEM_pH_iReadReg_OneByte(ADDRESS_LOCK_UNLOCK_REG);
  device_address = OEM_pH_iReadReg_OneByte(ADDRESS_REG);
  if ((lock_status == UNLOCKED) || (device_address != new_addr))
   operation_status = ERROR;
 }
 else
  operation_status = ERROR;
  
 return operation_status;  
}
/**
* This method used to configure interrupt pin with action when new reading is available.
* @author Ahmed Lotfy
* @param  pin_config : configuration for pin.
* @return NONE
* @date   11/29/2021
*/
void OEM_pH_gConfigure_InterruptPin_With_NewReading(OEM_pH_INTERUPT_PIN_CONFIG_t pin_config)
{
 switch (pin_config)
 {
  case PIN_DISABLED:
   OEM_pH_iWriteReg_OneByte(INTERRUPT_CONTROL_REG,PIN_DISABLED);
  break;
  	 
  case PIN_SET_HIGH_NEW_READING:
   OEM_pH_iWriteReg_OneByte(INTERRUPT_CONTROL_REG,PIN_SET_HIGH_NEW_READING);
   Externalnterrupt_gInit(OEM_pH_INTERRUPT_NUMBER, RISING_EDGE, OEM_pH_iHandler_Highlevel_InterruptPin);
  break;
  
  case PIN_SET_LOW_NEW_READING:
   OEM_pH_iWriteReg_OneByte(INTERRUPT_CONTROL_REG,PIN_SET_LOW_NEW_READING);
   Externalnterrupt_gInit(OEM_pH_INTERRUPT_NUMBER, FALLING_EDGE, OEM_pH_iHandler_Lowlevel_InterruptPin);
  break;
  
  case PIN_INVERT_STATE_NEW_READING:
   OEM_pH_iWriteReg_OneByte(INTERRUPT_CONTROL_REG,PIN_INVERT_STATE_NEW_READING);
   Externalnterrupt_gInit(OEM_pH_INTERRUPT_NUMBER, LOGICAL_CHANGE, OEM_pH_iHandler_Invertlevel_InterruptPin);
  break;	 
 }	
}
/**
* This method used to control the led pin action when a new reading is taken.
* @author Ahmed Lotfy
* @param  led_action : action be applied on LED.
* @return NONE
* @date   11/29/2021
*/
void OEM_pH_gConfigureLed_ReadTaken(OEM_pH_LED_PIN_CONFIG_t led_action)
{
 OEM_pH_iWriteReg_OneByte(LED_CONTROL_REG,led_action);
}
/**
* This method used to put the device in active mode or hibernate mode.
* @author Ahmed Lotfy
* @param  state : state to be changed.
* @return NONE
* @date   11/29/2021
*/
void OEM_pH_gChangeState(OEM_pH_STATE_t state)
{	
 OEM_pH_iWriteReg_OneByte(ACTIVE_HIBERNATE_REG,state);
}
/**
* This method used to check if there is an available reading by polling.
* @author Ahmed Lotfy
* @param  None.
* @return status of check
* @date   11/29/2021
*/
STATUS_t OEM_pH_gCheck_NewReading_Available(void)
{
 STATUS_t reading_ready_state = ERROR;
 
 if (OEM_pH_iReadReg_OneByte(NEW_READING_AVAILABLE_REG))
  reading_ready_state = SUCCESS;
 
 return reading_ready_state;
}
/**
* This method used to clear ready available register after been set and read is taken.
* @author Ahmed Lotfy
* @param  None.
* @return None.
* @date   11/29/2021
*/
void OEM_pH_gClear_ReadingAvailable_Register(void)
{
 OEM_pH_iWriteReg_OneByte(NEW_READING_AVAILABLE_REG,0);	
}
/**
* This method used to set a calibration value.
* @author Ahmed Lotfy
* @param  calibration_value : value to be set.
* @return NONE
* @date   11/29/2021
*/
void OEM_pH_gSet_CalibrationValue(float calibration_value)
{
 uint32 integer_calib_val = (uint32_t)(calibration_value * ((uint32_t)1000));
 OEM_pH_iWriteReg_FourByte(CALIBRATION_MSB_REG,integer_calib_val);	
}

/**
* This method used to request the calibration to start with some value with an action for calibration request.
* @author Ahmed Lotfy
* @param  calibration_value : value to calibration to be set.
* @param  action            : calibration action for calibration request
* @return NONE
* @date   11/29/2021
*/
void OEM_pH_gRequest_Calibration(float calibration_value, CALIBRATION_ACTION_t action)
{
  OEM_pH_gSet_CalibrationValue(calibration_value);
  OEM_pH_iWriteReg_FourByte(CALIBRATION_REQUEST_REG,action);
}
/**
* This method used to check if the calibration request is handled successfully or not.
* @author Ahmed Lotfy
* @param  calibration_value : value to calibration to be set.
* @return status of operation
* @date   11/29/2021
*/
STATUS_t OEM_pH_gCheck_CalibrationFinish(CALIBRATION_ACTION_t action)
{
 uint8_t calibration_point_status = 0;
 STATUS_t calib_finish_state = ERROR;

 calibration_point_status = OEM_pH_iReadReg_OneByte(CALIBRATION_CONFIRMATION_REG);
 switch (action)
 {
  case CLEAR_CALIB_DATA:
   if(calibration_point_status  == 0x00)
    calib_finish_state = SUCCESS;
  break;
  
  case LOW_POINT_CALIB:
   if(calibration_point_status & CALIBERATION_LOW_POINT_FINISH_MASK)
    calib_finish_state = SUCCESS;
  break;
  
  case MIDDLE_POINT_CALIB:
   if(calibration_point_status & CALIBERATION_MIDDLE_POINT_FINISH_MASK)
   calib_finish_state = SUCCESS;
  break;
  
  case HIGH_POINT_CALIB:
   if(calibration_point_status & CALIBERATION_HIGH_POINT_FINISH_MASK)
    calib_finish_state = SUCCESS;
  break;	 
 }
 
 return calib_finish_state;
}
/**
* This method used to set a temperature compensated pH reading.
* @author Ahmed Lotfy
* @param  temp : temperature degree to Be set.
* @return NONE
* @date   11/29/2021
*/
void OEM_pH_gSet_TempratureValue(float temp)
{
 uint32 integer_temp = (uint32_t)(temp * ((uint32_t)100));
 OEM_pH_iWriteReg_FourByte(TEMPERATURE_SET_MSB_REG,integer_temp);
}
/**
* This method used to get the temperature compensated pH reading.
* @author Ahmed Lotfy
* @param  NONE.
* @return temperature degree.
* @date   11/29/2021
*/
float OEM_pH_gGet_TempratureValue(void)
{
 uint32 integer_temp = OEM_pH_iReadReg_FourByte(TEMPERATURE_CONFIRMATION_MSB_REG);
 float temp = (float)((float)integer_temp / (float)100.00);
 return temp;
}
/**
* This method used to get the last pH reading from the sensor.
* @author Ahmed Lotfy
* @param  NONE.
* @return pH reading.
* @date   11/29/2021
*/
float OEM_pH_gGet_pHValue(void)
{
 uint32 integer_pH = OEM_pH_iReadReg_FourByte(pH_READING_MSB_REG);
 pH_level = (float)((float)integer_pH / (float)1000.00);
 return pH_level;
}

/* ==============================================================================================================
                                             Static function definitions
   ==============================================================================================================*/
/**
* This method used to write one byte value in a specific register .
* @author Ahmed Lotfy
* @param  reg_address: physical address of register
* @param  reg_data   : data to be written.
* @return NONE
* @date   11/29/2021
*/
static void OEM_pH_iWriteReg_OneByte(uint8_t reg_address,uint8_t reg_data)
{
 OEM_pH_GENREATE_START_BIT();
 OEM_pH_OPEN_WRITE_SESSION(device_address);
 OEM_pH_SEND_REG_ADDRESS(reg_address);
 OEM_pH_WRITE_REG_DATA(reg_data);
 OEM_pH_GENREATE_STOP_BIT();
}
/**
* This method used to write four byte value in a specific register .
* @author Ahmed Lotfy
* @param  reg_address: physical address of register
* @param  reg_data   : data to be written.
* @return NONE
* @date   11/29/2021
*/
static void OEM_pH_iWriteReg_FourByte(uint8_t reg_address,uint32_t reg_data)
{
 OEM_pH_GENREATE_START_BIT();
 OEM_pH_OPEN_WRITE_SESSION(device_address);
 OEM_pH_SEND_REG_ADDRESS(reg_address);
 OEM_pH_WRITE_REG_DATA((uint8_t)(reg_data >> 24));
 OEM_pH_WRITE_REG_DATA((uint8_t)(reg_data >> 16));
 OEM_pH_WRITE_REG_DATA((uint8_t)(reg_data >> 8));
 OEM_pH_WRITE_REG_DATA((uint8_t)reg_data);
 OEM_pH_GENREATE_STOP_BIT();
}
/**
* This method used to read one byte value from a specific register .
* @author Ahmed Lotfy
* @param  reg_address: physical address of register
* @return reg_data   : value of data after been read.
* @date   11/29/2021
*/
static uint8_t OEM_pH_iReadReg_OneByte(uint8_t reg_address)
{
 uint8_t reg_data = 0;
	
 OEM_pH_GENREATE_START_BIT();
 OEM_pH_OPEN_WRITE_SESSION(device_address);
 OEM_pH_SEND_REG_ADDRESS(reg_address);
 OEM_pH_GENREATE_STOP_BIT();
	
 OEM_pH_GENREATE_START_BIT();
 OEM_pH_OPEN_READ_SESSION(device_address);
 reg_data = OEM_pH_READ_REG_DATA();
 OEM_pH_GENREATE_STOP_BIT();

 return reg_data;
}
/**
* This method used to read four byte value from a specific register .
* @author Ahmed Lotfy
* @param  reg_address: physical address of register
* @return reg_data   : value of data after been read.
* @date   11/29/2021
*/
static uint32_t OEM_pH_iReadReg_FourByte(uint8_t reg_address)
{
 uint8_t reg_data = 0;
 uint32_t integer_reg_data = 0;
	
 OEM_pH_GENREATE_START_BIT();
 OEM_pH_OPEN_WRITE_SESSION(device_address);
 OEM_pH_SEND_REG_ADDRESS(reg_address);
 OEM_pH_GENREATE_STOP_BIT();
	
 OEM_pH_GENREATE_START_BIT();
 OEM_pH_OPEN_READ_SESSION(device_address);
 reg_data = OEM_pH_READ_REG_DATA();
 integer_reg_data |= (uint32_t)((uint32_t)reg_data << 24);
 reg_data = OEM_pH_READ_REG_DATA();
 integer_reg_data |= (uint32_t)((uint32_t)reg_data << 16);
 reg_data = OEM_pH_READ_REG_DATA();
 integer_reg_data |= (uint32_t)((uint32_t)reg_data << 8);
 reg_data = OEM_pH_READ_REG_DATA();
 integer_reg_data |= (uint32_t)reg_data;
 OEM_pH_GENREATE_STOP_BIT();

 return integer_reg_data;
} 
/**
* This method used as a handler when the interrupt pin set to high .
* @author Ahmed Lotfy
* @param  reg_address: NONE
* @return reg_data   : NONE.
* @date   11/29/2021
*/
static void OEM_pH_iHandler_Highlevel_InterruptPin(void)
{
 pH_level = OEM_pH_gGet_pHValue();
 OEM_pH_iWriteReg_OneByte(INTERRUPT_CONTROL_REG,PIN_SET_HIGH_NEW_READING);	
}
/**
* This method used as a handler when the interrupt pin set to low .
* @author Ahmed Lotfy
* @param  reg_address: NONE
* @return reg_data   : NONE.
* @date   11/29/2021
*/
static void OEM_pH_iHandler_Lowlevel_InterruptPin(void)
{
 pH_level = OEM_pH_gGet_pHValue();
 OEM_pH_iWriteReg_OneByte(INTERRUPT_CONTROL_REG,PIN_SET_LOW_NEW_READING);	
}
	
/**
* This method used as a handler when the interrupt pin invert the level .
* @author Ahmed Lotfy
* @param  reg_address: NONE
* @return reg_data   : NONE.
* @date   11/29/2021
*/
static void OEM_pH_iHandler_Invertlevel_InterruptPin(void)
{
 pH_level = OEM_pH_gGet_pHValue();	
}