#ifndef INT_ULTRASONIC_SENSOR_H
#define INT_ULTRASONIC_SENSOR_H

#include "stm8s.h"
#include "uart.h"
#include "int_to_str.h"
void tim3_init(void);
void tim3_reset(void);
int tim3_get_distance(uint16_t tim3_value);
void send_distance_via_uart(uint16_t tim3_value);
#endif