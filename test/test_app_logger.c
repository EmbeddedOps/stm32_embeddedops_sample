#include "unity.h"
#include "app_logger.h"
#include "mock_hal_stubs.h"
#include <string.h>

void setUp(void) {}
void tearDown(void) {}

/* ---- logger_format_temp_reading tests ----------------------------------- */

void test_format_positive_temperature(void)
{
    char buf[64];
    logger_format_temp_reading(25.3f, buf, sizeof(buf));
    TEST_ASSERT_EQUAL_STRING("Temp: 25.3 C\r\n", buf);
}

void test_format_high_temperature(void)
{
    char buf[64];
    logger_format_temp_reading(110.0f, buf, sizeof(buf));
    TEST_ASSERT_EQUAL_STRING("Temp: 110.0 C\r\n", buf);
}

void test_format_zero_temperature(void)
{
    char buf[64];
    logger_format_temp_reading(0.0f, buf, sizeof(buf));
    TEST_ASSERT_EQUAL_STRING("Temp: 0.0 C\r\n", buf);
}

void test_format_null_buffer_does_not_crash(void)
{
    logger_format_temp_reading(25.0f, NULL, 0);
    /* No crash = pass */
}

/* ---- logger_log tests --------------------------------------------------- */

void test_log_transmits_over_uart(void)
{
    UART_HandleTypeDef huart;
    logger_init(&huart);

    const char *msg = "Hello\r\n";
    HAL_UART_Transmit_ExpectAndReturn(&huart, (const uint8_t *)msg,
                                       (uint16_t)strlen(msg),
                                       HAL_MAX_DELAY, HAL_OK);
    logger_log(msg);
}

void test_log_null_message_does_not_transmit(void)
{
    UART_HandleTypeDef huart;
    logger_init(&huart);
    /* No HAL_UART_Transmit expectation → CMock fails if it's called */
    logger_log(NULL);
}
