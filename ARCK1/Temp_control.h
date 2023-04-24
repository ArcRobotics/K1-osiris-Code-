#ifndef Temp_control_H
#define Temp_control_H

void Read_temp()
{
    bool fire_was_on=false;
    if(delay_period==250){
      float val=0;
      val = analogRead(Temp_sensor_pin);
      float mv = ( val/1024.0)*5000;
      float cel = mv/10;
      String Temp_post="TEMPRATURE = "+String(cel)+"C";
      Serial.println(Temp_post); 
      delay_period=0;
      
      if(cel>50){
        while(cel>50)
        {
          val = analogRead(Temp_sensor_pin);
          mv = ( val/1024.0)*5000;
          cel = mv/10;
          Temp_post="TEMPRATURE = "+String(cel)+"C";
          Serial.println(Temp_post); 
          Fans_on
          buzzer_on;
          delay(2000);
          buzzer_off;
          delay(500);
          Disable_all
          fire_was_on=true;
        }
      }
      else if(fire_was_on)Fans_off;
    }
}
#endif
