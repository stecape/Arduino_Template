#ifndef db_Global_h
#define db_Global_h

#include "..\70_udt\_70_udt_Include.h"

struct db_Global{
    bool boAlarmsAck;
};
db_Global _Global, *Global = &_Global;


#endif