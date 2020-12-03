#ifndef _99_Library_Include_h
#define _99_Library_Include_h

#include "_99_Library_udt_Include.h"

#include <DueTimer.h>

//Cambiare DueFlashStorage con EEPROM e rimuovere efc.h e flash_efc.h in caso di Arduini diversi dal due
#include <DueFlashStorage.h>
#include <efc.h>
#include <flash_efc.h>
#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>


#include "fb_HMIFunctions.h"
#include "fb_AlarmFunctions.h"
#include "fb_Micrometer.h"
#include "fb_MQTT.h"

#endif