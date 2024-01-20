#include <common.h>

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
  // key_scan();  
}

void loop() {
  // put your main code here, to run repeatedly:
}
