#include <Enes100.h>
#include <FastLED.h>

#define NUM_LEDS 6

#define LED_DATA_PIN 13

// Define the array of leds
CRGB leds[NUM_LEDS];

//To compile you better have helpers.h and Enes100.h. I also edited helpers.h so you need to update it.

#define ENA 3
#define IN1 2
#define IN2 4
#define IN3 7
#define IN4 6
#define ENB 5
#define ENES100_HELPERS
#define STATE_DELAY .2
#include "helpers.h"

void setup() {
    FastLED.addLeds<WS2812B, LED_DATA_PIN, GRB>(leds, NUM_LEDS);  // GRB ordering is typical
    leds_set(CRGB(100, 0, 0));
    Enes100.begin("Richaron", DATA, 13, 8, 9);

    pinMode(ENA, OUTPUT);
    pinMode(ENB, OUTPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);

    psl("Starting sequence");
    Enes100.updateLocation();
    while (!sanityCheck()) {
        psl("The system reports faulty info :(");
        putl(Enes100.location.theta);
        putl(Enes100.location.x);
        putl(Enes100.location.y);
        leds_flash(10, CRGB(100, 0, 0));
        Enes100.updateLocation();
    }

    leds_set(CRGB(50, 50, 50));
    if (Enes100.location.x < .55)
        goTo(.2, 1);
    goTo(1.1, 1.84);
    goTo(1.2, 1.84);
    goTo(1.6, 1.84);
    goTo(2.0, 1.84);
    goTo(2.4, 1.83);
    goTo(2.8, 1.4);
    goTo(3.8, 1.4);
    psl("Done");
}

void loop() {
    setMotors(100, -100);
    party(255);
}

const float kP = 100.0;
#define MAX_TURN_SPEED 130
void setAngle(double target) {
    ps("Targeting angle: ");
    pl(target);
    Enes100.updateLocation();
    const double thresh = 0.1;
    double *curr = &Enes100.location.theta;
    while (abs(target - *curr) > thresh) {
        //    while (true) {
        Enes100.updateLocation();
        //        put(*curr);
        //        put(target);
        //        put(millis());
        double p = kP * (target - *curr);
        //        putl(p);
        p = constrain(p, -MAX_TURN_SPEED, MAX_TURN_SPEED);
        //        putl(p);
        setMotors(p, -p);
    }
    ps("Got to angle: ");
    putl(target);
    putl(*curr);
    setMotors(0);
}

void goTo(double tx, double ty) {
    Enes100.updateLocation();
    ps("Going to x:");
    p(tx);
    ps(" y:");
    pl(ty);
    double dis = 100;
    double speed = 0;
    float measuredSpeed = .5;
    const float alpha = 0.2;
    uint32_t last_time = millis();
    uint32_t current_time = millis();
    float lastTheta = Enes100.location.theta;
    int slowCount = 0;
    while (dis > 0.15) { //Within 5 CM
        Enes100.updateLocation();
        if (!sanityCheck()) {
            //            psl("The system reports faulty info :(");
            //            putl(Enes100.location.theta);
            //            putl(Enes100.location.x);
            //            putl(Enes100.location.y);
            randomWobble();
            delay(750);
            continue;
        }
        last_time = current_time;
        current_time = millis();
        float new_dis = sqrt((tx - Enes100.location.x) * (tx - Enes100.location.x) + (ty - Enes100.location.y) * (ty - Enes100.location.y));
        measuredSpeed = (.2 * ((dis - new_dis) / (current_time - last_time)) + .8 * measuredSpeed); //High alpha for buttery smooth. Speed in m/s
        dis = new_dis;
        putl(measuredSpeed * 1000);
        if (measuredSpeed * 1000 < 0.1) { //2
            slowCount++;
            //            psl("slow");
        }
        if (slowCount > 10) {
            //            psl("Detected stuck. Attempting measures");
            leds_set(CRGB(100, 0, 0));
            setMotors(-200, -70);
            delay(200);
            setMotors(0);
            delay(100);
            leds_set(CRGB(50, 50, 50));
            slowCount = 0;
        }
        //We could go directly to a point, but we could also shoot for a point on a line.
        float target_angle = atan2(ty - Enes100.location.y, tx - Enes100.location.x);
        //We are going to try to predict the robots location forward in time by extrapolating current rotational state.
        float delta_theta = Enes100.location.theta - lastTheta;
        lastTheta = Enes100.location.theta;
        float current_angle = Enes100.location.theta + HALF_PI + delta_theta * STATE_DELAY;
        if (current_angle > PI) current_angle -= 2 * PI;
        //        ps("c:");
        //        p(toDeg(current_angle));
        //Our current will stay the same. It is within the range -pi/2 to 3pi/2
        //Our target anle, however will change based on how we want to approach the thing.
        //For example, if (assume for a second our current is -pi to pi) we are targeting
        //.9pi and are currently at -.9 pi, we should instead try to target -1.1 pi, which is equivalent
        //We will try to find a potential new target.
        //Basically, we should be able to get the target within a pi of the current.
        float delta = abs(target_angle - current_angle);
        if (delta > PI) {
            if (target_angle > current_angle) {
                target_angle = target_angle - 2 * PI;
            }
            else {
                target_angle = target_angle + 2 * PI;
            }
        }
        //        p(" ft:") //fixed target;
        //        p(toDeg(target_angle));
        speed = alpha * (30 / (abs(target_angle - current_angle))) + ((1 - alpha) * speed);
        if (!(speed < 255)) speed = 255;
        //        ps(" ts: ");
        //        p(speed);
        ps(" ms: ");
        pl(measuredSpeed * 1000);
        double p = kP / 2 * (target_angle - current_angle);
        p = constrain(p, -MAX_TURN_SPEED, MAX_TURN_SPEED);
        //        putl(dis);
        setMotors(p + speed, -p + speed);
    }
}

void randomWobble() {
    //1 second of (not) random wobble
#define WOBBLE_PWR 100
    setMotors(WOBBLE_PWR, 0);
    delay(200);
    setMotors(0, WOBBLE_PWR);
    delay(200);
    setMotors(WOBBLE_PWR, 0);
    delay(200);
    setMotors(0, WOBBLE_PWR);
    delay(200);
    setMotors(WOBBLE_PWR, 0);
    delay(200);
    setMotors(0);
}

bool sanityCheck() {
    return Enes100.location.theta < PI * 1.1 &&
           Enes100.location.theta > -PI * 1.1 &&
           Enes100.location.x > -0.1 &&
           Enes100.location.x < 4.1 &&
           Enes100.location.y > -0.1 &&
           Enes100.location.y < 2.1;
}

float toDeg(float rad) {
    return 180.0f * rad / PI;
}
