#ifndef fb_InterruptCounter_h
#define fb_InterruptCounter_h

#include "..\..\__Include.h"

void fb_InterruptCounter(db_Interrupt volatile *inInterruptIO){
    if(inInterruptIO->inCounter >= 19){
        inInterruptIO->inCounter=0;
    }else{
        inInterruptIO->inCounter++;
    }

}

#endif