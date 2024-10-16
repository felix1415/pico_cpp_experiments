#include <pwm_pin.hpp>

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

PWMPin::PWMPin(const std::uint16_t pin, const std::uint16_t value):
IOPin(pin)
{
    gpio_set_function(pin, GPIO_FUNC_PWM);

    // Find out which PWM slice is connected to GPIO m_pinNumber
    mSliceNumber = pwm_gpio_to_slice_num(mPinNumber);
    mChannelNumber = pwm_gpio_to_channel(mPinNumber);

    pwm_set_wrap(mSliceNumber, 65535);

    pwm_set_chan_level(mSliceNumber, mChannelNumber, 0);

    pwm_set_enabled(mSliceNumber, true);

    setValue(value);
}

void PWMPin::setValue(const std::uint16_t value)
{
    mValue = value;
    pwm_set_gpio_level(mPinNumber, mValue);
}

std::uint16_t PWMPin::getValue()
{
    return mValue;
}