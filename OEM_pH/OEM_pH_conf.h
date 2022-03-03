/*
 * OEM_pH_conf.h
 *
 * Created: 30-Nov-21 12:07:11 AM
 *  Author: Ahmed Lotfy
 */ 


#ifndef OEM_PH_CONF_H_
#define OEM_PH_CONF_H_
#include "My_lib.h"

#define DEFAULT_DEVICE_ADDRESS                        (uint8_t)0x65
#define OEM_pH_SENSOR_CLK_RATE                        (uint32_t)100000
#define FIRST_CALIBRATION_POINT                       (float)7.00

#define DEVICE_TYPE_REG                               (uint8_t)0x00
#define FIRMWARE_VERSION_REG                          (uint8_t)0x01
#define ADDRESS_LOCK_UNLOCK_REG                       (uint8_t)0x02
#define ADDRESS_REG                                   (uint8_t)0x03
#define INTERRUPT_CONTROL_REG                         (uint8_t)0x04
#define LED_CONTROL_REG                               (uint8_t)0x05
#define ACTIVE_HIBERNATE_REG                          (uint8_t)0x06
#define NEW_READING_AVAILABLE_REG                     (uint8_t)0x07
#define CALIBRATION_MSB_REG                           (uint8_t)0x08
#define CALIBRATION_HIGH_BYTE_REG                     (uint8_t)0x09
#define CALIBRATION_LOW_BYTE_REG                      (uint8_t)0x0A
#define CALIBRATION_LSB_REG                           (uint8_t)0x0B
#define CALIBRATION_REQUEST_REG                       (uint8_t)0x0C 
#define CALIBRATION_CONFIRMATION_REG                  (uint8_t)0x0D
#define TEMPERATURE_SET_MSB_REG                       (uint8_t)0x0E 
#define TEMPERATURE_SET_HIGH_BYTE_REG                 (uint8_t)0x0F
#define TEMPERATURE_SET_LOW_BYTE_REG                  (uint8_t)0x10
#define TEMPERATURE_SET_LSB_REG                       (uint8_t)0x11
#define TEMPERATURE_CONFIRMATION_MSB_REG              (uint8_t)0x12
#define TEMPERATURE_CONFIRMATION_HIGH_BYTE_REG        (uint8_t)0x13
#define TEMPERATURE_CONFIRMATION_LOW_BYTE_REG         (uint8_t)0x14
#define TEMPERATURE_CONFIRMATION_LSB_REG              (uint8_t)0x15
#define pH_READING_MSB_REG                            (uint8_t)0x16
#define pH_READING_HIGH_BYTE_REG                      (uint8_t)0x17
#define pH_READING_LOW_BYTE_REG                       (uint8_t)0x18
#define pH_READING_LSB_REG                            (uint8_t)0x19




#endif /* OEM_PH_CONF_H_ */