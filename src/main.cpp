#include <Arduino.h>
#include <IRrecv.h>
#include <IRsend.h>
#include <IRutils.h>

#define IR_SENSOR 4
#define BUTTON 5
#define IR_LED 18

IRrecv receiver(IR_SENSOR, 1024, 15, true);
IRsend transmitter(IR_LED);

decode_results decodedData;
uint16_t rawCode[1024];
uint16_t rawLength = 0;

void setup() {
  pinMode(BUTTON, INPUT_PULLUP);
  receiver.enableIRIn();
  transmitter.begin();
}

void loop() {
  if (receiver.decode(&decodedData)) {
    rawLength = min<uint16_t>(getCorrectedRawLength(&decodedData), 1024);
    for (uint16_t i = 0; i < rawLength; i++)
      rawCode[i] = decodedData.rawbuf[i + 1] * kRawTick;
    receiver.resume();
  }

  if (!digitalRead(BUTTON)) {
    delay(50);
    if (!digitalRead(BUTTON) && rawLength) {
      transmitter.sendRaw(rawCode, rawLength, 38);
      while (!digitalRead(BUTTON)) delay(1);
    }
  }
}
