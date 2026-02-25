#ifndef APP_TEMP_SENSOR_H
#define APP_TEMP_SENSOR_H

#include <stdint.h>

#ifdef UNIT_TEST
#include "hal_stubs.h"
#else
#include "stm32f4xx_hal.h"
#endif

void     temp_sensor_init(ADC_HandleTypeDef *hadc);
uint32_t temp_sensor_read_raw(void);
float    temp_sensor_convert_celsius(uint32_t raw);

#endif /* APP_TEMP_SENSOR_H */
