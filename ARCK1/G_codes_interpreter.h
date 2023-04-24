#ifndef G_codes_interpreter_H
#define G_codes_interpreter_H
//*********************----------prototypes----------*********************//
void Process_Gcode(char cmd[]);  
/**************************************************************************/
void Process_Gcode(char cmd[])
{
    uint16_t G=0;
    char *g=strchr(cmd,'G');   //Get the Axis number
    if(g!=NULL)G=atoi(g+1);
    
    if(G==91){G91(cmd);}
    else if(G==92){G92(cmd);}
 }
#endif
