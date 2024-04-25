#include <Arduino.h>
#include <seal_servo.h>
#include <seal_accelstepper.h>
#include <heater.h>
#include <thermocouple.h>
#include <lcd_display.h>

unsigned long previousTime = 0;

void setup()
{
  Serial.begin(9600);
  lcd_innit();
  servo_innit();
  accelStepper_innit();
  heater_innit();
  servo_open_position();
}

void manual_code()
{
  // read temperature
  temperature_V = thermocoupleVertical.readCelsius();
  temperature_H = thermocoupleHorizontal.readCelsius();
  // servo open position
  servoVertical.write(120);
  servoHorizontal.write(65);
  // stepper motor ON
  stepperVertical.move(200);
  stepperHorizontal.move(200);
  while (stepperVertical.run() && stepperHorizontal.run()){}
  // pompa OFF
  digitalWrite(POMPA, HIGH);
  // LCD Display
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Fill & Seal Machine");
  lcd.setCursor(0, 1);
  lcd.print("T_Verical   :" + String(temperature_V));
  lcd.setCursor(0, 2);
  lcd.print("T_Horizontal:" + String(temperature_H));
  lcd.setCursor(0, 3);
  lcd.print("Pull Plastic");

  delay(1000);

  //==============seal condition==============
  // read temperature
  temperature_V = thermocoupleVertical.readCelsius();
  temperature_H = thermocoupleHorizontal.readCelsius();
  // servo close position
  servoVertical.write(20);
  servoHorizontal.write(0);
  // stepper motor OFF
  // pompa ON
  digitalWrite(POMPA, LOW);
  // LCD Display
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Fill & Seal Machine");
  lcd.setCursor(0, 1);
  lcd.print("T_Verical   :" + String(temperature_V));
  lcd.setCursor(0, 2);
  lcd.print("T_Horizontal:" + String(temperature_H));
  lcd.setCursor(0, 3);
  lcd.print("FIll and Seal Plastic");

  delay(2000);
}

void loop()
{
  manual_code();
  // unsigned long currentTime = millis();

  // read_thermocouple();
  // main_heater();
  // moveServo();
  // testStepper();
  // moveStepper();

  // if (currentTime - previousTime >= 1000)
  // {
  //   Serial.println("Tv:" + String(temperature_V) + " Th:" + String(temperature_H) + "  ||  Heater:" + String(heaterState) + "  Stepper:" + String(isStepperMove) + "  Servo:" + String(isServoMove));
  // lcd.clear();
  // lcd.setCursor(0, 0);
  // lcd.print("Fill & Seal Machine");
  // lcd.setCursor(0, 1);
  // lcd.print("T_Verical   :" + String(temperature_V));
  // lcd.setCursor(0, 2);
  // lcd.print("T_Horizontal:" + String(temperature_H));
  // lcd.setCursor(0, 3);
  // lcd.print("Heat" + String(heaterState) + "  Step" + String(isStepperMove) + "  Servo" + String(isServoMove));

  //   previousTime = currentTime;
  // }
}
