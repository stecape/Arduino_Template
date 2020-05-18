#ifndef fb_HMICom_h
#define fb_HMICom_h

#include "..\__Include.h"

//This function composes the bundle of data to send to HMI. It will be something like
//{"Wd":1,"Logic":"00020002000200020002","Act":"00280028002800640028","Alarm":"01010"}

struct db_HMICom {

  //Serie di instructions che arrivano dall'HMI nei primi 3 bit del byte di flag. 
  int const inSEND_VARIATIONS = 0;
  int const inSEND_LOGICS = 1;
  int const inSEND_BUTTONS = 2;
  int const inSEND_SETS = 3;
  int const inSEND_ACTS = 4;
  int const inSEND_ALARMS = 5;

  //byte dei Flag della comunicazione
  uint8_t byFlag;

  //WatchDog
  //se non mi arrivano frame per Config->wdTimeout ms, il wdCount raggiunge il Config->wdTimeout e resetto i buttons.
  //diversamente aggiorno il wdCount a millis()
  //recWd è il ritorno da PI
  int inWdCount=0;
};
db_HMICom _HMICom, *HMICom = &_HMICom;

void fb_getLogics(byte byInstr, int * inCursor){
  
  //Agisco solo se l'istruzione è inSEND_VARIATIONS o inSEND_LOGICS
  if (byInstr == HMICom->inSEND_VARIATIONS || byInstr == HMICom->inSEND_LOGICS) {

    //inizializzo il flag di changed a true se l'istruzione ricevuta è inSEND_LOGICS. Utilizzerò questa flag per decidere se scrivere la L nel buffer ed eventualmente per spostare il cursore se alla fine qualcosa sarà cambiato
    bool boChanged = byInstr == HMICom->inSEND_LOGICS;
    //inizializzo l'offset, che faccio crescere per non spostare il cursore dalla posizione iniziale nel buffer
    int inOffset = 2;
    //inizializzo il contatore delle variabili logiche
    byte byCounter = 0;
    
    //Scorro tutte le variabili logiche
    for (byte i=0; i<l_HMI_L; i++){

      //Creo un'istanza locale
      udtLogic * lVar = &VectL[i];
      
      //Se è cambiata o se devo mandare tutte le logiche
      if (lVar->bySt != lVar->byPrevSt || byInstr == HMICom->inSEND_LOGICS) {
        
        //Aggiorno la flag di changed
        boChanged = true;

        //incremento il contatore
        byCounter++;

        //Aggiorno il valore precedente
        lVar->byPrevSt = lVar->bySt;

        //Inserisco l'indice della variabile nel buffer
        myTransfer.txBuff[*inCursor+inOffset] = i;
        //Inserisco il valore della variabile nel buffer
        myTransfer.txBuff[*inCursor+inOffset+1] = lVar->bySt;

        //sposto l'offset in avanti
        inOffset+=2;
        
      }
    }

    //se qualcosa è cambiato e se il conteggio è > 0
    if (boChanged && byCounter > 0) {
      //allora inserisco la L ed il numero di items nel buffer
      myTransfer.txBuff[*inCursor] = 'L';
      myTransfer.txBuff[*inCursor+1] = byCounter;
      //ed aggiorno la posizione del cursore
      *inCursor = *inCursor + inOffset;
    }  
    
  }
}

void fb_getButtons(byte byInstr, int * inCursor){
  
  //Agisco solo se l'istruzione è inSEND_VARIATIONS o inSEND_BUTTONS
  if (byInstr == HMICom->inSEND_VARIATIONS || byInstr == HMICom->inSEND_BUTTONS) {

    //inizializzo il flag di changed a true se l'istruzione ricevuta è inSEND_BUTTONS. Utilizzerò questa flag per decidere se scrivere la B nel buffer ed eventualmente per spostare il cursore se alla fine qualcosa sarà cambiato
    bool boChanged = byInstr == HMICom->inSEND_BUTTONS;
    //inizializzo l'offset, che faccio crescere per non spostare il cursore dalla posizione iniziale nel buffer
    int inOffset = 2;
    //inizializzo il contatore delle variabili buttons
    byte byCounter = 0;
    
    //Scorro tutte le variabili buttons
    for (byte i=0; i<l_HMI_B; i++){

      //Creo un'istanza locale
      udtButton * bVar = &VectB[i];
      
      //Se è cambiata o se devo mandare tutti i buttons
      if (bVar->bySt != bVar->byPrevSt || byInstr == HMICom->inSEND_BUTTONS) {
        
        //Aggiorno la flag di changed
        boChanged = true;

        //incremento il contatore
        byCounter++;

        //Aggiorno il valore precedente
        bVar->byPrevSt = bVar->bySt;

        //Inserisco l'indice della variabile nel buffer
        myTransfer.txBuff[*inCursor+inOffset] = i;
        //Inserisco il valore della variabile nel buffer
        myTransfer.txBuff[*inCursor+inOffset+1] = bVar->bySt;

        //sposto l'offset in avanti
        inOffset+=2;
        
      }
    }

    //se qualcosa è cambiato e se il conteggio è > 0
    if (boChanged && byCounter > 0) {
      //allora inserisco la B ed il numero di items nel buffer
      myTransfer.txBuff[*inCursor] = 'B';
      myTransfer.txBuff[*inCursor+1] = byCounter;
      //ed aggiorno la posizione del cursore
      *inCursor = *inCursor + inOffset;
    }  
    
  }
}

