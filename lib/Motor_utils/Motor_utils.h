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
void RotateL_time(int ms);
void RotateR_time(int ms);


#endif // !_MOTOR_UTILS_
