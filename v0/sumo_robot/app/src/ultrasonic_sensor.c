#include "ultrasonic_sensor.h"

void tim3_init(void)
{
    TIM3_TimeBaseInit(TIM3_PRESCALER_4, 39999);
    TIM3_Cmd(ENABLE);
}

void tim3_reset(void)
{
    TIM3_SetCounter(0);
}

float tim3_get_distance(uint16_t tim3_value)
{
    uint16_t time_in_us = tim3_value/4; // devided timer value to get time in microseconds

    /* calculating distance in cm (0.034 -> speed of sound in the air - cm/us,
    devided by 2 cos we measured time to the object and back) */
    return ((time_in_us*0.034)/2);  
}