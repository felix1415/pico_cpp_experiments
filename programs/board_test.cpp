#include <board_test.hpp>

#include <pwm_pin.hpp>
#include <button.hpp>

#include <stdio.h>

BoardTest::BoardTest()
{
    stdio_init_all();

    mLedPins[0] = new PWMPin(PICO_DEFAULT_LED_PIN);
    // mLedPins[1] = new PWMPin(18); //red
    // mLedPins[2] = new PWMPin(19); //yellow
    // mLedPins[3] = new PWMPin(20); //green

    for (int i = 0; i < mLedPins.size() - 1; ++i) {
        //18,19,20
        mLedPins[i+1] = new PWMPin(18 + i);
    }
    for (int i = 0; i < mLPFPins.size(); ++i) {
        //0,2,4,6
        mLPFPins[i] = new PWMPin(i*2);
    }
}

BoardTest::~BoardTest()
{
    for (int i = 0; i < mLedPins.size(); ++i) {
        delete mLedPins[i];
    }

    for (int i = 0; i < mLPFPins.size(); ++i) {
        delete mLPFPins[i];
    }
}

void BoardTest::setLedPinLevels(const std::uint16_t value, auto& pins)
{
    for (int i = 0; i < pins.size(); ++i) {
        pins[i]->setValue(value);
    }
}

void BoardTest::run()
{
    mRunning.store(true);

    Button digitalModeButton = Button(16, 200000);
    Button stickyButton = Button(17, 200000);
    while (mRunning) {

        if(digitalModeButton.getValue())
        {
            mDigitalMode = !mDigitalMode;
            mStickyOn = false;
            mLastSwitchTime = time_us_64();   
        }

        if(stickyButton.getValue())
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

        setLedPinLevels(mPWMLevel, mLedPins);
        setLedPinLevels(mPWMLevel, mLPFPins);

        sleep_us(50);
    }
}