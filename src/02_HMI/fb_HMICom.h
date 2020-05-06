#ifndef fb_HMICom_h
#define fb_HMICom_h

#include "..\__Include.h"

//This function composes the bundle of data to send to HMI. It will be something like
//{"Wd":1,"Logic":"00020002000200020002","Act":"00280028002800640028","Alarm":"01010"}

struct db_HMICom {
  //Nuovo frame ricevuto dal PC
  bool boNewFrameFromPC;
  //ricezione frame in corso da PC
  bool boReceiving;
  //frame ricevuto corrotto
  bool boBroken;
  //conteggio carattere ricevuto
  int inCount;
  //Lunghezza attuale buffer
  int inLength;
  //Lunghezza del buffer di recezione da HMI
  uint8_t byBuffer[1024];
  //byte dei Flag della comunicazione
  uint8_t byFlags;
  //WatchDog
  //se non mi arrivano frame per Config->wdTimeout ms, il wdCount raggiunge il Config->wdTimeout e resetto i buttons.
  //diversamente aggiorno il wdCount a millis()
  //recWd è il ritorno da PI
  int inWdCount=0;
};
db_HMICom _HMICom, *HMICom = &_HMICom;

void fb_BuildTXData(){

  //inversione del bit di Wd verso l'HMI
  if (bitRead(HMICom->byFlags, 0) == false) {
    bitWrite(HMICom->byFlags, 0, true);
  } else {
    bitWrite(HMICom->byFlags, 0, false);
  }

  //salvo il valore del bit gimme everything
  bool boGimmeEverything = bitRead(HMICom->byFlags, 2);

  //resetto il flag gimme everything
  bitWrite(HMICom->byFlags, 2, false);

  //inizializzo il cursore e inizializzo il frame con lo starter e il byte dei flags, saltando la lunghezza della trama che la scrivo alla fine
  int inCursor=0;
  HMICom->byBuffer[inCursor] = Config->START_MARKER;
  HMICom->byBuffer[inCursor+3] = HMICom->byFlags;
  inCursor+=4;

  //Logics
  //il flag di "cambiamento nei valori" viene inizializzato al valore della flag gimme everything, così se fosse true siamo già a posto nel for che c'è dopo.
  bool boChanged=boGimmeEverything;
  int inOffset=2;
  uint8_t byCounter=0;

  for (uint8_t i=0; i<l_HMI_L; i++){
    udtLogic *lVal = &VectL[i];
    if (lVal->byPrevSt!=lVal->bySt || boGimmeEverything){
      boChanged=true;
      HMICom->byBuffer[inCursor+inOffset] = i;
      HMICom->byBuffer[inCursor+inOffset+1] = lVal->bySt;
      lVal->byPrevSt=lVal->bySt;
      inOffset+=2;
      byCounter++;
    }
  }

  //Se qualcosa è cambiato nelle logiche allora metto la L ed avanzo col cursore, sennò rimango dove sono e procedo coi buttons
  if(boChanged) {
    HMICom->byBuffer[inCursor]='L';
    HMICom->byBuffer[inCursor+1]=byCounter;
    inCursor+=inOffset;
  }

  //Buttons
  //il flag di "cambiamento nei valori" viene inizializzato al valore della flag gimme everything, così se fosse true siamo già a posto nel for che c'è dopo.
  boChanged=boGimmeEverything;
  inOffset=2;
  byCounter=0;

  for (uint8_t i=0; i<l_HMI_B; i++){
    udtButton *bVal = &VectB[i];
    if (bVal->byPrevSt!=bVal->bySt || boGimmeEverything){
      boChanged=true;
      HMICom->byBuffer[inCursor+inOffset] = i;
      HMICom->byBuffer[inCursor+inOffset+1] = bVal->bySt;
      bVal->byPrevSt=bVal->bySt;
      inOffset+=2;
      byCounter++;
    }
  }

  //Se qualcosa è cambiato nei buttons allora metto la B ed avanzo col cursore, sennò rimango dove sono e procedo coi faults
  if(boChanged) {
    HMICom->byBuffer[inCursor]='B';
    HMICom->byBuffer[inCursor+1]=byCounter;
    inCursor+=inOffset;
  }

  //Faults
  //il flag di "cambiamento nei valori" viene inizializzato al valore della flag gimme everything, così se fosse true siamo già a posto nel for che c'è dopo.
  boChanged=boGimmeEverything;
  inOffset=2;
  byCounter=0;

  for (uint8_t i=0; i<l_Alarms; i++){
    udtAlarm *alVal = &VectAl[i];
    if (alVal->byPrevSt!=alVal->bySt || boGimmeEverything){
      boChanged=true;
      HMICom->byBuffer[inCursor+inOffset] = i;
      HMICom->byBuffer[inCursor+inOffset+1] = alVal->bySt;
      alVal->byPrevSt=alVal->bySt;
      inOffset+=2;
      byCounter++;
    }
  }

  //Se qualcosa è cambiato nei faults allora metto la F ed avanzo col cursore, sennò rimango dove sono e procedo con gli actuals
  if(boChanged) {
    HMICom->byBuffer[inCursor]='F';
    HMICom->byBuffer[inCursor+1]=byCounter;
    inCursor+=inOffset;
  }

  //Actuals
  //il flag di "cambiamento nei valori" viene inizializzato al valore della flag gimme everything, così se fosse true siamo già a posto nel for che c'è dopo.
  boChanged=boGimmeEverything;
  inOffset=2;
  byCounter=0;

  for (uint8_t i=0; i<l_HMI_A; i++){
    udtAct *aVal = &VectA[i];
    if (aVal->inPrevVal!=aVal->inVal || boGimmeEverything){
      boChanged=true;
      HMICom->byBuffer[inCursor+inOffset] = i;
      HMICom->byBuffer[inCursor+inOffset+1] = highByte(aVal->inVal);
      HMICom->byBuffer[inCursor+inOffset+2] = lowByte(aVal->inVal);
      aVal->inPrevVal=aVal->inVal;
      inOffset+=3;
      byCounter++;
    }
  }

  //Se qualcosa è cambiato negli Actual allora metto la A ed avanzo col cursore, sennò rimango dove sono e procedo coi Setpoints
  if(boChanged) {
    HMICom->byBuffer[inCursor]='A';
    HMICom->byBuffer[inCursor+1]=byCounter;
    inCursor+=inOffset;
  }

  //Setpoints
  //Se il flag gimme everything è a true devo mandare anche i set. 
  //il flag di "cambiamento nei valori" viene inizializzato al valore della flag gimme everything, così se fosse true siamo già a posto nel for che c'è dopo.
  boChanged=boGimmeEverything;
  inOffset=2;
  byCounter=0;

  if (boChanged) {
    for (uint8_t i=0; i<l_HMI_S; i++){
      udtSet *sVal = &VectS[i];
      if (sVal->inPrevVal!=sVal->inVal || boGimmeEverything){
        boChanged=true;
        HMICom->byBuffer[inCursor+inOffset] = i;
        HMICom->byBuffer[inCursor+inOffset+1] = highByte(sVal->inVal);
        HMICom->byBuffer[inCursor+inOffset+2] = lowByte(sVal->inVal);
        sVal->inPrevVal=sVal->inVal;
        inOffset+=3;
        byCounter++;
      }
    }

  //Metto la S ed avanzo col cursore
    HMICom->byBuffer[inCursor]='S';
    HMICom->byBuffer[inCursor+1]=byCounter;
    inCursor+=inOffset;
  }
  //quindi procedo col terminatore
  HMICom->byBuffer[inCursor]=Config->END_MARKER;
  
  //ora che so qual è la lunghezza del frame la aggiorno
  HMICom->byBuffer[1]=highByte(inCursor+1);
  HMICom->byBuffer[2]=lowByte(inCursor+1);

  //trasmetto
  Serial.write(HMICom->byBuffer, inCursor+1);
};

