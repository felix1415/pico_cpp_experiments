#pragma once

#include "io_pin.hpp"

#include <cstdint>
#include <vector>
#include <memory>

#include <iostream>

class IOSet
{
    public:
        IOSet(std::vector<std::shared_ptr<IOPin>> array_of_pins): mPins(array_of_pins), mProgress(0) { std::cout << "IOSet mPins  " << mPins.size() << std::endl;}
        virtual ~IOSet() {}

        virtual void process(const std::uint8_t state) = 0;
        virtual std::uint16_t getValue() = 0;

        virtual int numberOfPins()
        {
            return mPins.size();
        }

    protected:
        std::vector<std::shared_ptr<IOPin>> mPins;
        std::uint8_t mProgress;
};
