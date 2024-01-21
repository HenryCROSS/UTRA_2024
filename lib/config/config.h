#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <Servo.h>

#define LEFT_SPEED 6              // Motor A enable pin
#define RIGHT_SPEED 7              // Motor B enable pin
#define RIGHT_WHEEL_FORWARD 8      // Motor B In1 pin
#define RIGHT_WHEEL_BACKWARD 9     // Motor B In2 pin
#define LEFT_WHEEL_FORWARD 10       // Motor A In1 pin 
#define LEFT_WHEEL_BACKWARD 11      // Motor A In2 pin


#define TRIGGER_PIN 5              // Ultrasonic sensor trigger pin
#define ECHO_PIN 12                 // Ultrasonic sensor echo pin

#define SPEED 100 //总体速度
const int delta = 0.05; //左轮减速调直


#define First_forward_time 200 //转弯前前进时间
#define First_turn_time 200 //转弯时第一次盲转的时间

#define QTR_SENSOR_L A1           // QTR sensor
#define QTR_SENSOR_R A2           // QTR sensor
#define QTR_SENSOR_ML A3           // QTR sensor
#define QTR_SENSOR_MR A4           // QTR sensor
#define black_fence 700

#define Ultrasonic_Distance 50
#define MAX_DISTANCE 200           // 最大超声波距离
extern double distance[3];

#define Micro_Delay_Time 1 

#define key 3 //start button

extern int numL;
extern int numML;
extern int numMR;
extern int numR;

extern Servo servo1;//舵机信号接口在setup里面
const int servo1_init = 90;  //舵机初始状态

#define TASK4_ROTATE_L_TIME 100
#define TASK4_ROTATE_R_TIME 100
#define TASK4_ULTRA_DISTANCE 10

#endif // !_CONFIG_H_