void fb_getAlarms(byte byInstr, int * inCursor){
  
  //Agisco solo se l'istruzione è inSEND_VARIATIONS o inSEND_ALARMS
  if (byInstr == HMICom->inSEND_VARIATIONS || byInstr == HMICom->inSEND_ALARMS) {

    //inizializzo il flag di changed a true se l'istruzione ricevuta è inSEND_ALARMS. Utilizzerò questa flag per decidere se scrivere la F nel buffer ed eventualmente per spostare il cursore se alla fine qualcosa sarà cambiato
    bool boChanged = byInstr == HMICom->inSEND_ALARMS;
    //inizializzo l'offset, che faccio crescere per non spostare il cursore dalla posizione iniziale nel buffer
    int inOffset = 2;
    //inizializzo il contatore delle variabili alarms
    byte byCounter = 0;
    
    //Scorro tutte le variabili alarms
    for (byte i=0; i<l_Alarms; i++){

      //Creo un'istanza locale
      udtAlarm * alVar = &VectAl[i];
      
      //Se è cambiata o se devo mandare tutti gli alarms
      if (alVar->bySt != alVar->byLastStSent || byInstr == HMICom->inSEND_ALARMS) {
        
        //Aggiorno la flag di changed
        boChanged = true;

        //incremento il contatore
        byCounter++;

        //Aggiorno il valore precedente
        alVar->byLastStSent = alVar->bySt;

        //Inserisco l'indice della variabile nel buffer
        myTransfer.txBuff[*inCursor+inOffset] = i;
        //Inserisco il valore della variabile nel buffer
        myTransfer.txBuff[*inCursor+inOffset+1] = alVar->bySt;

        //sposto l'offset in avanti
        inOffset+=2;
        
      }
    }

    //se qualcosa è cambiato e se il conteggio è > 0
    if (boChanged && byCounter > 0) {
      //allora inserisco la F ed il numero di items nel buffer
      myTransfer.txBuff[*inCursor] = 'F';
      myTransfer.txBuff[*inCursor+1] = byCounter;
      //ed aggiorno la posizione del cursore
      *inCursor = *inCursor + inOffset;
    }  
    
  }
}

void fb_getSets(byte byInstr, int * inCursor){
  
  //Agisco solo se l'istruzione è false o inSEND_SETS
  if (byInstr == HMICom->inSEND_VARIATIONS || byInstr == HMICom->inSEND_SETS) {
    
    //inizializzo il flag di changed a true se l'istruzione ricevuta è inSEND_SETS. Utilizzerò questa flag per decidere se scrivere la S nel buffer ed eventualmente per spostare il cursore se alla fine qualcosa sarà cambiato
    bool boChanged = byInstr == HMICom->inSEND_SETS;
    //inizializzo l'offset, che faccio crescere per non spostare il cursore dalla posizione iniziale nel buffer
    int inOffset = 2;
    //inizializzo il contatore delle variabili setpoints
    byte byCounter = 0;
    
    //Scorro tutte le variabili setpoints
    for (byte i=0; i<l_HMI_S; i++){

      //Creo un'istanza locale
      udtSet * sVar = &VectS[i];

      //Se è cambiata o se devo mandare tutti i setpoints
      if (sVar->inHMIVal != sVar->inPrevVal || byInstr == HMICom->inSEND_SETS) {
        
        //Aggiorno la flag di changed
        boChanged = true;

        //incremento il contatore
        byCounter++;

        //Aggiorno il valore precedente
        sVar->inPrevVal = sVar->inHMIVal;

        //Inserisco l'indice della variabile nel buffer
        myTransfer.txBuff[*inCursor+inOffset] = i;
        //Inserisco il valore della variabile nel buffer
        myTransfer.txBuff[*inCursor+inOffset+1] = highByte(sVar->inHMIVal);
        myTransfer.txBuff[*inCursor+inOffset+2] = lowByte(sVar->inHMIVal);

        //sposto l'offset in avanti
        inOffset+=3;
        
      }
    }

    //se qualcosa è cambiato e se il conteggio è > 0
    if (boChanged && byCounter > 0) {
      //allora inserisco la S ed il numero di items nel buffer
      myTransfer.txBuff[*inCursor] = 'S';
      myTransfer.txBuff[*inCursor+1] = byCounter;
      //ed aggiorno la posizione del cursore
      *inCursor = *inCursor + inOffset;
    }  
    
  }
}

