#include "tasks/DetectTask.h"
#include "Arduino.h"
#include "config.h"
#include "kernel/Logger.h"

#define DELAY_BEFORE_OFF 1000

DetectTask::DetectTask(CarWash* carWash): 
    carWash(carWash) {
    setState(IDLE);
}
  
void DetectTask::tick(){

}

void DetectTask::setState(int s){
    state = s;
    stateTimestamp = millis();
}

long DetectTask::elapsedTimeInState(){
    return millis() - stateTimestamp;
}

