#include <Arduino.h>
#include <Servo.h>

#define LEFT_SPEED 9           // Motor A enable pin
#define RIGHT_SPEED 3          // Motor B enable pin
#define RIGHT_WHEEL_FORWARD 4  // Motor B In1 pin
#define RIGHT_WHEEL_BACKWARD 5 // Motor B In2 pin
#define LEFT_WHEEL_FORWARD 8   // Motor A In1 pin
#define LEFT_WHEEL_BACKWARD 7  // Motor A In2 pin

#define TRIGGER_PIN 5 // Ultrasonic sensor trigger pin
#define ECHO_PIN 12   // Ultrasonic sensor echo pin

#define QTR_SENSOR_L A1  // QTR sensor
#define QTR_SENSOR_R A2  // QTR sensor
#define QTR_SENSOR_ML A3 // QTR sensor
#define QTR_SENSOR_MR A4 // QTR sensor
#define QTR_SENSOR_MF ?? // QTR sensor
#define BLACK_FENCE 65

#define SPEED 100   // 总体速度
#define DELTA 0.05; // 左轮减速调直

#define ULTRASONIC_DISTANCE 50
#define MAX_DISTANCE 200 // 最大超声波距离

#define MICRO_DELAY_TIME 1

#define FORWARD_TIME 200
#define ROTATE_TIME 200
#define TURN_LEFT_TIME 200
#define TURN_RIGHT_TIME 200

#define First_forward_time 200 //转弯前前进时间
#define First_turn_time 200 //转弯时第一次盲转的时间
#define AVOID_OBJ_TURN_TIME 10

#define black_fence 65
#define Micro_Delay_Time 1 



// Motor A connections
int enA = 9;
int in1 = 8;
int in2 = 7;
// Motor B connections
int enB = 3;
int in3 = 5;
int in4 = 4;

int numL = 0;
int numML = 0;
int numMF = 0;
int numMR = 0;
int numR = 0;

///////MOTOR////////
void motor_run(int lspeed, int rspeed)
{
    int motor_delta = SPEED * DELTA;
    int abslspeed = abs(lspeed);
    int absrspeed = abs(rspeed);
    analogWrite(enA, abslspeed);
    analogWrite(enB, absrspeed);
    if (lspeed > 0)
    {
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
    }
    else if (lspeed == 0)
    {
        digitalWrite(in1, LOW);
        digitalWrite(in2, LOW);
    }
    else
    {
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
    }

    if (rspeed > 0)
    {
        digitalWrite(in3, HIGH);
        digitalWrite(in4, LOW);
    }
    else if (rspeed == 0)
    {
        digitalWrite(in3, LOW);
        digitalWrite(in4, LOW);
    }
    else
    {
        digitalWrite(in3, LOW);
        digitalWrite(in4, HIGH);
    }
}

void Emerge_Stop()
{
    motor_run(0, 0);
}

void Forward()
{
    motor_run(SPEED, SPEED);
}

void Forward_By_Time(int forward_time)
{
    Forward();
    delay(forward_time);
    Emerge_Stop();
}

void Backward()
{
    motor_run(-SPEED, -SPEED);
}

void Backward_By_Time(int backward_time)
{
    Backward();
    delay(backward_time);
    Emerge_Stop();
}

void TurnL()
{
    motor_run(0, SPEED);
}

void TurnL_time(int ms)
{
    motor_run(0, SPEED);
    delay(ms);
}

void TurnR()
{
    motor_run(SPEED, 0);
}

void TurnR_time(int ms)
{
    motor_run(SPEED, 0);
    delay(ms);
}

void RotateL()
{
    motor_run(-SPEED, SPEED);
}

void RotateR()
{
    motor_run(SPEED, -SPEED);
}

void RotateL_time(int ms)
{
    motor_run(-SPEED, SPEED);
    delay(ms);
}

void RotateR_time(int ms)
{
    motor_run(SPEED, -SPEED);
    delay(ms);
}
//////////////////////////////////

////Ultrasonic//////////////////////////
double detect_obj_distance(uint8_t trigger_pin, uint8_t echo_pin)
{
    digitalWrite(trigger_pin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigger_pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigger_pin, LOW);
    return pulseIn(echo_pin, HIGH, MAX_DISTANCE * 58) / 58.0;
}

double detect_distance()
{
    return detect_obj_distance(TRIGGER_PIN, ECHO_PIN);
}

