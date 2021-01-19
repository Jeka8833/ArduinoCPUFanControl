//
// Created by Jeka8833 on 16.01.2021.
//

#include "SerialControl.h"
#include "FanControl.h"

void SerialControl::init() {
    Serial.begin(9600);
}

void SerialControl::update() {
    uint8_t command = read();
    if (command == 0xA0) {
        uint8_t fan1Mode = read();
        if (fan1Mode == 0x55)
            FanControl::fan1Speed = 0xFFFF;
        else if (fan1Mode == 0xCC)
            FanControl::fan1Speed = read();
        else
            return;
        uint8_t fan2Mode = read();
        if (fan2Mode == 0x55)
            FanControl::fan2Speed = 0xFFFF;
        else if (fan2Mode == 0xCC)
            FanControl::fan2Speed = read();
        else
            return;

        FanControl::fan0Speed = read();
        FanControl::update();
        Serial.write(0xFF);
    } else if (command == 0x50) {
        Serial.write(0xFF);
    }
}

uint8_t SerialControl::read() {
    while (!Serial.available()) {
    }
    return Serial.read();
}