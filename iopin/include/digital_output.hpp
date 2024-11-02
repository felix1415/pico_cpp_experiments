#pragma once

#include "io_pin.hpp"

#include <cstdint>

class DigitalOutput : public IOPin
{
    public:
        DigitalOutput(const std::uint16_t pin, const std::uint16_t value = 0);

        void setValue(const std::uint16_t value) override;
        std::uint16_t getValue() override;

    private:
        std::uint16_t mValue;
};