#include "unity.h"
#include "app_led.h"
#include "mock_hal_stubs.h"

/* Provide the stub GPIOA instance used by LED_PORT macro */
GPIO_TypeDef gpioa_stub;

void setUp(void) {}
void tearDown(void) {}

void test_led_on_sets_pin(void)
{
    HAL_GPIO_WritePin_Expect(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
    led_on();
}

void test_led_off_resets_pin(void)
{
    HAL_GPIO_WritePin_Expect(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
    led_off();
}

void test_led_toggle_calls_toggle(void)
{
    HAL_GPIO_TogglePin_Expect(GPIOA, GPIO_PIN_5);
    led_toggle();
}
