#include "analogue_input.hpp"

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"

AnalogueInput::AnalogueInput(const std::uint16_t pin):
IOPin(pin)
{
    mChannelNumber = pin - 26;
    
    adc_init();
    adc_gpio_init(pin);
    adc_select_input(mChannelNumber);

    setValue(adc_read());
}

void AnalogueInput::setValue(const std::uint16_t value)
{
    (void) value;
}

std::uint16_t AnalogueInput::getValue()
{
    printf("ADC channel %hu: \n", mChannelNumber);
    mValue = adc_read();
    return mValue;
}