#include <cstdint>

class Button
{
    public:
        Button(const std::uint16_t pin, const std::uint64_t debounceDelay);
        virtual ~Button() {}

        void setDebounceDelay(const std::uint16_t debounceDelay);
        virtual bool getValue();

    private:
        const std::uint16_t m_pinNumber;
        std::uint64_t  m_debounceDelay;
        std::uint64_t  m_lastDebounceTime;

};