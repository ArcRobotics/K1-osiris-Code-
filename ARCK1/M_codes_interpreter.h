#ifndef M_codes_interpreter_H
#define M_codes_interpreter_H

//*********************----------prototypes----------*********************//
void Process_Mcode(char cmd[]);
/**************************************************************************/
void Process_Mcode(char cmd[]){
  int16_t M=0;
  char *m=strchr(cmd,'M');   //Get the Axis number
  if(m!=NULL)M=atoi(m+1);
  switch (M)
  {   
    case 18:
    M18();
    break;
    
    case 19:
    M19();
    break;
    
    case 20:
    M20();
    break;
    
    case 21:
    M21();
    break;
    
    case 22:
    M22();
    break;
    
    case 31://Enable_all
    M31();
    break;
    
    case 32://Disable_all
    M32();
    break;
    case 33://Go_home
    M33();
    break;
    
    case 35://Delay
    M35(cmd);
    break;
    
    case 36://wait for external Input to go low
    M36(cmd);
    break;
        
    case 106:
    M106();
    break;
    /*
    case 107:
    M107();
    break;
    break;
    */  
    case 42:
    M42(cmd);
    break;
    
    case 43:
    M43(cmd);
    break;
    
    case 110://Acc Modifier
    M110(cmd);
    break;

    case 119://Acc Modifier
    M119();
    break;
    
    case 300://Acc Modifier
    M300(cmd);
    break;
    
    case 503:///Report Pos
    //M503();
    break;
    
    case 504://Report limits
    //M504();
    break;
    
    case 505://Speed_report
    //M505();
    break;
    
    case 506://Acceleration_report
    //M506();
    break;

    case 600://Acceleration_report
    M600();
    break;
    
    default:
    break;
  }
}


#endif /* Mcode_prossesor_H_ */
