#include "app_temp_sensor.h"

/* STM32F446RE internal temp sensor calibration (from datasheet):
 * TS_CAL1 = value at 30 °C  (stored at 0x1FFF7A2C)
 * TS_CAL2 = value at 110 °C (stored at 0x1FFF7A2E)
 * V_REF   = 3.3 V, ADC 12-bit
 *
 * Formula:
 *   temp = ((raw - TS_CAL1) * (110 - 30)) / (TS_CAL2 - TS_CAL1) + 30
 */
#define TS_CAL1_ADDR  ((uint16_t *)0x1FFF7A2CUL)
#define TS_CAL2_ADDR  ((uint16_t *)0x1FFF7A2EUL)

static ADC_HandleTypeDef *adc_handle;

void temp_sensor_init(ADC_HandleTypeDef *hadc)
{
    adc_handle = hadc;
}

uint32_t temp_sensor_read_raw(void)
{
    ADC_ChannelConfTypeDef cfg = {0};
    cfg.Channel      = ADC_CHANNEL_TEMPSENSOR;
    cfg.Rank         = 1;
    cfg.SamplingTime = ADC_SAMPLETIME_480CYCLES;
    HAL_ADC_ConfigChannel(adc_handle, &cfg);

    HAL_ADC_Start(adc_handle);
    HAL_ADC_PollForConversion(adc_handle, HAL_MAX_DELAY);
    uint32_t raw = HAL_ADC_GetValue(adc_handle);
    HAL_ADC_Stop(adc_handle);
    return raw;
}

float temp_sensor_convert_celsius(uint32_t raw)
{
#ifdef UNIT_TEST
    /* Use typical calibration values for unit testing */
    const uint16_t cal1 = 930;   /* ~30 °C */
    const uint16_t cal2 = 1210;  /* ~110 °C */
#else
    const uint16_t cal1 = *TS_CAL1_ADDR;
    const uint16_t cal2 = *TS_CAL2_ADDR;
#endif

    if (cal2 == cal1)
        return 0.0f;

    return ((float)((int32_t)raw - (int32_t)cal1) * (110.0f - 30.0f))
           / (float)(cal2 - cal1) + 30.0f;
}
