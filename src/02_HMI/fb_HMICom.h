#ifndef fb_HMICom_h
#define fb_HMICom_h

#include "..\__Include.h"

//This function composes the bundle of data to send to HMI.

struct db_HMICom {

  //Serie di instructions che arrivano dall'HMI nei primi 3 bit del byte di flag. 
  int const inSEND_VARIATIONS = 0;
  int const inSEND_HMI = 1;
  int const inSEND_ALARMS = 2;

  //byte dei Flag della comunicazione
  uint8_t byFlag;
};
db_HMICom _HMICom, *HMICom = &_HMICom;

void fb_getLogicSelections(){
  //- PLC/Logic/Selection 			- [{id:{st:#}},{id:{dy:#}},{id:{st:#,dy:#}}]
  //Scorro tutte le Logic selections
  for (byte i=0; i<l_HMI_LL; i++){

    //Creo un'istanza locale
    udtLogic * lVar = &VectLL[i];
    
    //Se è cambiata o se devo mandare tutte le hmi
    if (lVar->bySt != lVar->byPrevSt || (HMICom->byFlag && HMICom->inSEND_HMI)) {

      //Aggiorno il valore precedente
      lVar->byPrevSt = lVar->bySt;
      //Pubblico il msg
      String tpc = "PLC/Logic/Selection/"+lVar->inIndex;
      char topic [tpc.length()];
      tpc.toCharArray(topic, tpc.length());
      String msg = "{st:"+int(lVar->bySt);
      msg = msg+"}";
      char message [msg.length()];
      msg.toCharArray(message,msg.length());
      MQTTclient.publish(topic,message);

    }
  }
}

void fb_getLogicStatus(){
  //- PLC/Logic/Status					- [{id:{st:#}},{id:{dy:#}},{id:{st:#,dy:#}}]

}

void fb_getLogicButtons(){
  //- PLC/Logic/Button  				- [{id:{st:#}},{id:{dy:#}},{id:{st:#,dy:#}}]

}

void fb_getAlarmLogics(){

}

void fb_getAlarmAnalogics(){

}

void fb_getAnalogicSets(){
  //- PLC/Analogic/Set					- [{id:{vl:#}},{id:{mn:#}},{id:{mx:#}},{id:{mn:#,mx:#}},{id:{vl:#,mn:#,mx:#}},{id:{vl:#,mx:#}}]

}

void fb_getAnalogicActs(){
  //- PLC/Analogic/Act					- [{id:{vl:#}},{id:{mn:#}},{id:{mx:#}},{id:{mn:#,mx:#}},{id:{vl:#,mn:#,mx:#}},{id:{vl:#,mx:#}}]

}

void fb_HMIReceive(){
  if (!MQTTclient.connected()) {
    MQTTreconnect();
  } else{
    MQTTclient.loop();
  }
}

void fb_HMISend(int *inTsIO, int inTxRateIN){

  if (!MQTTclient.connected()) {
    MQTTreconnect();
  } else{
    fb_getLogicSelections();
    fb_getLogicStatus();
    fb_getLogicSelections();
    fb_getLogicButtons();
    fb_getAlarmLogics();
    fb_getAlarmAnalogics();
    fb_getAnalogicSets();
    fb_getAnalogicActs();
  }
}


#endif