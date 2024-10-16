add_library(iopin 
    pwm_pin.cpp)

# pull in common dependencies
target_link_libraries(iopin pico_stdlib hardware_gpio hardware_pwm)

target_include_directories(iopin PUBLIC include)
