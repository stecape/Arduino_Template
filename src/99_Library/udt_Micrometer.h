#ifndef udt_Micrometer_h
#define udt_Micrometer_h

#include <Arduino.h>

struct udtMicrometer {
  unsigned long int diTimer;
  uint8_t byCounter;
  bool boBitArray[24];
  float reReading;
  float reZeroOffset;
  float reValue;
};

#endif