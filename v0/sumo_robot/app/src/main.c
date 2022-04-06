#include "stm8s.h"
#include "uart.h"
#include "ultrasonic_sensor.h"
#include <stdio.h>
#include <stdlib.h>

uint8_t tim3_value;
float distance;
int rise_fall = 1;

INTERRUPT_HANDLER(EXTI_PORTD_IRQHandler, 6)
{
    if (rise_fall)
    {
        tim3_reset();
        rise_fall = 0;
    }
    else{
        tim3_value = TIM4_GetCounter();
        rise_fall = 1;
    }
    
}



uint8_t button_is_pressed(void){
    return (!(GPIO_ReadInputPin(GPIOE, GPIO_PIN_4)));
}


void main(void)
{
    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1); // FREQ MCU 16MHz
    GPIO_Init(GPIOC, GPIO_PIN_5, GPIO_MODE_OUT_PP_LOW_SLOW);
    GPIO_Init(GPIOC, GPIO_PIN_4, GPIO_MODE_OUT_PP_LOW_SLOW); // trig
    GPIO_Init(GPIOD, GPIO_PIN_3, GPIO_MODE_IN_FL_IT); // echo
    //GPIO_ExternalPullUpConfig(GPIOD, GPIO_PIN_3, ENABLE);

    EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOD, EXTI_SENSITIVITY_RISE_FALL);
    ITC_SetSoftwarePriority(ITC_IRQ_PORTE, ITC_PRIORITYLEVEL_0);
    enableInterrupts();

    uart1_init();
    tim4_init();
    tim3_init();

    while (1)
    {

        distance = tim3_get_distance(tim3_value);

        /*if (tim3_value < 1)
        {
            send_str("<3\n\r");
        }
        else if (tim3_value < 10)
        {
            send_str("<5\n\r");
        }
        else if (tim4_value < 20)
        {
            send_str("<7\n\r");
        }
        else if (tim4_value < 30)
        {
            send_str("<9\n\r");
        }
        else if (tim4_value < 11)
        {
            send_str("<11\n\r");
        }
        else if (tim4_value < 13)
        {
            send_str("<13\n\r");
        }
        else if (tim4_value < 15)
        {
            send_str("<15\n\r");
        }
        else if (tim4_value < 17)
        {
            send_str("<17\n\r");
        }
        else if (tim4_value < 19)
        {
            send_str("<19\n\r");
        }
        else if (tim4_value < 21)
        {
            send_str("<21\n\r");
        }
        else if (tim4_value > 21)
        {
            send_str("over 21\n\r");
        }*/

        if (distance < 3)
        {
            send_str("<3\n\r");
        }
        else if (distance < 5)
        {
            send_str("<5\n\r");
        }
        else if (distance < 7)
        {
            send_str("<7\n\r");
        }
        else if (distance < 9)
        {
            send_str("<9\n\r");
        }
        else if (distance < 11)
        {
            send_str("<11\n\r");
        }
        else if (distance < 13)
        {
            send_str("<13\n\r");
        }
        else if (distance < 15)
        {
            send_str("<15\n\r");
        }
        else if (distance < 17)
        {
            send_str("<17\n\r");
        }
        else if (distance < 19)
        {
            send_str("<19\n\r");
        }
        else if (distance < 21)
        {
            send_str("<21\n\r");
        }
        else if (distance > 21)
        {
            send_str("over 21\n\r");
        }

        GPIO_WriteLow(GPIOC, GPIO_PIN_4);
        delay_ms(1);
        GPIO_WriteHigh(GPIOC, GPIO_PIN_4);
        delay_ms(100);
        //send_str("CYKLUS\n\r");
        //GPIO_WriteLow(GPIOC, GPIO_PIN_4);*/
    }
}