#include <Arduino.h>

int pHSense = A0;
int samples = 10;
float adc_resolution = 1024.0;

void setup()
{
    Serial.begin(9600);
    delay(100);
    Serial.println("cimpleo pH Sense");
}

// Calibrate your sensor's readings
float ph(float voltage)
{
    // Calculate the slope and offset based on the new calibration values
    float slope = (7.0 - 2.7) / (2.7 - 2.86);
    float offset = 7.0 - slope * 2.7;

    return slope * voltage + offset;
}

void loop()
{
    int measurings = 0;

    for (int i = 0; i < samples; i++)
    {
        measurings += analogRead(pHSense);
        delay(10);
    }

    float voltage = 5.0 / adc_resolution * measurings / samples;
    Serial.print(voltage);
    Serial.print("V ");
    Serial.print("pH = ");
    Serial.println(ph(voltage), 2); // Display pH with two decimal places
}
