#ifndef _MOTOR_UTILS_
#define _MOTOR_UTILS_

void motor_run(int lspeed, int rspeed);
void Emerge_Stop();
void Forward();
void Forward_By_Time(int forward_time);
void Backward();
void Backward_By_Time(int backward_time);
void TurnL();
void TurnR();
void RotateL();
void RotateR();
void turn_Left_to_Line();
void turn_Right_to_Line();
void turn_Back_to_Line();

#endif // !_MOTOR_UTILS_
