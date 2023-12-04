#ifndef __MSG_SERVICE__
#define __MSG_SERVICE__

#include "Arduino.h"

class Msg
{
  String content;

public:
  Msg(String content)
  {
    this->content = content;
  }

  String getContent()
  {
    return this->content;
  }
};

class MsgServiceClass
{

public:
  Msg *currentMsg;
  bool msgAvailable;

  void init();

  bool isMsgAvailable();
  Msg *receiveMsg();

  void sendMsg(const String &msg);
};

extern MsgServiceClass MsgService;

#endif
