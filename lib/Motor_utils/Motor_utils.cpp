// official
#include <Arduino.h>

// third party

// ours
#include <config.h>
#include <Motor_utils.h>

void motor_run(int lspeed, int rspeed) {
  int motor_delta = speed * delta;
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
  motor_run(speed,speed);
}

void Forward_By_Time(int forward_time){
  Forward();
  delay(forward_time);
  Emerge_Stop();
}

void Backward(){
  motor_run(-speed,-speed);
}

void Backward_By_Time(int backward_time){
  Backward();
  delay(backward_time);
  Emerge_Stop();
}

void TurnL(){
  motor_run(0,speed);
}

void TurnR(){
  motor_run(speed,0);
}

void RotateL(){
  motor_run(-speed,speed);
}

void RotateR(){
  motor_run(speed,-speed);
}
void turn_Left_to_Line(){
  Forward_By_Time(First_forward_time);
  while (numMR < black_fence){
    read_data();
    TurnL();
    delay(Micro_Delay_Time);
  }
}
void turn_Right_to_Line(){
  Forward_By_Time(First_forward_time);
  while (numML < black_fence){
    read_data();
    TurnR();
    delay(Micro_Delay_Time);
  }
}
void turn_Back_to_Line(){
  RotateL();
  delay(First_turn_time);
  while (numMR < black_fence){
    read_data();
    RotateL();
    delay(Micro_Delay_Time);
  }
}