#ifndef Inverse_Kinmatics_h
#define Inverse_Kinmatics.h

#include <math.h>
#include "Matrix.h"



//This function creates a modified DH table same as the excel
#define create_DHM_table(out,th,alpha,d,a)\
    (out)[0]= cos(th);  \
    (out)[1]= -sin(th); \
    (out)[2]= 0;        \
    (out)[3]= a;        \
    (out)[4]= sin(th)*cos(alpha);   \
    (out)[5]= cos(th)*cos(alpha);   \
    (out)[6]=  -sin(alpha);         \
    (out)[7]= -d*sin(alpha);        \
    (out)[8]= sin(th)*sin(alpha);   \
    (out)[9]= cos(th)*sin(alpha);   \
    (out)[10]= cos(alpha);          \
    (out)[11]= d*cos(alpha);        \
    (out)[12]= 0; \
    (out)[13]= 0; \
    (out)[14]= 0; \
    (out)[15]= 1;

 
double q[6];
double th[6];
double ZYZ[3][3];
double R06[3][3];

//DENAVIT HARTENBERG PARAMETERS SAME AS ROBODK

double DHparams[24] =
    {    0,      0,  256.67,        0   ,
       -90,    -90,       0,   -11.87   ,
         0,      0,       0,    174.58  ,
         0,    -90,     215.0,    3.1  ,
         0,     90,       0,         0  ,
       180,    -90,      75.0,       0  };

// Custom robot base (user frame)
Matrix4x4 Robot_BaseFrame =
{1, 0, 0, 0 ,
 0, 1, 0, 0,
 0, 0, 1, 0 ,
 0, 0, 0, 1};

// Custom robot tool (tool frame, end of arm tool or TCP)
Matrix4x4 Robot_TCP_Frame =
{1, 0, 0, 0 ,
 0, 1, 0, 0,
 0, 0, 1, 0 ,
 0, 0, 0, 1};
//There are at least 12 Possible configurations not all will always be valid but this is the maximum number
//Front-> Elbow Up-> Flip
//Front-> Elbow Up-> Non-Flip
//Front-> Elbow Down-> Flip
//Front-> Elbow Down-> Non-Flip

//Back-> Elbow Up-> Flip
//Back-> Elbow Up-> Non-Flip
//Back-> Elbow Down-> Flip
//Back-> Elbow Down-> Non-Flip
float valid_ikSol[12][6];

//Note!!!
//The atan() function returns a value in the range -π/2 to π/2 radians
//The atan2() function returns a value in the range -π to π radians  

//Robot DH parameters
double d1=DHparams[2];
double d2=DHparams[7];
double a3=DHparams[11];
double a4=DHparams[15];
double d4=DHparams[14];
double d6=DHparams[22];
double a34=a4+a3;

//A variable to current pose
pose current_pose;

//Axis Limits SAME AS ROBODK
//Store these values in the eeprom off the Micro Controller and allow them to be changed under admin control
float Upper_limits[6] = {170.0,120.0,30.0,180.0,90.0};
float Lower_limits[6] = {-170.0,-80.0,-180.0,-90.0};

//define wrist points
double Wpx;
double Wpy;
double Wpz;

//Variables used in the inverse kinematics calculation
double r;
double s;
double pz;
double Pwz;
double l0=d2;


double alpha;
double beta;
double lamda;

//Define variables to store the euler ZYZ angles
double q1; // Z
double q2; // y
double q3; // Z

//since the cos(90) won't give an actual zero we will force it to be zero using this value
double epsilon=0.0001;
//-------------------------------------------------------//
//-------------------Protptypes--------------------------//
// calculate_ik:Solves the inverse kinmatics
void calculate_ik(double x,double y,double z,double roll,double pitch,double yaw,bool flip);
// calculate_the_wrist_point:Gets the wrist points values 
void calculate_the_wrist_point(double x,double y,double z,double rol ,double pit,double ya);
//Solve the forward kinmatics equations
void Fkine(double A1,double A2,double A3,double A4,double A5,double A6);
// calculate_R06_transpose:calculate the R06 matrix values
void calculate_R06_transpose(double th[3],double Q[3]);
//converts ZYZ euler angles to a rotation matrix
void calculate_ZYZ_euler(double th1,double th2, double th3);
void send_motion_cmd();
static void solve_for_zeroPos();
//-------------------------------------------------------//
void solve_for_zeroPos()
{
  calculate_ik(267.130,0.00,435.230,0,90,0,false);
 }
//-------------------------------------------------------//
/*
 * Step 1 solving the translation problem 
 * 1- calculating the wrist points x,y,z
 */
