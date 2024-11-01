#pragma once

#include "io_pin.hpp"

#include <cstdint>

class AnalogueInput : public IOPin
{
    public:
        AnalogueInput(const std::uint16_t pin);

        void setValue(const std::uint16_t value) override;
        std::uint16_t getValue() override;

    private:
        std::uint16_t mChannelNumber;
        std::uint16_t mValue;
};