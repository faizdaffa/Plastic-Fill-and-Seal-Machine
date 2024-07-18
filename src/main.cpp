#include <Arduino.h>
#include <seal_servo.h>
#include <seal_accelstepper.h>
#include <heater.h>
#include <thermocouple.h>
#include <lcd_display.h>

unsigned long previousTime = 0;
int stepsPerRotation = 200;
int increaseStep = 500;
int count = 0;

void setup()
{
  Serial.begin(9600);
  lcd_innit();
  servo_innit();
  accelStepper_innit();
  heater_innit();
  servo_open_position();
  lcd.clear();
}

void manual_code() 
{
  // ===================================READ TEMPERATURE THERMOCOUPLE====================================
  temperature_V = thermocoupleVertical.readCelsius();
  temperature_H = thermocoupleHorizontal.readCelsius();
  lcd.setCursor(0, 0);
  lcd.print("Fill & Seal Machine");
  lcd.setCursor(0, 1);
  lcd.print("T_Verical   :" + String(temperature_V));
  lcd.setCursor(0, 2);
  lcd.print("T_Horizontal:" + String(temperature_H));

  // ==============================================Kondisi 1=============================================
  // Kondisi 1: Pompa ON, Servo kebuka, Stepper Stop, LCD Display
  // 1. POMPA ON
  digitalWrite(POMPA, HIGH);
  // 2. Servo Kebuka
  servoVertical.write(120);
  servoHorizontal.write(65);
  delay(500);
  // 3. Stepper Stop
  digitalWrite(LPWM_VERTICAL, LOW);
  digitalWrite(RPWM_VERTICAL, LOW);
  analogWrite(PWM_VERTICAL, 0);
  digitalWrite(LPWM_HORIZONTAL, LOW);
  digitalWrite(RPWM_HORIZONTAL, LOW);
  analogWrite(PWM_HORIZONTAL, 0);
  // 4. LCD Display
  lcd.setCursor(0, 0);
  lcd.print("Fill & Seal Machine");
  lcd.setCursor(0, 1);
  lcd.print("T_Verical   :" + String(temperature_V));
  lcd.setCursor(0, 2);
  lcd.print("T_Horizontal:" + String(temperature_H));

  // ==============================================Kondisi 2===============================================
  // Kondisi 2: Stepper ON (Tarik Plastik), Servo Ketutup (ngejepit), Pompa ON (Ngisi kemasan), LCD Display
  // 1. Stepper ON (Tarik Plastik)
  stepsPerRotation += 200;
  stepperVertical.moveTo(stepsPerRotation);
  stepperHorizontal.moveTo(stepsPerRotation);
  while (stepperVertical.distanceToGo() != 0 || stepperHorizontal.distanceToGo() != 0) {
    stepperVertical.run();
    stepperHorizontal.run();
  }
  digitalWrite(LPWM_VERTICAL, HIGH);
  digitalWrite(RPWM_VERTICAL, LOW);
  analogWrite(PWM_VERTICAL, 50);        // Set PWM (0-255) untuk mengatur besar arus sealer/heater vertical
  digitalWrite(LPWM_HORIZONTAL, HIGH);
  digitalWrite(RPWM_HORIZONTAL, LOW);
  analogWrite(PWM_HORIZONTAL, 255);     // Set PWM (0-255) untuk mengatur besar arus sealer/heater horizontal
  // 2. Servo ketutup(ngejepit)
  servoVertical.write(20);
  servoHorizontal.write(0);
  // 3. pompa ON (Ngisi kemasan)
  digitalWrite(POMPA, LOW);
  // 4. LCD Display
  lcd.setCursor(0, 0);
  lcd.print("Fill & Seal Machine");
  lcd.setCursor(0, 1);
  lcd.print("T_Verical   :" + String(temperature_V));
  lcd.setCursor(0, 2);
  lcd.print("T_Horizontal:" + String(temperature_H));
  lcd.setCursor(0, 3);
  count += 1;
  lcd.print("Jumlah      :" + String(count));
  delay(3000);
  // ============================================Kembali ke awal===========================================
}

void loop()
{
  manual_code();
}