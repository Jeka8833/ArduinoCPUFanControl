//
// Created by Jeka8833 on 16.01.2021.
//

#ifndef FANCONTROL_FANCONTROL_H
#define FANCONTROL_FANCONTROL_H

#define MOTHERBOARD_CONTROL 0xFFFF

#include <Arduino.h>
#include "Pinout.h"

enum Fan {
    FAN0, FAN1, FAN2
};

class FanControl {
public:
    static void init();

    static void setSpeed(Fan fan, uint16_t speed);

    static void setTimeSpin(uint16_t time);

    static void update();

private:
    static uint32_t lastTime;
    static uint16_t timeFullSpin;

    static uint16_t fan0Speed;
    static uint16_t fan1Speed;
    static uint16_t fan2Speed;

    static uint16_t fan0LastSpeed;
    static uint16_t fan1LastSpeed;
    static uint16_t fan2LastSpeed;

    static uint16_t speedStep(uint16_t toSpeed, uint16_t lastSpeed);
};

#endif //FANCONTROL_FANCONTROL_H
