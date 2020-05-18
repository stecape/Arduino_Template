#ifndef fb_AlarmFunctions_h
#define fb_AlarmFunctions_h

#include "..\70_udt\_70_udt_Include.h"


void fb_Alarm(udtAlarm *alVarIN, bool boTriggerIN){

  switch (alVarIN->bySt)
  {
  case 0:
    if (boTriggerIN){
      alVarIN->bySt=1;
      alVarIN->boTrigger=true;
      alVarIN->boQ=true;
    }
    break;

  case 1:
    if (boTriggerIN && alVarIN->boAck){
      alVarIN->bySt=2;
      alVarIN->boTrigger=true;
      alVarIN->boQ=true;
    }
    else if (!boTriggerIN && alVarIN->boAck){
      alVarIN->bySt=0;
      alVarIN->boTrigger=false;
      alVarIN->boQ=false;
    }
    else if (!boTriggerIN && !alVarIN->boAck){
      alVarIN->bySt=3;
      alVarIN->boTrigger=false;
      alVarIN->boQ=true;
    }
    break;

  case 2:
    if (!boTriggerIN){
      alVarIN->bySt=0;
      alVarIN->boTrigger=false;
      alVarIN->boQ=false;
    }
    break;

  case 3:
    if (!boTriggerIN && alVarIN->boAck){
      alVarIN->bySt=0;
      alVarIN->boTrigger=false;
      alVarIN->boQ=false;
    }
    else if (boTriggerIN && !alVarIN->boAck){
      alVarIN->bySt=1;
      alVarIN->boTrigger=true;
      alVarIN->boQ=true;
    }
    else if (boTriggerIN && alVarIN->boAck){
      alVarIN->bySt=2;
      alVarIN->boTrigger=true;
      alVarIN->boQ=true;
    }
    break;

  default:
    break;

  }

  alVarIN->boAck = false;
  
};


struct db_AlarmsEvaluation {

  //Variabile di appoggio per il buzzer
  long int diBuzzerTimer=0;
  //Impostazione durata suono della sirena
  long int diBuzzerTime=3000;

};
db_AlarmsEvaluation _AlarmsEvaluation, *AlarmsEvaluation = &_AlarmsEvaluation;

void fb_AlarmsEvaluation(udtAlarm *VectAlIN, int inItemsNumber, bool *boAckIN, udtMachineReactions *ReactionsIN, bool *boAlarmPresentOUT, bool *boBuzzerOUT, bool *boNewAlarmOUT){

  //Inizializzo le flag di nuovo allarme e di nuovo allarme presente a false
  bool boNewAlarm=false;
  bool boAlarmPresent=false;
  udtMachineReactions _ReactionsMirror, *ReactionsMirror = &_ReactionsMirror;
  ReactionsMirror->boNormalStop = false;
  ReactionsMirror->boFastStop = false;
  ReactionsMirror->boWarning = false;
  ReactionsMirror->boSlowSpeed = false;
  ReactionsMirror->boNotification = false;

  for (int i=0; i<inItemsNumber; i++){

    udtAlarm * alVar = &VectAlIN[i];
    if (*boAckIN) alVar->boAck = true;

    switch (alVar->bySt)
    {
    case 0:
      /* code */
      break;
      
    case 1:
      switch (alVar->byReaction)
      {
      case REACT_NORMAL_STOP:
        boAlarmPresent=true;
        ReactionsMirror->boNormalStop = true;
        break;
      
      case REACT_FAST_STOP:
        boAlarmPresent=true;
        ReactionsMirror->boFastStop = true;
        break;
      
      case REACT_WARNING:
        boAlarmPresent=true;
        ReactionsMirror->boWarning = true;
        break;
      
      case REACT_SLOW_SPEED:
        boAlarmPresent=true;
        ReactionsMirror->boSlowSpeed = true;
        break;
      
      case REACT_NOTIFICATION:
        ReactionsMirror->boNotification = true;
        break;
      
      default:
        break;
      }

      if(alVar->byPrevSt == 0 || alVar->byPrevSt == 3) {
        AlarmsEvaluation->diBuzzerTimer = millis();
      }
      boNewAlarm = true;

      alVar->byPrevSt = 1;

      break;
      
    case 2:
      switch (alVar->byReaction)
      {
      case REACT_NORMAL_STOP:
        boAlarmPresent=true;
        ReactionsMirror->boNormalStop = true;
        break;
      
      case REACT_FAST_STOP:
        boAlarmPresent=true;
        ReactionsMirror->boFastStop = true;
        break;
      
      case REACT_WARNING:
        boAlarmPresent=true;
        ReactionsMirror->boWarning = true;
        break;
      
      case REACT_SLOW_SPEED:
        boAlarmPresent=true;
        ReactionsMirror->boSlowSpeed = true;
        break;
      
      case REACT_NOTIFICATION:
        ReactionsMirror->boNotification = true;
        break;
      
      default:
        break;
      }

      alVar->byPrevSt = 2;

      break;
      
    case 3:
      switch (alVar->byReaction)
      {
      case REACT_NORMAL_STOP:
        boAlarmPresent=true;
        ReactionsMirror->boNormalStop = true;
        break;
      
      case REACT_FAST_STOP:
        boAlarmPresent=true;
        ReactionsMirror->boFastStop = true;
        break;
      
      case REACT_WARNING:
        boAlarmPresent=true;
        ReactionsMirror->boWarning = true;
        break;
      
      case REACT_SLOW_SPEED:
        boAlarmPresent=true;
        ReactionsMirror->boSlowSpeed = true;
        break;
      
      case REACT_NOTIFICATION:
        ReactionsMirror->boNotification = true;
        break;
      
      default:
        break;
      }

      alVar->byPrevSt = 3;

      break;
    
    default:
      break;
    }
    
  }

  //Alla fine resetto il bit di ack
  *boAckIN=false;
  //Scrivo le reazioni
  ReactionsIN->boNormalStop = ReactionsMirror->boNormalStop;
  ReactionsIN->boFastStop = ReactionsMirror->boFastStop;
  ReactionsIN->boWarning = ReactionsMirror->boWarning;
  ReactionsIN->boSlowSpeed = ReactionsMirror->boSlowSpeed;
  ReactionsIN->boNotification = ReactionsMirror->boNotification;

  //Scrivo le uscite
  *boAlarmPresentOUT = boAlarmPresent;

  if(boNewAlarm && AlarmsEvaluation->diBuzzerTimer+AlarmsEvaluation->diBuzzerTime <= millis()){
    *boBuzzerOUT = true;
  } else {
    *boBuzzerOUT = false;
  }
  
  *boNewAlarmOUT = boNewAlarm; 
}

#endif