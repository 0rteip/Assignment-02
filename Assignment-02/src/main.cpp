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
#include "tasks/ControlTask.h"
#include "tasks/DistanceControlTask.h"
#include "devices/servo_motor.h"
#include "devices/servo_motor_impl.h"
#include "kernel/TaskWithReinit.h"
#include "UserConsole.h"
Scheduler sched;
CarWash* carWash;
ServoMotor* motor;
UserConsole* userConsole;
void setup() {
   //MsgService.init();
   Serial.begin(9600);
    sched.init(50);
    carWash = new CarWash();
    userConsole = new UserConsole();
    carWash->init();
	Task* blinkLedTask = new BlinkLedTask(LED2_PIN);
    blinkLedTask->init(100);
	blinkLedTask->setActive(false);
    Task* butTask = new ControlTask(blinkLedTask, userConsole, carWash);
    butTask->init(200);
    Task* detectTask = new DetectTask(carWash, blinkLedTask);
    detectTask->init(1000);
    sched.addTask(detectTask);
	sched.addTask(blinkLedTask);
    sched.addTask(butTask);
}


void loop() {
   
    sched.schedule();
    //pUserConsole->test();
}