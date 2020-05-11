#ifndef db_Config_h
#define db_Config_h

#include "..\70_udt\_70_udt_Include.h"

//Init variabili relative to Serial communication with HMI
struct db_Config{

  //BaudRate della Serial
  const int BAUD_RATE = 250000;
  //Lunghezza del buffer di recezione da HMI
  //è indicato nella fb_HMICom
  
  //ts è la variabile di appoggio del time stamp. Usato per trasmettere verso l'HMI ogni txRate ms
  int inTs=0;
  const int inTxRate = 500;
  
  //WatchDog
  //wd è il flag del watchdog dalla comunicazione con l'HMI. Ogni trasmissione verso l'HMI lo mando invertito.
  //Invece se non mi arrivano frame per wdTimeout ms, il wdCount raggiunge il wdTimeout e resetto i buttons.
  //diversamente aggiorno il wdCount a millis()
  //recWd è il ritorno da PI
  int inWdTimeout=2000;

  //EEPROM
  //LogicOffset è l'offset di indirizzamento di memoria EEPROM a partire dal quale vengono salvati gli stati logici.
  int inLogicOffset = 100;

  //Interrupt
  //Definisce la base tempi dell'interrupt. Da questa base tempi tb, espressa in microsecondi, verranno generati 2 task di interrupt: uno a 2*tb, uno a 10*tb.
  const long int INTERRUPT_TIME_BASE = 15000;
};
  
db_Config _Config, *Config = &_Config;


#endif