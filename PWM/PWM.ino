#include <Arduino.h>

const uint8_t POT_PIN = 4;
const uint8_t PWM_LED_PIN = 5;
bool pwmReady = false;
unsigned long lastPrint = 0;

void setup() {
  Serial.begin(115200);
  analogReadResolution(12);
  analogSetPinAttenuation(POT_PIN, ADC_11db);
  pinMode(PWM_LED_PIN, OUTPUT);
  digitalWrite(PWM_LED_PIN, LOW);
  pwmReady = ledcAttach(PWM_LED_PIN, 5000, 8);
  if (pwmReady) {
    ledcWrite(PWM_LED_PIN, 0);
  } else {
    Serial.println("PWM setup failed. Check board/core and pin.");
  }
}

void loop() {
  if (!pwmReady) {
    return;
  }
  const int raw = analogRead(POT_PIN);
  const int duty = constrain(map(raw, 0, 4095, 0, 255), 0L, 255L);
  ledcWrite(PWM_LED_PIN, duty);

  if (millis() - lastPrint >= 500) {
    lastPrint = millis();
    Serial.printf("Raw:%d\tDuty:%d\n", raw, duty);
  }
  delay(20);
}