//-------------------------------------------------------//
void calculate_the_wrist_point(double x,double y,double z,double rol ,double pit,double ya)
{
 // Serial.print("roll=");
 // Serial.print(rol);
  //Serial.print(",pitch=");
 // Serial.print(pit);
 // Serial.print(",yaw=");
 // Serial.println(ya);
    
    //Note ** is a pointer multiplication
    Wpx=x-(d6*rol);
    Wpy=y-(d6*pit);
    Wpz=z-(d6*ya);


//    Serial.print("Wrist point x=");
//    Serial.println(Wpx);
//    Serial.print("Wrist point y=");
//    Serial.println(Wpy);
//    Serial.print("Wrist point z=");
//    Serial.println(Wpz);
}

//-----------------------------------------------------//
/*
 * step 2 Solving orientation problem
 * 1-Find R06 through the given euler angles(calculate the rotation matrix ZYZ rotation matrix)
 */
//----------------------------------------------------//
void calculate_ZYZ_euler(double th1,double th2, double th3)
{
//  Serial.print("th1=");
//  Serial.println(th1);
//  Serial.print("th2=");
//  Serial.println(th2);
//  Serial.print("th3=");
//  Serial.println(th3);
    th1=toRad(th1);
    th2=toRad(th2);//R23 Matrix
    th3=toRad(th3);

    ZYZ[0][0]=(cos(th1)*cos(th2)*cos(th3))-(sin(th1)*sin(th3));
    ZYZ[0][1]=(-1*cos(th3)*sin(th1))-(cos(th1)*cos(th2)*sin(th3));
    ZYZ[0][2]=cos(th1)*sin(th2);

    ZYZ[1][0]=(cos(th1)*sin(th3))+(cos(th2)*cos(th3)*sin(th1));
    ZYZ[1][1]=(cos(th1)*cos(th3))-(cos(th2)*sin(th1)*sin(th3));
    ZYZ[1][2]=sin(th1)*sin(th2);

    ZYZ[2][0]=-1*cos(th3)*sin(th2);
    ZYZ[2][1]=sin(th2)*sin(th3);
    ZYZ[2][2]=cos(th2);

    q1=ZYZ[0][2];
    q2=ZYZ[1][2];
    q3=ZYZ[2][2];
}
//-----------------------------------------------------//
/*
 * step 2 Solving orientation problem
 * 2- we calculate R03=R01*R12*R23
 * 3- we multiply it by rotx(-90)
 * 4- we get R03 transpose 
 * 5- we multply R03^-1 * R to get R06
 */
//----------------------------------------------------//
void calculate_R06_transpose(double th[3],double Q[3])
{
    double M[3][3];
    double R01[3][3];    //rotation of frame 1 about frame 0
    double R12[3][3];    //rotation of frame 2 about frame 2
    double R23[3][3];    //rotation of frame 3 about frame 2
    double R03[3][3];    //rotation of frame 3 with respect to frame 0
    double R03T[3][3];   //R03 Transpose
    double RotX[3][3]={{1,0,0},{0,0,1},{0,-1,0}};     //rotation x(-90)

    //R01 Matrix
    R01[0][0]=cos(th[0]);
    R01[0][1]=-sin(th[0]);
    R01[0][2]=0;

    R01[1][0]=cos(Q[0])*sin(th[0]);
    R01[1][1]=cos(Q[0])*cos(th[0]);
    R01[1][2]=-sin(Q[0]);

    R01[2][0]=sin(Q[0])*sin(th[0]);
    R01[2][1]=cos(th[0])*sin(Q[0]);
    R01[2][2]=cos(Q[0]);

    //R12 Matrix
    R12[0][0]=cos(th[1]);
    R12[0][1]=-sin(th[1]);
    R12[0][2]=0;

    R12[1][0]=cos(Q[1])*sin(th[1]);
    R12[1][1]=cos(Q[1])*cos(th[1]);
    R12[1][2]=-sin(Q[1]);

    R12[2][0]=sin(Q[1])*sin(th[1]);
    R12[2][1]=cos(th[1])*sin(Q[1]);
    R12[2][2]=cos(Q[1]);

    //R23 Matrix
    R23[0][0]=cos(th[2]);
    R23[0][1]=-sin(th[2]);
    R23[0][2]=0;

    R23[1][0]=cos(Q[2])*sin(th[2]);
    R23[1][1]=cos(Q[2])*cos(th[2]);
    R23[1][2]=-sin(Q[2]);

    R23[2][0]=sin(Q[2])*sin(th[2]);
    R23[2][1]=cos(th[2])*sin(Q[2]);
    R23[2][2]=cos(Q[2]);

    //M=R01*R12
    for (int j = 0; j < 3; ++j) {
    for (int k = 0; k < 3; ++k) {
    double sum = 0;
    for (int i = 0; i < 3; ++i){
    sum += R01[j][i] * R12[i][k];
    M[j][k] = sum;}}}

   //R03=M*R23
    for (int j = 0; j < 3; ++j) {
    for (int k = 0; k < 3; ++k) {
    double sum = 0;
    for (int i = 0; i < 3; ++i){
    sum += M[j][i] * R23[i][k];
    R03[j][k] = sum;}}}

    //M=R03*rotx(-90)
    for (int j = 0; j < 3; ++j) {
    for (int k = 0; k < 3; ++k) {
    double sum = 0;
    for (int i = 0; i < 3; ++i){
    sum += R03[j][i] * RotX[i][k];
    M[j][k] = sum;}}}

    //R03T
    for (int j = 0; j < 3; ++j) {
    for (int k = 0; k < 3; ++k) {
    R03T[k][j] =M[j][k];}}

        //R06=R03T*R ZYZ
    for (int j = 0; j < 3; ++j) {
    for (int k = 0; k < 3; ++k) {
    double sum = 0;
    for (int i = 0; i < 3; ++i){
    sum += R03T[j][i] * ZYZ[i][k];
    R06[j][k] = sum;}}}

//    if(debug==true){
//        Serial.println("ZYZ=");
//        print_matrix(ZYZ);
//        Serial.println("R06=");
//        print_matrix(R06);
//    }
}
//-------------------------------------------------------//
/*
 * Solving the inverse kinmatics equations 
 * Note Flip mode is used by default
 */
