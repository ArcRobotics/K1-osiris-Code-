#ifndef Acode_interpreter_h
#define Acode_interpreter_h
//*********************----------prototypes----------*********************//
void Process_Acode(char cmd[]);
/**************************************************************************/
void Process_Acode(char cmd[])
{
  int16_t J=0;
  uint8_t A=0;
  int8_t delay_amount=1;
  char *a=strchr(cmd,'A');   //Get the Axis number
  if(a!=NULL)A=atoi(a+1);
  char *j=strchr(cmd,'J');   //Get the Jog amount
    if(j!=NULL)J=atoi(j+1);
  if(J>0){
    A1_Dir(0);
    A2_Dir(0);
    A3_Dir(0);
    A4_Dir(0);
    A5_Dir(0);
    }//+ Dir
  else {
    A1_Dir(1);
    A2_Dir(1);
    A3_Dir(1);
    A4_Dir(1);
    A5_Dir(1);
    }//- Dir
  
  if(abs(J)>0){
    
    switch (A)
    {
      case 1:
      {
        A1_LOW;
        _delay_us(delay_amount);
        A1_H;
      }
      break;
      case 2:
      {
        A2_LOW;
        _delay_us(delay_amount);
        A2_H;
      }
      break;
      case 3:
      {
        A3_LOW;
        _delay_us(delay_amount);
        A3_H;
      }
      break;
      case 4:
      {
        A4_LOW;
        _delay_us(delay_amount);
        A4_H;
      }
      break;
      case 5:
      {
        A5_LOW;
        _delay_us(delay_amount);
        A5_H;
      }
      break;
    }
  }
}
#endif
