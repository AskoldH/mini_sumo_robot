#ifndef INT_ULTRASONIC_SENSOR_H
#define INT_ULTRASONIC_SENSOR_H

#include "stm8s.h"
void tim4_init(void);
void tim3_init(void);
void delay_ms(uint32_t time_ms);
void tim4_reset(void);
void tim3_reset(void);
float tim3_get_distance(uint8_t tim4_value);

#endif