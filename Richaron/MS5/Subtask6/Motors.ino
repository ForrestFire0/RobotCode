/*
    There are two concepts that I am using here to possibly help
*/

#define BOOST_SPEED 200
#define RIGHT_DEADBAND 36
#define LEFT_DEADBAND 50

//left from -256 to 256
void setMotors(int left, int right) {
    //First, we need to calculate the actual motor precentage based on what we are passed.
    //We cannot do this in _setMotors because it uses recursion to help with cold starts.
    //We are adjusting for speeds that the motor will not even move from, even with a cold start help.
    if (left < 0) left -= LEFT_DEADBAND;
    if (left > 0) left += LEFT_DEADBAND;
    if (right < 0) right -= RIGHT_DEADBAND;
    if (right > 0) right += RIGHT_DEADBAND;
    left = constrain(left, -255, 255);
    right = constrain(right, -255, 255);
    _setMotors(left, right);
}

int d = 0;
int last_left, last_right;
void _setMotors(int left, int right) {
    int setLeft = left, setRight = right;
    boolean db = false;

    if (left > 0) {
        if (last_left == 0 && left < BOOST_SPEED) {
            left = BOOST_SPEED;
            db = true;
        }
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
    } else if (left < 0) {
        if (last_left == 0 && left > -BOOST_SPEED) {
            left = -BOOST_SPEED;    //Help with startup issues
            db = true;
        }
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
    }

    last_left = left;
    analogWrite(ENA, abs(left)); // Send PWM signal to motor A
    if (right > 0) {
        if (last_right == 0 && right < BOOST_SPEED) {
            right = BOOST_SPEED;
            db = true;
        }
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);
    } else if (right < 0) {
        if (last_right == 0 && right > -BOOST_SPEED) {
            right = -BOOST_SPEED;
            db = true;
        }
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, HIGH);
    }
    last_right = right;
    analogWrite(ENB, abs(right)); // Send PWM signal to motor B
    if (db) {
        delay(10);
        setMotors(setLeft, setRight); //Reset those bad boys to what they should be.
    }
}


void setMotors(int speed) {
    setMotors(speed, speed);
}
