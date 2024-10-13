add_library(pwm 
    pwm_pin.cpp)

# pull in common dependencies
target_link_libraries(pwm pico_stdlib hardware_gpio hardware_pwm)

target_include_directories(pwm PUBLIC include)
