#include <Arduino.h>

const uint8_t POT_PIN = 4;

void setup() {
  Serial.begin(115200);
  analogReadResolution(12);
  analogSetPinAttenuation(POT_PIN, ADC_11db);
}

void loop() {
  const int raw = analogRead(POT_PIN);
  const uint32_t millivolts = analogReadMilliVolts(POT_PIN);
  Serial.print("Raw:");
  Serial.print(raw);
  Serial.print("\tMillivolts:");
  Serial.println(millivolts);
  delay(100);
}