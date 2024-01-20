#ifndef _ULTRASONIC_
#define _ULTRASONIC_
#include <common.h>

double detect_obj_distance(uint8_t trigger_pin, uint8_t echo_pin);
bool is_obj_exist(double range);

#endif // !_ULTRASONIC_
