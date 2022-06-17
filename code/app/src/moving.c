#include "moving.h"

// output motor driver A-1A - right - log 1 straight
#define motor_driver_A1A_port GPIOD
#define motor_driver_A1A_pin GPIO_PIN_4

// output motor driver A-1B - right - log 1 back
#define motor_driver_A1B_port GPIOC
#define motor_driver_A1B_pin GPIO_PIN_3

// output motor driver B-1A - left - log 1 straight
#define motor_driver_B1A_port GPIOD
#define motor_driver_B1A_pin GPIO_PIN_3

// output motor driver B-1B - left - log 1 back
#define motor_driver_B1B_port GPIOG
#define motor_driver_B1B_pin GPIO_PIN_0

void motor_pins_init() {
    // motor driver init ports
    GPIO_Init(motor_driver_A1B_port, motor_driver_A1B_pin, GPIO_MODE_OUT_PP_LOW_SLOW);
    GPIO_Init(motor_driver_B1B_port, motor_driver_B1B_pin, GPIO_MODE_OUT_PP_LOW_SLOW);
}

void tim2_init() {
    TIM2_TimeBaseInit(TIM2_PRESCALER_8, 3999);
    TIM2_Cmd(ENABLE);
}

void tim2_PWM_init() {
    // pin PD4
    TIM2_OC1Init(
            TIM2_OCMODE_PWM1,
            TIM2_OUTPUTSTATE_ENABLE,
            20000,
            TIM2_OCPOLARITY_HIGH
    );
    // pin PD3
    TIM2_OC2Init(
            TIM2_OCMODE_PWM1,
            TIM2_OUTPUTSTATE_ENABLE,
            20000,
            TIM2_OCPOLARITY_HIGH
    );

    TIM2_OC1PreloadConfig(ENABLE); // right wheel
    TIM2_OC2PreloadConfig(ENABLE); // left wheel
}

void stop() {                                                   // stop motors
    TIM2_SetCompare1(0);
    GPIO_WriteLow(motor_driver_B1B_port, motor_driver_B1B_pin);
    TIM2_SetCompare2(0);
    GPIO_WriteLow(motor_driver_A1B_port, motor_driver_A1B_pin);
}

void go_straight(uint16_t speed) {                              // parameter range 0 - 4000 -> works well with over 800 -> the higher the faster
    GPIO_WriteLow(motor_driver_A1B_port, motor_driver_A1B_pin);
    GPIO_WriteLow(motor_driver_B1B_port, motor_driver_B1B_pin);

    TIM2_SetCompare1(speed);
    TIM2_SetCompare2(speed);
}

void go_gay() {
    TIM2_SetCompare1(0);
    TIM2_SetCompare2(0);

    GPIO_WriteHigh(motor_driver_A1B_port, motor_driver_A1B_pin);
    GPIO_WriteHigh(motor_driver_B1B_port, motor_driver_B1B_pin);
}

void rotate_right(uint16_t right_wheel_speed) {                     // parameter range 0 - 4000 -> works well with over 800
    TIM2_SetCompare2(0);
    GPIO_WriteLow(motor_driver_A1B_port, motor_driver_A1B_pin);

    TIM2_SetCompare1(right_wheel_speed);
    GPIO_WriteHigh(motor_driver_B1B_port, motor_driver_B1B_pin);
}

void rotate_left(uint16_t left_wheel_speed) {                      // parameter range 0 - 4000 -> works well with over 800
    TIM2_SetCompare1(0);
    GPIO_WriteLow(motor_driver_B1B_port, motor_driver_B1B_pin);

    TIM2_SetCompare2(left_wheel_speed);
    GPIO_WriteHigh(motor_driver_A1B_port, motor_driver_A1B_pin);
}

void turning(uint16_t left_wheel_speed, uint16_t right_wheel_speed) {   // parameters range 0 - 4000 -> works well with over 800
    TIM2_SetCompare1(right_wheel_speed);
    TIM2_SetCompare2(left_wheel_speed);

    GPIO_WriteLow(motor_driver_B1B_port, motor_driver_B1B_pin);
    GPIO_WriteLow(motor_driver_A1B_port, motor_driver_A1B_pin);
}