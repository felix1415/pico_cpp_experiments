# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NEVER EDIT THE NEXT LINES for Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.0.0)
set(toolchainVersion 13_2_Rel1)
set(picotoolVersion 2.0.0)
include(${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
# ====================================================================================
set(PICO_BOARD pico CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(pico_experiments C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

add_subdirectory(pwm)
add_subdirectory(button)
add_subdirectory(programs)

if (TARGET tinyusb_device)
    add_executable(pico_experiments
            main.cpp
            )

    target_compile_options(pico_experiments PUBLIC -fno-rtti)
    
    target_link_libraries(pico_experiments pwm button programs)

    # enable usb output, disable uart output
    pico_enable_stdio_usb(pico_experiments 1)
    pico_enable_stdio_uart(pico_experiments 0)

    # create map/bin/hex/uf2 file etc.
    pico_add_extra_outputs(pico_experiments)

    # add url via pico_set_program_url
elseif(PICO_ON_DEVICE)
    message("Skipping pico_experiments because TinyUSB submodule is not initialized in the SDK")
endif()
