#include <program.hpp>

#include "pico/stdlib.h"

#include <array>
#include <cstdint>

class PWMPin;
class Button;

class BoardTest : public Program {
    public:
        BoardTest();
        ~BoardTest();
        void run() override;

    private:
        // void setLedPinLevels(const std::uint16_t value);
        void setLedPinLevels(const std::uint16_t value, auto& pins);

        std::array <PWMPin*, 4> mLedPins;
        std::array <PWMPin*, 4> mLPFPins;

        bool mDigitalMode {false};
        bool mStickyOn = {false};
        bool mPinHigh {false};

        std::uint64_t  mDigitalModeDuration {1000000};
        std::uint64_t  mLastSwitchTime = {0};

        std::uint16_t mPWMLevel = {0};
};