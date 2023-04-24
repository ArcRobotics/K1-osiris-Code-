#ifndef Robot_predef_h
#define Robot_predef_h
//*********************----------variables----------*********************//
#define Buffer_size 100 //Maximum amount of char until \n
#define clear_memory memset(cmd,'\0',sizeof(cmd));
char cmd[Buffer_size];      //main buffer
//*********************----------prototypes----------*********************//
void init_Registers();
void Click();
void buzz_duo(uint8_t p);
void initalize_robot_speed_paramters();  
void configure_arduinoPins();
volatile float Max_Speed;  //Set the value by RPM
//------------------------------------------------------------------------//
/**************************************************************************/
/*
  @brief Create a class for the robot axis to hold its parameters
  @para speed
  @para acc
  @para pos
  @func init_axis_parameters(int axis_no,int axis_speed,int axis_acc)
*/
/**************************************************************************/
//------------------------------------------------------------------------//
class Axis
{
  public:
  float acceleration;
  float counter;
  
  float Min_delay;
  int P_steps;
  int steps;
  int16_t pos;
  int ramp_up_steps;
  float total_steps;
  int Max_pos;
  int Min_pos;
  float Max_speed;  //Set the value by RPM
  
  uint16_t steps_per_rev;
  
  void parameters(float Mx_speed,float acc,int Dev) ;
  void init_acc_parameters();
  void accelerate(int maxSpeed);
  void Set_speed(int16_t *maxSpeed);
  void Set_acceleration(float *maxacc);
  void Set_pos(int16_t *cpos);   
  void Set_Limits(int *MaxD,int *MinD);
  void Clear_acceleration_var();
  private :
  float Next_delay;
};

Axis Axis1;
Axis Axis2;
Axis Axis3;
Axis Axis4;
Axis Axis5;

#if Has_Axis6
  Axis Axis6;
#endif
 
#if Has_Axis7
  Axis Axis7;
#endif

//------------------------------------------------------------------------//
/**************************************************************************/
/*
    @brief Create a function to initialize the controller registers
*/
/**************************************************************************/
//------------------------------------------------------------------------//
void Start_K1_Osiris()
{ 
  Config_Pins();
  Disable_all;    //Disable all motor    
  configure_arduinoPins();
  init_Serial();
  Gripper_setup();
  PreSet_timer0();
  PreSet_timer1();  // Set up the timer registers
  PreSet_timer4();
  Axis1.steps_per_rev=A1_Step_devision*200;
  Axis2.steps_per_rev=A2_Step_devision*200;
  Axis3.steps_per_rev=A3_Step_devision*200;
  Axis4.steps_per_rev=A4_Step_devision*200;
  Axis5.steps_per_rev=A5_Step_devision*200;
  Axis6.steps_per_rev=A6_Step_devision*200;
  initalize_robot_speed_paramters(); 
  Click(); 
  }
//------------------------------------------------------------------------//
/**************************************************************************/
/*
    @brief Create a function to initialize the controller registers
*/
/**************************************************************************/
//------------------------------------------------------------------------//
void initalize_robot_speed_paramters()
{
  float a=500;
  float m=10;
  Axis1.parameters(m,1500,0);
  Axis2.parameters(m,1000,0);
  Axis3.parameters(5,90,0);
  Axis4.parameters(m,a,0); 
  Axis5.parameters(m,600,0);
  Axis6.parameters(m,300,0);
}
//------------------------------------------------------------------------//
/**************************************************************************/
//------------------------------------------------------------------------//
void Axis::parameters(float Mx_speed,float acc,int Dev) {
  acceleration=acc;
  Max_speed=Mx_speed;
  //calculate_Min_delay();
  //Deviation=&Dev;
}
//------------------------------------------------------------------------//
/**************************************************************************/
//------------------------------------------------------------------------//
void Axis::init_acc_parameters() {
  ramp_up_steps=0;
  counter=0;
  //step_count=0;
}
//------------------------------------------------------------------------//
/**************************************************************************/
//------------------------------------------------------------------------//
void Axis::Set_speed(int16_t *maxSpeed) {
  Max_speed=*maxSpeed;
  //calculate_Min_delay();
}
//------------------------------------------------------------------------//
/**************************************************************************/
//------------------------------------------------------------------------//
void Axis::Set_acceleration(float *maxacc) {
  acceleration=*maxacc;
}
/**************************************************************************/
void Axis::Set_pos(int16_t *cpos){
  pos=*cpos;
}
/**************************************************************************/
/*void Axis::calculate_Min_delay(){
  if ((Min/(steps_per_rev*Max_speed))<Min_step_delay)
  {
    Min_delay=Min_step_delay;
  }
  else
  Min_delay=(Min/(steps_per_rev*Max_speed));
  
} */
/**************************************************************************/
void buzz_duo(uint8_t p)
{
  for(;p>0;p--)
  {
    buzzer_on;
    _delay_ms(50);
    buzzer_off;
    _delay_ms(50);
  }
}
/**************************************************************************/
void Click()
{
  buzzer_on;
  delay(100);
  buzzer_off;
}
/**************************************************************************/
void configure_arduinoPins()
{
  for(int8_t i=0;i<(sizeof(Output_pins)/sizeof(Output_pins[0]));i++)
  {
    pinMode(Output_pins[i],OUTPUT);
    }
      //pinMode(buzzer,OUTPUT);
      pinMode(Fans,OUTPUT); 
      
    for(int8_t i=0;i<(sizeof(Output_pins)/sizeof(Output_pins[0]));i++)
  {
    digitalWrite(Output_pins[i],HIGH);
    }  
     
  for(int8_t i=0;i<=(sizeof(INPUT_pins)/sizeof(INPUT_pins[0]));i++)
  {
    pinMode(INPUT_pins[i],INPUT_PULLUP);
    }     
}
//------------------------------------------------------------------------//
#endif
