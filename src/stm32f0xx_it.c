
#include "stm32f0xx_it.h"
extern uint8_t aRxBuffer[8][BUFFER_SIZE];
__IO uint8_t RxCounter= 0, ReceiveState = 0;
void NMI_Handler(void)
{
}

void HardFault_Handler(void)
{
  while (1)
  {
  }
}

void SVC_Handler(void)
{
}

void PendSV_Handler(void)
{
}


void SysTick_Handler(void)
{
}


void USART1_IRQHandler(void)
{
  if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
  {
    /* Read one byte from the receive data register */
    aRxBuffer[0][RxCounter++] = USART_ReceiveData(USART1);

    if(RxCounter == BUFFER_SIZE)
    {
      ReceiveState = 1;
      RxCounter = 0;
    }
  }
}


void USART2_IRQHandler(void)
{
  uint8_t qqaqq;
  if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
  {
    /* Read one byte from the receive data register */
    qqaqq = USART_ReceiveData(USART2);
    USART_SendData(USART2, (uint8_t) qqaqq);

    if(RxCounter == BUFFER_SIZE)
    {
      ReceiveState = 1;
      RxCounter=0;
    }
  }
}
void USART3_8_IRQHandler(void)
{}
  
