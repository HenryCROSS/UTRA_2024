// official
#include <Arduino.h>

// third party

// ours
#include <Main_Task.h>
#include <Motor_utils.h>
#include <QTR_utils.h>
#include <Ultrasonic.h>
#include <config.h>
#include <data_type.h>
#include <track_line.h>

void task3()
{
}

void move_to_line(){
    while(numML < black_fence && numMR < black_fence){
        motor_run(SPEED, SPEED);
        read_data();
    }
}