add_library(programs 
    board_test.cpp)

# pull in common dependencies
target_link_libraries(programs pico_stdlib iopin button)

target_include_directories(programs PUBLIC include)
