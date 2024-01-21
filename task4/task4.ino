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
#define BLACK_FENCE 65

#define SPEED 100       // 总体速度
const int DELTA = 0.05; // 左轮减速调直

#define ULTRASONIC_DISTANCE 50
#define MAX_DISTANCE 200 // 最大超声波距离

#define MICRO_DELAY_TIME 1

#define ROTATE_TIME 200
#define TURN_LEFT_TIME 200
#define TURN_RIGHT_TIME 200

// Motor A connections
int enA = 9;
int in1 = 8;
int in2 = 7;
// Motor B connections
int enB = 3;
int in3 = 5;
int in4 = 4;

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

void setup()
{
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