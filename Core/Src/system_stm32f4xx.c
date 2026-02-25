/*
 * system_stm32f4xx.c — Minimal SystemInit for STM32F446RE.
 *
 * The CMSIS device submodule ships a template, but we provide a slim
 * version here so the project compiles stand-alone.  The real clock
 * tree is configured later in SystemClock_Config() (main.c).
 */
#include "stm32f4xx.h"

uint32_t SystemCoreClock = 16000000U;  /* HSI default */

const uint8_t AHBPrescTable[16] = {0, 0, 0, 0, 0, 0, 0, 0,
                                    1, 2, 3, 4, 6, 7, 8, 9};
const uint8_t APBPrescTable[8]  = {0, 0, 0, 0, 1, 2, 3, 4};

void SystemInit(void)
{
    /* FPU enable (Cortex-M4F) */
#if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
    SCB->CPACR |= ((3UL << 10 * 2) | (3UL << 11 * 2));
#endif
}
