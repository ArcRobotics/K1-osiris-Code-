#ifndef M_codes_H
#define M_codes_H
//*********************----------prototypes----------*********************//
void M18();//Gripper disable
void M19();//Gripper enable 
void M20();//Gripper close
void M21();//Gripper open
void M22();//Fans_on
void M23();//Fans_off
void M24();//Valve on
void M25();//Valve off
void M31();//Enable All Motors
void M32();//Disable All
void M33();//Buzzer
void M34();
void M35(char cmd[]);//Delay (Time)
void M36(char cmd[]);//wait for input
void M37(char cmd[]);//Get input value
void M42(char cmd[]); //Set DI/O
void M43(char cmd[]);
void M101();//Set A1 acceleration
void M102();//
void M103();//
void M104();//
void M105();//
void M106();//Homing
void M107();//Go home
void M108();//init servo()
void M109();//dis servo()
void M110(char cmd[]);
void M119();
void M300(char cmd[]);
/**************************************************************************/
void M18()
{
  //Gripper_Disable();
 }
/**************************************************************************/
void M19()
{
  //Gripper_Enable();
 }
/**************************************************************************/
void M20()
{//close_gripper
 close_gripper();
}
/**************************************************************************/
void M21()
{ //open_gripper
 open_gripper();
}
/**************************************************************************/
void M22()
{//Open_pump
Fans_on;
}
/**************************************************************************/
void M31()
{ //Enable all
  Fans_on;
  Enable_all;
}
/**************************************************************************/
void M32()
{ //Disable all
  Fans_off;
  Disable_all;
}
/**************************************************************************/
void M33()
{//Buzzer
//  buzz_duo(3);
    buzzer_on;
    delay(150);
    buzzer_off;
}
/**************************************************************************/
void M35(char cmd[])
{   //Delay
  char *t;
  int time_delay=0;
  
  t=strchr(cmd,'T');   //Get the command number
  if(t!=NULL)time_delay=atoi(t+1);
  for(int i=0;i<time_delay;i++)
  {
    _delay_ms(1);
  }
}
//--------------------------------------------------------------------------//
void M36(char cmd[])
{ 
  char *p;
  int pin=0;
  
  p=strchr(cmd,'P');   //Get the command number
  if(p!=NULL)pin=atoi(p+1);
  
  #if Debug == 1
    Serial.println(pin);
  #endif
  //wait until certain input is triggered
  while(digitalRead(INPUT_pins[pin])==1);
}
//--------------------------------------------------------------------------//
void M42(char cmd[])//Set or clear I/O pinouts
{
  char *I;
  char *S;
  uint8_t pin;
  uint16_t state;
  char data[8];
  
  I=strchr(cmd,'I');   //Get the pin number
  if(I!=NULL)pin=atoi(I+1);  

  S=strchr(cmd,'S');   //Get the pin number
  if(S!=NULL)state=atoi(S+1); 
  
  if (pin==6 && state==1)
  {
    for(uint8_t k=0;k<(sizeof(Output_pins)/sizeof(Output_pins[0]));k++){
      digitalWrite(Output_pins[k],LOW);
    }
    Out_pins_status+=4;
  }
  else 
  {
      if (pin==6 && state==0)
      {
      for(uint8_t k=0;k<(sizeof(Output_pins)/sizeof(Output_pins[0]));k++){
        digitalWrite(Output_pins[k],HIGH);
      }
      Out_pins_status=0;
    }
    else {
      digitalWrite(Output_pins[pin],state);
       if(state==1)Out_pins_status+=pin;
       else Out_pins_status-=pin;
    }

  }
}
//--------------------------------------------------------------------------//
void M43(char cmd[])//Get input switch readings
{
  int8_t INPUT_pins_status=0;
  if(digitalRead(INPUT_pins[1])==0)INPUT_pins_status+=1;
  if(digitalRead(INPUT_pins[2])==0)INPUT_pins_status+=2;
  if(digitalRead(INPUT_pins[3])==0)INPUT_pins_status+=4;
  if(digitalRead(INPUT_pins[4])==0)INPUT_pins_status+=8;
  if(digitalRead(INPUT_pins[5])==0)INPUT_pins_status+=15;
  if(digitalRead(INPUT_pins[6])==0)INPUT_pins_status+=32;
  Serial1.println(INPUT_pins_status);
  
  #if Debug == 1
    Serial.println(INPUT_pins_status);
  #endif
}
//--------------------------------------------------------------------------//
/*
void M101(char cmd[])
{
  char *f;
  float speed_multiplyer=0;
  
  f=strchr(cmd,'F');   //Get the command number
  if(f!=NULL)speed_multiplyer=atoi(f+1);
  Axis1.Set_acceleration(&speed_multiplyer);  
}
//--------------------------------------------------------------------------//
void M102(char cmd[])
{
  char *f;
  float speed_multiplyer=0;
    
  f=strchr(cmd,'F');   //Get the command number
  if(f!=NULL)speed_multiplyer=atoi(f+1);
  Axis2.Set_acceleration(&speed_multiplyer);
}
//--------------------------------------------------------------------------//
void M103(char cmd[])
{
  char *f;
  float speed_multiplyer=0;
  
  f=strchr(cmd,'F');   //Get the command number
  if(f!=NULL)speed_multiplyer=atoi(f+1);
  Axis3.Set_acceleration(&speed_multiplyer);
}
//--------------------------------------------------------------------------//
void M104(char cmd[])
{
  char *f;
  float speed_multiplyer=0;
  
  f=strchr(cmd,'F');   //Get the command number
  if(f!=NULL)speed_multiplyer=atoi(f+1);
  Axis4.Set_acceleration(&speed_multiplyer);
}
//--------------------------------------------------------------------------//
void M105(char cmd[])
{
  char *f;
  float speed_multiplyer=0;
  
  f=strchr(cmd,'F');   //Get the command number
  if(f!=NULL)speed_multiplyer=atoi(f+1);
  Axis5.Set_acceleration(&speed_multiplyer);
}*/
//--------------------------------------------------------------------------//

