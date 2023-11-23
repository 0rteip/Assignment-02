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
#include "tasks/DetectTask.h"
#include "tasks/BlinkLedTask.h"

Scheduler sched;
CarWash* carWash;

void setup() {
    MsgService.init();
    sched.init(50);
    Serial.begin(9600);
    Logger.log(".:: Smart Bridge  ::."); 
    carWash = new CarWash();
    carWash->init();
	Task* bilnkLedTask = new BlinkLedTask(LED1_PIN);
    bilnkLedTask->init(100);
	bilnkLedTask->setActive(false);
    Task* detectTask = new DetectTask(carWash, bilnkLedTask);
    detectTask->init(1000);
    sched.addTask(detectTask);
	sched.addTask(bilnkLedTask);
}

void loop() {
    sched.schedule();
    //pUserConsole->test();
}