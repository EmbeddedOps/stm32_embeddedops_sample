#include "unity.h"
#include "app_temp_sensor.h"
#include "mock_hal_stubs.h"

void setUp(void) {}
void tearDown(void) {}

/* ---- temp_sensor_convert_celsius tests ---------------------------------- */

void test_convert_celsius_at_30_degrees(void)
{
    /* cal1=930 maps to 30 °C, so raw=930 should give 30 */
    float result = temp_sensor_convert_celsius(930);
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 30.0f, result);
}

void test_convert_celsius_at_110_degrees(void)
{
    /* cal2=1210 maps to 110 °C, so raw=1210 should give 110 */
    float result = temp_sensor_convert_celsius(1210);
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 110.0f, result);
}

void test_convert_celsius_midpoint(void)
{
    /* Midpoint between 930 and 1210 → midpoint between 30 and 110 = 70 */
    uint32_t mid = (930 + 1210) / 2;  /* 1070 */
    float result = temp_sensor_convert_celsius(mid);
    TEST_ASSERT_FLOAT_WITHIN(0.5f, 70.0f, result);
}

void test_convert_celsius_below_cal1(void)
{
    /* Below calibration range — should extrapolate below 30 °C */
    float result = temp_sensor_convert_celsius(800);
    TEST_ASSERT_TRUE(result < 30.0f);
}

/* ---- temp_sensor_read_raw tests ----------------------------------------- */

void test_read_raw_returns_adc_value(void)
{
    ADC_HandleTypeDef hadc;
    temp_sensor_init(&hadc);

    HAL_ADC_ConfigChannel_IgnoreAndReturn(HAL_OK);
    HAL_ADC_Start_IgnoreAndReturn(HAL_OK);
    HAL_ADC_PollForConversion_IgnoreAndReturn(HAL_OK);
    HAL_ADC_GetValue_ExpectAndReturn(&hadc, 1050);
    HAL_ADC_Stop_IgnoreAndReturn(HAL_OK);

    uint32_t raw = temp_sensor_read_raw();
    TEST_ASSERT_EQUAL_UINT32(1050, raw);
}
