#include <QTR_utils.h>

int qtr_read_analog(uint8_t pin){
    return analogRead(pin);
}

int qtr_read_digital(uint8_t pin){
    return digitalRead(pin);
}