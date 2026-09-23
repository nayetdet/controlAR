#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <ir_Fujitsu.h>

constexpr uint8_t IR_DATA = 4;
constexpr uint8_t BUTTON = 5;

IRFujitsuAC airConditionerRemote(IR_DATA, ARRAH2E);
bool airConditionerIsOn = false;

void setup() {
    pinMode(BUTTON, INPUT_PULLUP);
    airConditionerRemote.begin();
    airConditionerRemote.setModel(ARRAH2E);
    airConditionerRemote.setMode(kFujitsuAcModeCool);
    airConditionerRemote.setTemp(24);
    airConditionerRemote.setFanSpeed(kFujitsuAcFanAuto);
    airConditionerRemote.setSwing(kFujitsuAcSwingOff);
}

void loop() {
    if (digitalRead(BUTTON) == LOW) {
        delay(50);

        if (digitalRead(BUTTON) == LOW) {
            airConditionerIsOn = !airConditionerIsOn;
            airConditionerRemote.setPower(airConditionerIsOn);
            airConditionerRemote.setCmd(airConditionerIsOn ? kFujitsuAcCmdTurnOn : kFujitsuAcCmdTurnOff);
            airConditionerRemote.send();

            while (digitalRead(BUTTON) == LOW) {
                delay(1);
            }
        }
    }
}
