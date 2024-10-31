// #include <cstdint>
// #include <array>
// #include <memory>
#include "led_set.hpp"

#include "pico/stdlib.h"

#include <limits>

LedSet::LedSet(std::vector<std::shared_ptr<IOPin>> array_of_pins) : IOSet(array_of_pins),
mProcessTime(time_us_64())
{
    assert(array_of_pins.size() == 3);
    assert(mPins.size() == 3);
}

std::uint16_t LedSet::getValue()
{
    return mState;
}

void LedSet::process(const std::uint8_t state)
{
    mProcessTime = time_us_64();
    switch (state) {
        case ALL_OFF:
            all_off();
            break;
        case FLASH_RED:
            short_flash_red();
            break;
        case ALL_ON:
            all_on();
            break;
        default:
            break;
    }

}

void LedSet::all_on()
{
    for(auto & led : mPins)
    {
        led->setValue(std::numeric_limits<uint16_t>::max());
    }
}

void LedSet::all_off()
{
    for(auto & led : mPins)
    {
        led->setValue(0);
    }
}

void LedSet::short_flash_red()
{
    // if(mCurrentTime - mLastPressTime > mDebounceDelay)
    // {
    //     return false;
    // }
    // for(const auto & led : IOSet<N>::mPins)
    // {
    //     led.setValue(0);
    // }
}