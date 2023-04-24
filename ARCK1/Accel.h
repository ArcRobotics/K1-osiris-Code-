#ifndef Accel.h
#define Accel.h

float speed_multiplier=0;
//------------------------------------------------------------------------//
volatile float Counter;

volatile float Min_delay;
volatile int Ramp_up_steps;
volatile float Total_steps;
volatile float  Next_Delay;
volatile float  Acel;
volatile int Step_count=0;
String lol2;
//volatile int16_t steps=0; //number of steps 
//*********************----------prototypes----------*********************//
void init_acc();
void calculate_delay();
float calculate_time_OCR1A();//(float Time);
//------------------------------------------------------------------------//
/**************************************************************************/
//------------------------------------------------------------------------//
void init_acc()
{
  Axis1.init_acc_parameters();
  Axis2.init_acc_parameters();
  Axis3.init_acc_parameters();
  Axis4.init_acc_parameters();
  Axis5.init_acc_parameters();
}
/**************************************************************************/
void Axis::Clear_acceleration_var()
{
  ramp_up_steps=0;
  //step_count=0;
  counter=0;
}
//------------------------------------------------------------------------//
/**************************************************************************/
/*
  @brief This function calculates the value of OCR1A in us
  @brief return to the time setup to check the time of tic 
  @brief The function takes a @para time and divide it by the time/tic and then 
  @para time in us
*/
/**************************************************************************/
//------------------------------------------------------------------------//
float calculate_time_OCR1A()//(float Time)
{
  /*//Time must be in us
  float time_per_tic=4.0; //16us
  float OCR1A_count=Time/time_per_tic;
  //transVar("OCR1A 1st=",OCR1A_count);
  return(OCR1A_count);*/
  Next_Delay=500;
}
/**************************************************************************/
void calculate_delay()
{
if(Ramp_up_steps==0)
{
   Counter++;
   Next_Delay=Acel-(2*Acel/(4*Counter+1));
  if((int)Next_Delay<=Max_Speed)
  {
    //if we hit max speed hold it
    Next_Delay=Max_Speed;
    //keep counting ramp up steps
    Ramp_up_steps=Step_count;
  }
  if(Step_count>=Total_steps/2)
  {
    //if we hit a triangle case where the steps are too few to hit max speed 
    Ramp_up_steps=Step_count;
  }
}
else if(Step_count>=Total_steps-Ramp_up_steps)
{
  Counter--;
   Next_Delay=(Acel*(4*Counter+1))/(4*Counter+1-2);
}
  Acel=Next_Delay;
 
  for(int i =0 ;i<=(int)Next_Delay;i++){
    _delay_us(1);
  }
}
#endif
