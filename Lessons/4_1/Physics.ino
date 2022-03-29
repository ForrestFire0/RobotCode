float wheelSpeed = 0;

float getWheelSpeed() {
    return wheelSpeed;
}

void setMotorPower(float power) {
    wheelSpeed += (-0.03 * wheelSpeed) + (0.05) * power;
}
