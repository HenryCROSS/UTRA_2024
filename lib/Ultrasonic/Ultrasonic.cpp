// official
#include <Arduino.h>

// third party

// ours
#include <config.h>
#include <Ultrasonic.h>

double detect_obj_distance(uint8_t trigger_pin, uint8_t echo_pin) {
  digitalWrite(trigger_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger_pin, LOW);
  return pulseIn(echo_pin, HIGH, MAX_DISTANCE * 58) / 58.0;
}

bool is_obj_exist(double range) {
  distance = detect_obj_distance(TRIGGER_PIN, ECHO_PIN);
  if (distance == 0.00) {
    return false;
  } else if (distance < range && distance > 0) {
    return true;
  } else {
    return false;
  }
}