void M106()
{//Axis Homing
  
  uint16_t delay_amount=150;
  uint16_t delay_amount2=160;

  int8_t a1;
  int8_t a2;
  int8_t a3;
  int8_t a5;
  
  //clear limit switch flag
  bool A1_status=false;
  bool A2_status=false;
  bool A3_status=false;
  bool A4_status=false;
  bool A5_status=false;

  initalize_robot_speed_paramters();  
  //clear previous position
  Axis5.P_steps=0;
  Axis1.P_steps=0;
  Axis2.P_steps=0;
  Axis3.P_steps=0;
  
  Homming=true;
  Enable_all;
  
  //Move the axis away from the limit switch first
  A1_Dir(1);//+Ve dir
  A2_Dir(-1);//+Ve dir
  A3_Dir(1);//+Ve dir
  A5_Dir(1);//+Ve dir
  if((Limit1_PIN&(1<<Limit_1))==0){a1=30;}
  else  {a1=0;}
  
  if((Limit2_PIN&(1<<Limit_2))==0){a2=30;}
  else  {a2=0;}
  
  if((Limit3_PIN&(1<<Limit_3))==0){a3=-35;}
  else  {a3=0;}
  
  if((Limit5_PIN&(1<<Limit_5))==0){a5=30;}
  else  {a5=0;}
  
  Go_to(a1,a2,a3,0,a5,0);
  
  
  Axis1.P_steps=0;
  Axis2.P_steps=0;
  Axis3.P_steps=0;
  Axis4.P_steps=0;
  Axis5.P_steps=0;

  A1_Dir(-1);//-Ve dir
  A2_Dir(1);//-Ve dir
  A3_Dir(-1);//-Ve dir
  A4_Dir(1);//-Ve dir
  A5_Dir(-1);//-Ve dir
  
  while(A1_status==false || A2_status==false || A3_status==false || A5_status==false)
  {
    if((Limit1_PIN&(1<<Limit_1))!=0) {A1_H;_delay_us(delay_amount);A1_LOW;_delay_us(delay_amount);}
    else  {A1_status=true;_delay_us(delay_amount2);}
      
    if((Limit2_PIN&(1<<Limit_2))!=0){A2_H;_delay_us(delay_amount);A2_LOW;_delay_us(delay_amount);}
    else  {A2_status=true;_delay_us(delay_amount2);}
      
    if((Limit3_PIN&(1<<Limit_3))!=0){A3_H;_delay_us(delay_amount);A3_LOW;_delay_us(delay_amount);}
    else  {A3_status=true;_delay_us(delay_amount2);}
    /*
    if((Limit4_PIN&(1<<Limit_4))!=1){A4_H;_delay_us(delay_amount);A4_LOW;_delay_us(delay_amount);}
    else  {A4_status=true;_delay_us(delay_amount2);}*/
    
    if((Limit5_PIN&(1<<Limit_5))!=0){A5_H;_delay_us(delay_amount);A5_LOW;_delay_us(delay_amount);}
    else  {A5_status=true;_delay_us(delay_amount2);}
  }  
  M110("M110 F50");
  Go_to(160,69,-43,0,-89,0);
  
  Axis1.P_steps=0;
  Axis2.P_steps=0;
  Axis3.P_steps=0;
  Axis4.P_steps=0;
  Axis5.P_steps=0;
  M110("M110 F100");
  
  Homming=false;
}
/*
//--------------------------------------------------------------------------//
void M107()
{//Go Home
  Enable_all;
  bool A1_status=false;
  bool A2_status=false;
  bool A3_status=false;
  bool A5_status=false;
  
  Axis5.P_steps=0;
  Axis1.P_steps=0;
  Axis2.P_steps=0;
  Axis3.P_steps=0;

  A1_Dir(1);//-Ve dir
  A2_Dir(1);//-Ve dir
  A3_Dir(0);//-Ve dir
  A5_Dir(0);//-Ve dir
  
  Axis1.parameters(35,1000,20);
  Axis2.parameters(35,1000,20);
  Axis3.parameters(35,1000,20);
  Axis4.parameters(35,1000,20);
  Axis5.parameters(35,1000,20);

  while((A3_status==false)||(A2_status==false)||(A5_status==false)||(A1_status==false))
  {
    if((PINB & (1<<A1_Limit_pin))){A1_H;_delay_us(350);A1_LOW;_delay_us(350);}
    else  A1_status=true;
    if((PINB & (1<<A2_Limit_pin))){A2_H;_delay_us(350);A2_LOW;_delay_us(350);}
    else  A2_status=true;
    if((PINB & (1<<A3_Limit_pin))){A3_H;_delay_us(350);A3_LOW;_delay_us(350);}
    else  A3_status=true;
    if((PIND & (1<<A5_Limit_pin))){A5_H;_delay_us(150);A5_LOW;_delay_us(150);}
    else  A5_status=true;
  }
  Go_to(172,60,-5,0,90);
  Disable_all;
}
//--------------------------------------------------------------------------//
void M108()
{//init servo
  //init_servo();
}
//--------------------------------------------------------------------------//
void M109()
{//dis servo
  //Disable_servo();
}
*/
//--------------------------------------------------------------------------//
void M110(char cmd[])
{
  initalize_robot_speed_paramters();//initialize the robot acceleration and speed values
    
  char *f;
  f=strchr(cmd,'F');   //Get the command number
  if(f!=NULL)speed_multiplier=atoi(f+1);

  Axis1.acceleration=Axis1.acceleration*((100+(100-speed_multiplier))/100);
  Axis2.acceleration=Axis2.acceleration*((100+(100-speed_multiplier))/100);
  Axis3.acceleration=Axis3.acceleration*((100+(100-speed_multiplier))/100);
  Axis4.acceleration=Axis4.acceleration*((100+(100-speed_multiplier))/100);
  Axis5.acceleration=Axis5.acceleration*((100+(100-speed_multiplier))/100);
}
//--------------------------------------------------------------------------//
void M300(char cmd[])
{
  char *p;
  p=strchr(cmd,'P');   //Get the Duration command number

  char *s;
  s=strchr(cmd,'S');   //Get the Frequency command number

   tone(buzzer,atoi(s+1), atoi(p+1)); 
  
}
//--------------------------------------------------------------------------//
void M119()
{
  uint8_t limit_status=0;
  
  if((Limit1_PIN&(1<<Limit_1))==0)limit_status+=1;
  if((Limit2_PIN&(1<<Limit_2))==0)limit_status+=2;
  if((Limit3_PIN&(1<<Limit_3))==0)limit_status+=4;
 // if((Limit4_PIN&(1<<Limit_4))==1)limit_status+=8;
  if((Limit5_PIN&(1<<Limit_5))==0)limit_status+=15;
  Serial1.println(limit_status);
  Serial.println(limit_status);
}
//--------------------------------------------------------------------------//
void M600()
{
  int index=0;
  String CMDS[3];
//  num_of_cmd=3;
for(int i=0;i<3;)
Serial.flush();
while(Serial.available()==0);
String cmd1=Serial.readStringUntil('\n');    
if(cmd1.startsWith("M"))Serial.println("error");
else {
  index++;
  Serial.println("OK");
}
/*
Serial.println(cmd1);
Serial.println(cmd2);
Serial.println(cmd3);*/
}
//--------------------------------------------------------------------------//
#endif
