#include <Arduino.h>

#define RPWM_HORIZONTAL 11
#define LPWM_HORIZONTAL 10
#define PWM_HORIZONTAL 9
#define PWM_VERTICAL 8
#define RPWM_VERTICAL 7
#define LPWM_VERTICAL 6

unsigned long previousMillisHeater = 0;
bool heaterState = false;
uint16_t pwm_heater = 500;

void heater_innit()
{
    pinMode(RPWM_HORIZONTAL, OUTPUT);
    pinMode(LPWM_HORIZONTAL, OUTPUT);
    pinMode(PWM_HORIZONTAL, OUTPUT);
    pinMode(PWM_VERTICAL, OUTPUT);
    pinMode(RPWM_VERTICAL, OUTPUT);
    pinMode(LPWM_VERTICAL, OUTPUT);
}

void main_heater()
{
    unsigned long currentMillisHeater = millis();
    if (heaterState)
    {
        if (currentMillisHeater - previousMillisHeater >= 2000)
        {
            // digitalWrite(LPWM_HORIZONTAL, HIGH);
            // digitalWrite(RPWM_HORIZONTAL, LOW);
            // analogWrite(PWM_HORIZONTAL, pwm_heater);
            digitalWrite(LPWM_VERTICAL, HIGH);
            digitalWrite(RPWM_VERTICAL, LOW);
            analogWrite(PWM_VERTICAL, pwm_heater);
            // Serial.println(" Heater ON");
            heaterState = false;
            previousMillisHeater = currentMillisHeater;
        }
    }
    else
    {
        if (currentMillisHeater - previousMillisHeater >= 1000)
        {
            digitalWrite(LPWM_HORIZONTAL, HIGH);
            digitalWrite(RPWM_HORIZONTAL, LOW);
            analogWrite(PWM_HORIZONTAL, 0);
            digitalWrite(LPWM_VERTICAL, HIGH);
            digitalWrite(RPWM_VERTICAL, LOW);
            analogWrite(PWM_VERTICAL, 0);
            // Serial.println("Heater OFF");
            heaterState = true;
            previousMillisHeater = currentMillisHeater;
        }
    }
}