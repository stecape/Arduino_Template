#ifndef fb_General_Loop_h
#define fb_General_Loop_h

#include "..\__Include.h"

void fb_General_Loop(){

  //Alarms management
  fb_AlarmsEvaluation(VectAlL, l_AlarmsL, &Global->boAlarmsAck, MachineReactions, &General->boAlarmPresent, &General->boBuzzer, &General->boNewAlarm);
  
  //Setpoint limits control
  for (int i=0; i< l_HMI_AS; i++)fb_Setpoint(&VectAS[i]); 


  //Some alarms, logic and analogic management
   
  fb_Alarm(AlarmsL->Alarm0, HMI_LB->Jog3->boQ0);
  fb_Alarm(AlarmsL->Alarm1, HMI_LL->Motor3->boQ1);

  fb_LogicSelectionSR(
    bitRead(HMI_LL->Motor0->byCmd, 1) and true,
    bitRead(HMI_LL->Motor0->byCmd, 0) and true,
    HMI_LL->Motor0
  );  
  fb_LogicSelectionSR(
    bitRead(HMI_LL->Motor1->byCmd, 1) and true,
    bitRead(HMI_LL->Motor1->byCmd, 0) and true,
    HMI_LL->Motor1
  );  
  fb_LogicSelectionSR(
    bitRead(HMI_LL->Motor2->byCmd, 1) and true,
    bitRead(HMI_LL->Motor2->byCmd, 0) and true,
    HMI_LL->Motor2
  );  
  fb_LogicSelectionSR(
    bitRead(HMI_LL->Motor3->byCmd, 1) and true,
    bitRead(HMI_LL->Motor3->byCmd, 0) and true,
    HMI_LL->Motor3
  );  
  fb_LogicSelectionSR(
    bitRead(HMI_LL->Motor4->byCmd, 1) and true,
    bitRead(HMI_LL->Motor4->byCmd, 0) and true,
    HMI_LL->Motor4
  );

  fb_LogicButton(
    HMI_LB->Jog0,
    bitRead(HMI_LB->Jog0->byCmd, 0),false,false,false,false,false,false,false
  );
  fb_LogicButton(
    HMI_LB->Jog1,
    bitRead(HMI_LB->Jog1->byCmd, 0),bitRead(HMI_LB->Jog1->byCmd, 1) and HMI_LL->Motor0->boQ1,false,false,false,false,false,false
  );
  fb_LogicButton(
    HMI_LB->Jog2,
    bitRead(HMI_LB->Jog2->byCmd, 0),false,false,false,false,false,false,false
  );
  fb_LogicButton(
    HMI_LB->Jog3,
    bitRead(HMI_LB->Jog3->byCmd, 0),false,false,false,false,false,false,false
  );
  fb_LogicButton(
    HMI_LB->Jog4,
    bitRead(HMI_LB->Jog4->byCmd, 0),false,false,false,false,false,false,false
  );
  
  digitalWrite(LED_BUILTIN, HMI_LB->Jog1->boQ0);
  
  HMI_AA->Current0->inVal=HMI_AS->Speed0->inVal*2;
  HMI_AA->Current1->inVal=HMI_AS->Speed1->inVal*2;
  HMI_AA->Micr1->inVal=(int)(Micrometer1->reValue*100);
  HMI_AA->Current3->inVal=HMI_AS->Speed3->inVal*2;
  HMI_AA->Current4->inVal=HMI_AS->Speed4->inVal*2;

  //Loop cycle time
  Global->diCycleTime = micros()-Global->diPrevCycleTime;
  Global->diPrevCycleTime = micros();
  HMI_AA->CycleTime->inVal = (int)(Global->diCycleTime);
}


#endif