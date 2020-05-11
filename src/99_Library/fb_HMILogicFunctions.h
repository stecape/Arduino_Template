#ifndef fb_HMILogicFunctions_h
#define fb_HMILogicFunctions_h

#include "..\70_udt\_70_udt_Include.h"


DueFlashStorage dueFlashStorage;


void fb_LogicSelectionSR(bool S, bool R, udtLogic * lVar){

  //Se lo stato della selezione è zero, vuol dire che l'Arduino si è appena avviato. Lo inizializzo leggendolo dalla EEPROM.
  //Cambiare DueFlashStorage con EEPROM in caso di Arduini diversi dal due

  //Leggo il valore salvato in EEPROM
  unsigned char EEPROMst = dueFlashStorage.read(lVar->inIndex);

  //Nel caso stia usando la DueFlashStorage, dopo aver ricaricato il software avrò la Flash tutta a true, quindi EEPROMst varrà 255.
  //Dovrò quindi proteggere questo caso, e dire che se la EEPROMst vale più di 128 (caso di selezione a 1 dell'ottavo bit) allora vuol dire che
  //ho sbagasciato tutto, e metto la selezione a 1 (di default off)
  if (EEPROMst >= 128) EEPROMst=1;
  if (lVar->bySt == 0){
    lVar->bySt = EEPROMst;
  }

  //Valuto se ho dei comandi di S o R e li applico allo stato
  if (S and not R) {
    lVar->bySt= 2;
  }
  if (R)  {
    lVar->bySt= 1;
  }

  //Resetto il byte di comando
  bitWrite(lVar->byCmd, 0, false);
  bitWrite(lVar->byCmd, 1, false);

  //Se il valore dello stato, dopo l'elaborazione, è diverso da quello della EEPROM, aggiorno la EEPROM
  if (EEPROMst != lVar->bySt){
    //Cambiare DueFlashStorage con EEPROM in caso di Arduini diversi dal due
    dueFlashStorage.write(lVar->inIndex, lVar->bySt);
  }

  //Aggiorno Q a partire dallo stato
  lVar->boQ0 = bitRead(lVar->bySt, 0);
  lVar->boQ1 = bitRead(lVar->bySt, 1);
}

void fb_LogicButton(udtButton * bVarIN, bool boIn0IN, bool boIn1IN, bool boIn2IN, bool boIn3IN, bool boIn4IN, bool boIn5IN, bool boIn6IN, bool boIn7IN){
  bVarIN->boQ0 = boIn0IN;
  bitWrite(bVarIN->bySt, 0, boIn0IN);  
  bVarIN->boQ1 = boIn1IN;
  bitWrite(bVarIN->bySt, 1, boIn1IN); 
  bVarIN->boQ2 = boIn2IN;
  bitWrite(bVarIN->bySt, 2, boIn2IN);  
  bVarIN->boQ3 = boIn3IN;
  bitWrite(bVarIN->bySt, 3, boIn3IN); 
  bVarIN->boQ4 = boIn4IN;
  bitWrite(bVarIN->bySt, 4, boIn4IN); 
  bVarIN->boQ5 = boIn5IN;
  bitWrite(bVarIN->bySt, 5, boIn5IN); 
  bVarIN->boQ6 = boIn6IN;
  bitWrite(bVarIN->bySt, 6, boIn6IN); 
  bVarIN->boQ7 = boIn7IN;
  bitWrite(bVarIN->bySt, 7, boIn7IN); 
}

void fb_ResetButtons(int inl_HMI_BIN, udtButton *VectBIN){
  for (int i=0; i<inl_HMI_BIN; i++){
    udtButton *bVar = &VectBIN[i];
    bVar->byCmd = 0;
  }
}

#endif