#pragma once

#include <cstdint>
#include <iostream>

class IOPin
{
    public:
        IOPin(const std::uint16_t pin):
        mPinNumber(pin)
        {
            printf("IOPin created on GPIO %hu \n", mPinNumber);
        }

        virtual ~IOPin() {}

        virtual void setValue(const std::uint16_t value) = 0;
        virtual std::uint16_t getValue() = 0;

        std::uint16_t getPin() const
        {
            return mPinNumber;
        }

    protected:
        const std::uint16_t mPinNumber;
};