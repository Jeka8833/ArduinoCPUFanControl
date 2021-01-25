#include <Arduino.h>
#include "SerialControl.h"
#include "FanControl.h"

void setup() {
    SerialControl::init();
    FanControl::init();
}

void loop() {
    SerialControl::update();
    FanControl::update();
}