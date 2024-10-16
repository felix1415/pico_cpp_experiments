#include "button.hpp"

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

Button::Button(const std::uint16_t pin):
mPinNumber(pin),
mHoldDuration(5000000),
mDebounceDelay(2000000),
mLastPressTime(0),
mLastReleaseTime(0),
mState(BUTTON_STATE::NO_PRESS)
{
    gpio_init(mPinNumber);
    gpio_set_dir(mPinNumber, GPIO_IN);
    gpio_pull_up(mPinNumber);
}

bool Button::getPress()
{
    if (gpio_get(mPinNumber))
    {
        return false;
    }

    return true;
}

bool Button::getHold()
{
    if(mCurrentTime - mLastPressTime < mHoldDuration)
    {
        return false;
    }

    return true;
}

bool Button::debounce()
{
    if(mCurrentTime - mLastPressTime > mDebounceDelay)
    {
        return false;
    }

    return true;
}

BUTTON_STATE Button::getState()
{
    mCurrentTime = time_us_64();

    if(getPress())
    {
        if(getHold() && mLastPressTime > mLastReleaseTime)
        {
            if(mState != BUTTON_STATE::HOLDING && mState != BUTTON_STATE::HOLD)
            {
                // printf("HOLD\n");
                mState = BUTTON_STATE::HOLD;
            }
            else
            {
                // printf("HOLDING\n");
                mState = BUTTON_STATE::HOLDING;
            }
        }
        else if(debounce() || mLastPressTime > mLastReleaseTime)
        {
            // if the last press time is more than the last release time, we're still holding the button, but not enough to trigger the hold
            // printf("DEBOUNCE\n");
            mState = BUTTON_STATE::DEBOUNCE;
        }
        else
        {
            // this should only trigger once, as the last release time has to be less than press time
            mLastPressTime = mCurrentTime;
            // printf("PRESS  %llu   %llu\n", mLastPressTime, mLastReleaseTime);
            mState = BUTTON_STATE::PRESS;
        }
    }
    else
    {
        if(mState != BUTTON_STATE::RELEASE && mState != BUTTON_STATE::NO_PRESS)
        {
            mLastReleaseTime = mCurrentTime;
            // printf("RELEASE  %llu   %llu\n", mLastPressTime, mLastReleaseTime);
            mState = BUTTON_STATE::RELEASE;
        }
        else
        {
            mState = BUTTON_STATE::NO_PRESS;
        }
    }

    return mState;
}

void Button::setHoldDuration(const std::uint16_t holdDuration)
{
    mHoldDuration = holdDuration;
}

void Button::setDebounceDelay(const std::uint16_t debounceDelay)
{
    mDebounceDelay = debounceDelay;
}