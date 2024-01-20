#ifndef _ORIENTATION_SENSOR_
#define _ORIENTATION_SENSOR_
#include <common.h>
/* Set the delay between fresh samples */
uint16_t BNO055_SAMPLERATE_DELAY_MS = 100;

// Check I2C device address and correct line below (by default address is 0x29 or 0x28)
//                                   id, address
Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28, &Wire);

void get_all_data();
void printEvent(sensors_event_t* event);

#endif // !_ORIENTATION_SENSOR_