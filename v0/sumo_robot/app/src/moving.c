#include "moving.h"

// output motor driver A-1A - right - log 1 straight
#define motor_driver_A1A_port GPIOE
#define motor_driver_A1A_pin GPIO_PIN_0

// output motor driver A-1B - right - log 1 back
#define motor_driver_A1B_port GPIOC
#define motor_driver_A1B_pin GPIO_PIN_3

// output motor driver B-1A - left - log 1 straight
#define motor_driver_B1A_port GPIOC
#define motor_driver_B1A_pin GPIO_PIN_2

// output motor driver B-1B - left - log 1 back
#define motor_driver_B1B_port GPIOG
#define motor_driver_B1B_pin GPIO_PIN_0

void motor_pins_init()
{
    // motor driver init ports
    GPIO_Init(motor_driver_A1A_port, motor_driver_A1A_pin, GPIO_MODE_OUT_PP_LOW_SLOW);
    GPIO_Init(motor_driver_A1B_port, motor_driver_A1B_pin, GPIO_MODE_OUT_PP_LOW_SLOW);
    GPIO_Init(motor_driver_B1A_port, motor_driver_B1A_pin, GPIO_MODE_OUT_PP_LOW_SLOW);
    GPIO_Init(motor_driver_B1B_port, motor_driver_B1B_pin, GPIO_MODE_OUT_PP_LOW_SLOW);
}

void stop()
{
    GPIO_WriteLow(motor_driver_A1A_port, motor_driver_A1A_pin);
    GPIO_WriteLow(motor_driver_B1B_port, motor_driver_B1B_pin);
    GPIO_WriteLow(motor_driver_B1A_port, motor_driver_B1A_pin);
    GPIO_WriteLow(motor_driver_A1B_port, motor_driver_A1B_pin);
}

void go_straight(uint32_t time_ms)
{
    GPIO_WriteLow(motor_driver_A1B_port, motor_driver_A1B_pin);
    GPIO_WriteLow(motor_driver_B1B_port, motor_driver_B1B_pin);
        
    GPIO_WriteHigh(motor_driver_A1A_port, motor_driver_A1A_pin);
    GPIO_WriteHigh(motor_driver_B1A_port, motor_driver_B1A_pin);

    delay_ms(time_ms);
    stop();
}

void go_gay(uint32_t time_ms)
{
    GPIO_WriteLow(motor_driver_A1A_port, motor_driver_A1A_pin);
    GPIO_WriteLow(motor_driver_B1A_port, motor_driver_B1A_pin);

    GPIO_WriteHigh(motor_driver_A1B_port, motor_driver_A1B_pin);
    GPIO_WriteHigh(motor_driver_B1B_port, motor_driver_B1B_pin);

    delay_ms(time_ms);
    stop();
}

void rotate_left(uint32_t time_ms)
{
    GPIO_WriteLow(motor_driver_B1A_port, motor_driver_B1A_pin);
    GPIO_WriteLow(motor_driver_A1B_port, motor_driver_A1B_pin);

    GPIO_WriteHigh(motor_driver_A1A_port, motor_driver_A1A_pin);
    GPIO_WriteHigh(motor_driver_B1B_port, motor_driver_B1B_pin);

    delay_ms(time_ms);
    stop();
}

void rotate_right(uint32_t time_ms)
{
    GPIO_WriteLow(motor_driver_A1A_port, motor_driver_A1A_pin);
    GPIO_WriteLow(motor_driver_B1B_port, motor_driver_B1B_pin);

    GPIO_WriteHigh(motor_driver_B1A_port, motor_driver_B1A_pin);
    GPIO_WriteHigh(motor_driver_A1B_port, motor_driver_A1B_pin);

    delay_ms(time_ms);
    stop();
}