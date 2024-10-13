/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/gpio.h"

// #include <pwm_pin.hpp>
// #include <button.hpp>
#include <board_test.hpp>

int main() {
    BoardTest bt{};
    bt.run();
    // stdio_init_all();

    // PWMPin led_pin = PWMPin(PICO_DEFAULT_LED_PIN);
    // PWMPin pin_15 = PWMPin(20);
    // PWMPin pin_16 = PWMPin(19);
    // PWMPin pin_17 = PWMPin(18);

    // PWMPin pin_1 = PWMPin(0);
    // PWMPin pin_4 = PWMPin(2);
    // PWMPin pin_6 = PWMPin(4);
    // PWMPin pin_9 = PWMPin(6);

    // std::uint16_t level = 0;
    // Button b1(16, 200000);
    // Button b2(17, 200000);
    // bool digital_mode = false;
    // bool power_value = false;
    // bool sticky_value = false;

    // std::uint64_t  digitalModeDuration = 1000000;
    // std::uint64_t  lastSwitchTime = 0;

    // while (true) {

    //     if(b1.getValue())
    //     {
    //         digital_mode = !digital_mode;
    //         lastSwitchTime = time_us_64();
    //     }

    //     if(b2.getValue())
    //     {
    //         sticky_value = !sticky_value;
    //     }
        

    //     if(!sticky_value && digital_mode)
    //     {
    //         if(time_us_64() < lastSwitchTime + digitalModeDuration)
    //         {
    //             if(power_value)
    //             {
    //                 level = 65535;
    //             }
    //             else
    //             {
    //                 level = 0;
    //             }
    //         }
    //         else
    //         {
    //             power_value = !power_value;
    //             lastSwitchTime = time_us_64();
    //         }
    //     }

    //     led_pin.setValue(level);
    //     pin_15.setValue(level);
    //     pin_16.setValue(level);
    //     pin_17.setValue(level);

    //     pin_1.setValue(level);
    //     pin_4.setValue(level);
    //     pin_6.setValue(level);
    //     pin_9.setValue(level);

    //     if(digital_mode)
    //     {
    //         continue;
    //     }


    //     level++;

    //     if(level == 65535)
    //     {
    //         printf("Hello, world reset!\n");
    //         level = 0;
    //     }
        
    //     sleep_us(20);
    // }
}
