#ifndef db_AnalogInputs_h
#define db_AnalogInputs_h

#include "..\70_udt\_70_udt_Include.h"
#include "..\__Include.h"

udtMicrometer _Micrometer1;
udtMicrometer volatile *Micrometer1 = &_Micrometer1;


//Definizione pin di data e di clock del micrometro1. Verde data, blu clock
int inMicrometer1DataPin = 52, inMicrometer1ClockPin = 53; 

//Definizione della ISR da passare all'interrupt. Funzione di lettura del micrometro1
void ISRMicrometer1(){
  
  //unsigned long int now = micros();
  
  if(micros() - Micrometer1->diTimer > 800){
    Micrometer1->byCounter=0;
  } else {
    Micrometer1->byCounter++;
  }
  Micrometer1->diTimer=micros();
  //To protect the reading from glitches disturbs, I read three times the data, then if the final sum is <2 I consider it as a true, else as a false
  //(Neglected logic)
  uint8_t byBit = digitalRead(inMicrometer1DataPin) + digitalRead(inMicrometer1DataPin) + digitalRead(inMicrometer1DataPin);

  Micrometer1->boBitArray[Micrometer1->byCounter]=byBit<2;
  if(Micrometer1->byCounter == 23){
    
    int16_t inVal = 0;
    for (int i=15; i>0; i--){
      inVal = inVal << 1 | Micrometer1->boBitArray[i];
    }
    if(Micrometer1->boBitArray[21]==1) inVal=-inVal;
    Micrometer1->reReading = float(inVal)/100;
    Micrometer1->reValue = Micrometer1->reReading-Micrometer1->reZeroOffset;
  }
};

void fb_AnalogInputsInit(){
  pinMode(inMicrometer1DataPin, INPUT_PULLUP);
  pinMode(inMicrometer1ClockPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(inMicrometer1ClockPin), ISRMicrometer1, RISING);
}

#endif