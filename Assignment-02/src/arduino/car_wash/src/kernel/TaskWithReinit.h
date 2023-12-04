#ifndef __TASK_WITH_REINIT__
#define __TASK_WITH_REINIT__

#include "kernel/Task.h"
#include "Arduino.h"

class TaskWithReinit: public Task {

public:
  TaskWithReinit() 
    : Task(){
  }

  void setPeriod(int newPeriod){
      this->myPeriod = newPeriod;
  }
  
private:
  int state;
  long stateTimestamp;
};

#endif
