//
// Created by Jeka8833 on 16.01.2021.
//

#include "FanControl.h"

uint32_t FanControl::lastTime = 0;
uint16_t FanControl::timeFullSpin = 0;

uint16_t FanControl::fan0Speed = 0x0020;
uint16_t FanControl::fan1Speed = 0xFFFF;
uint16_t FanControl::fan2Speed = 0xFFFF;

uint16_t FanControl::fan0LastSpeed = 0x0020;
uint16_t FanControl::fan1LastSpeed = 0xFFFF;
uint16_t FanControl::fan2LastSpeed = 0xFFFF;

void FanControl::init() {
    pinMode(F1BLOCK, OUTPUT);
    pinMode(F2BLOCK, OUTPUT);
    pinMode(F0PWM, OUTPUT);
    pinMode(F1PWM, OUTPUT);
    pinMode(F2PWM, OUTPUT);

    // Pin D3 and D11 - 31.4 kHz
    TCCR2B = 0b00000001;
    TCCR2A = 0b00000001;

    // Pin D9 and D10 - 25 kHz
    TCCR1A = 0;
    TCCR1B = 0;
    TCNT1 = 0;
    TCCR1A = _BV(COM1A1) | _BV(COM1B1) | _BV(WGM11);
    TCCR1B = _BV(WGM13) | _BV(CS10);
    ICR1 = 320;

}

void FanControl::setSpeed(Fan fan, uint16_t speed) {
    switch (fan) {
        case FAN0:
            fan0LastSpeed = fan0Speed;
            fan0Speed = speed % 321;
            break;
        case FAN1:
            fan1LastSpeed = fan1Speed;
            if (speed == 0xFFFF)
                fan1Speed = 0xFFFF;
            else
                fan1Speed = speed % 256;
            break;
        case FAN2:
            fan2LastSpeed = fan2Speed;
            if (speed == 0xFFFF)
                fan2Speed = 0xFFFF;
            else
                fan2Speed = speed % 321;
            break;
    }
}

void FanControl::setTimeSpin(uint16_t time) {
    timeFullSpin = time;
    lastTime = millis();
}

void FanControl::update() {
    OCR1B = speedStep(fan0Speed, fan0LastSpeed);                       // Set frequency to pin 10 (320)
    if (fan1Speed == MOTHERBOARD_CONTROL) {
        digitalWrite(F1BLOCK, HIGH);
        pinMode(F1PWM, INPUT);
    } else {
        digitalWrite(F1BLOCK, LOW);
        pinMode(F1PWM, OUTPUT);
        analogWrite(F1PWM, speedStep(fan1Speed, fan1LastSpeed));       // Set frequency to pin 3 (255)
    }
    if (fan2Speed == MOTHERBOARD_CONTROL) {
        digitalWrite(F2BLOCK, HIGH);
        pinMode(F2PWM, INPUT);
    } else {
        digitalWrite(F2BLOCK, LOW);
        pinMode(F2PWM, OUTPUT);
        OCR1A = speedStep(fan2Speed, fan2LastSpeed);                   // Set frequency to pin 9 (320)
    }
}

uint16_t FanControl::speedStep(uint16_t toSpeed, uint16_t lastSpeed) {
    if (timeFullSpin == 0)
        return toSpeed;
    uint32_t time = millis() - lastTime;
    if (time > timeFullSpin)
        return toSpeed;
    return (int16_t) lastSpeed + ((int16_t) toSpeed - (int16_t) lastSpeed) * (int32_t) time / (int16_t) timeFullSpin;
}