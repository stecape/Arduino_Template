#ifndef db_HMI_h
#define db_HMI_h

#include "..\70_udt\_70_udt_Include.h"

//Vects length definition
const int l_HMI_L= 5;
const int l_HMI_B= 5;
const int l_HMI_S= 5;
const int l_HMI_A= 5;
const int l_Alarms= 5;

//Logic vars. lVecL is the lenght of the Logic variables array.
udtLogic VectL[l_HMI_L];

//Here you can give a name to the variable in the vect, for an easier use in the program. Only Logic type is allowed in this array.
struct db_HMI_L {
  udtLogic *Motor0 = &VectL[0];
  udtLogic *Motor1 = &VectL[1];
  udtLogic *Motor2 = &VectL[2];
  udtLogic *Motor3 = &VectL[3];
  udtLogic *Motor4 = &VectL[4];
};

db_HMI_L _HMI_L, *HMI_L = &_HMI_L;




//Button vars. lVecB is the lenght of the Button variables array.
udtButton VectB[l_HMI_B];

//Here you can give a name to the variable in the vect, for an easier use in the program. Only Button type is allowed in this array.
struct db_HMI_B {
  udtButton *Jog0 = &VectB[0];
  udtButton *Jog1 = &VectB[1];
  udtButton *Jog2 = &VectB[2];
  udtButton *Jog3 = &VectB[3];
  udtButton *Jog4 = &VectB[4];
};

db_HMI_B _HMI_B, *HMI_B = &_HMI_B;




//Setpoint vars. lVecS is the lenght of the Setpoint variables array.
udtSet VectS[l_HMI_S];

//Here you can give a name to the variable in the vect, for an easier use in the program. Only Set type is allowed in this array.
struct db_HMI_S {
  udtSet *Speed0 = &VectS[0];
  udtSet *Speed1 = &VectS[1];
  udtSet *Speed2 = &VectS[2];
  udtSet *Speed3 = &VectS[3];
  udtSet *Speed4 = &VectS[4];
};

db_HMI_S _HMI_S, *HMI_S = &_HMI_S;




//Actual vars. lVecS is the lenght of the Setpoint variables array.
udtAct VectA[l_HMI_A];

//Here you can give a name to the variable in the vect, for an easier use in the program. Only Act type is allowed in this array.
struct db_HMI_A {
udtAct *Current0 = &VectA[0];
udtAct *Current1 = &VectA[1];
udtAct *Current2 = &VectA[2];
udtAct *Current3 = &VectA[3];
udtAct *Current4 = &VectA[4];
};

db_HMI_A _HMI_A, *HMI_A = &_HMI_A;




//Alarm vars. lVecAl is the lenght of the Alarm variables array.
udtAlarm VectAl[l_Alarms];

//Here you can give a name to the variable in the vect, for an easier use in the program. Only Alarm type is allowed in this array.
struct db_Alarms {
udtAlarm *Fault0 = &VectAl[0];
udtAlarm *Fault1 = &VectAl[1];
udtAlarm *Fault2 = &VectAl[2];
udtAlarm *Fault3 = &VectAl[3];
udtAlarm *Fault4 = &VectAl[4];
};

db_Alarms _Alarms, *Alarms = &_Alarms;

#endif