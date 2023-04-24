#include <avr/io.h>
#include "Pins.h"

//---------------------------------//
void Config_Pins()
{
	Config_Steppers_Pins();
	Config_Limits_Pins();
	Config_INPUT_Pins();
}
//---------------------------------//
void Config_Steppers_Pins()
{
	Axis1_REG|=(1<<STP_1);
	Axis2_REG|=(1<<STP_2);
	Axis3_REG|=(1<<STP_3);
	Axis4_REG|=(1<<STP_4);
	Axis5_REG_STP|=(1<<STP_5);
	Axis6_REG|=(1<<STP_6);
	
	Axis1_REG|=(1<<DIR_1);
	Axis2_REG|=(1<<DIR_2);
	Axis3_REG|=(1<<DIR_3);
	Axis4_REG|=(1<<DIR_4);
	Axis5_REG_DIR|=(1<<DIR_5);
	Axis6_REG|=(1<<DIR_6);
	
	Enable_REG|=(1<<En);
	
}

//---------------------------------//
void Config_Limits_Pins()
{
	//Set limit pins as inputs & Enable pullup resisitors
	Limit1_REG&=~(1<<Limit_1);
	Limit2_REG&=~(1<<Limit_2);
	Limit3_REG&=~(1<<Limit_3);
	//Limit4_REG&=~(1<<Limit_4);
	Limit5_REG&=~(1<<Limit_5);
	
	Limit1_PORT|=(1<<Limit_1);
	Limit2_PORT|=(1<<Limit_2);
	Limit3_PORT|=(1<<Limit_3);
	//Limit4_PORT|=(1<<Limit_4);
	Limit5_PORT|=(1<<Limit_5);	
}
//---------------------------------//
void Config_INPUT_Pins()
{
	//Set INPUT pins as inputs & Enable pullup resisitors
	//Set limit pins as inputs & Enable pullup resisitors

}
//---------------------------------//
void Config_OUTPUT_Pins()
{
	//Set OUTPUT pins as OUTPUTS
	
	IO5_REG|=(1<<IO5);
	IO6_REG|=(1<<IO6);
	IO7_REG|=(1<<IO7);
	IO8_REG|=(1<<IO7);
	IO9_REG|=(1<<IO9);
	
	IO5_PORT&=~(1<<IO5);
	IO6_PORT&=~(1<<IO6);
	IO7_PORT&=~(1<<IO7);
	IO8_PORT&=~(1<<IO7);
	IO9_PORT&=~(1<<IO9);
}
