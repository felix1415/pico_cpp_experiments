#include <board_test.hpp>

#include "pwm_pin.hpp"
#include "analogue_input.hpp"
#include "button.hpp"

#include "led_set.hpp"

#include <stdio.h>
#include <iostream>

BoardTest::BoardTest()
{
    stdio_init_all();

    mMainLed = std::make_shared<PWMPin>(PICO_DEFAULT_LED_PIN);
    // mLedSet = std::make_shared<LedSet>(mLedPins);

    mHallSensor = std::make_shared<AnalogueInput>(28);
    // mVariableResistor = std::make_shared<AnalogueInput>(26);
    
    // mLedPins[1] = std::make_shared<PWMPin>(18); //red
    // mLedPins[2] = std::make_shared<PWMPin>(19); //yellow
    // mLedPins[3] = std::make_shared<PWMPin>(20); //green

    for (int i = 0; i < 3; ++i) {
        //18,19,20
        mLedPins.push_back(std::make_shared<PWMPin>(18 + i));
    }
    for (int i = 0; i < mLPFPins.size(); ++i) {
        //0,2,4,6
        mLPFPins[i] = std::make_shared<PWMPin>(i*2);
    }

    mLedSet = std::make_shared<LedSet>(mLedPins);
}

BoardTest::~BoardTest()
{
    for (int i = 0; i < mLedPins.size(); ++i) {
        mLedPins[i].reset();
    }

    for (int i = 0; i < mLPFPins.size(); ++i) {
        mLPFPins[i].reset();
    }
}

void BoardTest::setLedPinLevels(const std::uint16_t value, auto& pins)
{
    mMainLed->setValue(value);
    // for (int i = 0; i < pins.size(); ++i) {
    //     pins[i]->setValue(value);
    // }
}

void BoardTest::run()
{
    mRunning.store(true);

    Button digitalModeButton = Button(16);
    Button stickyButton = Button(17);

    std::uint8_t ledSetState = LedSetting::ALL_OFF;

    while (mRunning) {
        if(digitalModeButton.getState() == BUTTON_STATE::PRESS)
        {
            if(LedSetting::ALL_OFF != ledSetState)
            {
                ledSetState = LedSetting::ALL_OFF;
            }
            else if(LedSetting::ALL_ON != ledSetState)
            {
                ledSetState = LedSetting::ALL_ON;
            }

            mDigitalMode = !mDigitalMode;
            mStickyOn = false;
            mLastSwitchTime = time_us_64();   
        }

        if(stickyButton.getState() == BUTTON_STATE::PRESS)
        {
            mStickyOn = !mStickyOn;
            if(!mDigitalMode)
            {
                printf("mPWMLevel value: %d", mPWMLevel);
            }
        }

        if(!mStickyOn && mDigitalMode)
        {
            if(time_us_64() < mLastSwitchTime + mDigitalModeDuration)
            {
                if(mPinHigh)
                {
                    mPWMLevel = 65535;
                }
                else
                {
                    mPWMLevel = 0;
                }
            }
            else
            {
                mPWMLevel = 0;
                mPinHigh = !mPinHigh;
                mLastSwitchTime = time_us_64();
            }
        }
        else if(!mDigitalMode)
        {
            mPWMLevel++;

            if(mPWMLevel == 65535)
            {
                mPWMLevel = 0;
            }
        }

        mMainLed->setValue(mPWMLevel);
        mLedSet->process(ledSetState);
        const float conversion_factor = 3.3f / (1 << 12);
        uint16_t result =  mHallSensor->getValue();
        printf("ADC %hu: 0x%03x    voltage: %f\n", mHallSensor->getPin(), result, result * conversion_factor);

        sleep_us(500000);
    }
}
