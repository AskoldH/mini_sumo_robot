#include "ultrasonic_sensor.h"

void tim3_init(void)
{
    TIM3_TimeBaseInit(TIM3_PRESCALER_4, 39999);
    TIM3_Cmd(ENABLE);
}

void tim3_reset(void)
{
    TIM3_ClearFlag(TIM3_FLAG_UPDATE);
    TIM3_SetCounter(0);
}

float tim3_get_distance(uint16_t tim3_value)
{
    uint16_t time_in_us = tim3_value/4; // devided timer value to get time in microseconds

    /* calculating distance in cm (0.034 -> speed of sound in the air - cm/us,
    devided by 2 cos we measured time to the object and back) */
    return ((time_in_us*0.034)/2);  
}

void send_distance_via_uart(uint16_t tim3_value)
{   
    float distance = tim3_get_distance(tim3_value);
    uint16_t distance_to_sent = distance;
    send_str(int_to_str(distance_to_sent)); 
    send_str("\n\r");
}