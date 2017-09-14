//STM32F030_NUCLEO
#include "main.h"

static void LED_GPIO_Configuration(void);

int main(void)
{
  LED_GPIO_Configuration();
 
  GPIO_SetBits(GPIOA,GPIO_Pin_5);
  
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
