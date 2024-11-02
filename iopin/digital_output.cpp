#include "digital_output.hpp"

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

DigitalOutput::DigitalOutput(const std::uint16_t pin, const std::uint16_t value):
IOPin(pin)
{
    gpio_init(pin);
    gpio_set_dir(pin, GPIO_OUT); 

    setValue(value);
}

void DigitalOutput::setValue(const std::uint16_t value)
{
    mValue = value ? 1 : 0;

    if(mValue)
    {
        gpio_put(mPinNumber, 1);
    }
    else
    {
        gpio_put(mPinNumber, 0);
    }
}

std::uint16_t DigitalOutput::getValue()
{
    return mValue;
}