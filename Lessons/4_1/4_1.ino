#include <helpers.h>

void setup() {
    Serial.begin(115200);
}

//Goal - hold the wheel speed constant at 100 rads/second

#define kP 1
#define kI 1
#define kD 1

float target = 100; 
float lastValue = getWheelSpeed();
float integrand = 0;

void loop() {
    //This function getWheelSpeed is any function that gets the current value.
    float current = getWheelSpeed();
    
    float difference = target - current;
    if (abs(difference) < 5)
        integrand += difference;
    else
        integrand = 0;

    float output = kP * difference
                   + kI * integrand
                   + kD * (lastValue - current);

    setMotorPower(output);

    lastValue = current;
}
