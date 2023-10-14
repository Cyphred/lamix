#include <Arduino.h>
#include <DallasTemperature.h>

#define MQ3 A1
#define PH A0

struct {
  int pin = PH;
  int samples = 10;
  float adc_resolution = 276.5;
} phSensor;

float voltageToPh(float voltage) {
  // Mulitmeter readings
  // 3.99V for 0 pH
  // 3.85V for 7 pH
  // 3.71V for 14 pH
  
  // Arduino Readings
  // Upper	4.61
  // Lower	2.5
  // Median	3.555
  // return 7 + ((3.85 - voltage) / 0.18);
  return (3.99 - voltage) / 0.02;
}

float getPhReading() {
  int measurings = 0;

  for (int i = 0; i < phSensor.samples; i++) {
    measurings += analogRead(phSensor.pin) / 4;
    delay(10);
  }

  float voltage = 5 / phSensor.adc_resolution * measurings / phSensor.samples;
  return voltageToPh(voltage);
}

float getEthanolReading() {
  float value = analogRead(MQ3);
  return value;
}

void setup() {
  Serial.begin(9600);
  delay(100);
}


void loop() {
  float ph = getPhReading();            // 100ms
  float ethanol = getEthanolReading();  // 0ms

  Serial.print("[");

  Serial.print("<");
  Serial.print(ph);
  Serial.print(">");

  Serial.print("<");
  Serial.print(ethanol);
  Serial.print(">");

  Serial.print("]");

  delay(400);
}