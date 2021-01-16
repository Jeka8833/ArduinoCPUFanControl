//
// Created by Jeka8833 on 16.01.2021.
//

#ifndef FANCONTROL_SERIALCONTROL_H
#define FANCONTROL_SERIALCONTROL_H

#include <Arduino.h>

class SerialControl {
public:
    static void init();
    static void update();

private:
    static uint8_t read();
};


#endif //FANCONTROL_SERIALCONTROL_H
