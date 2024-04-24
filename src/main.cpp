#include <Arduino.h>
#include <seal_servo.h>
#include <seal_accelstepper.h>
#include <heater.h>
#include <thermocouple.h>

unsigned long previousTime = 0;

void setup() 
{
  Serial.begin(9600);
  servo_innit();
  accelStepper_innit();
  heater_innit();
  // servo_open_position();
}

void loop() 
{
  unsigned long currentTime = millis();

  read_thermocouple(); 
  main_heater();
  // moveServo();
  // moveStepper();
  
  if (currentTime - previousTime >= 1000) 
  {
    Serial.println("Tv:" + String(temperature_V) + " Th:" + String(temperature_H) + "  ||  Heater:" + String(heaterState) + "  Stepper:" + String(isStepperMove) + "  Servo:" + String(isServoMove));
    previousTime = currentTime;
  }
}