void fb_ParseRecData(){
  //Ho ricevuto una trama da PI, quindi la comunicazione è sana.
  //Aggiorno il wdCount per non far scattare il watchdog che mi resetta i pulsanti
  HMICom->inWdCount=millis();

  //inizializzazione cursore
  int inCursor = 0;
  //calcolo la lunghezza del frame prendendola dai primi due byte del buffer. Tolgo due per escludere i caratteri di apertura e chiusura frame
  int inLength = HMICom->byBuffer[inCursor]*255+HMICom->byBuffer[inCursor+1]-2;
  //sposto il cursore (da qui in poi questo commento verrà omesso)
  inCursor+=2;
  //salvo il byte dei flags ricevuto
  HMICom->byFlags = HMICom->byBuffer[inCursor];
  inCursor++;

  //parsifico il payload
  while(inCursor<inLength){
    int inItemsN = HMICom->byBuffer[inCursor+1];
    inCursor+=2;
    switch ((char)HMICom->byBuffer[inCursor-2]){
    case 'S':
      for(int i=0; i<inItemsN; i++){
        udtSet *sVar = &VectS[HMICom->byBuffer[inCursor]];
        sVar->inVal = HMICom->byBuffer[inCursor+1]*255+HMICom->byBuffer[inCursor+2];
        inCursor+=3;
      }
      break;
      
    case 'L':
      for(int i=0; i<inItemsN; i++){
        udtLogic *lVar = &VectL[HMICom->byBuffer[inCursor]];
        lVar->byCmd = HMICom->byBuffer[inCursor+1];
        inCursor+=2;
      }
      break;

    case 'B':
      for(int i=0; i<inItemsN; i++){
        udtButton *bVar = &VectB[HMICom->byBuffer[inCursor]];
        bVar->byCmd = HMICom->byBuffer[inCursor+1];
        inCursor+=2;
      }
      break;
    }
  }
}

