#include <Arduino.h>
#include "config.h"
#include "kernel/Scheduler.h"
#include "kernel/MsgService.h"
#include "model/CarWash.h"
#include "tasks/DetectTask.h"
#include "tasks/BlinkLedTask.h"
#include "tasks/ControlTask.h"
#include "tasks/WashingAreaControlTask.h"
#include "tasks/TemperatureControlTask.h"
#include "kernel/TaskWithReinit.h"
#include "UserConsole.h"

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
    blinkLedTask->init(300);
    blinkLedTask->setActive(false);

    ControlTask *controlTask = new ControlTask(blinkLedTask, userConsole, carWash);
    controlTask->init(50);
    controlTask->setActive(false);

    WashingAreaControlTask *washingAreaControlTask = new WashingAreaControlTask(carWash, blinkLedTask, controlTask);
    washingAreaControlTask->init(500);

    Task *detectTask = new DetectTask(carWash, washingAreaControlTask, blinkLedTask);
    detectTask->init(1000);

    Task *tempTask = new TemperatureControlTask(carWash);
    tempTask->init(1000);

    sched->addTask(blinkLedTask);
    sched->addTask(controlTask);
    sched->addTask(detectTask);
    sched->addTask(washingAreaControlTask);
    sched->addTask(tempTask);
}

void loop()
{
    sched->schedule();
}