//
// Created by Jeka8833 on 16.01.2021.
//

#ifndef FANCONTROL_FANCONTROL_H
#define FANCONTROL_FANCONTROL_H

#include <Arduino.h>
#include "Pinout.h"

class FanControl {
public:
    static uint8_t fan0Speed;
    static uint16_t fan1Speed;
    static uint16_t fan2Speed;

    static void init();
    static void update();

};


#endif //FANCONTROL_FANCONTROL_H
