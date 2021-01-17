#include <Arduino.h>
#include "SerialControl.h"
#include "FanControl.h"

void setup() {
    SerialControl::init();
    FanControl::init();
    FanControl::update();
}

void loop() {
    SerialControl::update();
}