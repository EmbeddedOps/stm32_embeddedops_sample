#include "app_logger.h"
#include <stdio.h>
#include <string.h>

static UART_HandleTypeDef *uart_handle;

void logger_init(UART_HandleTypeDef *huart)
{
    uart_handle = huart;
}

void logger_log(const char *msg)
{
    if (uart_handle == NULL || msg == NULL)
        return;
    HAL_UART_Transmit(uart_handle, (const uint8_t *)msg,
                      (uint16_t)strlen(msg), HAL_MAX_DELAY);
}

void logger_format_temp_reading(float temp_c, char *buf, size_t len)
{
    if (buf == NULL || len == 0)
        return;
    int whole = (int)temp_c;
    int frac  = (int)((temp_c - (float)whole) * 10.0f + 0.5f);
    if (frac < 0) frac = -frac;
    snprintf(buf, len, "Temp: %d.%d C\r\n", whole, frac);
}
