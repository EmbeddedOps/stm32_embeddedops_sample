#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx_hal.h"

/* Nucleo-F446RE USART2 (ST-Link VCP) */
#define USART_TX_PIN   GPIO_PIN_2
#define USART_RX_PIN   GPIO_PIN_3
#define USART_PORT     GPIOA

void Error_Handler(void);

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
