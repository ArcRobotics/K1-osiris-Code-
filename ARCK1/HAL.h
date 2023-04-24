#ifndef HAL_h
#define HAL_h

//-------------------------------------------------------------------------//
/*******************************Axis Directions*****************************/
int8_t Axis1_Dir = 1;
int8_t Axis2_Dir = -1;
int8_t Axis3_Dir = 1;
int8_t Axis4_Dir = -1;
int8_t Axis5_Dir = -1;
int8_t Axis6_Dir = -1;
int8_t Axis7_Dir = 1;
/*******************************Axis-1**************************************/

#define A1_Dir(dir) ((dir>0)?(Axis1_PORT|=(1<<DIR_1)):(Axis1_PORT&=~(1<<DIR_1)));

#define A1_H  Axis1_PORT|=(1<<STP_1); //STP
#define A1_LOW  Axis1_PORT&=~(1<<STP_1);

/*******************************Axis-2**************************************/

#define A2_Dir(dir) ((dir>0)?(Axis2_PORT|=(1<<DIR_2)):(Axis2_PORT&=~(1<<DIR_2)));

#define A2_H  Axis2_PORT|=(1<<STP_2); //STP
#define A2_LOW  Axis2_PORT&=~(1<<STP_2);

/*******************************Axis-3**************************************/

#define A3_Dir(dir) ((dir>0)?(Axis3_PORT|=(1<<DIR_3)):(Axis3_PORT&=~(1<<DIR_3)));

#define A3_H  Axis3_PORT|=(1<<STP_3);
#define A3_LOW  Axis3_PORT&=~(1<<STP_3);

/*******************************Axis-4**************************************/
//------------------------------------------------------------------------//
#define A4_Dir(dir) ((dir>0)?(Axis4_PORT|=(1<<DIR_4)):(Axis4_PORT&=~(1<<DIR_4)));

#define A4_H  Axis4_PORT|=(1<<STP_4);
#define A4_LOW  Axis4_PORT&=~(1<<STP_4);

/*******************************Axis-5**************************************/
//-------------------------------------------------------------------------//
#define A5_Dir(dir) ((dir>0)?(Axis5_PORT_DIR|=(1<<DIR_5)):(Axis5_PORT_DIR&=~(1<<DIR_5)));

#define A5_H  Axis5_PORT_STP|=(1<<STP_5);
#define A5_LOW  Axis5_PORT_STP&=~(1<<STP_5);

/*******************************Axis-6**************************************/
//-------------------------------------------------------------------------//
#if Has_Axis6
  #define A6_Dir(dir) ((dir>0)?(Axis6_PORT|=(1<<DIR_6)):(Axis6_PORT&=~(1<<DIR_6)));
  
  #define A6_H  Axis6_PORT|=(1<<STP_6);
  #define A6_LOW  Axis6_PORT&=~(1<<STP_6);
#endif
/*******************************Axis-7**************************************/
//-------------------------------------------------------------------------//
#if Has_Axis7
  #define A7_Dir(dir) ((dir>0)?(Axis7_PORT_DIR|=(1<<DIR_7)):(Axis7_PORT_DIR&=~(1<<DIR_7));
  
  #define A7_H  Axis7_PORT_STP|=(1<<STP_7);
  #define A7_LOW  Axis7_PORT_DIR&=~(1<<STP_7);
#endif

/***************************************************************************/
//-------------------------------------------------------------------------//
#define Disable_all  Enable_PORT|=(1<<En);
#define Enable_all Enable_PORT&=~(1<<En);

#define A1_Step_devision 4
#define A2_Step_devision 4
#define A3_Step_devision 4
#define A4_Step_devision 8
#define A5_Step_devision 4
#if Has_Axis6 
  #define A6_Step_devision 4
#endif

#if Has_Axis7 
  #define A7_Step_devision 8
#endif

#define deg_per_step (200.0/360.0)
#define dps_A1  (A1_Step_devision*deg_per_step)   //Degree per step
#define dps_A2  (A2_Step_devision*deg_per_step)
#define dps_A3  (A3_Step_devision*deg_per_step)
#define dps_A4  (A4_Step_devision*deg_per_step)
#define dps_A5  (A5_Step_devision*deg_per_step)
#if Has_Axis6 
  #define dps_A6 (A6_Step_devision*deg_per_step)
#endif

#if Has_Axis7 
  #define dps_A7 (A7_Step_devision*deg_per_step)
#endif

//Default metal pulley teeth 15T

const float A1_Gear_ratio = 5.067;
//const float A2_Gear_ratio = 9.2933;
const float A2_Gear_ratio =8.553;
//const float A3_Gear_ratio = 10.889;    
const float A3_Gear_ratio = 68.4;    
#if Has_Axis6 
   const float A4_Gear_ratio = 3.3;
#elif
  const float A4_Gear_ratio = 9;   
#endif
//const float A5_Gear_ratio = 2.467;
const float A5_Gear_ratio = 8.368;
#if Has_Axis6 
  const float A6_Gear_ratio = 1.00;
#endif

#if Has_Axis7 
  const float A7_Gear_ratio = 1.00;
#endif

/* Assume nema 17 motor running 1step/us
therefore =1000steps/ms
thus =60000 steps/s
1 Rev=200 x step div 
assume 1/8 step division
thus 1 Rev = 200 x 8 =1800 steps/Rev
Steps/sec / steps/rev = 60000/1600 =37 rps
Rps to Rpm = 37 x 60 =2250

Therefore Steps/us = ((Rpm/60)*(200*Stepdiv))/(60*1000)
*/
#define Min 60000000.0
#define Min_step_delay 1

//Define Robot software limits
#define Axis1_max 170
#define Axis1_min -170

#define Axis2_max 115
#define Axis2_min -90

#define Axis3_max 60
#define Axis3_min -200

#define Axis4_max 180
#define Axis4_min -180

#define Axis5_max 80
#define Axis5_min -80

#endif
