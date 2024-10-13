add_library(button 
    button.cpp)

# pull in common dependencies
target_link_libraries(button pico_stdlib hardware_gpio)

target_include_directories(button PUBLIC include)
