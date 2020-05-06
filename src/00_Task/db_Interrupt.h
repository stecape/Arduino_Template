#ifndef db_Interrupt_h
#define db_Interrupt_h

#include "..\70_udt\_70_udt_Include.h"

struct db_Interrupt{
    bool boFlag;
    int inCounter;
};
db_Interrupt _Interrupt; 
db_Interrupt volatile *Interrupt = &_Interrupt;
#endif