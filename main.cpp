/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/gpio.h"

#include <board_test.hpp>

#include <limits>
#include "pwm_pin.hpp"

int main() {

    stdio_init_all();
    auto mainLed = std::make_shared<PWMPin>(PICO_DEFAULT_LED_PIN);
    mainLed->setValue(std::numeric_limits<uint16_t>::max());

    uint64_t currentTime= time_us_64();
    uint64_t delay = 3000000; //3 seconds
    uint64_t nextTime = currentTime + delay;

    //delay until putty terminal is connected
    while(currentTime - delay > nextTime)
    {
        printf("start");
        currentTime = time_us_64();
    }
    printf("\n\n\n\n\n");

    mainLed->setValue(0);
    mainLed.reset();

    {
        BoardTest bt{};
        bt.run();
    }
}
