#include <Servo.h>

#define POMPA 25
Servo servoVertical;
Servo servoHorizontal;
unsigned long previousMillisServo = 0;
bool isServoMove = false;

void servo_innit()
{
  servoVertical.attach(12);
  servoHorizontal.attach(13);
  pinMode(POMPA, OUTPUT);
  digitalWrite(POMPA, HIGH);
}

void servo_open_position()
{
  servoVertical.write(120);
  servoHorizontal.write(65);
}

void servo_close_position()
{
  servoVertical.write(20);
  servoHorizontal.write(0);
}

void moveServo()
{
  unsigned long currentMillisServo = millis();

  if (isServoMove)
  {
    if (currentMillisServo - previousMillisServo >= 1000)
    {
      digitalWrite(POMPA, HIGH);
      servoVertical.write(120);
      servoHorizontal.write(65);
      isServoMove = false;
      previousMillisServo = currentMillisServo;
      Serial.println("Close Seal");
    }
  }
  else
  {
    if (currentMillisServo - previousMillisServo >= 2000)
    {
      digitalWrite(POMPA, LOW);
      servoVertical.write(20);
      servoHorizontal.write(0);
      isServoMove = true;
      previousMillisServo = currentMillisServo;
      Serial.println("Open Seal");
    }
  }
}
