#include <Servo.h>

Servo servoVertical;
Servo servoHorizontal;
unsigned long previousMillisServo = 0;
bool isServoMove = false;

void servo_innit() 
{
  servoVertical.attach(12);
  servoHorizontal.attach(13);
}

void servo_open_position()
{
  servoVertical.write(20);
  servoHorizontal.write(0);
}

void moveServo() 
{
  unsigned long currentMillisServo = millis();

  if (isServoMove)
  {
    if (currentMillisServo - previousMillisServo >= 3000)
    {
      Serial.println("Close Seal");
      servoVertical.write(120);
      servoHorizontal.write(65);
      isServoMove = false;
      previousMillisServo = currentMillisServo;
    }
  }
  else
  {
    if (currentMillisServo - previousMillisServo >= 1000)
    {
      Serial.println("Open Seal");
      servoVertical.write(20);
      servoHorizontal.write(0);
      isServoMove = true;
      previousMillisServo = currentMillisServo;
    }
  }
}

