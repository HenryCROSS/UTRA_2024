#define LEFT_SPEED 9            // Motor A enable pin
#define RIGHT_SPEED 3           // Motor B enable pin
#define RIGHT_WHEEL_FORWARD 4   // Motor B In1 pin
#define RIGHT_WHEEL_BACKWARD 5  // Motor B In2 pin
#define LEFT_WHEEL_FORWARD 8    // Motor A In1 pin
#define LEFT_WHEEL_BACKWARD 7   // Motor A In2 pin


#define TRIGGER_PIN 5  // Ultrasonic sensor trigger pin
#define ECHO_PIN 12    // Ultrasonic sensor echo pin

#define SPEED 100        //总体速度
const int delta = 0.05;  //左轮减速调直


#define First_forward_time 200  //转弯前前进时间
#define First_turn_time 200     //转弯时第一次盲转的时间

#define QTR_SENSOR_L A1   // QTR sensor
#define QTR_SENSOR_R A2   // QTR sensor
#define QTR_SENSOR_ML A3  // QTR sensor
#define QTR_SENSOR_MR A4  // QTR sensor
#define black_fence 65

#define Ultrasonic_Distance 50
#define MAX_DISTANCE 200  // 最大超声波距离
double distance[3];

#define Micro_Delay_Time 1

#define key 3  //start button

int numL;
int numML;
int numMR;
int numR;

Servo servo1;                //舵机信号接口在setup里面
const int servo1_init = 90;  //舵机初始状态

#define TASK4_ROTATE_L_TIME 100
#define TASK4_ROTATE_R_TIME 100
#define TASK4_ULTRA_DISTANCE 10

// Motor A connections
int enA = 9;
int in1 = 8;
int in2 = 7;
// Motor B connections
int enB = 3;
int in3 = 5;
int in4 = 4;

void motor_run(int lspeed, int rspeed) {
  int motor_delta = SPEED * delta;
  int abslspeed = abs(lspeed);
  int absrspeed = abs(rspeed);
  analogWrite(enA, abslspeed);
  //   analogWrite(LEFT_SPEED,abslspeed-motor_delta);
  analogWrite(enB, absrspeed);
  if (lspeed > 0) {
    // digitalWrite(LEFT_WHEEL_FORWARD,HIGH);
    // digitalWrite(LEFT_WHEEL_BACKWARD,LOW);
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
  } else if (lspeed == 0) {
    // digitalWrite(LEFT_WHEEL_FORWARD,HIGH);
    // digitalWrite(LEFT_WHEEL_BACKWARD,HIGH);
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
  } else {
    // digitalWrite(LEFT_WHEEL_FORWARD,LOW);
    // digitalWrite(LEFT_WHEEL_BACKWARD,HIGH);
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
  }

  if (rspeed > 0) {
    // digitalWrite(RIGHT_WHEEL_FORWARD,HIGH);
    // digitalWrite(RIGHT_WHEEL_BACKWARD,LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  } else if (rspeed == 0) {
    // digitalWrite(RIGHT_WHEEL_FORWARD,HIGH);
    // digitalWrite(RIGHT_WHEEL_BACKWARD,HIGH);

    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
  } else {
    // digitalWrite(RIGHT_WHEEL_FORWARD,LOW);
    // digitalWrite(RIGHT_WHEEL_BACKWARD,HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
  }
}

void Emerge_Stop() {
  // motor_run(-255,-255);
  // delay(10);
  motor_run(0, 0);
}

void Forward() {
  motor_run(SPEED, SPEED);
}

void Forward_By_Time(int forward_time) {
  Forward();
  delay(forward_time);
  Emerge_Stop();
}

void Backward() {
  motor_run(-SPEED, -SPEED);
}

void Backward_By_Time(int backward_time) {
  Backward();
  delay(backward_time);
  Emerge_Stop();
}

void TurnL() {
  motor_run(0, SPEED);
}

void TurnR() {
  motor_run(SPEED, 0);
}

void RotateL() {
  motor_run(-SPEED, SPEED);
}

void RotateR() {
  motor_run(SPEED, -SPEED);
}

void RotateL_time(int ms) {
  motor_run(-SPEED, SPEED);
  delay(ms);
}

void RotateR_time(int ms) {
  motor_run(SPEED, -SPEED);
  delay(ms);
}

void setup() {
  // Set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  // Turn off motors - Initial state
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void loop() {
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// This function lets you control spinning direction of motors
void directionControl() {
  // Set motors to maximum speed
  // For PWM maximum possible values are 0 to 255
  analogWrite(enA, 255);
  analogWrite(enB, 255);

  // Turn on motor A & B
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  delay(2000);

  // Now change motor directions
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  delay(2000);

  // Turn off motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