bool is_obj_exist(double range)
{
    double distance = detect_obj_distance(TRIGGER_PIN, ECHO_PIN);
    if (distance == 0.00)
    {
        return false;
    }
    else if (distance < range && distance > 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool is_obj_in_distance(double distance, double range)
{
    if (distance == 0.00)
    {
        return false;
    }
    else if (distance < range && distance > 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
///////////////////////////////////

/// Servo ///////////////////
enum Direction
{
    LEFT,
    FRONT,
    RIGHT,
};
Servo servo1;               // 舵机信号接口在setup里面
const int SERVO1_INIT = 90; // 舵机初始状态
const int DEGREE_LZ[] = {15, 90, 165};
int distance[] = {0, 0, 0};

void init_servo()
{
    servo1.write(SERVO1_INIT);
}

void scan_front()
{
    servo1.write(DEGREE_LZ[1]);
    delay(30);
    distance[1] = detect_obj_distance(TRIGGER_PIN, ECHO_PIN);
    Serial.print(DEGREE_LZ[1]);
    Serial.print(",");
    Serial.print(distance[1]);
    Serial.print(".");
}

void scan_left_right()
{
    servo1.write(DEGREE_LZ[0]);
    delay(30);
    distance[1] = detect_obj_distance(TRIGGER_PIN, ECHO_PIN);
    Serial.print(DEGREE_LZ[0]);
    Serial.print(",");
    Serial.print(distance[0]);
    Serial.print(".");

    servo1.write(DEGREE_LZ[2]);
    delay(30);
    distance[1] = detect_obj_distance(TRIGGER_PIN, ECHO_PIN);
    Serial.print(DEGREE_LZ[2]);
    Serial.print(",");
    Serial.print(distance[2]);
    Serial.print(".");
}

void scan_for_obj()
{
    for (int idx = 0; idx < sizeof(DEGREE_LZ); idx++)
    {
        servo1.write(DEGREE_LZ[idx]);
        delay(30);
        distance[idx] = detect_obj_distance(TRIGGER_PIN, ECHO_PIN);
        Serial.print(DEGREE_LZ[idx]);
        Serial.print(",");
        Serial.print(distance[idx]);
        Serial.print(".");
    }
    for (int idx = sizeof(DEGREE_LZ) - 1; idx >= 0; idx--)
    {
        servo1.write(DEGREE_LZ[idx]);
        delay(30);
        distance[idx] = detect_obj_distance(TRIGGER_PIN, ECHO_PIN);
        Serial.print(DEGREE_LZ[idx]);
        Serial.print(",");
        Serial.print(distance[idx]);
        Serial.print(".");
    }
}
/////////////////////////////////////////////

////////////Task 3//////////////////////////////
void read_data()
{
    numL = analogRead(QTR_SENSOR_L);
    numML = analogRead(QTR_SENSOR_ML);
    numMF = analogRead(QTR_SENSOR_MF);
    numMR = analogRead(QTR_SENSOR_MR);
    numR = analogRead(QTR_SENSOR_R);
}

void turn_Left_to_Line()
{
    Forward_By_Time(First_forward_time);
    while (numMR < black_fence)
    {
        read_data();
        TurnL();
        delay(Micro_Delay_Time);
    }
}
void turn_Right_to_Line()
{
    Forward_By_Time(First_forward_time);
    while (numML < black_fence)
    {
        read_data();
        TurnR();
        delay(Micro_Delay_Time);
    }
}
void turn_Back_to_Line()
{
    RotateL();
    delay(First_turn_time);
    while (numMR < black_fence)
    {
        read_data();
        RotateL();
        delay(Micro_Delay_Time);
    }
}

void Go_by_Ultrasonic()
{
    scan_for_obj();
    bool is_exist = is_obj_in_distance(distance[1], ULTRASONIC_DISTANCE);
    bool is_exist_left = is_obj_in_distance(distance[0], ULTRASONIC_DISTANCE);
    bool is_exist_right = is_obj_in_distance(distance[2], ULTRASONIC_DISTANCE);

    if (is_exist_left)
    {
        motor_run(SPEED, -SPEED);
    }
    else if (is_exist_right)
    {
        motor_run(-SPEED, SPEED);
    }
    else
    {
        motor_run(SPEED, SPEED);
    }
    delay(100);
}

void line_in_task3(){
    read_data(); // 读取传感器值
    if (numL >= black_fence && numR >= black_fence)
    {
        turn_Right_to_Line();
    }
    else if (numL >= black_fence && numR < black_fence)
    {
        turn_Left_to_Line();
    }
    else if (numL < black_fence && numR >= black_fence)
    {
        turn_Right_to_Line();
    }
    else
    {
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
        else if (numML >= black_fence && numMR >= black_fence && numMF >= black_fence)
        {
            Forward();
        }

        else
        {
            Go_by_Ultrasonic();
        }
    }
}

void move_to_line(){
    while(numML < black_fence && numMR < black_fence){
        motor_run(SPEED, SPEED);
        read_data();
    }
}

void avoid_obj(){
    RotateR();
    delay(AVOID_OBJ_TURN_TIME);
    move_to_line();
    while(numML >= black_fence || numMR >= black_fence){
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
    }
    RotateL();
    delay(AVOID_OBJ_TURN_TIME);
    move_to_line();
    
}

void task3()
{
    scan_front();
    bool is_exist = is_obj_in_distance(distance[1], ULTRASONIC_DISTANCE);

    if(is_exist){
        avoid_obj();
    } else {
        motor_run(SPEED, SPEED);
    }
}
/////////////////////////////////////////////


void setup()
{
    // Set all the motor control pins to outputs
    pinMode(enA, OUTPUT);
    pinMode(enB, OUTPUT);
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(in3, OUTPUT);
    pinMode(in4, OUTPUT);

    pinMode(QTR_SENSOR_ML, INPUT);
    pinMode(QTR_SENSOR_MR, INPUT);
    pinMode(QTR_SENSOR_L, INPUT);
    pinMode(QTR_SENSOR_R, INPUT);

    pinMode(TRIGGER_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);

    // Turn off motors - Initial state
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
}

void loop()
{
    init_servo();
    if (!is_obj_exist(ULTRASONIC_DISTANCE))
    {
        Forward();
    }
    else
    {
        scan_left_right();
        if (is_obj_in_distance(distance[LEFT], ULTRASONIC_DISTANCE) && is_obj_in_distance(distance[LEFT], ULTRASONIC_DISTANCE))
        {
            // 死胡同
            RotateL_time(ROTATE_TIME);
        }
        else if (distance[LEFT] > distance[RIGHT])
        {
            TurnL_time(TURN_LEFT_TIME);
        }
        else if (distance[LEFT] < distance[RIGHT])
        {
            TurnR_time(TURN_RIGHT_TIME);
        }
    }
}