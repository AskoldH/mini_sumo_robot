#include "ultrasonic_sensor.h"


void tim4_init(void)
{
    TIM4_TimeBaseInit(TIM4_PRESCALER_64, 249);
    TIM4_Cmd(ENABLE);
}

void tim3_init(void)
{
    TIM3_TimeBaseInit(TIM2_PRESCALER_4, 39999);
    TIM3_Cmd(ENABLE);
}

void delay_ms(uint32_t time_ms)
{
    
    TIM4_SetCounter(0);
    for(int ms = 0; ms < time_ms; ms++)
    {
        while(TIM4_GetFlagStatus(TIM4_FLAG_UPDATE) != SET);
        TIM4_ClearFlag(TIM4_FLAG_UPDATE);
    }
}

void tim4_reset(void)
{
    TIM4_SetCounter(0);
}

void tim3_reset(void)
{
    TIM3_SetCounter(0);
}

float tim3_get_distance(uint8_t tim3_value)
{
    uint16_t time_in_us = tim3_value/10000;
    return ((time_in_us*0.034)/2);
}