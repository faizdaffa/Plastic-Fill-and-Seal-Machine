#include <max6675.h>

float temperature_V = 0;
float temperature_H = 0;
unsigned long previousTime_T = 0;

// MAX6675 thermocouple(SCK, CS, SO)
MAX6675 thermocoupleVertical(29, 30, 31);
MAX6675 thermocoupleHorizontal(26, 27, 28);

void read_thermocouple()
{
    unsigned long currentTime_T = millis();
    if (currentTime_T - previousTime_T >= 1000)
    {
        temperature_V = thermocoupleVertical.readCelsius();
        temperature_H = thermocoupleHorizontal.readCelsius();
        // Serial.println("Tv: " + String(temperature_V) + "  ||  Th: " + String(temperature_H));
        previousTime_T = currentTime_T;
    }
}