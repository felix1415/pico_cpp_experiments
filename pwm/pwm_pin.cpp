#include "pwm_pin.hpp"

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

PWMPin::PWMPin(const std::uint16_t pin, const std::uint16_t value):
m_pinNumber(pin)
{
    gpio_set_function(pin, GPIO_FUNC_PWM);

    // Find out which PWM slice is connected to GPIO m_pinNumber
    m_sliceNumber = pwm_gpio_to_slice_num(m_pinNumber);
    m_channelNumber = pwm_gpio_to_channel(m_pinNumber);

    pwm_set_wrap(m_sliceNumber, 65535);

    pwm_set_chan_level(m_sliceNumber, m_channelNumber, 0);

    pwm_set_enabled(m_sliceNumber, true);

    setValue(value);
}

void PWMPin::setValue(const std::uint16_t value)
{
    pwm_set_gpio_level(m_pinNumber, value);
}