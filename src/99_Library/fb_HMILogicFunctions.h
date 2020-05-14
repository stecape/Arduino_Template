#ifndef fb_HMILogicFunctions_h
#define fb_HMILogicFunctions_h

#include "..\70_udt\_70_udt_Include.h"


DueFlashStorage dueFlashStorage;


void fb_LogicSelectionSR(bool S, bool R, udtLogic * lVar){

  //Se lo stato della init è false, vuol dire che l'Arduino si è appena avviato. Lo inizializzo leggendolo dalla EEPROM.
  //Cambiare DueFlashStorage con EEPROM in caso di Arduini diversi dal due

  //Leggo il valore salvato in EEPROM
  unsigned char EEPROMst = dueFlashStorage.read(lVar->inIndex+Config->inLogicOffset);

  //Nel caso stia usando la DueFlashStorage, dopo aver ricaricato il software avrò la Flash tutta a true, quindi EEPROMst varrà 255.
  //Dovrò quindi proteggere questo caso, e dire che se la EEPROMst vale più di 128 (caso di selezione a 1 dell'ottavo bit) allora vuol dire che
  //ho sbagasciato tutto, e metto la selezione a 1 (di default off)
  if (EEPROMst >= 128) EEPROMst=1;
  if (lVar->boInit == false){
    lVar->bySt = EEPROMst;
    lVar->boInit = true;
  }

  //Valuto se ho dei comandi di S o R e li applico allo stato
  if (S and not R) {
    lVar->bySt= 2;
  }
  if (R)  {
    lVar->bySt= 1;
  }

  //Resetto il byte di comando
  lVar->byCmd=false;

  //Se il valore dello stato, dopo l'elaborazione, è diverso da quello della EEPROM, aggiorno la EEPROM
  if (EEPROMst != lVar->bySt){
    //Cambiare DueFlashStorage con EEPROM in caso di Arduini diversi dal due
    dueFlashStorage.write(lVar->inIndex+Config->inLogicOffset, lVar->bySt);
  }

  //Aggiorno Q a partire dallo stato
  lVar->boQ0 = bitRead(lVar->bySt, 0);
  lVar->boQ1 = bitRead(lVar->bySt, 1);
  lVar->boQ2 = bitRead(lVar->bySt, 2);
  lVar->boQ3 = bitRead(lVar->bySt, 3);
  lVar->boQ4 = bitRead(lVar->bySt, 4);
  lVar->boQ5 = bitRead(lVar->bySt, 5);
  lVar->boQ6 = bitRead(lVar->bySt, 6);
  lVar->boQ7 = bitRead(lVar->bySt, 7);
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

void fb_Setpoint(udtSet *sVar){
  
  int inIndex = (2*sVar->inIndex)+Config->inSetpointOffset;
  //Leggo il valore salvato in EEPROM
  int EEPROMval = (dueFlashStorage.read(inIndex)<<8)+dueFlashStorage.read(inIndex+1);

  if (sVar->boInit == false){
    sVar->inVal = EEPROMval;
    sVar->inHMIVal = EEPROMval;
    sVar->boInit = true;
  }

  if (sVar->inMin > sVar->inVal){
    sVar->inVal = sVar->inMin;
  } 
  else if (sVar->inVal > sVar->inMax)
  {
    sVar->inVal = sVar->inMax;
  }
  
  if (sVar->inMin > sVar->inHMIVal || sVar->inHMIVal > sVar->inMax) {
    sVar->inHMIVal = sVar->inVal;
  } else {
    sVar->inVal = sVar->inHMIVal;
  }
  
  //Se il valore dello stato, dopo l'elaborazione, è diverso da quello della EEPROM, aggiorno la EEPROM
  if (EEPROMval != sVar->inVal){
    //Cambiare DueFlashStorage con EEPROM in caso di Arduini diversi dal due
    dueFlashStorage.write(inIndex, highByte(sVar->inVal));
    dueFlashStorage.write(inIndex+1, lowByte(sVar->inVal));

  }
}

#endif