//-------------------------------------------------------//
void calculate_ik(double x,double y,double z,double roll,double pitch,double yaw,bool flip)
{
//  Serial.print("x");
//  Serial.print(x);
//  Serial.print(",");
//  Serial.print("y=");
//  Serial.print(y);
//  Serial.print(",");
//  Serial.print("z=");
//  Serial.println(z);

    calculate_ZYZ_euler(roll,pitch,yaw);
    calculate_the_wrist_point(x,y,z,q1,q2,q3);
    
    //Calculate axis(1) angle
    q[0]=atan(Wpy/Wpx);

    if(y>0&&x>0);//1st coordinate leave it
    else if(y>0&&x<0){q[0]=M_PI+q[0];}
    else if(y<0&&x<0){q[0]=(M_PI-q[0])*-1;}

    r=sqrt(pow(Wpx,2)+pow(Wpy,2));

    if(flip==true){r=r+l0;}
    else if(flip==false) {r=r-l0;}

    pz=Wpz-d1;


    s=sqrt(pow(r,2)+pow(pz,2));

    alpha=atan(pz/r);

    beta=acos((pow(s,2)+pow(a34,2)-pow(d4,2))/(2*a34*s));

    q[1]=(M_PI/2)-alpha-beta;

    if(q[1]<epsilon&&q[1]>0)q[1]=0;


    lamda=acos((pow(d4,2)+pow(a34,2)-pow(s,2))/(2*a34*d4));

    q[2]=(M_PI/2)-lamda;

    if(q[2]<epsilon&&q[2]>0)q[2]=0;



    double o[3]={q[0],q[1]-(90*degtorad),q[2]};//Theta From DH tables
    double beb[3]={0,-90*degtorad,0};//Alpha From DH Table
    calculate_R06_transpose(o,beb);

    //check that th5 not =90
    if(R06[2][2]<epsilon&&R06[2][2]>-epsilon){
            q[4]=M_PI/2;}

    else {
        q[4]=atan(sqrt(1-pow(R06[2][2],2))/R06[2][2]);}


    if(R06[2][0]<epsilon&&R06[2][0]>-epsilon){R06[2][0]=0;}
    if(R06[2][1]<epsilon&&R06[2][1]>-epsilon){R06[2][1]=0;}

    if(q[4]>0){
        q[3]=atan(R06[1][2]/R06[0][2]);
        q[5]=atan(R06[2][1]/(-1*R06[2][0]));
        //q[5]=q[5]+M_PI;
    }
    else if(q[4]<0){
    q[3]=atan(R06[1][2])/(R06[0][2]);
    if((q[3]-M_PI)>-M_PI){q[3]=q[3]-M_PI;}
   // if(-1*R06[1][2]<0||R06[0][2]<0){if((q[3]-M_PI)>-M_PI){q[3]=q[3]-M_PI;}}
   // else {if((q[3]+M_PI)<M_PI){q[3]=q[3]+M_PI;}}
    }

    else if(q[4]==0) {q[3]=atan(R06[1][0]/R06[0][0]);}

    
      /*
    for(int i=0;i<6;i++)
        {
      j[i]=&q[i];
      //  Serial.print("q");
      //  Serial.print(i+1);
      //  Serial.print("=");
      //  Serial.println(q[i]*radtodeg);
       // Serial.print(",");
     //   Serial.print("Joint_limits_min=");
     //   Serial.println(Joint_limits[i][0]);
       // if(q[i]*radtodeg<Joint_limits[i][0] || q[i]>Joint_limits[i][1]){break;}
        }*/
       Fkine(q[0],q[1],q[2],q[3],q[4],0);
       if(current_pose[0]/x>1.1||current_pose[0]/x<0.99){
       q[4]=-1*q[4];
       Fkine(q[0],q[1],q[2],q[3],q[4],q[5]);}

    for(int i=0;i<6;i++)
        {
     // j[i]=&q[i];
        Serial.print("q");
        Serial.print(i+1);
        Serial.print("=");
        Serial.println(q[i]*radtodeg);
       // Serial.print(",");
     //   Serial.print("Joint_limits_min=");
     //   Serial.println(Joint_limits[i][0]);
       // if(q[i]*radtodeg<Joint_limits[i][0] || q[i]>Joint_limits[i][1]){break;}
        }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Fkine(double A1,double A2,double A3,double A4,double A5,double A6)
{

    Matrix4x4 T1;
    Matrix4x4 T2;
    Matrix4x4 T3;
    Matrix4x4 T4;
    Matrix4x4 T5;
    Matrix4x4 T6;
    Matrix4x4 T06;

    Matrix_Eye(T06);

    //create_DHM_table(out,th,alpha,d,a)
    create_DHM_table(T1,RADIANS(DHparams[0])+A1,RADIANS(DHparams[1]),DHparams[2],DHparams[3]);
    create_DHM_table(T2,RADIANS(DHparams[4])+A2,RADIANS(DHparams[5]),DHparams[6],DHparams[7]);
    create_DHM_table(T3,RADIANS(DHparams[8])+A3,RADIANS(DHparams[9]),DHparams[10],DHparams[11]);
    create_DHM_table(T4,RADIANS(DHparams[12])+A4,RADIANS(DHparams[13]),DHparams[14],DHparams[15]);
    create_DHM_table(T5,RADIANS(DHparams[16])+A5,RADIANS(DHparams[17]),DHparams[18],DHparams[19]);
    create_DHM_table(T6,RADIANS(DHparams[20])+A6,RADIANS(DHparams[21]),DHparams[22],DHparams[23]);

    //T06=T_Base*T1*T1*T2*T3*T4*T4*T5*T6
    Matrix_Multiply_Cumul(T06,T1);
    Matrix_Multiply_Cumul(T06,T2);
    Matrix_Multiply_Cumul(T06,T3);
    Matrix_Multiply_Cumul(T06,T4);
    Matrix_Multiply_Cumul(T06,T5);
    Matrix_Multiply_Cumul(T06,T6);


    current_pose[0]=T06[3];
    current_pose[1]=T06[7];
    current_pose[2]=T06[11];
    current_pose[3]=DEGREES(atan2(T06[6],T06[2]));
    current_pose[4]=DEGREES(atan2(sqrt(1-T06[10]*T06[10]),T06[10]));
    current_pose[5]=DEGREES(atan2(T06[9],-1*T06[8]));
/*
   Serial.print("Current pose=");
    for(int8_t k=0;k<6;k++)
        {
            Serial.print(current_pose[k]);
            Serial.print(",");
        }
         Serial.println("");*/
}
//----------------------------------------//
#define NUM_POINTS 20

void draw_line(float start_point[3], float end_point[3], float points[NUM_POINTS][3]) {
  // Compute the direction vector of the line
  float direction[3];
  for (int i = 0; i < 3; i++) {
    direction[i] = end_point[i] - start_point[i];
  }
  
  // Compute the step size between each point on the line
  float step_size = 1.0 / (NUM_POINTS - 1);
  
  // Compute the points on the line
  for (int i = 0; i < NUM_POINTS; i++) {
    // Compute the position of the current point
    float pos[3];
    for (int j = 0; j < 3; j++) {
      pos[j] = start_point[j] + i * step_size * direction[j];
    }
    
    // Store the current point in the points array
    for (int j = 0; j < 3; j++) {
      points[i][j] = pos[j];
    }
  }
}

#endif
