# ---------------------------------------------------------------------------
# CMake module: STM32 HAL/CMSIS static library
# ---------------------------------------------------------------------------

set(HAL_DIR ${CMAKE_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver)
set(CMSIS_CORE_DIR ${CMAKE_SOURCE_DIR}/Drivers/CMSIS/Core)
set(CMSIS_DEVICE_DIR ${CMAKE_SOURCE_DIR}/Drivers/CMSIS/Device/ST/STM32F4xx)

# Only the HAL source files we actually use
set(HAL_SOURCES
    ${HAL_DIR}/Src/stm32f4xx_hal.c
    ${HAL_DIR}/Src/stm32f4xx_hal_rcc.c
    ${HAL_DIR}/Src/stm32f4xx_hal_rcc_ex.c
    ${HAL_DIR}/Src/stm32f4xx_hal_gpio.c
    ${HAL_DIR}/Src/stm32f4xx_hal_uart.c
    ${HAL_DIR}/Src/stm32f4xx_hal_adc.c
    ${HAL_DIR}/Src/stm32f4xx_hal_adc_ex.c
    ${HAL_DIR}/Src/stm32f4xx_hal_cortex.c
    ${HAL_DIR}/Src/stm32f4xx_hal_dma.c
    ${HAL_DIR}/Src/stm32f4xx_hal_pwr.c
    ${HAL_DIR}/Src/stm32f4xx_hal_pwr_ex.c
    ${HAL_DIR}/Src/stm32f4xx_hal_flash.c
    ${HAL_DIR}/Src/stm32f4xx_hal_flash_ex.c
)

add_library(stm32hal STATIC ${HAL_SOURCES})

target_include_directories(stm32hal PUBLIC
    ${HAL_DIR}/Inc
    ${CMSIS_CORE_DIR}/Include
    ${CMSIS_DEVICE_DIR}/Include
    ${CMAKE_SOURCE_DIR}/Core/Inc    # stm32f4xx_hal_conf.h lives here
)

target_compile_definitions(stm32hal PUBLIC
    STM32F446xx
    USE_HAL_DRIVER
)
