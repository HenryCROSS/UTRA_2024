#include <common.h>
#include <Motor_utils.h>
#include <QTR_utils.h>
#include <Servo_control.h>
#include <Main_Task.h>

Servo servo1;
int numL = 0;
int numML = 0;
int numMR = 0;
int numR = 0;
double distance[3] = {0, 0, 0};

//按键扫描程序,检测按钮是否按下
void key_scan()
{
  while (!digitalRead(key));     //当按键没有被按下一直循环（被按下为T=1，没有被按下为F=0）
  while (digitalRead(key))       //当按键被按下时
  {
    delay(10);	                  //延时10ms
    if (digitalRead(key)  ==  HIGH)//第二次判断按键是否被按下
    {
      delay(100);
      while (digitalRead(key));  //判断按键是否被松开
    }
  }
}

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
//   key_scan();  

  servo1.attach(6);//舵机信号接口
  servo1.write(servo1_init); //舵机归位

  delay(5000);
}

void qtr_test(){
    int qtr_l = qtr_read_analog(QTR_SENSOR_L);
    int qtr_r = qtr_read_analog(QTR_SENSOR_R);
    int qtr_ml = qtr_read_analog(QTR_SENSOR_ML);
    int qtr_mr = qtr_read_analog(QTR_SENSOR_MR);

    Serial.print("qtr_l: ");
    Serial.print(qtr_l);
    Serial.print("qtr_r: ");
    Serial.print(qtr_r);
    Serial.print("qtr_ml: ");
    Serial.print(qtr_ml);
    Serial.print("qtr_mr: ");
    Serial.print(qtr_mr);
    Serial.println();
}

void loop() {
    // task1();
    // qtr_test();
    // scan_for_obj();
    Forward();
}
