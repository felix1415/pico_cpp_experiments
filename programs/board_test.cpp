#include <board_test.hpp>

#include "pwm_pin.hpp"
#include "analogue_input.hpp"
#include "digital_output.hpp"
#include "digital_input.hpp"
#include "button.hpp"

#include "led_set.hpp"

#include <stdio.h>
#include <iostream>

BoardTest::BoardTest()
{
    mMainLed = std::make_shared<PWMPin>(PICO_DEFAULT_LED_PIN);
    // mLedSet = std::make_shared<LedSet>(mLedPins);

    mHallSensor = std::make_shared<AnalogueInput>(28);
    // mVariableResistor = std::make_shared<AnalogueInput>(26);
    
    // mLedPins[1] = std::make_shared<PWMPin>(18); //red
    // mLedPins[2] = std::make_shared<PWMPin>(19); //yellow
    // mLedPins[3] = std::make_shared<PWMPin>(20); //green

    for (int i = 0; i < 3; ++i) 
    {
        //18,19,20
        mLedPins.push_back(std::make_shared<DigitalOutput>(18 + i));
    }

    mLedSet = std::make_shared<LedSet>(mLedPins);

    for (int i = 0; i < 4; ++i) 
    {
        //0,2,4,6
        mLPFPins.push_back(std::make_shared<PWMPin>(i*2));
    }

    mInputPins.push_back(std::make_shared<DigitalInput>(7));
    mInputPins.push_back(std::make_shared<DigitalInput>(9));
    mInputPins.push_back(std::make_shared<DigitalInput>(10));
    mInputPins.push_back(std::make_shared<DigitalInput>(12));

    // 0 - 10
    // 2 - 12
    // 4 - 7
    // 6 - 9
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

void BoardTest::setup()
{
    mLedSet->process(LedSetting::ALL_OFF);

    for (int i = 0; i < mLPFPins.size(); ++i) {
        printf("mLPFPins PIN NUMBER %hu", i);
        mLPFPins[i]->setValue(0);
    }
}

void BoardTest::run()
{
    mRunning.store(true);

    Button edgeButton = Button(16);
    Button cornerButton = Button(17);

    std::uint8_t ledSetState = LedSetting::ERROR;

    //this will delay the start by 3 seconds
    setup();

    while (mRunning) 
    {
        BUTTON_STATE edgeButtonState = edgeButton.getState();
        BUTTON_STATE cornerButtonState = cornerButton.getState();

        if(edgeButtonState == BUTTON_STATE::PRESS)
        {
            printf("edge button PRESS\n");
            for (int i = 0; i < mLPFPins.size(); ++i) {
                printf("mLPFPins PIN NUMBER %hu", i);
            }
            mLPFPins[2]->setValue(std::numeric_limits<uint16_t>::max());
        }

        if(edgeButtonState == BUTTON_STATE::RELEASE)
        {
            printf("edge button released\n");
            for(const auto & pin : mInputPins)
            {
                if(pin->getValue())
                {
                    printf("digital input for pin high %hu     %hu \n", mLPFPins[2]->getPin(), pin->getPin());
                }
            }
            mLPFPins[2]->setValue(0);
        }

        if(cornerButtonState == BUTTON_STATE::PRESS)
        {
            printf("corner button pressed\n");
            mLPFPins[3]->setValue(std::numeric_limits<uint16_t>::max());
        }

        if(cornerButtonState == BUTTON_STATE::RELEASE)
        {
            printf("corner button released\n");

            // for (int i = 0; i < mLPFPins.size(); ++i) {
            //     printf("TEST %hu   %hu  \n", mLPFPins[i]->getPin(), mLPFPins[i]->getValue());
            // }
            for(const auto & pin : mInputPins)
            {
                if(pin->getValue())
                {
                    printf("digital input for pin high %hu     %hu \n", mLPFPins[3]->getPin(), pin->getPin());
                }
            }
            mLPFPins[3]->setValue(0);
        }


        // if(!mStickyOn && mDigitalMode)
        // {
        //     if(time_us_64() < mLastSwitchTime + mDigitalModeDuration)
        //     {
        //         if(mPinHigh)
        //         {
        //             mPWMLevel = 65535;
        //         }
        //         else
        //         {
        //             mPWMLevel = 0;
        //         }
        //     }
        //     else
        //     {
        //         mPWMLevel = 0;
        //         mPinHigh = !mPinHigh;
        //         mLastSwitchTime = time_us_64();
        //     }
        // }
        // else if(!mDigitalMode)
        // {
        //     mPWMLevel++;

        //     if(mPWMLevel == 65535)
        //     {
        //         mPWMLevel = 0;
        //     }
        // }

        // mMainLed->setValue(mPWMLevel);
        mLedSet->process(ledSetState);
        // const float conversion_factor = 3.3f / (1 << 12);
        // uint16_t result =  mHallSensor->getValue();
        // printf("ADC %hu: 0x%03x    voltage: %f\n", mHallSensor->getPin(), result, result * conversion_factor);

    }
}
