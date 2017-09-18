#ifndef __STM32F0XX_IT_H
#define __STM32F0XX_IT_H

#ifdef __cplusplus
 extern "C" {
#endif 
#include "stm32f0xx.h"
#include "main.h"
void NMI_Handler(void);
void HardFault_Handler(void);
void SVC_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);
void USART1_IRQHandler(void);
void USART2_IRQHandler(void);
void USART3_8_IRQHandler(void);
#ifdef __cplusplus
}
#endif

#endif /* __STM32F0XX_IT_H */
