#ifndef MOVING_H
#define MOVING_H

#include "stm8s.h"
#include "delay.h"
void motor_pins_init(void);
void tim2_init(void);
void tim2_PWM_init(void);
void stop(void);
void go_straight(uint16_t speed);
void go_gay(void);
void rotate_right(uint16_t right_speed_speed);
void rotate_left(uint16_t left_speed_speed);
void turning(uint16_t left_wheel_speed, uint16_t right_wheel_speed);
#endif