#pragma once

#include "io_pin.hpp"
#include "io_set.hpp"

#include <cstdint>
#include <vector>
#include <memory>
#include <limits>

enum LedSetting : std::uint8_t
{
    ALL_OFF = 0,
    FLASH_RED = 1,
    ALL_ON = 255,
};

#define SHORT_FLASH_LENGTH_US 50000
#define LONG_FLASH_LENGTH_US 300000

class LedSet : public IOSet
{
    public:
        LedSet(std::vector<std::shared_ptr<IOPin>> array_of_pins);
        ~LedSet() {}

        virtual void process(const std::uint8_t state) override;
        virtual std::uint16_t getValue() override;


    private:
        void all_on();
        void all_off();
        void short_flash_red();

        std::uint16_t mState;
        std::uint64_t mProcessTime;

};