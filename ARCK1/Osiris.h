#ifndef Osiris_H
#define Osiris_H

#define Debug 0

#define Test_controller_pins 1

/***************************************************************************/
//-------------------------------------------------------------------------//
#define Has_Axis6 1
#define Has_Axis7 0

#define Baurd_rate_1 115200
 
//-------------------------------------------------------------------------//
#define Has_Wireless_connection 1

#if Has_Wireless_connection
  #define Baurd_rate_3 115200
#endif 

//-------------------------------------------------------------------------//
//Pins definetions 
#define servo_pin A8
#define Fans 12
#define buzzer 3
#define buzzer_off digitalWrite(buzzer,LOW);
#define buzzer_on  digitalWrite(buzzer,HIGH);
#define Fans_on   digitalWrite(12,HIGH);
#define Fans_off  digitalWrite(12,LOW);

//-------------------------------------------------------------------------//
#define Has_temp_sensor 1

#if Has_temp_sensor
  #define Temp_sensor_pin A0
#endif

//-------------------------------------------------------------------------//
#define Has_more_inputs 1

#if Has_more_inputs
  uint8_t INPUT_pins[]={23,27,29,31,35,37,25,33};
#else
  uint8_t INPUT_pins[]={29,27,23,25,31};
#endif
uint8_t Output_pins[]={39,41,43,45};
//old output pins
//uint8_t Output_pins[]={33,35,37,41};
uint8_t Out_pins_status=0;
//-------------------------------------------------------------------------//

#include "Pins.h"
#include "Timers.h"
#include "Serial.h"
#include <Servo.h>
#include <Wire.h>
#include "HAL.h"
#include "Enocder.h"
#include "Temp_control.h"
#include "Gripper.h"
#include "Robot_predef.h"
#include "Accel.h"
#include "Motion_controller.h"
#include "M_codes.h"
#include "M_codes_interpreter.h"
#include "G_codes.h"
#include "G_codes_interpreter.h"
#include "Acode_interpreter.h"
#include "CMD_interpreter.h"
#include "CMD_parser.h"
#endif
