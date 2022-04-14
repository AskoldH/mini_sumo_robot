#ifndef INT_ULTRASONIC_SENSOR_H
#define INT_ULTRASONIC_SENSOR_H

#include "stm8s.h"
void tim3_init(void);
void tim3_reset(void);
float tim3_get_distance(uint16_t tim3_value);
#endif