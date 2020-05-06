#ifndef fb_Interrupt_10TB_h
#define fb_Interrupt_10TB_h

#include "..\__Include.h"


void fb_Interrupt_10TB(db_Interrupt volatile *inInterruptIO){

    switch (inInterruptIO->inCounter)
    {
    case 1:
        
        break;
        
    case 3:
    
        break;
        
    case 5:
    
        break;
        
    case 7:
    
        break;
        
    case 9:
    
        break;
        
    case 11:
        
        break;
        
    case 13:
    
        break;
        
    case 15:
    
        break;
        
    case 17:
    
        break;
        
    case 19:
        inInterruptIO->boFlag=true;
        break;
        
    }
}

#endif