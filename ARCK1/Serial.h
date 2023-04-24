#ifndef Serial_H
#define Serial_H
void init_Serial()
{
    
    Serial.begin(115200);
    //Serial1.begin(115200);
    Serial2.begin(115200);
    //Serial3.begin(Baurd_rate_3);
    
    Serial1.setTimeout(10);
}
//-----------------------------------------------------//
void printVar(const char *strng,int variable)
{
  char tempstr[5];
  itoa(variable,tempstr,10);
  
  Serial.print(strng);
  Serial.println(tempstr);
}
#endif
