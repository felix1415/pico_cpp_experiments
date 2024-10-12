/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/gpio.h"

#include <pwm_pin.hpp>

// #ifndef LED_DELAY_MS
// #define LED_DELAY_MS 250
// #endif

// Initialize the GPIO for the LED
// void pico_led_init(void) {
// #ifdef PICO_DEFAULT_LED_PIN
//     // A device like Pico that uses a GPIO for the LED will define PICO_DEFAULT_LED_PIN
//     // so we can use normal GPIO functionality to turn the led on and off
//     gpio_init(PICO_DEFAULT_LED_PIN);
//     gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
// #endif
// }

// // Turn the LED on or off
// void pico_set_led(bool led_on) {
// #if defined(PICO_DEFAULT_LED_PIN)
//     // Just set the GPIO on or off
//     gpio_put(PICO_DEFAULT_LED_PIN, led_on);
// #endif
// }

// void on_pwm_wrap() {
//     static int fade = 0;
//     static bool going_up = true;
//     // Clear the interrupt flag that brought us here
//     pwm_clear_irq(pwm_gpio_to_slice_num(PICO_DEFAULT_LED_PIN));

//     if (going_up) {
//         ++fade;
//         if (fade > 255) {
//             fade = 255;
//             going_up = false;
//         }
//     } else {
//         --fade;
//         if (fade < 0) {
//             fade = 0;
//             going_up = true;
//         }
//     }
//     // Square the fade value to make the LED's brightness appear more linear
//     // Note this range matches with the wrap value
//     pwm_set_gpio_level(PICO_DEFAULT_LED_PIN, fade * fade);
// }

#define BUTTON_PIN 16

int main() {
    stdio_init_all();

    PWMPin led_pin = PWMPin(PICO_DEFAULT_LED_PIN);
    PWMPin pin_15 = PWMPin(20);
    PWMPin pin_16 = PWMPin(19);
    PWMPin pin_17 = PWMPin(18);

    PWMPin pin_1 = PWMPin(0);
    PWMPin pin_4 = PWMPin(2);
    PWMPin pin_6 = PWMPin(4);
    PWMPin pin_9 = PWMPin(6);

    std::uint16_t level = 0;

    bool button_value = false;
    bool power_value = false;
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);

    sleep_us(200000);

    while (true) {

        if(!gpio_get(BUTTON_PIN))
        {
            printf("button pressed\n");
            button_value = !button_value;
            sleep_us(200000);
        }

        if(button_value)
        {
            if(power_value)
            {
                level = 65535;
            }
            else
            {
                level = 0;
            }
            power_value = !power_value;
            sleep_us(2000000);
        }

        led_pin.setValue(level);
        pin_15.setValue(level);
        pin_16.setValue(level);
        pin_17.setValue(level);

        pin_1.setValue(level);
        pin_4.setValue(level);
        pin_6.setValue(level);
        pin_9.setValue(level);

        if(button_value)
        {
            continue;
        }


        level++;

        if(level == 65535)
        {
            printf("Hello, world reset!\n");
            level = 0;
        }
        // pico_set_led(led_on = !led_on);
        sleep_us(20);
    }
}



// tu = TimeUtils(timeout=10)
// timer = Timer()

// potentiometer = ADC(Pin(26))
// pwm = PWM(Pin(1), freq=1000)
// led_pwm = PWM(Pin(25), freq=1000)
// print(pwm)


// def flash_led(led, good=False):
//     count = 0
//     while True:
//         led.toggle()
//         time.sleep(0.04)
//         count += 1
//         if count > 10 and not good:
//             led.on()
//             time.sleep(2)
//             break
//         else:
//             break

// def blink_led(led):
//     count = 0
//     while True:
//         led.toggle()
//         time.sleep(0.4)
//         count += 1
//         if count > 20:
//             led.value = True
//             break


// MAX_DUTY = (2 ** 16) - 1

// led = Pin(21, Pin.OUT)


// while True:
//     # for duty in range(65025):
//     #     led_pwm.duty_u16(duty)
//     #     time.sleep(0.0001)
//     # for duty in range(65025, 0, -1):
//     #     led_pwm.duty_u16(duty)
//     #     time.sleep(0.0001)

//     time.sleep(0.1)
//     # led.toggle()

//     duty_val = potentiometer.read_u16()
//     pwm.duty_u16(duty_val)
//     led_pwm.duty_u16(duty_val)
//     print(str(pwm.duty_u16()))