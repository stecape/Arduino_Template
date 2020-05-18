#ifndef udt_HMI_h
#define udt_HMI_h

#include <Arduino.h>

struct udtLogic {
  byte byCmd;
  byte bySt;
  byte byPrevSt;
  int inIndex;
  bool boInit;
  bool boQ0;
  bool boQ1;
  bool boQ2;
  bool boQ3;
  bool boQ4;
  bool boQ5;
  bool boQ6;
  bool boQ7;
};

struct udtButton {
  byte byCmd;
  byte bySt;
  byte byPrevSt;
  bool boQ0;
  bool boQ1;
  bool boQ2;
  bool boQ3;
  bool boQ4;
  bool boQ5;
  bool boQ6;
  bool boQ7;
};

struct udtSet {
  int inVal;
  int inHMIVal;
  int inPrevVal;
  int inMin;
  int inMax;
  int inIndex;
  bool boInit;
};

struct udtAct {
  int inVal;
  int inPrevVal;
};

struct udtAlarm {
  int inIndex;
  byte byReaction;
  bool boTrigger;
  bool boQ;
  byte bySt;
  byte byPrevSt;
  byte byLastStSent;
  bool boAck;
};

struct udtMachineReactions {
  bool boNormalStop;
  bool boFastStop;
  bool boWarning;
  bool boSlowSpeed;
  bool boNotification;
};

const byte REACT_NORMAL_STOP = 1;
const byte REACT_FAST_STOP = 2;
const byte REACT_WARNING = 3;
const byte REACT_SLOW_SPEED = 4;
const byte REACT_NOTIFICATION = 5;

#endif