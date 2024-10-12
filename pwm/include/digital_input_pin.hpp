#include <cstdint>

class Pin
{
    public:
        Pin(const std::uint16_t pin, const std::uint16_t value = 0);

        void setValue(const std::uint16_t value);
        std::uint16_t getValue();

    private:
        const std::uint16_t m_pinNumber;
};