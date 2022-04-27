#include "stm8s.h"
#include "uart.h"
#include "ultrasonic_sensor.h"
#include "int_to_str.h"
#include "delay.h"
#include "moving.h"

// triger for ultrasonic sensor
#define trig_port GPIOC
#define trig_pin GPIO_PIN_4

// echo for ultrasonic sensor
#define echo_port GPIOD
#define echo_pin GPIO_PIN_3

// on board led for testing 
#define on_board_led_port GPIOC
#define on_board_led_pin GPIO_PIN_5

// output from infrared sensor on the right
#define ir_sensor_right_port GPIOE
#define ir_sensor_right_pin GPIO_PIN_5

// output from infrared sensor on the right
#define ir_sensor_left_port GPIOC
#define ir_sensor_left_pin GPIO_PIN_6


// declere needed global variables
int rise_fall = 1; 


// interrupt handler for ultrasonic sensor 
INTERRUPT_HANDLER(EXTI_PORTD_IRQHandler, 6)
{
    // if interrupt caused by rise edge -> reset timer 3 and set that next interrupt had to be fall edge
    if (rise_fall)
    {
        tim3_reset();
        rise_fall = 0;
    }
    // else if interrupt caused by fall edge -> write timer 3 counter value into variable and set that next interrupt had to be rise edge
    else if(!(rise_fall))
    {
        if (TIM3_GetFlagStatus(TIM3_FLAG_UPDATE) != SET)
        {
            send_distance_via_uart(TIM3_GetCounter());
        }
        else if (TIM3_GetFlagStatus(TIM3_FLAG_UPDATE) == SET)
        {
            send_str("Čítač přetekl!");
        }
        rise_fall = 1;
    }
}


// interrupt handler for right infrared sensor
INTERRUPT_HANDLER(EXTI_PORTE_IRQHandler, 7)
{
    send_str("Right infrared sensor is on black (logical 0)\n\r");
}

// interrupt handler for left infrared sensor
INTERRUPT_HANDLER(EXTI_PORTC_IRQHandler, 5)
{
    send_str("Left infrared sensor is on black (logical 0)\n\r");
}

void main(void)
{
    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1); // FREQ MCU 16MHz
    GPIO_Init(on_board_led_port, on_board_led_pin, GPIO_MODE_OUT_PP_LOW_SLOW); // init on board led

    // ultrasonic sensor init ports
    GPIO_Init(trig_port, trig_pin, GPIO_MODE_OUT_PP_LOW_SLOW); // trig
    GPIO_Init(echo_port, echo_pin, GPIO_MODE_IN_FL_IT); // echo

    // infrared sensor init ports
    GPIO_Init(ir_sensor_left_port, ir_sensor_left_pin, GPIO_MODE_IN_FL_IT);
    GPIO_Init(ir_sensor_right_port, ir_sensor_right_pin, GPIO_MODE_IN_FL_IT);

    // infrared sensors interrupts
    EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOE, EXTI_SENSITIVITY_RISE_ONLY); // interrupts settup for port E - right ir sensor
    EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOC, EXTI_SENSITIVITY_RISE_ONLY); // interrupts settup for port C - left ir sensor
    ITC_SetSoftwarePriority(ITC_IRQ_PORTE, ITC_PRIORITYLEVEL_0); //interrupts priorities for port E
    ITC_SetSoftwarePriority(ITC_IRQ_PORTC, ITC_PRIORITYLEVEL_0); //interrupts priorities for port C

    // ultrasonic sensor interrupts 
    EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOD, EXTI_SENSITIVITY_RISE_FALL); // interrupts settup for port D
    ITC_SetSoftwarePriority(ITC_IRQ_PORTD, ITC_PRIORITYLEVEL_0);

    enableInterrupts();
    
    uart1_init();
    tim4_init();
    tim3_init();
    motor_pins_init();

    while(1)
    {
        delay_ms(100);
        GPIO_WriteHigh(trig_port, trig_pin);
        GPIO_WriteHigh(on_board_led_port, on_board_led_pin);
        delay_ms(100);
        GPIO_WriteLow(trig_port, trig_pin);
        GPIO_WriteLow(on_board_led_port, on_board_led_pin);
    }
}