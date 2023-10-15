#include <Arduino.h>
#include <DallasTemperature.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is plugged into digital pin 2 on the Arduino
#define ONE_WIRE_BUS 2

// Setup a oneWire instance to communicate with any OneWire device
OneWire oneWire(ONE_WIRE_BUS);	

// Pass oneWire reference to DallasTemperature library
DallasTemperature sensors(&oneWire);

#define MQ3 A1
#define PH A0
#define FAN_RELAY 5
#define HEATER_RELAY 4
#define PUMP_RELAY 3

struct {
  int pin = PH;
  int samples = 10;
  float adc_resolution = 1024.0;
} phSensor;

struct {
  bool fan = false;
  bool heater = false;
  bool pump = false;
} relay_states;

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

  float voltage = 5.0 / phSensor.adc_resolution * measurings / phSensor.samples;
  return voltageToPh(voltage);
}

float getEthanolReading() {
  float value = analogRead(MQ3);
  return value;
}

void setFan(bool state) {
  if (state) {
    relay_states.fan = true;
    digitalWrite(FAN_RELAY, LOW);
  } else {
    relay_states.fan = false;
    digitalWrite(FAN_RELAY, HIGH);
  }
}

void setHeater(bool state) {
  if (state) {
    relay_states.heater = true;
    digitalWrite(HEATER_RELAY, LOW);
  } else {
    relay_states.heater = false;
    digitalWrite(HEATER_RELAY, HIGH);
  }
}

void setPump(bool state) {
  if (state) {
    relay_states.pump = true;
    digitalWrite(PUMP_RELAY, LOW);
  } else {
    relay_states.pump = false;
    digitalWrite(PUMP_RELAY, HIGH);
  }
}

void setup() {
  sensors.begin();
  Serial.begin(9600);
  pinMode(FAN_RELAY, OUTPUT);
  pinMode(HEATER_RELAY, OUTPUT);
  pinMode(PUMP_RELAY, OUTPUT);

  // Turn off all relays
  setFan(false);
  setHeater(false);
  setPump(false);

  delay(100);
}


void loop() {
  byte input = Serial.read();

  if (input == '1') setFan(true);
  else if (input == '2') setFan(false);
  else if (input == '3') setHeater(true);
  else if (input == '4') setHeater(false);
  else if (input == '5') setPump(true);
  else if (input == '6') setPump(false);

  sensors.requestTemperatures(); 

  float temp = sensors.getTempCByIndex(0);
  float ph = getPhReading();            // 100ms
  float ethanol = getEthanolReading();  // 0ms

  Serial.print(ph);
  Serial.print(",");
  Serial.print(ethanol);
  Serial.print(",");
  Serial.print(temp);
  Serial.print(",");
  Serial.print(relay_states.fan);
  Serial.print(",");
  Serial.print(relay_states.heater);
  Serial.print(",");
  Serial.print(relay_states.pump);


  Serial.println();
}