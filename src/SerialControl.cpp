//
// Created by Jeka8833 on 16.01.2021.
//

#include "SerialControl.h"
#include "FanControl.h"

#define HEADER 0xAA
#define SET_SPEED_MODE 0x01
#define IDLE 0xFF
#define WAIT_CHECKSUM 0xEF


uint8_t lenAndSum;
uint8_t *data;
uint8_t position = IDLE;
uint8_t checksum;


void SerialControl::init() {
    Serial.begin(9600);
}

void SerialControl::update() {
    while (Serial.available()) {
        uint8_t receivedByte = Serial.read();
        switch (position) {
            case IDLE:
                if (receivedByte == HEADER)
                    position = WAIT_CHECKSUM;
                break;
            case WAIT_CHECKSUM:
                lenAndSum = receivedByte;
                data = new uint8_t[(receivedByte & 0xF0) >> 4];
                position = 0;
                checksum = 0;
                break;
            default:
                data[position++] = receivedByte;
                checksum += receivedByte;
                if (position >= ((lenAndSum & 0xF0) >> 4)) {
                    if ((((checksum & 0x0F) ^ ((checksum & 0xF0) >> 4)) & 0x0F) == (lenAndSum & 0x0F)) {
                        decode(data, (receivedByte & 0xF0) >> 4);
                        Serial.write(0xFF);
                    }
                    delete data;
                    position = IDLE;
                }
                break;
        }
    }
}

void SerialControl::decode(uint8_t *array, uint_least8_t len) {
    if (array[0] == SET_SPEED_MODE) {
        FanControl::setSpeed(FAN0, (array[1] << 8) + array[2]);
        FanControl::setSpeed(FAN1, (array[3] << 8) + array[4]);
        FanControl::setSpeed(FAN2, (array[5] << 8) + array[6]);
        FanControl::setTimeSpin((array[7] << 8) + array[8]);
    }
}