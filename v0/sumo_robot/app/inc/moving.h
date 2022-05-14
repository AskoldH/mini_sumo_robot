#ifndef MOVING_H
#define MOVING_H

#include "stm8s.h"
#include "delay.h"
void motor_pins_init(void);
void stop(void);
void go_straight(uint32_t time_ms);
void go_gay(uint32_t time_ms);
void rotate_right(uint32_t time_ms);
void rotate_left(uint32_t time_ms);
#endif