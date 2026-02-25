#ifndef APP_LOGGER_H
#define APP_LOGGER_H

#include <stddef.h>

#ifdef UNIT_TEST
#include "hal_stubs.h"
#else
#include "stm32f4xx_hal.h"
#endif

void logger_init(UART_HandleTypeDef *huart);
void logger_log(const char *msg);
void logger_format_temp_reading(float temp_c, char *buf, size_t len);

#endif /* APP_LOGGER_H */
