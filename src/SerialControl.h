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
    static void decode(uint8_t array[], uint_least8_t len);
};


#endif //FANCONTROL_SERIALCONTROL_H
