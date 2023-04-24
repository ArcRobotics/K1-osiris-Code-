#ifndef Gripper_h
#define Gripper_h


//volatile int duration=0;
//volatile int pulseH=150;
volatile bool ISon=false;
Servo griper;  // create servo object to control a servo
//*********************----------prototypes----------*********************//
void Gripper_setup();
void open_gripper();
void close_gripper();
void Gripper_Enable();
void Gripper_Disable();
//-------------------------------------------------------------------------//
void Gripper_setup(){
 griper.attach(servo_pin);  // attaches the servo on pin 9 to the servo object
 open_gripper();
}
//-------------------------------------------------------------------------//
void set_gripper_pos(char cmd[]){
  

}
//-------------------------------------------------------------------------//
void open_gripper()//M21 open gripper
{
  griper.write(90);  //150 Big gripper
}
//-------------------------------------------------------------------------//
void close_gripper()//M20 close gripper
{
  griper.write(25);  //35 Big gripper
}

#endif 
