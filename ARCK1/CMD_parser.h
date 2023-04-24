#ifndef CMD_parser_h
#define CMD_parser_h


//*********************----------prototypes----------*********************//
void Receive_data();
/**************************************************************************/
uint8_t head = 0;
uint16_t IncomingData;
#define Data_exist_InSerial Serial.available()>0
#define Data_exist_InSerial1 Serial1.available()>0
#define Data_exist_InSerial2 Serial2.available()>0
/**************************************************************************/
void Receive_data()
{
  while(Data_exist_InSerial2)
  {
      //Read_temp();    
      
      IncomingData = Serial2.read(); //while data is available
      //IncomingData = Serial.read(); //while data is available
      
    //Wrap the head and the tail if they reached the end of the array
    if (head > Buffer_size - 1) {
      head = 0;
    }
    //if found CR terminate the communication cmd[data_counter]='\0';
    else if ((IncomingData == '\r') || (IncomingData == '\n'))
    {
      cmd[head] = '\0';
      head++;
      Serial.println(cmd);
       #if Debug == 1
          Serial.println(cmd);
       #endif
      
      head = 0;
      Process_CMD();
    }
    else if ((IncomingData >= 'a') && (IncomingData <= 'z'))
    {
      cmd[head] = IncomingData - 'a' + 'A'; //if the letter is small make it capital
      head++;
    }
    //else if(IncomingData=='\0');//Ignore white space data==' '||'\0'
    else if (isdigit(IncomingData) || isalpha(IncomingData) || IncomingData == ' ' || IncomingData == '-' || IncomingData == '.'||IncomingData == '%') {
      //if non of the above cond. is valid then store the data
      cmd[head] = IncomingData;
      //Serial.println(IncomingData);
      head++;
    }
  }
}
/**************************************************************************/
int checksum(char arr[], int n)
{
  int sum = 0;
  for (int i = 0; i < n; i++) {
    sum += arr[i];
  }

  return sum;
}
#endif /* DATA_RECIVER_H_ */
