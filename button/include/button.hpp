#include <cstdint>

enum BUTTON_STATE
{
    NO_PRESS,
    PRESS,
    DEBOUNCE,
    HOLD,
    HOLDING,
    RELEASE,
};

class Button
{
    public:
        Button(const std::uint16_t pin);
        ~Button() {}

        void setDebounceDelay(const std::uint16_t debounceDelay);
        void setHoldDuration(const std::uint16_t holdDuration);
        BUTTON_STATE getState();

    private:
        bool getPress();
        bool getHold();
        bool debounce();

        const std::uint16_t mPinNumber;
        
        std::uint64_t  mCurrentTime;
        std::uint64_t  mLastPressTime;
        std::uint64_t  mLastReleaseTime;
        
        std::uint64_t  mDebounceDelay;
        std::uint64_t  mHoldDuration;

        bool mIsHeld {false};
        BUTTON_STATE mState;
};
