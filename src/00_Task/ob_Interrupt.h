#ifndef ob_Interrupt_h
#define ob_Interrupt_h

#include "..\__Include.h"
#include "Submodules\fb_InterruptCounter.h"
#include "fb_Interrupt_2TB.h"
#include "fb_Interrupt_10TB.h"

void ob_Interrupt(){ 
    fb_InterruptCounter(Interrupt);
    fb_Interrupt_2TB(Interrupt);
    fb_Interrupt_10TB(Interrupt);

}


#endif