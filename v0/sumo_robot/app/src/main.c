// TODO MAKE DESCRIPTIONS AND COMMENTS TO DESCRIBE WHAT IS HAPPENNING
// TODO CLEAN CODE !!!!!

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
    turning(1500, 4000);
}

void to_object(uint16_t distance)
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

void near_object()
{
    disableInterrupts();
    rotate_left(1000);
    delay_ms(2000);
    stop();
    delay_ms(1000);
    rotate_right(1000);
    delay_ms(2000);
    stop();
    delay_ms(1000);
    enableInterrupts();
}

void triger_triger_lul(int on)
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
        rise_fall = 0;                                              // rise fall = 0 -> next interrupt won't be execuded this if
    }
    // else if interrupt caused by fall edge -> write timer 3 counter value into variable and set that next interrupt had to be rise edge
    else if(!(rise_fall))
    {
        GPIO_WriteLow(on_board_led_port, on_board_led_pin);         // off on board led for visualization

    if (TIM3_GetFlagStatus(TIM3_FLAG_UPDATE)!= SET)                 // TODO I ENDED UP HERE WITH COMMENTS
    {
        uint16_t distance = tim3_get_distance(TIM3_GetCounter());

        if (distance < 8)
        {
            near_object();

        }
        else if (distance < 60)
        {
            to_object(distance);
        }
        else
        {
            searching();
        }
    }
    else if (TIM3_GetFlagStatus(TIM3_FLAG_UPDATE)== SET)
    {
        // false value -> timer overflow
        searching();
        //send_str("Čítač přetekl!\n\r");
    }
    rise_fall = 1;
    }
}


// interrupt handler for right infrared sensor
INTERRUPT_HANDLER(EXTI_PORTE_IRQHandler,7)
{
    // FIXME UPDATE THIS CRAP
    /*go_gay(500);
    delay_ms(500);

    GPIO_WriteHigh(on_board_led_port, on_board_led_pin);
    delay_ms(500);
    GPIO_WriteLow(on_board_led_port, on_board_led_pin);*/

    // send_str("Right infrared sensor is on black (logical 0)\n\r");
}

// interrupt handler for left infrared sensor
INTERRUPT_HANDLER(EXTI_PORTC_IRQHandler,5)
{
    // FIXME UPDATE THIS CRAP2
    /*go_gay(500);
    delay_ms(500);

    GPIO_WriteHigh(on_board_led_port, on_board_led_pin);
    delay_ms(250);
    GPIO_WriteLow(on_board_led_port, on_board_led_pin);
    delay_ms(250);
    GPIO_WriteHigh(on_board_led_port, on_board_led_pin);
    delay_ms(250);
    GPIO_WriteLow(on_board_led_port, on_board_led_pin);*/

    // send_str("Left infrared sensor is on black (logical 0)\n\r");
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

    enableInterrupts(); // IMPORTANT TO ENABLE INTERRUPTS!

    uart1_init();           // init uart -> TODO delete if not needed anymore
    tim4_init();            // init timer 4 -> used for function delay_ms
    tim3_init();            // init timer 3 -> used for calculating distance with ultrasonic sensor
    tim2_init();            // init timer 2 -> used for PWM
    tim2_PWM_init();        // init timer 2 PWM chanels -> used for motor control
    motor_pins_init();      // init motor pins -> used for motor control

    delay_ms(5000);         // start delay 5s

    while (true) {
        triger_triger_lul(true);  // if parameter true -> function is sending pulses on ultrasonic sensor triger pin
    }
}