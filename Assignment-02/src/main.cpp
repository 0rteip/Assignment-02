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
#include "devices/servo_motor.h"
#include "devices/servo_motor_impl.h"

Scheduler sched;
CarWash* carWash;
ServoMotor* motor;
void setup() {
    Serial.begin(9600);

    /*MsgService.init();
    sched.init(50);
    
    Logger.log(".:: Smart Bridge  ::."); 
    carWash = new CarWash();
    carWash->init();
	Task* bilnkLedTask = new BlinkLedTask(LED1_PIN);
    bilnkLedTask->init(100);
	//bilnkLedTask->setActive(false);
    Task* controlTask = new ControlTask(BT_PIN, bilnkLedTask);
    controlTask->init(100);
	controlTask->setActive(false);
    Task* detectTask = new DetectTask(carWash, bilnkLedTask);
    detectTask->init(1000);
    sched.addTask(detectTask);
	sched.addTask(bilnkLedTask);*/
    motor = new ServoMotorImpl(GATE_PIN);
    motor->on();
    motor->setPosition(0);
    delay(1500);
    motor->setPosition(90);

}

void loop() {
   
    //sched.schedule();
    //pUserConsole->test();
}