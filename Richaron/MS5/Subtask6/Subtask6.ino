#include <Enes100.h>

//To compile you better have helpers.h and Enes100.h. I also edited helpers.h so you need to update it.

#define ENA 3
#define IN1 2
#define IN2 4
#define IN3 7
#define IN4 6
#define ENB 5
#define ENES100_HELPERS
#include "helpers.h"

void setup() {
    Enes100.begin("Richaron", DATA, 3, 8, 9);
    pinMode(ENA, OUTPUT);
    pinMode(ENB, OUTPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
    goTo(1,1);
    setAngle(0);
    setAngle(HALF_PI);
    setAngle(0);
    setAngle(-HALF_PI);
    setAngle(0);
    psl("We are done lol");
}

void loop() {
}

const float kP = 300;
void setAngle(double target){
    ps("Targeting angle: ");
    pl(target);
    Enes100.updateLocation();
    const double thresh = 0.1;
    double *curr = &Enes100.location.theta;
    while(abs(target - *curr) > thresh) {
        Enes100.updateLocation();
        double p = kP * (target - *curr);
        setMotors(-p, p);
    }
}

void goTo(double tx, double ty) {
    double* cx = &Enes100.location.x;
    double* cy = &Enes100.location.y;
    double *c0 = &Enes100.location.theta;
    double dis = 100;
    while(dis > 0.05){ //Within 5 CM
        Enes100.updateLocation();
        dis = sqrt((tx - *cx) * (tx - *cx) + (ty - *cy) * (ty - *cy));
        //We could go directly to a point, but we could also shoot for a point on a line.
        float angle = atan2(ty - *cy, tx - *cx);
        p("Current: ");
        p(*c0);
        p("  Target: ");
        p(angle);
        double speed = 3/(abs(angle - *c0));
        if(!(speed < 200)) speed = 200; 
        p("  Speed: ");
        p(speed);
        double p = kP * (angle - *c0);
        p("  Turning: ");
        pl(p);
        setMotors(-p + speed, p + speed);
    }
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
