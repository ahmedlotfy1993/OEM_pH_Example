/*
 * OEM_pH.c
 *
 * Created: 30-Nov-21 12:23:14 AM
 * Author : Ahmed Lotfy
 */ 

#include "My_lib.h"
#include <avr/io.h>
#include <util/delay.h>
#include "OEM_pH.h"
int main(void)
{
 OEM_pH_gInit();
 OEM_pH_gConfigure_InterruptPin_With_NewReading(PIN_DISABLED);
 OEM_pH_gConfigureLed_ReadTaken(LED_BLINK_NEW_READING);
 OEM_pH_gRequest_Calibration(FIRST_CALIBRATION_POINT,MIDDLE_POINT_CALIB);
 OEM_pH_gChangeState(ACTIVE_STATE);
 while (1) 
 {
  while(OEM_pH_gCheck_CalibrationFinish(MIDDLE_POINT_CALIB) == ERROR);

   if(OEM_pH_gCheck_NewReading_Available() == SUCCESS)
   {
    OEM_pH_gGet_pHValue();
    OEM_pH_gClear_ReadingAvailable_Register();
   }
 }
}

