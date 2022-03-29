#define ENA 3
#define IN1 2
#define IN2 4
#define IN3 7
#define IN4 6
#define ENB 5

#include <helpers.h>

void setup() {
    Serial.begin(115200);
    
    pinMode(ENA, OUTPUT);
    pinMode(ENB, OUTPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
    int rf=29,rb=29,lf=29,lb=29;
    psl("\n\n\nProgram Started\n\n\nNow testing right wheel forward\n\nPress any key when the wheel moves.");
    while(true) {
        if(Serial.available()) break;
        rf++;
        putl(rf);
        setMotors(0, rf);
        delay(250);
    }
    while(Serial.available()) Serial.read();
    ps("Right forward deadband is ");
    pl(rf);

    psl("\n\nNow testing right wheel backward\n\nPress any key when the wheel moves.");
    while(true) {
        if(Serial.available()) break;
        rb++;
        putl(rb);
        setMotors(0, -rb);
        delay(250);
    }
    while(Serial.available()) Serial.read();
    ps("Right backward deadband is ");
    pl(rb);


    psl("\nNow testing left wheel forward\n\nPress any key when the wheel moves.");
    while(true) {
        if(Serial.available()) break;
        lf++;
        putl(lf);
        setMotors(lf, 0);
        delay(250);
    }
    while(Serial.available()) Serial.read();
    ps("Left forward deadband is ");
    pl(lf);

    psl("\n\nNow testing left wheel backward\n\nPress any key when the wheel moves.");
    while(true) {
        if(Serial.available()) break;
        lb++;
        putl(lb);
        setMotors(-lb, 0);
        delay(250);
    }
    while(Serial.available()) Serial.read();
    ps("Left backward deadband is ");
    pl(lb);

    psl("Done.");
    reset();
}

void loop() {
    
}

#define LEFT_POS 0
#define LEFT_NEG 0
#define RIGHT_POS 0
#define RIGHT_NEG 0


//left from -256 to 256
void setMotors(int left, int right) {
    if(left > 0) {
        if(left < LEFT_POS) left = LEFT_POS;
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
    } else if(left < 0){
        if(left > -LEFT_NEG) left = -LEFT_NEG;
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
    }
    analogWrite(ENA, abs(left)); // Send PWM signal to motor A
    
    if(right > 0) {
        if(right < RIGHT_POS) right = RIGHT_POS;
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);
    } else if (right < 0) {
        if(right > -RIGHT_NEG) right = -RIGHT_NEG;
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, HIGH);
    }
    analogWrite(ENB, abs(right)); // Send PWM signal to motor B
}
