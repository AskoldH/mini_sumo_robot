// TODO MAKE DESCRIPTIONS AND COMMENTS TO DESCRIBE WHAT IS HAPPENNING
// TODO CLEAN CODE !!!!!
// TODO DELETE UNNECESSARY STUFF -> UART AND INT TO STRING

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
#define echo_pin GPIO_PIN_6

// on board led for testing 
#define on_board_led_port GPIOC
#define on_board_led_pin GPIO_PIN_5

// output from infrared sensor on the right
#define ir_sensor_right_port GPIOE
#define ir_sensor_right_pin GPIO_PIN_5

// output from infrared sensor on the left
#define ir_sensor_left_port GPIOC
#define ir_sensor_left_pin GPIO_PIN_6


// declere global variables
int rise_fall = 1;          // for ultrasonic sensor -> needed for determinating if interrupt was raised by rise or fall edge
int false = 0;              // idk how and if boolean works here so ...
int true = 1;               // yeah

void searching()
{
    // TODO FIND THE RIGHT RATIO
    turning(1200, 4000);                        // parameters are -> left_wheel_speed, right_wheel_speed, range is 0 - 4000 -> works ok with over 800
}

void to_object(uint16_t distance)               // driving to the object -> the closer the faster
{
    if (distance > 40)
    {
        go_straight(1500);
    }
    else if (distance > 20)
    {
        go_straight(2500);
    }
    else
    {
        go_straight(4000);
    }
}

void near_object()                              // TODO in final version will be attack function
{
    disableInterrupts();                        // there is delay in function so I need to turn off Interrupts
    rotate_left(2000);
    delay_ms(1000);
    enableInterrupts();
}

void triger_triger_lul(int on)                  // send pulses to ultrasonic sensor triger port
{
    if (on){
        GPIO_WriteHigh(trig_port, trig_pin);
        delay_ms(1);
        GPIO_WriteLow(trig_port, trig_pin);
        delay_ms(50);
    }
}

// interrupt handler for ultrasonic sensor 
INTERRUPT_HANDLER(EXTI_PORTD_IRQHandler,6)
{
    // if interrupt caused by rise edge
    if (rise_fall)
    {
        GPIO_WriteHigh(on_board_led_port, on_board_led_pin);        // on on board led for visualization
        tim3_reset();                                               // reset timer 3
        rise_fall = 0;                                              // next interruption will be fall edge
    }
    // else if interrupt caused by fall edge -> write timer 3 counter value into variable and set that next interrupt had to be rise edge
    else if(!(rise_fall))
    {
        GPIO_WriteLow(on_board_led_port, on_board_led_pin);         // off on board led for visualization

    if (TIM3_GetFlagStatus(TIM3_FLAG_UPDATE)!= SET)                 // if timer has not overflowed
    {
        uint16_t distance = tim3_get_distance(TIM3_GetCounter());   // set distance, get value from function, parameters is time 3 counter value

        if (distance < 10)
        {
            near_object();                                          // if distance is lower that 15 cm perform near function (attack)

        }
        else if (distance < 60)
        {
            to_object(distance);                                    // if distance is lower that 60 cm drive to object
        }
        else
        {
            searching();                                            // if distance is higher that 60 cm perform searching function
        }
    }
    else if (TIM3_GetFlagStatus(TIM3_FLAG_UPDATE)== SET)            // timer has overflowed -> value is not correct, perform searching
    {
        searching();
    }
    rise_fall = 1;                                                  // next interruption will be rise edge
    }
}


// interrupt handler for right infrared sensor
INTERRUPT_HANDLER(EXTI_PORTE_IRQHandler,7)          // TODO find out the right moves, moves like jagger
{
    disableInterrupts();                            // I need to disable interrupts cos of the delay
    go_gay();
    delay_ms(300);
    rotate_left(2000);
    delay_ms(200);
    enableInterrupts();                               // enable interrupts back again
}

// interrupt handler for left infrared sensor
INTERRUPT_HANDLER(EXTI_PORTC_IRQHandler,5)         // TODO find out the right moves, moves like jagger
{
    disableInterrupts();                            // I need to disable interrupts cos of the delay
    go_gay();
    delay_ms(300);
    rotate_right(2000);
    delay_ms(200);
    enableInterrupts();                              // enable interrupts back again
}

void main(void) {
    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1); // FREQ MCU 16MHz
    GPIO_Init(on_board_led_port, on_board_led_pin, GPIO_MODE_OUT_PP_LOW_SLOW); // init on board led

    // ultrasonic sensor init ports
    GPIO_Init(trig_port, trig_pin, GPIO_MODE_OUT_PP_LOW_SLOW); // trig
    GPIO_Init(echo_port, echo_pin, GPIO_MODE_IN_FL_IT); // echo

    // infrared sensor init ports
    GPIO_Init(ir_sensor_left_port, ir_sensor_left_pin, GPIO_MODE_IN_FL_IT); // init left ir sensor
    GPIO_Init(ir_sensor_right_port, ir_sensor_right_pin, GPIO_MODE_IN_FL_IT); // init right ir sensor

    // infrared sensors interrupts
    EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOE,
                              EXTI_SENSITIVITY_FALL_ONLY);  // interrupts settup for port E - right ir sensor
    EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOC,
                              EXTI_SENSITIVITY_FALL_ONLY);  // interrupts settup for port C - left ir sensor
    ITC_SetSoftwarePriority(ITC_IRQ_PORTE,
                            ITC_PRIORITYLEVEL_1);           // interrupts priorities for port E -> higher prio than ultrasonic
    ITC_SetSoftwarePriority(ITC_IRQ_PORTC,
                            ITC_PRIORITYLEVEL_1);           // interrupts priorities for port C -> higher prio than ultrasonic

    // ultrasonic sensor interrupts 
    EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOD, EXTI_SENSITIVITY_RISE_FALL); // interrupts settup for port D
    ITC_SetSoftwarePriority(ITC_IRQ_PORTD, ITC_PRIORITYLEVEL_0); // interrupts priorities for port D



    uart1_init();           // init uart -> TODO delete if not needed anymore
    tim4_init();            // init timer 4 -> used for function delay_ms
    tim3_init();            // init timer 3 -> used for calculating distance with ultrasonic sensor
    tim2_init();            // init timer 2 -> used for PWM
    tim2_PWM_init();        // init timer 2 PWM chanels -> used for motor control
    motor_pins_init();      // init motor pins -> used for motor control
    stop();

    turning(4000, 1500);
    delay_ms(300);
    go_straight(3000);
    delay_ms(300);

    delay_ms(5000);         // start delay 5s
    enableInterrupts(); // IMPORTANT TO ENABLE INTERRUPTS!

    while (true) {
        triger_triger_lul(true);  // if parameter true -> function is sending pulses on ultrasonic sensor triger pin
    }
}