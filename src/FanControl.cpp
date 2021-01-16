//
// Created by Jeka8833 on 16.01.2021.
//

#include "FanControl.h"

uint8_t FanControl::fan0Speed = 0x20;
uint16_t FanControl::fan1Speed = 0xFFFF;
uint16_t FanControl::fan2Speed = 0xFFFF;

void FanControl::init() {
    pinMode(10, F1BLOCK);
    pinMode(10, F2BLOCK);
    pinMode(10, F0PWM);
    pinMode(10, F1PWM);
    pinMode(10, F2PWM);

    // Пины D9 и D10 - 31.4 кГц
    TCCR1A = 0b00000001;  // 8bit
    TCCR1B = 0b00000001;  // x1 phase correct

    // Пины D3 и D11 - 31.4 кГц
    TCCR2B = 0b00000001;  // x1
    TCCR2A = 0b00000001;  // phase correct
}

void FanControl::update() {
    analogWrite(F0PWM, fan0Speed);
    if (fan1Speed == 0xFFFF) {
        digitalWrite(F1BLOCK, HIGH);
    } else {
        digitalWrite(F1BLOCK, LOW);
        analogWrite(F1PWM, fan1Speed & 0xFF);
    }
    if (fan2Speed == 0xFFFF) {
        digitalWrite(F2BLOCK, HIGH);
    } else {
        digitalWrite(F2BLOCK, LOW);
        analogWrite(F2PWM, fan2Speed & 0xFF);
    }
}
