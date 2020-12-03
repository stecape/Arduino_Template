#ifndef db_HMI_h
#define db_HMI_h

#include "..\70_udt\_70_udt_Include.h"

//Vects length definition
const int l_HMI_LL= 5;
const int l_HMI_LB= 5;
const int l_HMI_LS= 5;
const int l_HMI_AS= 6;
const int l_HMI_AA= 6;
const int l_AlarmsL= 5;
const int l_AlarmsA= 5;


//Machine reactions definition
const byte REACT_NORMAL_STOP = 1;
const byte REACT_FAST_STOP = 2;
const byte REACT_WARNING = 3;
const byte REACT_SLOW_SPEED = 4;
const byte REACT_NOTIFICATION = 5;


//Logic vars. lVecL is the lenght of the Logic variables array.
udtLogic VectLL[l_HMI_LL];

//Here you can give a name to the variable in the vect, for an easier use in the program. Only Logic type is allowed in this array.
struct db_HMI_LL {
	udtLogic *Motor0 = &VectLL[0];
	udtLogic *Motor1 = &VectLL[1];
	udtLogic *Motor2 = &VectLL[2];
	udtLogic *Motor3 = &VectLL[3];
	udtLogic *Motor4 = &VectLL[4];  
};

db_HMI_LL _HMI_LL, *HMI_LL = &_HMI_LL;




//Button vars. lVecB is the lenght of the Button variables array.
udtButton VectLB[l_HMI_LB];

//Here you can give a name to the variable in the vect, for an easier use in the program. Only Button type is allowed in this array.
struct db_HMI_LB {
	udtButton *Jog0 = &VectLB[0];
	udtButton *Jog1 = &VectLB[1];
	udtButton *Jog2 = &VectLB[2];
	udtButton *Jog3 = &VectLB[3];
	udtButton *Jog4 = &VectLB[4];  
};

db_HMI_LB _HMI_LB, *HMI_LB = &_HMI_LB;




//Setpoint vars. lVecS is the lenght of the Setpoint variables array.
udtSet VectAS[l_HMI_AS];

//Here you can give a name to the variable in the vect, for an easier use in the program. Only Set type is allowed in this array.
struct db_HMI_AS {
	udtSet *Speed0 = &VectAS[0];
	udtSet *Speed1 = &VectAS[1];
	udtSet *Speed2 = &VectAS[2];
	udtSet *Speed3 = &VectAS[3];
	udtSet *Speed4 = &VectAS[4];  
};

db_HMI_AS _HMI_AS, *HMI_AS = &_HMI_AS;




//Actual vars. lVecS is the lenght of the Setpoint variables array.
udtAct VectAA[l_HMI_AA];

//Here you can give a name to the variable in the vect, for an easier use in the program. Only Act type is allowed in this array.
struct db_HMI_AA {
	udtAct *Current0 = &VectAA[0];
	udtAct *Current1 = &VectAA[1];
	udtAct *Micr1 = &VectAA[2];
	udtAct *Current3 = &VectAA[3];
	udtAct *Current4 = &VectAA[4];
	udtAct *CycleTime = &VectAA[5];
};

db_HMI_AA _HMI_AA, *HMI_AA = &_HMI_AA;




//Alarm vars. lVecAl is the lenght of the Alarm variables array.
udtAlarm VectAlL[l_AlarmsL];

//Here you can give a name to the variable in the vect, for an easier use in the program. Only Alarm type is allowed in this array.
struct db_AlarmsL {
	udtAlarm *Alarm0 = &VectAlL[0];
	udtAlarm *Alarm1 = &VectAlL[1];
	udtAlarm *Alarm2 = &VectAlL[2];
	udtAlarm *Alarm3 = &VectAlL[3];
	udtAlarm *Alarm4 = &VectAlL[4];
};

db_AlarmsL _AlarmsL, *AlarmsL = &_AlarmsL;
udtMachineReactions _MachineReactions, *MachineReactions = &_MachineReactions;

//Setpoints limits and indexes initialization
void fb_HMIInit(){

  //Inizializzazione indici Logiche
  for(int i=0; i<l_HMI_LL; i++) {
      udtLogic *lVar = &VectLL[i];
      lVar->inIndex = i;
  }
  
  //Inizializzazione indici setpoints
  for(int i=0; i<l_HMI_AS; i++) {
      udtSet *sVar = &VectAS[i];
      sVar->inIndex = i;
  }

  //Inizializzazione Limiti Setpoints
	HMI_AS->Speed0->inMin=20;
	HMI_AS->Speed0->inMax=600;
	HMI_AS->Speed1->inMin=20;
	HMI_AS->Speed1->inMax=600;
	HMI_AS->Speed2->inMin=20;
	HMI_AS->Speed2->inMax=600;
	HMI_AS->Speed3->inMin=20;
	HMI_AS->Speed3->inMax=600;
	HMI_AS->Speed4->inMin=20;
	HMI_AS->Speed4->inMax=600;

  //Inizializzazione reazioni Allarmi
	AlarmsL->Alarm0->byReaction = REACT_WARNING;
	AlarmsL->Alarm1->byReaction = REACT_NORMAL_STOP;
	AlarmsL->Alarm2->byReaction = REACT_WARNING;
	AlarmsL->Alarm3->byReaction = REACT_WARNING;
	AlarmsL->Alarm4->byReaction = REACT_NOTIFICATION;
}

#endif