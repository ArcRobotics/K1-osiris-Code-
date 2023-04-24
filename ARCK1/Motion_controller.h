#ifndef Motion_controller_H
#define Motion_controller_H
//*********************----------prototypes----------*********************//
void Go_to(float degs1,float degs2,float degs3,float degs4,float degs5,float deg6);
void select_motor_to_move(int8_t selector);
void make_a_step(int8_t n);
void end_motion();
volatile int8_t Selector;
volatile int16_t c1=0;
volatile int16_t c2=0;
volatile int16_t c3=0;
volatile int16_t c4=0;
volatile int16_t c5=0;
volatile bool movementDone=true;
volatile bool cmd_terminator=false;
volatile bool Homming=false;
int dir_mask=1;
//volatile bool homming=false;
//------------------------------------------------------------------------//
/**************************************************************************/
/*
  @brief Create a function to receive the desired angles 
  @brief Calculate the  steps for each axis
  @brief Calculate the delta steps for each axis
  @brief Decide which axis direction
  @brief Decide which axis to move 
  @brief Save  pos for future reference
  @para degs1,degs2,degs3... angle values
*/
/**************************************************************************/
//------------------------------------------------------------------------//
void Go_to(float degs1,float degs2,float degs3,float degs4,float degs5,float degs6)
{ 
  if (cmd_terminator==true)
  {
    movementDone=true;
  }
  else
    {
      movementDone=false;
    }
    
    if (Homming==false)
    {
    //Check that the robot won't exceeds it's limits    
    if (degs1>Axis1_max||degs1<Axis1_min)   movementDone=true;
    else if (degs2>Axis2_max||degs2<Axis2_min)  movementDone=true;
    else if (degs3>Axis3_max||degs3<Axis3_min)  movementDone=true;
    else if (degs4>Axis4_max||degs4<Axis4_min)  movementDone=true;
    else if (degs5>Axis5_max||degs5<Axis5_min)  movementDone=true;
        }

//    transVar("deg1=",degs1);
//    transVar("deg2=",degs2);
//    transVar("deg3=",degs3);
//    transVar("deg4=",degs4);
//    transVar("deg5=",degs5);
//    transVar("movementDone=",movementDone);
    
  Axis1.steps=degs1*(A1_Gear_ratio*dps_A1);
  Axis2.steps=degs2*(A2_Gear_ratio*dps_A2);
  Axis3.steps=degs3*(A3_Gear_ratio*dps_A3);
  Axis4.steps=degs4*(A4_Gear_ratio*dps_A4);
  Axis5.steps=degs5*(A5_Gear_ratio*dps_A5);
  #if Has_Axis6 
    Axis6.steps=degs6*(A6_Gear_ratio*dps_A6);
  #endif


  //Find the Difference in position
  int delta_A1=abs(Axis1.steps-Axis1.P_steps);
  int delta_A2=abs(Axis2.steps-Axis2.P_steps);
  int delta_A3=abs(Axis3.steps-Axis3.P_steps);
  int delta_A4=abs(Axis4.steps-Axis4.P_steps);
  int delta_A5=abs(Axis5.steps-Axis5.P_steps);
  #if Has_Axis6 
    int delta_A6=abs(Axis6.steps-Axis6.P_steps);
  #endif
  

  if(((int)Axis1.steps-(int)Axis1.P_steps)>0){A1_Dir(Axis1_Dir);}//+ Dir
  else {A1_Dir(-1*Axis1_Dir);}//- Dir
  
  if(((int)Axis2.steps-(int)Axis2.P_steps)>0){A2_Dir(Axis2_Dir);}//+ Dir
  else A2_Dir(-1*Axis2_Dir);//- Dir
  
  if(((int)Axis3.steps-(int)Axis3.P_steps)>0){A3_Dir(Axis3_Dir);}//+ Dir
  else A3_Dir(-1*Axis3_Dir);//- Dir

  if(((int)Axis4.steps-(int)Axis4.P_steps)>0){A4_Dir(Axis4_Dir);delay(20);}//+ Dir
  else {A4_Dir(-1*Axis4_Dir);delay(20);}//- Dir
  
  if(((int)Axis5.steps-(int)Axis5.P_steps)>0){A5_Dir(Axis5_Dir);}//+ Dir
  else A5_Dir(-1*Axis5_Dir);//- Dir
  
  #if Has_Axis6 
    if(((int)Axis6.steps-(int)Axis6.P_steps)>0){A6_Dir(Axis6_Dir);}//+ Dir
    else A6_Dir(-1*Axis6_Dir);//- Dir
  #endif
  Axis1.P_steps=Axis1.steps;
  Axis2.P_steps=Axis2.steps;
  Axis3.P_steps=Axis3.steps;
  Axis4.P_steps=Axis4.steps;
  Axis5.P_steps=Axis5.steps;
  #if Has_Axis6 
    Axis6.P_steps=Axis6.steps;
  #endif
  
  Axis1.total_steps=delta_A1;
  Axis2.total_steps=delta_A2;
  Axis3.total_steps=delta_A3;
  Axis4.total_steps=delta_A4;
  Axis5.total_steps=delta_A5;
  #if Has_Axis6 
    Axis6.total_steps=delta_A6;
  #endif   
  
    if((delta_A1>=delta_A2)&&(delta_A1>=delta_A3)&&(delta_A1>=delta_A4)&&(delta_A1>=delta_A5)&&(delta_A1>=delta_A6))
    {
      Selector=1;
      Total_steps=delta_A1;
      Max_Speed=Axis1.Max_speed;
      Acel=Axis1.acceleration;
      }

    else if((delta_A2>delta_A1)&&(delta_A2>delta_A3)&&(delta_A2>delta_A4)&&(delta_A2>delta_A5)&&(delta_A2>delta_A6))
    { 
      Selector=2;
      Total_steps=delta_A2;
      Max_Speed=Axis2.Max_speed;
      Acel=Axis2.acceleration;
      }
  
    else if ((delta_A3>delta_A1)&&(delta_A3>delta_A2)&&(delta_A3>delta_A4)&&(delta_A3>delta_A5)&&(delta_A3>delta_A6))
    {
      Selector=3;
      Total_steps=delta_A3;
      Max_Speed=Axis3.Max_speed;
      Acel=Axis3.acceleration;
      }
  
    else if ((delta_A4>delta_A1)&&(delta_A4>delta_A2)&&(delta_A4>delta_A3)&&(delta_A4>delta_A5)&&(delta_A4>delta_A6))
    {
      Selector=4;
      Total_steps=delta_A4;
      Max_Speed=Axis4.Max_speed;
      Acel=Axis4.acceleration;
      }
  
    else if ((delta_A5>delta_A1)&&(delta_A5>delta_A2)&&(delta_A5>delta_A3)&&(delta_A5>delta_A4)&&(delta_A5>delta_A6))
    {
      Selector=5;
      Total_steps=delta_A5;
      Max_Speed=Axis5.Max_speed;
      Acel=Axis5.acceleration;
      }
    #if Has_Axis6 
     if ((delta_A6>delta_A1)&&(delta_A6>delta_A2)&&(delta_A6>delta_A3)&&(delta_A6>delta_A4)&&(delta_A6>delta_A5))
    {
      Selector=6;
      Total_steps=delta_A6;
      Max_Speed=Axis6.Max_speed;
      Acel=Axis6.acceleration;
      }
    #endif 
  //TI_En;
  while(movementDone==false){
    
  if(Serial2.read()=='%'){
    end_motion();
    }
  if(Step_count<Total_steps){
    Step_count++;
    select_motor_to_move(Selector);
    calculate_delay();
  }
  else end_motion();
  }
}
//------------------------------------------------------------------------//
/**************************************************************************/
/*
    @brief Create a function to select which axis to move and move it
  @brief receive delta each axis and decide which one to move according to the selector
    @para Delta1,Delta2,degs3... Delta steps of each axis
  @para selector
*/
/**************************************************************************/
//------------------------------------------------------------------------//
void select_motor_to_move(int8_t selector)
{
    float *Delta1=&Axis1.total_steps;
    float *Delta2=&Axis2.total_steps;
    float *Delta3=&Axis3.total_steps;
    float *Delta4=&Axis4.total_steps;
    float *Delta5=&Axis5.total_steps;
    #if Has_Axis6 
    float *Delta6=&Axis6.total_steps;
    #endif
  switch (Selector)
  {
    
    case 1:{
      make_a_step(1);
      c1+=*Delta2;
      c2+=*Delta3;
      c3+=*Delta4;
      c4+=*Delta5;
      c5+=*Delta6;
      if(c1>*Delta1)
        {make_a_step(2);
        c1-=*Delta1;}
      if(c2>*Delta1)
        {make_a_step(3);
        c2-=*Delta1;}
      if(c3>*Delta1)
        {make_a_step(4);
        c3-=*Delta1;}
      if(c4>*Delta1)
        {make_a_step(5);
        c4-=*Delta1;}
      if(c5>*Delta1)
        {make_a_step(6);
        c5-=*Delta1;}
      break;
    }
    case 2:{
      make_a_step(2);
      c1+=*Delta1;
      c2+=*Delta3;
      c3+=*Delta4;
      c4+=*Delta5;
      c5+=*Delta6;
      if(c1>*Delta2)
        {make_a_step(1);
        c1-=*Delta2;}
      if(c2>*Delta2)
        {make_a_step(3);
        c2-=*Delta2;}
      if(c3>*Delta2)
        {make_a_step(4);
        c3-=*Delta2;}
      if(c4>*Delta2)
        {make_a_step(5);
        c4-=*Delta2;}
      if(c5>*Delta2)
        {make_a_step(6);
        c5-=*Delta2;}
      break;
    }
    case 3:{
      make_a_step(3);
      c1+=*Delta1;
      c2+=*Delta2;
      c3+=*Delta4;
      c4+=*Delta5;
      c5+=*Delta6;
      if(c1>*Delta3)
        {make_a_step(1);
        c1-=*Delta3;}
      if(c2>*Delta3)
        {make_a_step(2);
        c2-=*Delta3;}
      if(c3>*Delta3)
        {make_a_step(4);
        c3-=*Delta3;}
      if(c4>*Delta3)
        {make_a_step(5);
        c4-=*Delta3;}
      if(c5>*Delta3)
        {make_a_step(6);
        c5-=*Delta3;}
      break;
    }
    case 4:
    {
      make_a_step(4);
      c1+=*Delta1;
      c2+=*Delta2;
      c3+=*Delta3;
      c4+=*Delta5;
      c5+=*Delta6;
      if(c1>*Delta4)
        {make_a_step(1);
        c1-=*Delta4;}
      if(c2>*Delta4)
        {make_a_step(2);
        c2-=*Delta4;}
      if(c3>*Delta4)
        {make_a_step(3);
        c3-=*Delta4;}
      if(c4>*Delta4)
        {make_a_step(5);
        c4-=*Delta4;}
      if(c5>*Delta4)
        {make_a_step(6);
        c5-=*Delta4;}
      break;
    }
    case 5:
    {
      make_a_step(5);
      c1+=*Delta1;
      c2+=*Delta2;
      c3+=*Delta3;
      c4+=*Delta4;
      c5+=*Delta6;
      if(c1>*Delta5)
        {make_a_step(1);
        c1-=*Delta5;}
      if(c2>*Delta5)
        {make_a_step(2);
        c2-=*Delta5;}
      if(c3>*Delta5)
        {make_a_step(3);
        c3-=*Delta5;}
      if(c4>*Delta5)
        {make_a_step(4);
        c4-=*Delta5;}
      if(c5>*Delta5)
        {make_a_step(6);
        c5-=*Delta5;}
      break;
    }
    case 6:
    {
      make_a_step(6);
      c1+=*Delta1;
      c2+=*Delta2;
      c3+=*Delta3;
      c4+=*Delta4;
      c5+=*Delta5;
      if(c1>*Delta6)
        {make_a_step(1);
        c1-=*Delta6;}
      if(c2>*Delta6)
        {make_a_step(2);
        c2-=*Delta6;}
      if(c3>*Delta6)
        {make_a_step(3);
        c3-=*Delta6;}
      if(c4>*Delta6)
        {make_a_step(4);
        c4-=*Delta6;}
      if(c5>*Delta6)
        {make_a_step(5);
        c5-=*Delta6;}
      break;
    }
  }   
}
/**************************************************************************/
void make_a_step(int8_t n)
{
    switch (n)
    {
    case 1:
      A1_H;
      _delay_us(1);
      A1_LOW;
    break;
    
    case 2:
      A2_H;
      _delay_us(1);
      A2_LOW;
    break;
    
    case 3:
      A3_H;
      _delay_us(1);
      A3_LOW; 
    break;
    
    case 4:
      A4_H;
      _delay_us(1);
      A4_LOW;
    break;
    
    case 5:
      A5_H;
      _delay_us(1);
      A5_LOW;    
    break;

    case 6:
      A6_H;
      _delay_us(1);
      A6_LOW;
    break;
    }
}
/**************************************************************************/
void end_motion()
{
  Step_count=0;
  Counter=0;
  Ramp_up_steps=0;
  movementDone=true;
}
#endif
