#ifndef udt_HMI_h
#define udt_HMI_h


struct udtLogic {
  unsigned char byCmd;
  unsigned char bySt;
  unsigned char byPrevSt;
  unsigned char inIndex;
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
  unsigned char byCmd;
  unsigned char bySt;
  unsigned char byPrevSt;
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
  unsigned char bySt;
  unsigned char byPrevSt;
};


#endif