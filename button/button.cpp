#include "button.hpp"

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

Button::Button(const std::uint16_t pin, const std::uint64_t debounceDelay):
m_pinNumber(pin),
m_debounceDelay(debounceDelay),
m_lastDebounceTime(0)
{
    gpio_init(m_pinNumber);
    gpio_set_dir(m_pinNumber, GPIO_IN);
    gpio_pull_up(m_pinNumber);
}

bool Button::getValue()
{
    if(m_lastDebounceTime > 0)
    {
        if(time_us_64() < m_lastDebounceTime + m_debounceDelay)
        {
            return false;
        }
    }

    if (gpio_get(m_pinNumber))
    {
        return false;
    }

    m_lastDebounceTime = time_us_64();
    return true;
}

void Button::setDebounceDelay(const std::uint16_t debounceDelay)
{
    m_debounceDelay = debounceDelay;
}