// official
#include <Arduino.h>

// third party

// ours
#include <config.h>
#include <Ultrasonic.h>

void Servo_Start(){
    servo1.write(servo1_init);
}

void Scan_for_Obj(){
  for(int i=15;i<=165;i++){  
    servo1.write(i);
    delay(30);
    distance = detect_obj_distance(TRIGGER_PIN, ECHO_PIN);
    Serial.print(i);
    Serial.print(",");
    Serial.print(distance);
    Serial.print(".");
  }
  for(int i=165;i>15;i--){  
    servo1.write(i);
    delay(30);
    distance = detect_obj_distance(TRIGGER_PIN, ECHO_PIN);
    Serial.print(i);
    Serial.print(",");
    Serial.print(distance);
    Serial.print(".");
  }
}