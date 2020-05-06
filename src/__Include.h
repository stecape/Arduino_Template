#ifndef __Include_h
#define __Include_h

#include <Arduino.h>

//Includendo questo file hai accesso a tutte le udt di progetto e libreria,
//a tutte le DB pubbliche di progetto e a tutte le fb di libreria
//udt. Contiene anche quelle di libreria
#include "70_udt\_70_udt_Include.h"

//db HMI
#include "02_HMI\db_HMI.h"

//db Share
#include "01_Global_DBs\db_Global.h"
#include "03_General\db_General.h"
#include "00_Task\db_Interrupt.h"

//db config
#include "01_Global_DBs\db_Config.h"

//Librerie
#include "99_Library\_99_Library_Include.h"

#endif