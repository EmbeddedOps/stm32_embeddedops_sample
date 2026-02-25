/*
 * hal_stubs.h — Minimal HAL type definitions for host-side unit testing.
 *
 * This file provides just enough type stubs so that the App layer headers
 * compile with the host GCC.  Ceedling/CMock will generate mocks for the
 * HAL functions; we only need the types to exist.
 */
#ifndef HAL_STUBS_H
#define HAL_STUBS_H

#include <stdint.h>
#include <stddef.h>

/* ---------- Status / return codes ---------------------------------------- */
typedef enum {
    HAL_OK      = 0x00U,
    HAL_ERROR   = 0x01U,
    HAL_BUSY    = 0x02U,
    HAL_TIMEOUT = 0x03U
} HAL_StatusTypeDef;

/* ---------- GPIO --------------------------------------------------------- */
typedef struct { uint32_t dummy; } GPIO_TypeDef;

typedef struct {
    uint32_t Pin;
    uint32_t Mode;
    uint32_t Pull;
    uint32_t Speed;
    uint32_t Alternate;
} GPIO_InitTypeDef;

typedef enum {
    GPIO_PIN_RESET = 0U,
    GPIO_PIN_SET   = 1U
} GPIO_PinState;

#define GPIO_PIN_5         ((uint16_t)0x0020)
#define GPIO_MODE_OUTPUT_PP 0x00000001U
#define GPIO_NOPULL         0x00000000U
#define GPIO_SPEED_FREQ_LOW 0x00000000U

/* Provide a stub GPIOA pointer */
extern GPIO_TypeDef gpioa_stub;
#define GPIOA (&gpioa_stub)

/* HAL GPIO function prototypes (will be mocked by CMock) */
void HAL_GPIO_Init(GPIO_TypeDef *GPIOx, GPIO_InitTypeDef *GPIO_Init);
void HAL_GPIO_WritePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState);
void HAL_GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

/* ---------- UART --------------------------------------------------------- */
typedef struct {
    uint32_t BaudRate;
    uint32_t WordLength;
    uint32_t StopBits;
    uint32_t Parity;
    uint32_t Mode;
    uint32_t HwFlowCtl;
    uint32_t OverSampling;
} UART_InitTypeDef;

typedef struct {
    void            *Instance;
    UART_InitTypeDef Init;
} UART_HandleTypeDef;

#define HAL_MAX_DELAY 0xFFFFFFFFU

HAL_StatusTypeDef HAL_UART_Transmit(UART_HandleTypeDef *huart,
                                     const uint8_t *pData,
                                     uint16_t Size,
                                     uint32_t Timeout);

/* ---------- ADC ---------------------------------------------------------- */
typedef struct {
    uint32_t ClockPrescaler;
    uint32_t Resolution;
    uint32_t ScanConvMode;
    uint32_t ContinuousConvMode;
    uint32_t DiscontinuousConvMode;
    uint32_t ExternalTrigConvEdge;
    uint32_t ExternalTrigConv;
    uint32_t DataAlign;
    uint32_t NbrOfConversion;
    uint32_t DMAContinuousRequests;
    uint32_t EOCSelection;
} ADC_InitTypeDef;

typedef struct {
    void           *Instance;
    ADC_InitTypeDef Init;
} ADC_HandleTypeDef;

typedef struct {
    uint32_t Channel;
    uint32_t Rank;
    uint32_t SamplingTime;
    uint32_t Offset;
} ADC_ChannelConfTypeDef;

#define ADC_CHANNEL_TEMPSENSOR 0x00120000U
#define ADC_SAMPLETIME_480CYCLES 0x00000007U

HAL_StatusTypeDef HAL_ADC_ConfigChannel(ADC_HandleTypeDef *hadc,
                                         ADC_ChannelConfTypeDef *sConfig);
HAL_StatusTypeDef HAL_ADC_Start(ADC_HandleTypeDef *hadc);
HAL_StatusTypeDef HAL_ADC_PollForConversion(ADC_HandleTypeDef *hadc,
                                             uint32_t Timeout);
uint32_t          HAL_ADC_GetValue(ADC_HandleTypeDef *hadc);
HAL_StatusTypeDef HAL_ADC_Stop(ADC_HandleTypeDef *hadc);

#endif /* HAL_STUBS_H */
