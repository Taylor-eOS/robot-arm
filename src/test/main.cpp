#include <Arduino.h>

#define SERVO_PIN 13
#define PWM_CHANNEL 0
#define PWM_FREQ 50
#define PWM_RES 16

void setServoAngle(int angle) {
    int pulseWidth = map(angle, 0, 180, 1000, 2000);
    int duty = (pulseWidth * (1 << PWM_RES)) / 20000;
    ledcWrite(PWM_CHANNEL, duty);
}

void setup() {
    Serial.begin(115200);
    ledcSetup(PWM_CHANNEL, PWM_FREQ, PWM_RES);
    ledcAttachPin(SERVO_PIN, PWM_CHANNEL);
    setServoAngle(90);
}

void loop() {
    for (int i = 0; i < 3; i++) {
        Serial.println(i + 1);
        setServoAngle(110);
        delay(1000);
        setServoAngle(70);
        delay(1000);
    }
}

