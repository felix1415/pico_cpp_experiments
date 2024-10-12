#include <cstdint>

class PWMPin
{
    public:
        PWMPin(const std::uint16_t pin, const std::uint16_t value = 32767);

        void setValue(const std::uint16_t value);
        std::uint16_t getValue();

    private:
        const std::uint16_t m_pinNumber;
        std::uint16_t m_sliceNumber;
        std::uint16_t m_channelNumber;

};