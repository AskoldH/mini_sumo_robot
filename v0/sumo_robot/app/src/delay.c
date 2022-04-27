#include "delay.h"

void tim4_init(void)
{
    TIM4_TimeBaseInit(TIM4_PRESCALER_64, 249);
    TIM4_Cmd(ENABLE);
}

void tim4_reset(void)
{
    TIM4_SetCounter(0);
}

void delay_ms(uint32_t time_ms)
{
    tim4_reset();
    for(int ms = 0; ms < time_ms; ms++)
    {
        while(TIM4_GetFlagStatus(TIM4_FLAG_UPDATE) != SET);
        TIM4_ClearFlag(TIM4_FLAG_UPDATE);
    }
}