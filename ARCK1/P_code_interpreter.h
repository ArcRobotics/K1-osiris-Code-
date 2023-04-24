#ifndef P_code_interpreter_H
#define P_code_interpreter_H
//*********************----------prototypes----------*********************//
void Process_Pcode(char cmd[]);
/**************************************************************************/
void Process_Gcode(char cmd[])
{
  float X_pos=0;
  float Y_pos=0;
  float Z_pos=0;
  float Roll=0;
  float Pitch=0;
  float Yaw=0;
  
  char *x_pos = strchr(cmd, 'X'); //Get the x value
  char *y_pos = strchr(cmd, 'Y'); //Get the x value
  char *z_pos = strchr(cmd, 'Z'); //Get the x value
  char *roll = strchr(cmd, 'R'); //Get the x value
  char *pitch = strchr(cmd, 'P'); //Get the x value
  char *yaw = strchr(cmd, 'U'); //Get the x value

  if (atof(x) != '\0')x = prev_x;
  else X_pos = atof(x);
  
  if (atof(y) != '\0')y = prev_y;
  else Y_pos = atof(y);
  
  if (atof(z) != '\0')z = prev_z;
  else Z_pos = atof(z);
  
  if (atof(r) != '\0')r = prev_r;
  else Roll = atof(r);

  if (atof(p) != '\0')p = prev_p;
  else Pitch = atof(p);

  if (atof(u) != '\0')u = prev_u;
  else Yaw = atof(u);

  calculate_ik(X_pos,Y_pos,Z_pos,Roll,Pitch,Yaw,false);
  Goto(q1,q2,q3,q4,q5,q6);
}
#endif
