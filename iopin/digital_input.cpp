#include "digital_input.hpp"

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

DigitalInput::DigitalInput(const std::uint16_t pin, const std::uint16_t value):
IOPin(pin)
{
    gpio_init(pin);
    gpio_set_dir(pin, GPIO_IN); 

    setValue(value);
}

void DigitalInput::setValue(const std::uint16_t value)
{
    (void) value;
}

std::uint16_t DigitalInput::getValue()
{
    mValue = gpio_get(mPinNumber) ? 1 : 0;
    return mValue;
}