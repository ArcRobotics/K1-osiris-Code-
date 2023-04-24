#ifndef Pins_H_
#define Pins_H_

//Number of Degrees of freedom -> num of stepper motors
#define DegreesOFfreedom +

//                  +---\ /---+
//    STP5    PB0  1|         |40  PA0 STP 1 (Arduino Pin 22)
//    DIR5    PB1  2|         |39  PA1 STP 2 (Arduino Pin 23)
//    Enable  PB2  3|         |38  PA2 DIR 1 (Arduino Pin 24)
//     Limit1 PB3  4|    A    |37  PA3 DIR 2 (Arduino Pin 25)
//     Limit2 PB4  5|    R    |36  PA4 STP 4 (Arduino Pin 26)
//     Limit3 PB5  6|    D    |35  PA5 STP 5 (Arduino Pin 27)
//     Limit4 PB6  7|    U    |34  PA6 DIR 4 (Arduino Pin 28)
//     Limit5 PB7  8|    I    |33  PA7 DIR 5 (Arduino Pin 29)
//          Reset  9|    N    |32  AREF
//           VCC  10|    O    |31  GND
//           GND  11|    M    |30  AVCC
//          XTAL2 12|    E    |29  PC7 STP3	(Arduino Pin 30)
//          XTAL1 13|    G    |28  PC6 En 	(Arduino Pin 31)
//         RX PD0 14|    A    |27  PC5 DIR3 (Arduino Pin 32)
//         TX PD1 15|    2    |26  PC4  (Arduino Pin 33)
//       IO6  PD2 16|    5    |25  PC3  (Arduino Pin 34)
//       IO7  PD3 17|    6    |24  PC2  (Arduino Pin 34)
//       IO8  PD4 18|    0    |23  PC1 SDA
//     Servo  PD5 19|         |22  PC0 SCL
//       IO9  PD6 20|         |21  PD7 Buzzer
//          XTAL2 12|         |29  PC7 IO4
//          XTAL1 13|         |28  PC6 DIR5
//         RX PD0 14|         |27  PC5 STP5
//         TX PD1 15|         |26  PC4 DIR4
//       IO6  PD2 16|         |25  PC3 STP4
//       IO7  PD3 17|         |24  PC2 IO5
//       IO8  PD4 18|         |23  PC1 SDA
//     Servo  PD5 19|         |22  PC0 SCL
//       IO9  PD6 20|         |21  PD7 Buzzer
//                  +---------+

//All pins definitions are mentioned in the schematic digram
#define Axis1_REG DDRA
#define Axis2_REG DDRA
#define Axis3_REG DDRC
#define Axis4_REG DDRC
#define Axis5_REG_STP DDRD
#define Axis5_REG_DIR DDRG
#define Axis6_REG DDRL
#define Axis7_REG_STP DDRB
#define Axis7_REG_DIR DDRL
#define Enable_REG DDRL


#define Axis1_PORT PORTA
#define Axis2_PORT PORTA
#define Axis3_PORT PORTC
#define Axis4_PORT PORTC
#define Axis5_PORT_STP PORTD
#define Axis5_PORT_DIR PORTG
#define Axis6_PORT PORTL
#define Axis7_PORT_STP PORTB
#define Axis7_PORT_DIR PORTL
#define Enable_PORT PORTL


#define STP_1 PA0
#define DIR_1 PA2

#define STP_2 PA4
#define DIR_2 PA6

#define STP_3 PC7
#define DIR_3 PC5

#define STP_4 PC3
#define DIR_4 PC1

#define STP_5 PD7
#define DIR_5 PG1

#define STP_6 PL7
#define DIR_6 PL5

#define STP_7 PB3
#define DIR_7 PL1

#define En 	  PL3

//===========================================================//

/*
#define IO0_REG 23
#define IO1_REG 25
#define IO2_REG 27
#define IO3_REG 29
#define IO4_REG 31*/

#define IO5_REG DDRC
#define IO6_REG DDRC
#define IO7_REG DDRC
#define IO8_REG DDRG
#define IO9_REG DDRG

#define IO5_PORT PORTC
#define IO6_PORT PORTC
#define IO7_PORT PORTC
#define IO8_PORT PORTG
#define IO9_PORT PORTG
/*
#define IO0 23
#define IO1 25
#define IO2 27
#define IO3 29
#define IO4 31*/

#define IO5 PC4
#define IO6 PC2
#define IO7 PC0
#define IO8 PG2
#define IO9 PG0
//===========================================================//
//Limit pins , ports and Regs

//Arduino Pin 52
#define Limit1_REG  DDRB//DDRL
#define Limit1_PORT PORTB//PORTL
#define Limit1_PIN  PINB//PINL
#define Limit_1 	  PB1//PL0

//Arduino Pin 53
#define Limit2_REG	DDRB//DDRL 
#define Limit2_PORT PORTB//PORTL
#define Limit2_PIN  PINB//PINL
#define Limit_2 	  PB0//PL2    

//Arduino Pin 51
#define Limit3_REG 	DDRB//DDRL
#define Limit3_PORT PORTB//PORTL
#define Limit3_PIN  PINB//PINL
#define Limit_3 	  PB2//PL4  

//Arduino Pin 49
#define Limit4_REG  DDRL
#define Limit4_PORT PORTL
#define Limit4_PIN  PINL
#define Limit_4 	  PL0 

//Arduino Pin 47
#define Limit5_REG 	DDRL
#define Limit5_PORT PORTL
#define Limit5_PIN  PINL
#define Limit_5 	  PL2

//===========================================================//
//#define servo_REG  DDRB
//#define servo_PORT PORTB
//#define servo 	   PB0

//#define buzzer_REG  DDRE
//#define buzzer_PORT PORTE
//#define buzzer 		3

#define Number_of_Output_pins 5
#define Number_of_Input_pins 5
#define Number_of_Limit_pins 5


//Function prototypes
void Config_Pins();
void Config_Steppers_Pins();
void Config_Limits_Pins();
void Config_INPUT_Pins();
void Config_OUTPUT_Pins();

#endif
