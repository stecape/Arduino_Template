#ifndef db_General_h
#define db_General_h

#include "..\70_udt\_70_udt_Include.h"

struct db_General{
    bool boBuzzer;
    bool boNewAlarm;
    bool boAlarmPresent;
};
db_General _General, *General = &_General;


#endif