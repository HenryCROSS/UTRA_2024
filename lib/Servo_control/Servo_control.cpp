// official
#include <Arduino.h>

// third party

// ours
#include <Ultrasonic.h>
#include <config.h>

int degree_lz[] = {15, 90, 165};

void Servo_Start()
{
    servo1.write(servo1_init);
}

// 15 90 165
void Scan_for_Obj()
{
    for (int idx = 0; idx < sizeof(degree_lz); idx++)
    {
        servo1.write(degree_lz[idx]);
        delay(30);
        distance = detect_obj_distance(TRIGGER_PIN, ECHO_PIN);
        Serial.print(degree_lz[idx]);
        Serial.print(",");
        Serial.print(distance);
        Serial.print(".");
    }
    for (int idx = sizeof(degree_lz) - 1; idx >= 0; idx--)
    {
        servo1.write(degree_lz[idx]);
        delay(30);
        distance = detect_obj_distance(TRIGGER_PIN, ECHO_PIN);
        Serial.print(degree_lz[idx]);
        Serial.print(",");
        Serial.print(distance);
        Serial.print(".");
    }
}