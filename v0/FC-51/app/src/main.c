#include "stm8s.h"

uint8_t fc51_right(void){
    return (!(GPIO_ReadInputPin(GPIOD, GPIO_PIN_3)));
}

void main(void)
{
    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1); // FREQ MCU 16MHz
    GPIO_Init(GPIOC, GPIO_PIN_5, GPIO_MODE_OUT_PP_LOW_SLOW);
    GPIO_Init(GPIOD, GPIO_PIN_3, GPIO_MODE_IN_FL_NO_IT);

    while (1)
    {
        if (fc51_right())
        {
            GPIO_WriteHigh(GPIOC, GPIO_PIN_5);
            continue;
        }
        GPIO_WriteLow(GPIOC, GPIO_PIN_5);
    }
}
