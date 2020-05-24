#ifndef db_AnalogInputs_h
#define db_AnalogInputs_h

#include "..\70_udt\_70_udt_Include.h"

udtMicrometer _Micrometer1;
udtMicrometer volatile *Micrometer1 = &_Micrometer1;


//Definizione pin di data e di clock del micrometro1. 
int inMicrometer1DataPin = 52, inMicrometer1ClockPin = 53; 

void fb_AnalogInputsInit(){
  //Visto che sono pullup, la logica negata della comunicazione del micrometro viene raddrizzata.
  pinMode(inMicrometer1DataPin, INPUT_PULLUP);
  pinMode(inMicrometer1ClockPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(inMicrometer1ClockPin), ISRMicrometer1, FALLING);
}

//Definizione della ISR da passare all'interrupt. Funzione di lettura del micrometro1
void ISRMicrometer1(){
  fb_Micrometer(Micrometer1, inMicrometer1DataPin);
} 

#endif