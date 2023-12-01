#include <Arduino.h>
#include "config.h"
#include "kernel/Scheduler.h"
#include "kernel/MsgService.h"
#include "model/CarWash.h"
#include "tasks/DetectTask.h"
#include "tasks/BlinkLedTask.h"
#include "tasks/ControlTask.h"
#include "tasks/DistanceControlTask.h"
#include "tasks/TemperatureControlTask.h"
#include "kernel/TaskWithReinit.h"
#include "UserConsole.h"

#include "devices/DisplayLcdI2C.h"

Scheduler *sched;
CarWash *carWash;
UserConsole *userConsole;

void setup()
{
    MsgService.init();
    sched = new Scheduler();
    sched->init(50);

    userConsole = new UserConsole();
    carWash = new CarWash(userConsole);

    BlinkLedTask *blinkLedTask = new BlinkLedTask(LED2_PIN);
    blinkLedTask->init(100);
    blinkLedTask->setActive(false);

    Task *butTask = new ControlTask(blinkLedTask, userConsole, carWash);
    butTask->init(150);

    DistanceControlTask *distanceControlTask = new DistanceControlTask(carWash, blinkLedTask);
    distanceControlTask->init(500);

    Task *detectTask = new DetectTask(carWash, distanceControlTask, blinkLedTask);
    detectTask->init(1000);

    Task *tempTask = new TemperatureControlTask(carWash, userConsole);
    tempTask->init(500);

    sched->addTask(blinkLedTask);
    sched->addTask(butTask);
    sched->addTask(detectTask);
    sched->addTask(distanceControlTask);
    sched->addTask(tempTask);
}

void loop()
{
    sched->schedule();
}