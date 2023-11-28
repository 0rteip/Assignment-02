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
#include "tasks/TemperatureControlTask.h"
#include "kernel/TaskWithReinit.h"
#include "UserConsole.h"

Scheduler sched;
CarWash *carWash;
UserConsole *userConsole;

void setup()
{
    // MsgService.init();
    Serial.begin(9600);
    sched.init(50);

    userConsole = new UserConsole();
    carWash = new CarWash(userConsole);
    /*
    BlinkLedTask *blinkLedTask = new BlinkLedTask(LED2_PIN);
    blinkLedTask->init(100);
    blinkLedTask->setActive(false);

    Task *butTask = new ControlTask(blinkLedTask, userConsole, carWash);
    butTask->init(200);

    Task *detectTask = new DetectTask(carWash, blinkLedTask);
    detectTask->init(1000);

    Task *distanceControlTask = new DistanceControlTask(carWash, blinkLedTask);
    distanceControlTask->init(500);

    sched.addTask(blinkLedTask);
    sched.addTask(butTask);
    sched.addTask(detectTask);
    sched.addTask(distanceControlTask);*/
    Task *temp = new TemperatureControlTask(carWash, userConsole);
    temp->init(5000);
    sched.addTask(temp);
}

void loop()
{
    sched.schedule();
}