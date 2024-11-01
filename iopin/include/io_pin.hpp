#pragma once

#include <cstdint>

class IOPin
{
    public:
        IOPin(const std::uint16_t pin):
        mPinNumber(pin)
        {
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