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

status_t status;

void task1()
{
    track_line();
}

void task2()
{
    track_line();
}

void task3()
{
    auto ml = qtr_read_analog(QTR_SENSOR_ML);
    auto mr = qtr_read_analog(QTR_SENSOR_MR);
    if (ml > 100 && mr > 100 && !status.op_stack.empty())
    {
        Emerge_Stop();
    }
    else
    {

        bool is_exist = is_obj_exist(10);
        if (is_exist)
        {
            Emerge_Stop();

            command_t cmd;
            cmd.code = OP_TURNING_POINT;
            status.op_stack.push(cmd);

            if (status.direction_checksum < 1)
            {
                command_t cmd;
                cmd.code = OP_TURN_RIGHT;
                cmd.arg1 = SPEED;
                cmd.arg2 = -SPEED;
                cmd.arg3 = 100;
                status.op_stack.push(cmd);

                cmd.code = OP_TURN_LEFT;
                cmd.arg1 = SPEED;
                cmd.arg2 = -SPEED;
                cmd.arg3 = 100;
                status.op_stack.push(cmd);

                status.direction_checksum += OP_TURN_LEFT;

                motor_run(SPEED, -SPEED);
                delay(100);
            }
            else if (status.direction_checksum > -1)
            {
                command_t cmd;
                cmd.code = OP_TURN_LEFT;
                cmd.arg1 = -SPEED;
                cmd.arg2 = SPEED;
                cmd.arg3 = 100;
                status.op_stack.push(cmd);

                cmd.code = OP_TURN_RIGHT;
                cmd.arg1 = -SPEED;
                cmd.arg2 = SPEED;
                cmd.arg3 = 100;
                status.op_stack.push(cmd);

                status.direction_checksum += OP_TURN_RIGHT;

                motor_run(-SPEED, SPEED);
                delay(100);
            }
        }
        else
        {
            if (numML >= black_fence && numMR >= black_fence)
            {
                if (status.direction_checksum < 1)
                {
                    command_t cmd;
                    cmd.code = OP_TURN_LEFT;
                    cmd.arg1 = SPEED;
                    cmd.arg2 = -SPEED;
                    cmd.arg3 = 100;
                    status.op_stack.push(cmd);

                    status.direction_checksum += OP_TURN_LEFT;

                    motor_run(SPEED, -SPEED);
                    delay(100);
                }
                else if (status.direction_checksum > -1)
                {
                    command_t cmd;
                    cmd.code = OP_TURN_RIGHT;
                    cmd.arg1 = -SPEED;
                    cmd.arg2 = SPEED;
                    cmd.arg3 = 100;
                    status.op_stack.push(cmd);

                    status.direction_checksum += OP_TURN_RIGHT;

                    motor_run(-SPEED, SPEED);
                    delay(100);
                }
            }
            else
            {
                command_t cmd = status.op_stack.top();

                if (cmd.code == OP_GO_STRAIGHT && cmd.arg3 > 1000 || status.current_cmd == STG_REVERT_DOING)
                {
                    status.current_cmd = STG_REVERT_DOING;

                    if (cmd.code == OP_TURN_LEFT)
                    {
                        motor_run(cmd.arg1, -cmd.arg2);
                        delay(cmd.arg3);
                        status.direction_checksum += OP_TURN_LEFT;
                    }
                    else if (cmd.code == OP_TURN_RIGHT)
                    {
                        motor_run(-cmd.arg1, cmd.arg2);
                        delay(cmd.arg3);
                        status.direction_checksum += OP_TURN_RIGHT;
                    }
                    else if (cmd.code == OP_GO_STRAIGHT)
                    {
                        motor_run(-cmd.arg1, -cmd.arg2);
                        delay(cmd.arg3);
                    }

                    status.op_stack.pop();

                    if (cmd.code == OP_TURNING_POINT)
                    {
                        status.op_stack.pop();
                        cmd.code = OP_DEAD_POINT;
                        status.op_stack.push(cmd);

                        status.current_cmd = STG_REVERT_DONE;
                    }
                }
                else
                {
                    if (cmd.code == OP_GO_STRAIGHT)
                    {
                        cmd.arg3 += 100;
                        status.op_stack.pop();
                    }
                    else
                    {
                        cmd.code = OP_GO_STRAIGHT;
                        cmd.arg1 = SPEED;
                        cmd.arg2 = SPEED;
                        cmd.arg3 = 100;
                    }
                    status.op_stack.push(cmd);

                    motor_run(SPEED, SPEED);
                    delay(100);
                }
            }
        }
        // delay(300);
    }
}

//every 20cm, search for the branch, record to the stack
void task4()
{
}
