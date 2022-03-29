/*  Arduino DC Motor Control - PWM | H-Bridge | L298N
         Example 02 - Arduino Robot Car Control
    by Dejan Nedelkovski, www.HowToMechatronics.com
*/

//3, 5, 6, 9, 10, 11
#define ENA 3
#define IN1 2
#define IN2 4
#define IN3 7
#define IN4 6
#define ENB 5
#include "helpers.h"


void setup() {
    Serial.begin(115200);
    pinMode(ENA, OUTPUT);
    pinMode(ENB, OUTPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
    psl("Yeet");
}

byte i = 0;
void loop() {
    psl("Start");
    setMotors(i);
    putl(i);
    if(i == 255) {
        while(true);
    }
    i++;
    delay(50);
}

//left from -256 to 256
void setMotors(int left, int right) {
    
}

void setMotors(int speed) {
    if(speed > 0) {
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);
    } else {
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);
    }
    speed = abs(speed);
    analogWrite(ENA, speed); // Send PWM signal to motor A
    analogWrite(ENB, speed); // Send PWM signal to motor B
}
