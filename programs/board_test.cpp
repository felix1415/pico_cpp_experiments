#include <board_test.hpp>

#include <pwm_pin.hpp>
#include <button.hpp>

#include <array>
#include "pico/stdlib.h"

void BoardTest::setup()
{
    stdio_init_all();

    std::array <PWMPin*, 4> led_pins;
    led_pins[0] = new PWMPin(PICO_DEFAULT_LED_PIN);

    for (int i = 0; i < led_pins.size() - 1; ++i) {
        led_pins[i] = new PWMPin(18 + i);
    }

    std::array <PWMPin*, 4> lpf_pins;
    for (int i = 0; i < lpf_pins.size(); ++i) {
        led_pins[i] = new PWMPin(i*2);
    }
}

void BoardTest::teardown()
{
    
}

void BoardTest::run()
{
    
}