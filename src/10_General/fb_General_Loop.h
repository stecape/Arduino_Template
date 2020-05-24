#ifndef fb_General_Loop_h
#define fb_General_Loop_h

#include "..\__Include.h"

void fb_General_Loop(){

  //Alarms management
  fb_AlarmsEvaluation(VectAl, l_Alarms, &Global->boAlarmsAck, MachineReactions, &General->boAlarmPresent, &General->boBuzzer, &General->boNewAlarm);
  
  //Setpoint limits control
  for (int i=0; i< l_HMI_S; i++)fb_Setpoint(&VectS[i]); 


  //Some alarms, logic and analogic management
   
  fb_Alarm(Alarms->Alarm0, HMI_B->Jog3->boQ0);
  fb_Alarm(Alarms->Alarm1, HMI_L->Motor3->boQ1);

  fb_LogicSelectionSR(
    bitRead(HMI_L->Motor0->byCmd, 1) and true,
    bitRead(HMI_L->Motor0->byCmd, 0) and true,
    HMI_L->Motor0
  );  
  fb_LogicSelectionSR(
    bitRead(HMI_L->Motor1->byCmd, 1) and true,
    bitRead(HMI_L->Motor1->byCmd, 0) and true,
    HMI_L->Motor1
  );  
  fb_LogicSelectionSR(
    bitRead(HMI_L->Motor2->byCmd, 1) and true,
    bitRead(HMI_L->Motor2->byCmd, 0) and true,
    HMI_L->Motor2
  );  
  fb_LogicSelectionSR(
    bitRead(HMI_L->Motor3->byCmd, 1) and true,
    bitRead(HMI_L->Motor3->byCmd, 0) and true,
    HMI_L->Motor3
  );  
  fb_LogicSelectionSR(
    bitRead(HMI_L->Motor4->byCmd, 1) and true,
    bitRead(HMI_L->Motor4->byCmd, 0) and true,
    HMI_L->Motor4
  );

  fb_LogicButton(
    HMI_B->Jog0,
    bitRead(HMI_B->Jog0->byCmd, 0),false,false,false,false,false,false,false
  );
  fb_LogicButton(
    HMI_B->Jog1,
    bitRead(HMI_B->Jog1->byCmd, 0),bitRead(HMI_B->Jog1->byCmd, 1) and HMI_L->Motor0->boQ1,false,false,false,false,false,false
  );
  fb_LogicButton(
    HMI_B->Jog2,
    bitRead(HMI_B->Jog2->byCmd, 0),false,false,false,false,false,false,false
  );
  fb_LogicButton(
    HMI_B->Jog3,
    bitRead(HMI_B->Jog3->byCmd, 0),false,false,false,false,false,false,false
  );
  fb_LogicButton(
    HMI_B->Jog4,
    bitRead(HMI_B->Jog4->byCmd, 0),false,false,false,false,false,false,false
  );
  
  digitalWrite(LED_BUILTIN, HMI_B->Jog1->boQ0);
  
  HMI_A->Current0->inVal=HMI_S->Speed0->inVal*2;
  HMI_A->Current1->inVal=HMI_S->Speed1->inVal*2;
  HMI_A->Micrometer1->inVal=Micrometer1->reValue;
  HMI_A->Current3->inVal=HMI_S->Speed3->inVal*2;
  HMI_A->Current4->inVal=HMI_S->Speed4->inVal*2;

  //Loop cycle time
  Global->diCycleTime = micros()-Global->diPrevCycleTime;
  Global->diPrevCycleTime = micros();
  HMI_A->CycleTime->inVal = (int)(Global->diCycleTime);
}


#endif