

//Arrange your code in sections: each software units should manage a section
//A section is something like a filesystem folder in which yoy put:
//
//- #Section_import.h include file, in which you define section vars and section submodules (if is present)
//  The vars should be put toghether in a struct, so you can point them with something that seems a "sectionName->tipeVar"
//  Each section can put and write vars in his struct. Other sections can only read from that struct.
//  Var prefix must indicate the type of the var itself: per ex: struct Grinder { bool boOn, int inSpeed, real reWidth }
//
//- Section_init(){} function: it includes all the vars initialization, objects instantiation and so on. this function will be called in the setup method.
//                             Naming convention: Grinder_init
//
//- Section_loop(){} function: it includes all the business logic of the section that should be executed in loop.
//                             Naming convention: Grinder_loop, Grinder_loop_driver...
//
//- Section_interrupt(){} function: it will includes all the business logic of the section that should be executed in interrupt (regulators etc).
//                                  Naming convention: Grinder_I20, Grinder_I20_Speed, Grinder_I20_Temperature... where the 20 is the interruption rate in which it will be declared


//Include section
//Put here whaterver you need to include:
//libs, vars & submodules definition files (.h), ecc


//prima includo le DB e le librerie
#include "__Include.h"

//Per ultima la _00_Task_Include perchè contiene le chiamate a tutto il resto del sw
#include "00_Task\ob_Setup.h"
#include "00_Task\ob_Loop.h"

void setup() {
    ob_Setup();
}


   
void loop() {
    ob_Loop();
}