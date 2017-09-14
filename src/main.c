//STM32F030_NUCLEO
#include "main.h"

static void LED_GPIO_Configuration(void);
void Delay(__IO uint32_t nTime);
static __IO int32_t TimingDelay;

int main(void)
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
  LED_GPIO_Configuration();
	if (SysTick_Config(SystemCoreClock / 1000))
  { 
  while(1);
  }
  while(1)
 {
   GPIO_SetBits(GPIOA,GPIO_Pin_5);
   Delay(30);
   GPIO_ResetBits(GPIOA,GPIO_Pin_5);
 	 Delay(30);
 }
}
  
static void LED_GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure; 	
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void Delay(__IO uint32_t nTime)
{ 
  TimingDelay = nTime; 
  while(TimingDelay != 0);
}
void TimingDelay_Decrement(void)
{
  if (TimingDelay != 0x00)
  { 
    TimingDelay--;
  }
}
