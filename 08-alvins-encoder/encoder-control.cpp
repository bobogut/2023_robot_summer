#include <ESP32Encoder.h>
#include <Arduino.h>

#include "global-var.h"

ESP32Encoder encoderA;
ESP32Encoder encoderB;

int E1A_PIN = 36;
int E1B_PIN = 39;
int E2A_PIN = 34;
int E2B_PIN = 35;

void setupEncoder()
{
    ESP32Encoder::useInternalWeakPullResistors = UP;
    encoderA.attachHalfQuad(E1A_PIN, E1B_PIN);
    encoderA.setCount(0);
    encoderB.attachHalfQuad(E2A_PIN, E2B_PIN);
    encoderB.setCount(0);
}

void calcEncoder()
{
    currentEncoderA = encoderA.getCount();
    currentEncoderB = encoderB.getCount();

    // Serial.printf("preCountA = %ld\tB = %ld\tCurrent A = %ld\tB = %ld\n", prevCountA, prevCountB, currentEncoderA, currentEncoderB);

    double deA = abs(currentEncoderA - prevCountA);
    double deB = abs(currentEncoderB - prevCountB);
    currentTime = millis();
    double dt = (currentTime - lastIntervalTime);

    if (dt >= 100)
    {
        encoderSpeedA = deA / dt;
        encoderSpeedB = deB / dt;

        prevCountA = currentEncoderA;
        prevCountB = currentEncoderB;
        lastIntervalTime = currentTime;
    }
}
