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
    {
        BoardTest bt{};
        bt.run();
    }
}