void fb_HMIReceive (uint8_t byStartMarkerIN, uint8_t byEndMarkerIN) {
  while(Serial.available() > 0 && HMICom->boNewFrameFromPC == false) {
    //inizializzo boBroken a 1
    HMICom->boBroken = true;
    //leggo un carattere
    uint8_t ch = Serial.read();
    //se stavo già ricevendo
    if(HMICom->boReceiving){
      //incremento il contatore dei caratteri ricevuti
      HMICom->inCount++;
      //se ho già ricevuto 3 caratteri vuol dire che ho la lunghezza del frame disponibile
      if(HMICom->inCount==3){
        //la lunghezza del frame è contenuta nel carattere precedente (salvato nell'elemento 0 del buffer)
        //e dal carattere appena letto. Il valore della int16 della lunghezza sarà byBuffer[0]*255+ch
        HMICom->inLength=HMICom->byBuffer[0]*255+ch;
      };
      //se il conteggio dei byte ricevuti è uguale alla lunghezza del frame
      if(HMICom->inCount==HMICom->inLength){
        //boBroken sarà false se ch è il terminatore di frame
        HMICom->boBroken = ch==byEndMarkerIN;
        //setto la flag di nuova frame ricevuta
        HMICom->boNewFrameFromPC = true;
      } else {
        //sennò vuol dire che non ho ancora finito di salvare il frame e semplicemente salvo
        //il ch nel buffer
        HMICom->byBuffer[HMICom->inCount-1] = ch;
      }
    //se invece non stavo ricevendo
    } else {
      //e il carattere ricevuto è l'apri frame
      if (ch==byStartMarkerIN){
        //setto il flag di ricezione in corso
        HMICom->boReceiving=true;
        //inizializzo il contatore di byte ricevuti
        HMICom->inCount=1;
        //inizializzo la lunghezza ad un numero qualsiasi superiore a 3
        //(non appena in contatore raggiungerà 3 saremo in grado di aggiornare la  lunghezza col valore reale) 
        HMICom->inLength=5;
      }
    }
  }

  //Se ho ricevuto un frame dal PC
  if(HMICom->boNewFrameFromPC){
    //e non è broken
    if(!HMICom->boBroken){
      //lo parsifico
      fb_ParseRecData();
    }
    //dopodichè resetto i flag
    HMICom->boNewFrameFromPC=false;
    HMICom->boReceiving=false;
  }

  
  //Watchdog che chiama la callback (resetta i buttons) se non c'è comunicazione col PI.
  //wdCount viene incrementato ogni volta che si riceve una trama dal PI col wd corretto.
  if ((HMICom->inWdCount+Config->inWdTimeout) <= millis()){
    fb_ResetButtons(l_HMI_B, VectB);
    HMICom->inWdCount=millis();
  }
}


void fb_HMISend(int *inTsIO, int inTxRateIN){
  //Trasmettiamo verso l'HMI non prima di ts+txRate millisecondi e se il buffer è vuoto
  if(millis() >= *inTsIO+inTxRateIN){

    fb_BuildTXData();

    *inTsIO= millis();
  }
}


#endif