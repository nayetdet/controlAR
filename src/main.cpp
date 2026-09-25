#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <ir_Fujitsu.h>

constexpr uint8_t IR_DATA = 4;
constexpr uint8_t POWER_BUTTON = 5;
constexpr uint8_t TEMP_UP_BUTTON = 21;
constexpr uint8_t TEMP_DOWN_BUTTON = 22;
constexpr uint8_t POWER_LED = 25;
constexpr uint8_t TEMP_LED_PINS[5] = {23, 19, 18, 17, 16}; // 16, 8, 4, 2, 1

IRFujitsuAC airConditionerRemote(IR_DATA, ARRAH2E);
bool airConditionerIsOn = false;

bool wasPressed(uint8_t button) {
    if (digitalRead(button) != LOW) {
        return false;
    }

    delay(50);
    if (digitalRead(button) != LOW) {
        return false;
    }

    while (digitalRead(button) == LOW) {
        delay(1);
    }

    return true;
}

void showTemperature() {
    uint8_t temperature = static_cast<uint8_t>(airConditionerRemote.getTemp());
    for (uint8_t i = 0; i < 5; i++) {
        bool isLit = temperature & (1 << (4 - i));
        digitalWrite(TEMP_LED_PINS[i], isLit ? HIGH : LOW);
    }
}

void changeTemperature(int8_t delta) {
    airConditionerRemote.setTemp(airConditionerRemote.getTemp() + delta);
    showTemperature();
    if (airConditionerIsOn) {
        airConditionerRemote.setCmd(kFujitsuAcCmdStayOn);
        airConditionerRemote.send();
    }
        
}

void setup() {
    pinMode(POWER_BUTTON, INPUT_PULLUP);
    pinMode(TEMP_UP_BUTTON, INPUT_PULLUP);
    pinMode(TEMP_DOWN_BUTTON, INPUT_PULLUP);
    pinMode(POWER_LED, OUTPUT);
    digitalWrite(POWER_LED, LOW);
    for (uint8_t pin : TEMP_LED_PINS) {
        pinMode(pin, OUTPUT);
        digitalWrite(pin, LOW);
    }

    airConditionerRemote.begin();
    airConditionerRemote.setModel(ARRAH2E);
    airConditionerRemote.setMode(kFujitsuAcModeCool);
    airConditionerRemote.setTemp(24);
    airConditionerRemote.setFanSpeed(kFujitsuAcFanAuto);
    airConditionerRemote.setSwing(kFujitsuAcSwingOff);
    showTemperature();
}

void loop() {
    if (wasPressed(POWER_BUTTON)) {
        airConditionerIsOn = !airConditionerIsOn;
        airConditionerRemote.setPower(airConditionerIsOn);
        digitalWrite(POWER_LED, airConditionerIsOn ? HIGH : LOW);
        airConditionerRemote.setCmd(airConditionerIsOn ? kFujitsuAcCmdTurnOn : kFujitsuAcCmdTurnOff);
        airConditionerRemote.send();
    }

    if (wasPressed(TEMP_UP_BUTTON)) {
        changeTemperature(1);
    }

    if (wasPressed(TEMP_DOWN_BUTTON)) {
        changeTemperature(-1);
    }
}
