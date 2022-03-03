/*
 * OEM_pH.h
 *
 * Created: 30-Nov-21 12:08:02 AM
 *  Author: Ahmed Lotfy
 */ 


#ifndef OEM_PH_H_
#define OEM_PH_H_
/* ==============================================================================================================
                                             Include files
   ==============================================================================================================*/
#include "My_lib.h"
#include "OEM_pH_conf.h"
/* ==============================================================================================================
                                             Global Macros
   ==============================================================================================================*/
#define UNLOCKED  ((uint8_t)0x00)
#define LOCKED    ((uint8_t)0x01)

#define CALIBERATION_LOW_POINT_FINISH_MASK       (uint8_t)0x01
#define CALIBERATION_MIDDLE_POINT_FINISH_MASK    (uint8_t)0x02
#define CALIBERATION_HIGH_POINT_FINISH_MASK      (uint8_t)0x04
/* ==============================================================================================================
                                             New types decelerations
   ==============================================================================================================*/
typedef enum
{
 ERROR   = (uint8_t)0x00,
 SUCCESS = (uint8_t)0x01
}STATUS_t;

typedef enum
{
 PIN_DISABLED                 = (uint8_t)0x00,
 PIN_SET_HIGH_NEW_READING     = (uint8_t)0x02,
 PIN_SET_LOW_NEW_READING      = (uint8_t)0x04,
 PIN_INVERT_STATE_NEW_READING = (uint8_t)0x08	
}OEM_pH_INTERUPT_PIN_CONFIG_t;

typedef enum
{
 LED_DISABLED          = (uint8_t)0x00,
 LED_BLINK_NEW_READING = (uint8_t)0x01,	
}OEM_pH_LED_PIN_CONFIG_t;

typedef enum
{
 HIBERNATE_STATE = (uint8_t)0x00,
 ACTIVE_STATE    = (uint8_t)0x01,	
}OEM_pH_STATE_t;

typedef enum
{
 CLEAR_CALIB_DATA          = (uint8_t)0x01,	
 LOW_POINT_CALIB           = (uint8_t)0x02,
 MIDDLE_POINT_CALIB        = (uint8_t)0x03,
 HIGH_POINT_CALIB          = (uint8_t)0x04,
}CALIBRATION_ACTION_t;

/* ==============================================================================================================
                                             Global function prototypes
   ==============================================================================================================*/
/**
* This method used to initialize OEM_pH sensor.
* @author Ahmed Lotfy
* @param  NONE.
* @return NONE.
* @date   11/29/2021
*/
void OEM_pH_gInit(void);
/**
* This method used to get the device type data.
* @author Ahmed Lotfy
* @param  NONE
* @return device type
* @date   11/29/2021
*/
uint8_t OEM_pH_gRead_DeviceType(void);
/**
* This method used to get the firmware version number.
* @author Ahmed Lotfy
* @param  NONE
* @return FW version number
* @date   11/29/2021
*/
uint8_t OEM_pH_gRead_FW_VERSION(void);
/**
* This method used to handle the process of changing physical device address.
* @author Ahmed Lotfy
* @param  new_addr : value to be changed.
* @return Status for operation
* @date   11/29/2021
*/
STATUS_t OEM_pH_gModify_DeviceAddress(uint8_t new_addr);
/**
* This method used to configure interrupt pin with action when new reading is available.
* @author Ahmed Lotfy
* @param  pin_config : configuration for pin.
* @return NONE
* @date   11/29/2021
*/
void OEM_pH_gConfigure_InterruptPin_With_NewReading(OEM_pH_INTERUPT_PIN_CONFIG_t pin_config);
/**
* This method used to control the led pin action when a new reading is taken.
* @author Ahmed Lotfy
* @param  led_action : action be applied on LED.
* @return NONE
* @date   11/29/2021
*/
void OEM_pH_gConfigureLed_ReadTaken(OEM_pH_LED_PIN_CONFIG_t led_action);
/**
* This method used to put the device in active mode or hibernate mode.
* @author Ahmed Lotfy
* @param  state : state to be changed.
* @return NONE
* @date   11/29/2021
*/
void OEM_pH_gChangeState(OEM_pH_STATE_t state);
/**
* This method used to check if there is an available reading by polling.
* @author Ahmed Lotfy
* @param  None.
* @return status of check
* @date   11/29/2021
*/
STATUS_t OEM_pH_gCheck_NewReading_Available(void);
/**
* This method used to clear ready available register after been set and read is taken.
* @author Ahmed Lotfy
* @param  None.
* @return None.
* @date   11/29/2021
*/
void OEM_pH_gClear_ReadingAvailable_Register(void);
/**
* This method used to set a calibration value.
* @author Ahmed Lotfy
* @param  calibration_value : value to be set.
* @return NONE
* @date   11/29/2021
*/
void OEM_pH_gSet_CalibrationValue(float calibration_value);
/**
* This method used to request the calibration to start with some value with an action for calibration request.
* @author Ahmed Lotfy
* @param  calibration_value : value to calibration to be set.
* @param  action            : calibration action for calibration request
* @return NONE
* @date   11/29/2021
*/
void OEM_pH_gRequest_Calibration(float calibration_value, CALIBRATION_ACTION_t action);
/**
* This method used to check if the calibration request is handled successfully or not.
* @author Ahmed Lotfy
* @param  calibration_value : value to calibration to be set.
* @return status of operation
* @date   11/29/2021
*/
STATUS_t OEM_pH_gCheck_CalibrationFinish(CALIBRATION_ACTION_t action);
/**
* This method used to set a temperature compensated pH reading.
* @author Ahmed Lotfy
* @param  temp : temperature degree to Be set.
* @return NONE
* @date   11/29/2021
*/
void OEM_pH_gSet_TempratureValue(float temp);
/**
* This method used to get the temperature compensated pH reading.
* @author Ahmed Lotfy
* @param  NONE.
* @return temperature degree.
* @date   11/29/2021
*/
float OEM_pH_gGet_TempratureValue(void);
/**
* This method used to get the last pH reading from the sensor.
* @author Ahmed Lotfy
* @param  NONE.
* @return pH reading.
* @date   11/29/2021
*/
float OEM_pH_gGet_pHValue(void);



#endif /* OEM_PH_H_ */