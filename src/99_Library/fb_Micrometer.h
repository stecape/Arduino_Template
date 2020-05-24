#ifndef fb_Micrometer_h
#define fb_Micrometer_h

#include "..\70_udt\_70_udt_Include.h"

void fb_Micrometer(volatile udtMicrometer * Micrometer, int inDataPin){
  
  if(micros() - Micrometer->diTimer > 450){
    Micrometer->byCounter=0;
  } else {
    Micrometer->byCounter++;
  }
  Micrometer->diTimer=micros();
  
  //To protect the reading from glitches disturbs, I read three times the data, then if the final sum is >= 2 I consider it as a true, else as a false
  uint8_t byBit = digitalRead(inDataPin) + digitalRead(inDataPin) + digitalRead(inDataPin);

  Micrometer->boBitArray[Micrometer->byCounter]=byBit>=2;
  if(Micrometer->byCounter == 23){
    uint16_t inVal = 0;
    for (int i=1; i==15; i++){
      inVal = inVal << 1 | Micrometer->boBitArray[i];
    }
    uint8_t bySign = 1;
    if(Micrometer->boBitArray[21]==1) bySign=-1;
    Micrometer->reReading = bySign*inVal/100;
    Micrometer->reValue = Micrometer->reReading-Micrometer->reZeroOffset;
  }
}
#endif