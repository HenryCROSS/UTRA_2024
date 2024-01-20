// official
#include <Arduino.h>

// third party

// ours
#include <config.h>
#include <track_line.h>
#include <Motor_utils.h>
#include <Ultrasonic.h>
#include <QTR_utils.h>

//读取传感器数值
void read_data() {
  numL= qtr_read_analog(QTR_SENSOR_L);
  numML = qtr_read_analog(QTR_SENSOR_ML);
  numMR = qtr_read_analog(QTR_SENSOR_MR);
  numR = qtr_read_analog(QTR_SENSOR_R);
} 

void track_line(){
  read_data();    //读取传感器值
  if(numL >= black_fence && numR >= black_fence){
    Emerge_Stop();
    delay();
  }else if(numL >= black_fence && numR < black_fence){
    turn_Left_to_Line();
  }else if(numL < black_fence && numR >= black_fence){
    turn_Right_to_Line();
  }else{
    // X 0 X X
      if (numML >= black_fence && numMR < black_fence)
    {
      TurnL();
      delay(Micro_Delay_Time);
    }
    
    // X X 0 X
    else if (numML < black_fence && numMR >= black_fence)
    {
      TurnR();
      delay(Micro_Delay_Time);
    }

    // X 0 0 X
    else if (numML >= black_fence && numMR >= black_fence)
    {
      Forward();
    }

    else{
      Go_by_Ultrasonic();
    }
  }
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

void Go_by_Ultrasonic(){

}