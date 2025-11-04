#include <Arduino.h>

#define SERVO_PIN 13
#define PWM_CHANNEL 0
#define PWM_FREQ 50
#define PWM_RES 16

int currentAngle = 90;

void setServoAngle(int angle) {
    int pulseWidth = map(angle, 0, 180, 1000, 2000);
    int duty = (pulseWidth * (1 << PWM_RES)) / 20000;
    ledcWrite(PWM_CHANNEL, duty);
}

void moveToAngle(int target) {
    int stepSize = 1;
    int stepDelay = 30;
    if (currentAngle < target) {
        for (int pos = currentAngle; pos <= target; pos += stepSize) {
            setServoAngle(pos);
            delay(stepDelay);
        }
    } else if (currentAngle > target) {
        for (int pos = currentAngle; pos >= target; pos -= stepSize) {
            setServoAngle(pos);
            delay(stepDelay);
        }
    }
    currentAngle = target;
}

void setup() {
    Serial.begin(115200);
    ledcSetup(PWM_CHANNEL, PWM_FREQ, PWM_RES);
    ledcAttachPin(SERVO_PIN, PWM_CHANNEL);
    setServoAngle(90);
    currentAngle = 90;
}

void loop() {
    for (int i = 0; i < 3; i++) {
        moveToAngle(115);
        delay(800);
        moveToAngle(65);
        delay(1000);
    }
}

