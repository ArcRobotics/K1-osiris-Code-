#ifndef G_CODES_H
#define G_CODES_H
//*********************----------prototypes----------*********************//
void G91(char cmd[]);
void G92(char cmd[]);
/**************************************************************************/
void G91(char cmd[])
{
  char *m=strchr(cmd,'A');   //Get the command number
  float angle[6];
  memset(angle,'\0',sizeof(angle));
  uint8_t i=0;
  uint8_t Axis_selector=atoi(m+1)-1;
  while(m!=NULL)
  {
    if (atof(m+3)!='\0')
    {angle[Axis_selector]=atof(m+3);}
    
    else
    {angle[i]=0;}
    m=strchr(m+1,'A');
    i++;
    Axis_selector=atoi(m+1)-1;
  }
  Go_to(angle[0],angle[1],angle[2],angle[3],angle[4],angle[5]);
}
/**************************************************************************/
void G92(char cmd[])
{
  char *m=strchr(cmd,'A');   //Get the command number
  float angle[5];
  memset(angle,'\0',sizeof(angle));
  uint8_t i=0;
  uint8_t Axis_selector=atoi(m+1)-1;
  while(m!=NULL)
  {
    if (atof(m+3)!='\0')
    {angle[Axis_selector]=atof(m+3);}
    
    else
    {angle[i]=0;}
    m=strchr(m+1,'A');
    i++;
    Axis_selector=atoi(m+1)-1;
  }
  
  Axis1.P_steps=angle[0];
  Axis2.P_steps=angle[1];
  Axis3.P_steps=angle[2];
  Axis4.P_steps=angle[3];
  Axis5.P_steps=angle[4];
}
#endif
