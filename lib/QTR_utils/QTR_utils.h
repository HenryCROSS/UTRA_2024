#ifndef _QTR_UTILS_
#define _QTR_UTILS_

#include <Arduino.h>

enum qtr_case_t {
    XOOX,
    XXOX,
    XOXO
};

int qtr_read_analog(uint8_t pin);
int qtr_read_digital(uint8_t pin);

#endif // !_QTR_UTILS_