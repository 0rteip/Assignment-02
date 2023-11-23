/*
 * SMART ROOM - Assignment #02 - ESIOT a.y. 2022-2023
 * 
 * Solution sketch by AR
 * 
 */
#include <Arduino.h>
#include "config.h"
#include "kernel/Scheduler.h"
#include "kernel/Logger.h"
#include "kernel/MsgService.h"
#include "model/CarWash.h"

Scheduler sched;

CarWash* carWash;

void setup() {
  MsgService.init();
  sched.init(50);

  Logger.log(".:: Smart Bridge  ::.");
  
  carWash = new CarWash();
  carWash->init();
  
}

void loop() {
    sched.schedule();
    // pUserConsole->test();
}