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
#include <Servo_control.h>

void task4()
{
    scan_for_obj();
    if(!is_obj_exist(distance[0], 10)){
        // Left
        RotateL();
    } else if(!is_obj_exist(distance[1], 10)) {
        // Front
        Forward();
    } else if(!is_obj_exist(distance[2], 10)){
        // Right
        RotateR();
    } else {
        // dead road
    }
}