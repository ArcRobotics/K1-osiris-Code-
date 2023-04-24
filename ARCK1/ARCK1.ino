#include "Osiris.h"
#include "Inverse_Kinmatics.h"
void setup() {
 Start_K1_Osiris();
 delay(20);
 Serial.println("Robot Started");
/* pinMode(53,INPUT_PULLUP);
 pinMode(52,INPUT_PULLUP);
 pinMode(51,INPUT_PULLUP);
 pinMode(49,INPUT_PULLUP);
 pinMode(47,INPUT_PULLUP);*/
 calculate_ik(230.0,100.0,230.0,0.0,90.0,0.0,false);
}

void loop() {
  //Receive_data();   
 // calculate_ik(230.0,100.0,230.0,0.0,90.0,0.0,false);
  }
  
   //int INPUT_pins_status=0;
    /*
     * Serial.println("Robot Started");
  if(digitalRead(INPUT_pins[0])==0)INPUT_pins_status=1;
  if(digitalRead(INPUT_pins[1])==0)INPUT_pins_status=2;
  if(digitalRead(INPUT_pins[2])==0)INPUT_pins_status=3;
  if(digitalRead(INPUT_pins[3])==0)INPUT_pins_status=4;
  if(digitalRead(INPUT_pins[4])==0)INPUT_pins_status=5;
  if(digitalRead(INPUT_pins[5])==0)INPUT_pins_status=6;
  if(digitalRead(INPUT_pins[6])==0)INPUT_pins_status=7;
  if(digitalRead(INPUT_pins[7])==0)INPUT_pins_status=8;
  Serial.println("INPUT_pins_status="+String(INPUT_pins_status));
  delay(100);*/


  /*
  if(digitalRead(52)==0)Serial.println(1);
  if(digitalRead(53)==0)Serial.println(2);
  if(digitalRead(51)==0)Serial.println(3);
  if(digitalRead(49)==0)Serial.println(4);
  if(digitalRead(47)==0)Serial.println(5);
  //Serial1.println(limit_status);
  delay(100);*/
