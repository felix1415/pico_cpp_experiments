add_library(iopin 
    pwm_pin.cpp
    led_set.cpp
    analogue_input.cpp)

# pull in common dependencies
target_link_libraries(iopin pico_stdlib hardware_gpio hardware_pwm hardware_adc)

target_include_directories(iopin PUBLIC include)
