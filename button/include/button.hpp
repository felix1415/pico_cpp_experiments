#include <cstdint>

class PWMPin
{
    public:
        PWMPin(const std::uint16_t pin, const std::uint16_t value = 32767);

        void setDebounceValue(const std::uint16_t delay);
        bool getValue();

    private:
        const std::uint16_t m_pinNumber;
        std::uint16_t m_debounceDelay;
        std::uint16_t m_lastDebounceTime;

};