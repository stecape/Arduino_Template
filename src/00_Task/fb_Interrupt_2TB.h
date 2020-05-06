#ifndef fb_Interrupt_2TB_h
#define fb_Interrupt_2TB_h

#include "..\__Include.h"

void fb_Interrupt_2TB(db_Interrupt volatile *inInterruptIO){

    switch (inInterruptIO->inCounter)
    {
    case 0:
    case 4:
    case 8:
    case 12:
    case 16:
//
//        break; uncomment to get 2 slot @4 tb instead of 1 @2 tb
//    
    case 2:
    case 6:
    case 10:
    case 14:
    case 18:
        inInterruptIO->boFlag=true;
        break;
    }
}

#endif