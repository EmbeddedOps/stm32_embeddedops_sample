#ifndef APP_LED_H
#define APP_LED_H

#ifdef UNIT_TEST
#include "hal_stubs.h"
#else
#include "stm32f4xx_hal.h"
#endif

#define LED_PIN   GPIO_PIN_5
#define LED_PORT  GPIOA

void led_init(void);
void led_on(void);
void led_off(void);
void led_toggle(void);

#endif /* APP_LED_H */