void fb_getActs(byte byInstr, int * inCursor){
  
  //Agisco solo se l'istruzione è inSEND_VARIATIONS o inSEND_ACTS
  if (byInstr == HMICom->inSEND_VARIATIONS || byInstr == HMICom->inSEND_ACTS) {

    //inizializzo il flag di changed a true se l'istruzione ricevuta è inSEND_ACTS. Utilizzerò questa flag per decidere se scrivere la A nel buffer ed eventualmente per spostare il cursore se alla fine qualcosa sarà cambiato
    bool boChanged = byInstr == HMICom->inSEND_ACTS;
    //inizializzo l'offset, che faccio crescere per non spostare il cursore dalla posizione iniziale nel buffer
    int inOffset = 2;
    //inizializzo il contatore delle variabili actuals
    byte byCounter = 0;
    
    //Scorro tutte le variabili actuals
    for (byte i=0; i<l_HMI_A; i++){

      //Creo un'istanza locale
      udtAct * aVar = &VectA[i];
      
      //Se è cambiata o se devo mandare tutti gli actuals
      if (aVar->inVal != aVar->inPrevVal || byInstr == HMICom->inSEND_ACTS) {
        
        //Aggiorno la flag di changed
        boChanged = true;

        //incremento il contatore
        byCounter++;

        //Aggiorno il valore precedente
        aVar->inPrevVal = aVar->inVal;

        //Inserisco l'indice della variabile nel buffer
        myTransfer.txBuff[*inCursor+inOffset] = i;
        //Inserisco il valore della variabile nel buffer
        myTransfer.txBuff[*inCursor+inOffset+1] = highByte(aVar->inVal);
        myTransfer.txBuff[*inCursor+inOffset+2] = lowByte(aVar->inVal);

        //sposto l'offset in avanti
        inOffset+=3;
        
      }
    }

    //se qualcosa è cambiato e se il conteggio è > 0
    if (boChanged && byCounter > 0) {
      //allora inserisco la A ed il numero di items nel buffer
      myTransfer.txBuff[*inCursor] = 'A';
      myTransfer.txBuff[*inCursor+1] = byCounter;
      //ed aggiorno la posizione del cursore
      *inCursor = *inCursor + inOffset;
    }  
    
  }
}

void fb_HMIReceive () {

  if(myTransfer.available()){
    //Ho ricevuto una trama da PI, quindi la comunicazione è sana.
    //Aggiorno il wdCount per non far scattare il watchdog che mi resetta i pulsanti
    HMICom->inWdCount=millis();

    //Aggiorno il Flag
    HMICom->byFlag = myTransfer.rxBuff[0];
    Global->boAlarmsAck = bitRead(HMICom->byFlag, 3);
    //Inizializzo il cursore
    int inCursor = 1;
    int inItemsNumber = 0;
    
    //Scorro il payload finchè non finisce
    while (inCursor < myTransfer.bytesRead){
      switch (myTransfer.rxBuff[inCursor]) {
        case 'L':
          inItemsNumber = myTransfer.rxBuff[inCursor+1];
          inCursor+=2;
          for (int i=0; i < inItemsNumber; i++){
            udtLogic * lVar = &VectL[myTransfer.rxBuff[inCursor]];
            lVar->byCmd = myTransfer.rxBuff[inCursor+1];
            inCursor+=2;
          }
          break;
        case 'B':
          inItemsNumber = myTransfer.rxBuff[inCursor+1];
          inCursor+=2;
          for (int i=0; i < inItemsNumber; i++){
            udtButton * bVar = &VectB[myTransfer.rxBuff[inCursor]];
            bVar->byCmd = myTransfer.rxBuff[inCursor+1];
            inCursor+=2;
          }
          break;
        case 'S':
          inItemsNumber = myTransfer.rxBuff[inCursor+1];
          inCursor+=2;
          for (int i=0; i < inItemsNumber; i++){
            //Getting index of the var
            udtSet * sVar = &VectS[myTransfer.rxBuff[inCursor]];
            //Retreiving value of the var
            sVar->inHMIVal = (myTransfer.rxBuff[inCursor+1]<<8) + myTransfer.rxBuff[inCursor+2];
            inCursor+=3;
          }
          break;
        
        //default case: if you get there it means that you have an error on the frame. Stop the loop forcing the exit condition
        default:
          inCursor= myTransfer.bytesRead-1;
          break;
      }
    }
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
    //Aggiorno il timer
    *inTsIO= millis();

    //inserisco la Flag nel buffer
    myTransfer.txBuff[0] = HMICom->byFlag;

    //Estrapolo l'istruzione
    byte byInstr = HMICom->byFlag & 0x07;
      
    //Inizializzo il cursore
    int inCursor = 1;

    //Popolo il buffer
    fb_getLogics(byInstr, &inCursor);
    fb_getButtons(byInstr, &inCursor);
    fb_getAlarms(byInstr, &inCursor);
    fb_getSets(byInstr, &inCursor);
    fb_getActs(byInstr, &inCursor);

    //Scrivo
    myTransfer.sendData(inCursor);
  }
}


#endif