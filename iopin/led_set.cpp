// #include <cstdint>
// #include <array>
// #include <memory>
#include "led_set.hpp"

#include "pico/stdlib.h"

#include <limits>

LedSet::LedSet(std::vector<std::shared_ptr<IOPin>> array_of_pins) : IOSet(array_of_pins),
mState(LedSetting::ALL_OFF),
mCurrentTime(time_us_64())
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
    mCurrentTime = time_us_64();
    if(state != mState)
    {
        all_off();
        mState = state;
        mTimeShortDelay = mCurrentTime + SHORT_DELAY_LENGTH_US;
        mTimeLongDelay = mCurrentTime + LONG_DELAY_LENGTH_US;
    }
    
    switch (state) {
        case ALL_OFF:
            all_off();
            break;
        case ALL_ON:
            all_on();
            break;
        case ERROR:
            short_flash_pin(LedColor::RED);
            break;

        default:
            break;
    }
}

void LedSet::all_on()
{
    for(int i = 0; i < mPins.size(); ++i)
    {
        pin_on(i);
    }
}

void LedSet::all_off()
{
    for(int i = 0; i < mPins.size(); ++i)
    {
        pin_off(i);
    }
}

void LedSet::pin_on(const std::uint8_t pin)
{
    mPins[pin]->setValue(std::numeric_limits<uint16_t>::max());
}
void LedSet::pin_off(const std::uint8_t pin)
{
    mPins[pin]->setValue(0);
}

void LedSet::short_flash_pin(const std::uint8_t pin)
{
    if(mCurrentTime - SHORT_DELAY_LENGTH_US > mTimeShortDelay)
    {
        if(mPins[pin]->getValue() == 0)
        {
            mPins[pin]->setValue(std::numeric_limits<uint16_t>::max());
            printf("pin short flash: %hu \n", mPins[pin]->getPin());
        }
        else
        {
            mPins[pin]->setValue(0);
        }

        mTimeShortDelay = mCurrentTime + SHORT_DELAY_LENGTH_US;
    }
}

void LedSet::long_flash_pin(const std::uint8_t pin)
{
    if(mCurrentTime - LONG_DELAY_LENGTH_US > mTimeLongDelay)
    {
        if(mPins[pin]->getValue() == 0)
        {
            mPins[pin]->setValue(std::numeric_limits<uint16_t>::max());
        }
        else
        {
            mPins[pin]->setValue(0);
        }

        mTimeLongDelay = mCurrentTime + LONG_DELAY_LENGTH_US;
    }
}