#ifndef ob_Setup_h
#define ob_Setup_h

#include "..\__Include.h"

#include "ob_Interrupt.h"

void ob_Setup(){    
    
    //Serial initialization
    Serial.begin(Config->BAUD_RATE);
    while(!Serial){

    } 

    myTransfer.begin(Serial);

    //Inizializzazione I/O. Probabilmente bisognerà fare una sua function
    pinMode(LED_BUILTIN, OUTPUT);

    //Inizializzazione indici variabili Logiche per puntamento EEPROM
    for(int i=0; i<l_HMI_L; i++) {
        udtLogic *lVar = &VectL[i];
        lVar->inIndex = i;
    }
    
    //Interrupt attachment
    //Timer8.attachInterrupt(ob_Interrupt).start(Config->INTERRUPT_TIME_BASE);
}


#endif