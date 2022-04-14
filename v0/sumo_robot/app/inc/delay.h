#ifndef DELAY_H
#define DELAY_H

#include "stm8s.h"
void tim4_init(void);
void tim4_reset(void);
void delay_ms(uint32_t time_ms);
#endif