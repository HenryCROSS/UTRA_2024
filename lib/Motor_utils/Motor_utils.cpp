// official
#include <Arduino.h>

// third party

// ours
#include <config.h>
#include <Motor_utils.h>

void motor_run(int lspeed, int rspeed) {
  int motor_delta = SPEED * delta;
  int abslspeed=abs(lspeed);
  int absrspeed=abs(rspeed);
  analogWrite(LEFT_SPEED,abslspeed-motor_delta);
  analogWrite(RIGHT_SPEED,absrspeed);
  if(lspeed > 0){
    digitalWrite(LEFT_WHEEL_FORWARD,HIGH);
    digitalWrite(LEFT_WHEEL_BACKWARD,LOW);
  }else if(lspeed == 0){
    digitalWrite(LEFT_WHEEL_FORWARD,HIGH);
    digitalWrite(LEFT_WHEEL_BACKWARD,HIGH);
  }else{
    digitalWrite(LEFT_WHEEL_FORWARD,LOW);
    digitalWrite(LEFT_WHEEL_BACKWARD,HIGH);
  }

  if(rspeed > 0){
    digitalWrite(RIGHT_WHEEL_FORWARD,HIGH);
    digitalWrite(RIGHT_WHEEL_BACKWARD,LOW);
  }else if(rspeed == 0){
    digitalWrite(RIGHT_WHEEL_FORWARD,HIGH);
    digitalWrite(RIGHT_WHEEL_BACKWARD,HIGH);
  }else{
    digitalWrite(RIGHT_WHEEL_FORWARD,LOW);
    digitalWrite(RIGHT_WHEEL_BACKWARD,HIGH);
  }
}

void Emerge_Stop(){
  // motor_run(-255,-255);
  // delay(10);
  motor_run(0,0);
}

void Forward(){
  motor_run(SPEED,SPEED);
}

void Forward_By_Time(int forward_time){
  Forward();
  delay(forward_time);
  Emerge_Stop();
}

void Backward(){
  motor_run(-SPEED,-SPEED);
}

void Backward_By_Time(int backward_time){
  Backward();
  delay(backward_time);
  Emerge_Stop();
}

void TurnL(){
  motor_run(0,SPEED);
}

void TurnR(){
  motor_run(SPEED,0);
}

void RotateL(){
  motor_run(-SPEED,SPEED);
}

void RotateR(){
  motor_run(SPEED,-SPEED);
}

void RotateL_time(int ms){
  motor_run(-SPEED,SPEED);
  delay(ms);
}

void RotateR_time(int ms){
  motor_run(SPEED,-SPEED);
  delay(ms);
}
