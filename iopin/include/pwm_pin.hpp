#include <cstdint>
#include <io_pin.hpp>

class PWMPin : public IOPin
{
    public:
        PWMPin(const std::uint16_t pin, const std::uint16_t value = 32767);

        void setValue(const std::uint16_t value) override;
        std::uint16_t getValue() override;

    private:
        std::uint16_t mSliceNumber;
        std::uint16_t mChannelNumber;
        std::uint16_t mValue;
};