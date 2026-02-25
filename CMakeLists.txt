cmake_minimum_required(VERSION 3.22)

project(stm32_temp_logger
    VERSION   0.1.0
    LANGUAGES C ASM
)

# STM32 HAL library
include(${CMAKE_SOURCE_DIR}/cmake/stm32hal.cmake)

# Firmware sources
set(FIRMWARE_SOURCES
    Core/Src/main.c
    Core/Src/stm32f4xx_it.c
    Core/Src/system_stm32f4xx.c
    Core/Src/syscalls.c
    App/Src/app_temp_sensor.c
    App/Src/app_logger.c
    App/Src/app_led.c
    Startup/startup_stm32f446xx.s
)

add_executable(${PROJECT_NAME} ${FIRMWARE_SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE
    Core/Inc
    App/Inc
)

target_link_libraries(${PROJECT_NAME} PRIVATE stm32hal)

# Linker script
set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/Startup/STM32F446RETx_FLASH.ld)
target_link_options(${PROJECT_NAME} PRIVATE
    -T${LINKER_SCRIPT}
    -Wl,-Map=${PROJECT_NAME}.map,--cref
)

# Ensure relink when linker script changes
set_target_properties(${PROJECT_NAME} PROPERTIES
    LINK_DEPENDS ${LINKER_SCRIPT}
)

# Post-build: generate .hex and .bin, print size
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex   $<TARGET_FILE:${PROJECT_NAME}> ${PROJECT_NAME}.hex
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${PROJECT_NAME}> ${PROJECT_NAME}.bin
    COMMAND ${CMAKE_SIZE}    $<TARGET_FILE:${PROJECT_NAME}>
    COMMENT "Generating .hex / .bin and printing size info"
)
