#ifndef CMD_interpreter_H
#define CMD_interpreter_H

#define Respond Serial2.println("OK");

//*********************----------prototypes----------*********************//
 void Process_CMD();
/**************************************************************************/
void Process_CMD()
{
  switch (cmd[0])
  {
    case 'A':
    {
      Process_Acode(cmd);
      clear_memory;   //Clear main buffer
      Respond
    }
    break;
    
    case 'M':
    {
     Process_Mcode(cmd);
     clear_memory;   //Clear main buffer
     Respond
    }
    break;
    
    case 'G':
    {
      Process_Gcode(cmd);
      if(movementDone==true){
        clear_memory;
       Respond
        }
    }
    break;
    
    case 'P':{
      // Process_Pcode(cmd);
    }
    break;
        
    default:
    //transStr("NO");
    break;
  }
}
#endif
