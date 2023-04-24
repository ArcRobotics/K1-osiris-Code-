#ifndef Timers_H
#define Timers_H
#include <avr/interrupt.h>

//#define FCPU 12
//#define Timer_0_CS 64

volatile int delay_period=0;
//Timers Definitions
//#define TI0_En TIMSK0|=(1<<TOIE0);   //Enable Timer 0  CTC interrupt
//#define TI0_Dis TIMSK0&=~(1<<TOIE0); //Disable Timer 0 CTC interrupt

#define TI_En  TIMSK1 |=(1 << OCIE1A);  //Timer interrupt Enabled
#define TI_Dis  TIMSK1 &= ~(1 << OCIE1A);  //Timer interrupt disabled

#define TI4_En  TIMSK4 |=(1 << TOIE4);  //Timer interrupt Enabled
#define TI4_Dis  TIMSK4 &=~(1 << TOIE4);  //Timer interrupt disabled
//*********************----------prototypes----------*********************//
void PreSet_timer0();
void PreSet_timer1();
void PreSet_timer2();
void PreSet_timer4();
/**************************************************************************/
void PreSet_timer0(){
  TCCR0A=0;  // CTC Mode
  TCCR0B|=(1<<CS01); //64 prescaling
//  TI0_En;
}
/**************************************************************************/
void PreSet_timer1()
{
  TCCR1A =0x00;
  TCCR1B =0x00;
  TCNT1  = 0;
  TCCR1B |= (1 << WGM12); //CTC MODE OCR1A
  TCCR1B |= ((1 << CS10) | (1 << CS11));  //Pre-scaler set to 64 --> time per tick is now 4us
  TI_Dis;
}

/**************************************************************************/
void PreSet_timer4()
{
  noInterrupts();           // disable all interrupts
  TCCR4A = 0;
  TCCR4B = 0;
  TCNT4  = 0;

 
  TCCR4B =0;  // CTC mode
  TCCR4B |= (1 << CS40);    // 256 prescaler 
  TIMSK4 |= (1 << TOIE4);  // enable timer compare interrupt
  interrupts();             // enable all interrupts
}
ISR(TIMER4_OVF_vect){
  delay_period++;
  if(delay_period>250)delay_period=0;
}
#endif
