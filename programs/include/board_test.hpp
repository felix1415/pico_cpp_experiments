#include <program.hpp>

#include "pico/stdlib.h"

#include <array>
#include <vector>
#include <memory>
#include <cstdint>

class IOPin;
class Button;
class LedSet;

class BoardTest : public Program {
    public:
        BoardTest();
        ~BoardTest();
        void run() override;

    private:
        void setLedPinLevels(const std::uint16_t value, auto& pins);

        std::shared_ptr<LedSet> mLedSet;
        std::shared_ptr<IOPin> mMainLed;
        std::shared_ptr<IOPin> mHallSensor;
        std::vector<std::shared_ptr<IOPin>> mLedPins;
        std::array <std::shared_ptr<IOPin>, 4> mLPFPins;

        bool mDigitalMode {false};
        bool mStickyOn = {false};
        bool mPinHigh {false};

        std::uint64_t  mDigitalModeDuration {1000000};
        std::uint64_t  mLastSwitchTime = {0};

        std::uint16_t mPWMLevel = {0};
};