#ifndef ob_Loop_h
#define ob_Loop_h

#include "..\__Include.h"

#include "..\02_HMI\fb_HMICom.h"
#include "..\10_General\fb_General_Loop.h"


void ob_Loop(){
    //HMI Receive
    fb_HMIReceive();

    fb_General_Loop();

    //HMI Send
    fb_HMISend(&Config->inTs, Config->inTxRate);
}


#endif