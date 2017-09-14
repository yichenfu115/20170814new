//STM32F030_NUCLEO
#include "main.h"

static void LED_GPIO_Configuration(void);
static void ADC_Config(void);
void Delay(__IO uint32_t nTime);
static __IO int32_t TimingDelay;
extern __IO  uint8_t Stepping = 0;
__IO uint16_t  ADC1ConvertedValue = 0, ADC1ConvertedVoltage = 0;
uint32_t PC1v = 0, PC1mv = 0;

int main(void)
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
  LED_GPIO_Configuration();
 	ADC_Config();
	if (SysTick_Config(SystemCoreClock / 1000))
  { 
  while(1);
  }
  while(1)
 {
   while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
		ADC1ConvertedValue = ADC_GetConversionValue(ADC1);

		/* Compute the voltage */
		ADC1ConvertedVoltage = (ADC1ConvertedValue * 3300) / 0xFFF;
		PC1v = (ADC1ConvertedVoltage) / 1000;
		PC1mv = (ADC1ConvertedVoltage % 1000) / 100;
   if(PC1v>1)
   {
   GPIO_SetBits(GPIOA,GPIO_Pin_5);
   Delay(30);
   GPIO_ResetBits(GPIOA,GPIO_Pin_5);
 	 Delay(30);
   }
   else   GPIO_SetBits(GPIOA,GPIO_Pin_5);

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
static void ADC_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure; 	
  ADC_InitTypeDef     ADC_InitStructure;

	/* GPIOC Periph clock enable */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);

	/* ADC1 Periph clock enable */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

	/* Configure ADC Channel11 as analog input */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	/* ADCs DeInit */
	ADC_DeInit(ADC1);

	/* Initialize ADC structure */
	ADC_StructInit(&ADC_InitStructure);

	/* Configure the ADC1 in continuous mode with a resolution equal to 12 bits  */
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_ScanDirection = ADC_ScanDirection_Upward;
	ADC_Init(ADC1, &ADC_InitStructure);

	/* Convert the ADC1 Channel 11 with 239.5 Cycles as sampling time */
	ADC_ChannelConfig(ADC1, ADC_Channel_11, ADC_SampleTime_239_5Cycles);

	/* ADC Calibration */
	ADC_GetCalibrationFactor(ADC1);

	/* Enable the ADC peripheral */
	ADC_Cmd(ADC1, ENABLE);

	/* Wait the ADRDY flag */
	while (!ADC_GetFlagStatus(ADC1, ADC_FLAG_ADRDY));

	/* ADC1 regular Software Start Conv */
	ADC_StartOfConversion(ADC1);

}
