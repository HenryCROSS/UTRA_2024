// official
#include <Arduino.h>

// third party

// ours
#include <Ultrasonic.h>
#include <config.h>

int degree_lz[] = {15, 90, 165};

void servo_start()
{
    servo1.write(servo1_init);
}

// 15 90 165
void scan_for_obj()
{
    for (int idx = 0; idx < sizeof(degree_lz); idx++)
    {
        servo1.write(degree_lz[idx]);
        delay(30);
        distance[idx] = detect_obj_distance(TRIGGER_PIN, ECHO_PIN);
        Serial.print(degree_lz[idx]);
        Serial.print(",");
        Serial.print(distance[idx]);
        Serial.print(".");
    }
    for (int idx = sizeof(degree_lz) - 1; idx >= 0; idx--)
    {
        servo1.write(degree_lz[idx]);
        delay(30);
        distance[idx] = detect_obj_distance(TRIGGER_PIN, ECHO_PIN);
        Serial.print(degree_lz[idx]);
        Serial.print(",");
        Serial.print(distance[idx]);
        Serial.print(".");
    }
}