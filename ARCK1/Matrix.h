#ifndef MATRIX_H_
#define MATRIX_H_

typedef float Matrix4x4[16];
typedef float pose[6];
typedef int8_t int8;

#define PI          3.141592653589793238462
#define half_pi     1.570796326794897
#define degtorad    0.0174532925199
#define radtodeg    57.295779513082

//converts angle to degree *pi/180
double toRad(double a) { return a * degtorad; }
//converts angle to degree *180/pi
double toDeg(double a) { return a * radtodeg; }

//converts angle to degree *pi/180
double RADIANS(double a) { return a * degtorad; }
//converts angle to degree *180/pi
double DEGREES(double a) { return a * radtodeg; }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//MATRIX OPERATIONS
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//This allow to return a array as an argument instead of using global pointer
//This function Multiply the the matrix A*B and Store the Result back in "out"
/*
The answer is not stored in this format but instead -->{ -, -, -, -   ,-, -, -, -   ,-, -, -, -  ,0,0,0,1  }
  { -, -, -, -  }
  { -, -, -, -  }
  { -, -, -, -  }
  { 0, 0, 0, 1  }
*/
#define Matrix_Multiply(out,inA,inB)\
  (out)[0]  = (inA)[0]*(inB)[0] + (inA)[1]*(inB)[4] + (inA)[2]*(inB)[8]     +   (inA)[3]*(inB)[12];\
  (out)[1]  = (inA)[0]*(inB)[1] + (inA)[1]*(inB)[5] + (inA)[2]*(inB)[9]     +   (inA)[3]*(inB)[13];\
  (out)[2]  = (inA)[0]*(inB)[2] + (inA)[1]*(inB)[6] + (inA)[2]*(inB)[10]    +   (inA)[3]*(inB)[14];\
  (out)[3]  = (inA)[0]*(inB)[3] + (inA)[1]*(inB)[7] + (inA)[2]*(inB)[11]    +   (inA)[3]*(inB)[15];\
  (out)[4]  = (inA)[4]*(inB)[0] + (inA)[5]*(inB)[4] + (inA)[6]*(inB)[8]     +   (inA)[7]*(inB)[12];\
  (out)[5]  = (inA)[4]*(inB)[1] + (inA)[5]*(inB)[5] + (inA)[6]*(inB)[9]     +   (inA)[7]*(inB)[13];\
  (out)[6]  = (inA)[4]*(inB)[2] + (inA)[5]*(inB)[6] + (inA)[6]*(inB)[10]    +   (inA)[7]*(inB)[14];\
  (out)[7]  = (inA)[4]*(inB)[3] + (inA)[5]*(inB)[7] + (inA)[6]*(inB)[11]    +   (inA)[7]*(inB)[15];\
  (out)[8]  = (inA)[8]*(inB)[0] + (inA)[9]*(inB)[4] + (inA)[10]*(inB)[8]    +   (inA)[7]*(inB)[12];\
  (out)[9]  = (inA)[8]*(inB)[1] + (inA)[9]*(inB)[5] + (inA)[10]*(inB)[9]    +   (inA)[15]*(inB)[13];\
  (out)[10] = (inA)[8]*(inB)[2] + (inA)[9]*(inB)[6] + (inA)[10]*(inB)[10]   +   (inA)[15]*(inB)[14];\
  (out)[11] = (inA)[8]*(inB)[3] + (inA)[9]*(inB)[7] + (inA)[10]*(inB)[11]   +   (inA)[11]*(inB)[15];\
  (out)[12] = 0;\
  (out)[13] = 0;\
  (out)[14] = 0;\
  (out)[15] = 1;

//This function find the inverse of the matrix A and Store the Result back in "out"
#define Matrix_Inv(out,A)\
  (out)[0] = (A)[0];\
  (out)[1] = (A)[4];\
  (out)[2] = (A)[8];\
  (out)[3] = -((A)[0]*(A)[3] + (A)[4]*(A)[7] + (in)[8]*(A)[11]);\
  (out)[4] = (A)[1];\
  (out)[5] = (A)[5];\
  (out)[6] = (A)[9];\
  (out)[7] = -((A)[1]*(A)[3] + (A)[5]*(A)[7] + (A)[6]*(A)[11]);\
  (out)[8] = (A)[2];\
  (out)[9] = (A)[6];\
  (out)[10] = (A)[10];\
  (out)[11] = -((A)[8]*(A)[3] + (A)[9]*(A)[7] + (A)[10]*(A)[11]);\
  (out)[12] = 0;\
  (out)[13] = 0;\
  (out)[14] = 0;\
  (out)[15] = 1;

#define Matrix_Copy(out,in)\
  (out)[0]=(in)[0];\
  (out)[1]=(in)[1];\
  (out)[2]=(in)[2];\
  (out)[3]=(in)[3];\
  (out)[4]=(in)[4];\
  (out)[5]=(in)[5];\
  (out)[6]=(in)[6];\
  (out)[7]=(in)[7];\
  (out)[8]=(in)[8];\
  (out)[9]=(in)[9];\
  (out)[10]=(in)[10];\
  (out)[11]=(in)[11];\
  (out)[12]=(in)[12];\
  (out)[13]=(in)[13];\
  (out)[14]=(in)[14];\
  (out)[15]=(in)[15];

#define Matrix_Eye(inout)\
  (inout)[0] = 1;\
  (inout)[1] = 0;\
  (inout)[2] = 0;\
  (inout)[3] = 0;\
  (inout)[4] = 0;\
  (inout)[5] = 1;\
  (inout)[6] = 0;\
  (inout)[7] = 0;\
  (inout)[8] = 0;\
  (inout)[9] = 0;\
  (inout)[10] = 1;\
  (inout)[11] = 0;\
  (inout)[12] = 0;\
  (inout)[13] = 0;\
  (inout)[14] = 0;\
  (inout)[15] = 1;

//This function Multiply the the matrix A*B and Store the Result back in A
#define Matrix_Multiply_Cumul(A,B){\
    Matrix4x4 out;\
    Matrix_Multiply(out,A,B);\
    Matrix_Copy(A,out);}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // MATRIX_H_INCLUDED
