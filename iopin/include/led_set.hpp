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
    ERROR = 1,
    ALL_ON = 255,
};

enum LedColor : std::uint8_t
{
    RED = 0,
    YELLOW = 1,
    GREEN = 2,
};

#define SHORT_DELAY_LENGTH_US 500000
#define LONG_DELAY_LENGTH_US 300000

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
        void pin_on(const std::uint8_t pin);
        void pin_off(const std::uint8_t pin);
        void short_flash_pin(const std::uint8_t pin);
        void long_flash_pin(const std::uint8_t pin);

        std::uint8_t mState;
        std::uint64_t mCurrentTime;
        std::uint64_t mTimeShortDelay;
        std::uint64_t mTimeLongDelay;

};