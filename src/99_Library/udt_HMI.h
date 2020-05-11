#ifndef udt_HMI_h
#define udt_HMI_h


struct udtLogic {
  byte byCmd;
  byte bySt;
  byte byPrevSt;
  byte inIndex;
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
  int inPrevVal;
};

struct udtAct {
  int inVal;
  int inPrevVal;
};

struct udtAlarm {
  byte bySt;
  byte byPrevSt;
};


#endif