#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <common.h>

#define LEFT_SPEED 10              // Motor A enable pin
#define RIGHT_SPEED 9              // Motor B enable pin
#define RIGHT_WHEEL_FORWARD 2      // Motor B In1 pin
#define RIGHT_WHEEL_BACKWARD 3     // Motor B In2 pin
#define LEFT_WHEEL_FORWARD 4       // Motor A In1 pin 
#define LEFT_WHEEL_BACKWARD 5      // Motor A In2 pin
#define TRIGGER_PIN 6              // Ultrasonic sensor trigger pin
#define ECHO_PIN 7                 // Ultrasonic sensor echo pin

#define speed 100 //总体速度
int delta = 0.05; //左轮减速调直


#define First_forward_time 200 //转弯前前进时间
#define First_turn_time 200 //转弯时第一次盲转的时间

#define QTR_SENSOR_L A1           // QTR sensor
#define QTR_SENSOR_R A2           // QTR sensor
#define QTR_SENSOR_ML A3           // QTR sensor
#define QTR_SENSOR_MR A4           // QTR sensor
#define black_fence 700

#define Ultrasonic_Distance 50
#define MAX_DISTANCE 200           // 最大超声波距离
double distance = 0;

#define Micro_Delay_Time 1 

#define key 1 //start button

int numL = 0;
int numML = 0;
int numMR = 0;
int numR = 0;


Servo servo1;//舵机信号接口在setup里面
int servo1_init = 90;  //舵机初始状态

#endif // !_CONFIG_H_