// official
#include <Arduino.h>

// third party

// ours
#include <Main_Task.h>
#include <Motor_utils.h>
#include <QTR_utils.h>
#include <Servo_control.h>
#include <Ultrasonic.h>
#include <config.h>
#include <data_type.h>
#include <track_line.h>

void task4()
{
    scan_front();
    if (!is_obj_exist(distance[1], TASK4_ULTRA_DISTANCE))
    {
        Forward();
    }
    else
    {
        scan_for_obj();
        if (!is_obj_exist(distance[0], TASK4_ULTRA_DISTANCE))
        {
            // Left
            RotateL_time(TASK4_ROTATE_L_TIME);
        }
        else if (!is_obj_exist(distance[1], TASK4_ULTRA_DISTANCE))
        {
            // Front
            Forward();
        }
        else if (!is_obj_exist(distance[2], TASK4_ULTRA_DISTANCE))
        {
            // Right
            RotateR_time(TASK4_ROTATE_R_TIME);
        }
        else
        {
            // dead road
            RotateR_time(TASK4_ROTATE_R_TIME);
        }
    }
}