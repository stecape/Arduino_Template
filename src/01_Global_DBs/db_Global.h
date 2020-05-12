#ifndef db_Global_h
#define db_Global_h

#include "..\70_udt\_70_udt_Include.h"

struct db_Global{
    bool boAlarmsAck;
    uint32_t diCycleTime;
    uint32_t diPrevCycleTime;
};
db_Global _Global, *Global = &_Global;


#endif