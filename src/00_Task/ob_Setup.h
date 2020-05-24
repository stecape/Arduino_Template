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

    //Inizializzazione limiti Setpoints e indici variabili logiche e setpoints per puntamento EEPROM
    fb_HMIInit();

    fb_AnalogInputsInit();

    //Cyclic Interrupt attachment
    Timer8.attachInterrupt(ob_Interrupt).start(Config->INTERRUPT_TIME_BASE);
}


#endif