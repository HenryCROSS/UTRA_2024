#include <common.h>


void setup() {
  // put your setup code here, to run once:
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LEFT_WHEEL_FORWARD, OUTPUT);
  pinMode(LEFT_WHEEL_BACKWARD, OUTPUT);
  pinMode(RIGHT_WHEEL_FORWARD, OUTPUT);
  pinMode(RIGHT_WHEEL_BACKWARD, OUTPUT);
  pinMode(LEFT_SPEED, OUTPUT);
  pinMode(RIGHT_SPEED, OUTPUT);
  pinMode(QTR_SENSOR_ML, INPUT);
  pinMode(QTR_SENSOR_MR, INPUT);
  pinMode(QTR_SENSOR_L, INPUT);
  pinMode(QTR_SENSOR_R, INPUT); 
  Serial.begin(9600);

  servo1.attach(6);//舵机信号接口
  servo1.write(servo1_init); //舵机归位
  // key_scan();  
}

void loop() {
  // put your main code here, to run repeatedly:
}
