#include <AccelStepper.h>

unsigned long previousMillisStepper = 0;
bool isStepperMove = false;
uint16_t set_speed = 500;

AccelStepper stepperVertical(1, 52, 53);   // (Type of driver: with 2 pins, STEP, DIR)
AccelStepper stepperHorizontal(1, 50, 51); // (Type of driver: with 2 pins, STEP, DIR)

void accelStepper_innit()
{
    stepperVertical.setMaxSpeed(1000);   // Set maximum speed value for the stepper
    stepperHorizontal.setMaxSpeed(1000); // Set maximum speed value for the stepper
    stepperVertical.setAcceleration(500); // Set acceleration value for the stepper
    stepperHorizontal.setAcceleration(500); // Set acceleration value for the stepper
}

void move_stepper()
{
    stepperVertical.setSpeed(set_speed);
    stepperHorizontal.setSpeed(set_speed);
    stepperHorizontal.runSpeed();
    stepperVertical.runSpeed();
}

void stop_stepper()
{
    stepperVertical.setSpeed(0);
    stepperHorizontal.setSpeed(0);
    stepperHorizontal.runSpeed();
    stepperVertical.runSpeed();
}

void moveStepper()
{
    unsigned long currentMillisStepper = millis();
    if (isStepperMove)
    {
        if (currentMillisStepper - previousMillisStepper >= 1000)
        {
            Serial.println("stop stepper");
            stepperVertical.setSpeed(0);
            stepperHorizontal.setSpeed(0);
            isStepperMove = false;
            previousMillisStepper = currentMillisStepper;
        }
        else
        {
            stepperVertical.runSpeed();
            stepperHorizontal.runSpeed();
        }
    }
    else
    {
        if (currentMillisStepper - previousMillisStepper >= 3000)
        {
            Serial.println("move stepper");
            stepperVertical.setSpeed(set_speed);
            stepperHorizontal.setSpeed(set_speed);
            stepperVertical.runSpeed();
            stepperHorizontal.runSpeed();
            isStepperMove = true;
            previousMillisStepper = currentMillisStepper;
        }
    }
}