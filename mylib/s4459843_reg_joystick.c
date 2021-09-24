/** 
 **************************************************************
 * @file mylib/s4459843_reg_joystick.c
 * @author Yang Zheng - 44598435
 * @date 14032021
 * @brief Using the joystick to control the dutycycle
*         
 * REFERENCE: None
 ***************************************************************
 * EXTERNAL FUNCTIONS 
 ***************************************************************
 * 
 * 
 * 
 * 
 *************************************************************** 
 */
#include "s4459843_reg_joystick.h"

void s4459843_reg_joystick_init(void)
{
	//s4459843_reg_joystick_init1();
	//s4459843_reg_joystick_init2();
	s4459843_reg_joystick_init3();
}
void s4459843_reg_joystick_init1(void) //Init X
{


	// Enable the GPIO A Clock
  	__GPIOA_CLK_ENABLE();
 
  
	// Initalise PA3 as an Analog input.
  	GPIOA->MODER |= (0x03 << (3 * 2));			//Set bits for Analog input mode
  	GPIOA->OSPEEDR &= ~(0x03<<(3 * 2));
	GPIOA->OSPEEDR |= 0x02<<(3 * 2);  			// Fast speed
	GPIOA->PUPDR &= ~(0x03 << (3 * 2));			//Clear bits for no push/pull


	__ADC1_CLK_ENABLE();						//Enable ADC1 clock

	AdcHandle.Instance = (ADC_TypeDef *)(ADC1_BASE);						//Use ADC1 (For PA3)
	AdcHandle.Init.ClockPrescaler        = ADC_CLOCKPRESCALER_PCLK_DIV2;	//Set clock prescaler
	AdcHandle.Init.Resolution            = ADC_RESOLUTION12b;				//Set 12-bit data resolution
	AdcHandle.Init.ScanConvMode          = DISABLE;
	AdcHandle.Init.ContinuousConvMode    = DISABLE;
	AdcHandle.Init.DiscontinuousConvMode = DISABLE;
	AdcHandle.Init.NbrOfDiscConversion   = 0;
	AdcHandle.Init.ExternalTrigConvEdge  = ADC_EXTERNALTRIGCONVEDGE_NONE;	//No Trigger
	AdcHandle.Init.ExternalTrigConv      = ADC_EXTERNALTRIGCONV_T1_CC1;		//No Trigger
	AdcHandle.Init.DataAlign             = ADC_DATAALIGN_RIGHT;				//Right align data
	AdcHandle.Init.NbrOfConversion       = 1;
	AdcHandle.Init.DMAContinuousRequests = DISABLE;
	AdcHandle.Init.EOCSelection          = DISABLE;

	HAL_ADC_Init(&AdcHandle);		//Initialise ADC

	// Configure ADC Channel
	AdcChanConfig.Channel = ADC_CHANNEL_3;					//PA3 has Analog Channel 3 connected
	AdcChanConfig.Rank         = 1;
	AdcChanConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
	AdcChanConfig.Offset       = 0;

	HAL_ADC_ConfigChannel(&AdcHandle, &AdcChanConfig);		//Initialise ADC Channel
}
void s4459843_reg_joystick_init2(void)  //Init Y
{


	// Enable the GPIO A Clock

    __GPIOC_CLK_ENABLE();
 

    GPIOC->MODER |= (0x03 << (0 * 2));			//Set bits for Analog input mode
  	GPIOC->OSPEEDR &= ~(0x03<<(0 * 2));
	GPIOC->OSPEEDR |= 0x02<<(0 * 2);  			// Fast speed
	GPIOC->PUPDR &= ~(0x03 << (0 * 2));			//Clear bits for no push/pull


	__ADC2_CLK_ENABLE();						//Enable ADC1 clock

	AdcHandle.Instance = (ADC_TypeDef *)(ADC2_BASE);						//Use ADC1 (For PA3)
	AdcHandle.Init.ClockPrescaler        = ADC_CLOCKPRESCALER_PCLK_DIV2;	//Set clock prescaler
	AdcHandle.Init.Resolution            = ADC_RESOLUTION12b;				//Set 12-bit data resolution
	AdcHandle.Init.ScanConvMode          = DISABLE;
	AdcHandle.Init.ContinuousConvMode    = DISABLE;
	AdcHandle.Init.DiscontinuousConvMode = DISABLE;
	AdcHandle.Init.NbrOfDiscConversion   = 0;
	AdcHandle.Init.ExternalTrigConvEdge  = ADC_EXTERNALTRIGCONVEDGE_NONE;	//No Trigger
	AdcHandle.Init.ExternalTrigConv      = ADC_EXTERNALTRIGCONV_T1_CC1;		//No Trigger
	AdcHandle.Init.DataAlign             = ADC_DATAALIGN_RIGHT;				//Right align data
	AdcHandle.Init.NbrOfConversion       = 1;
	AdcHandle.Init.DMAContinuousRequests = DISABLE;
	AdcHandle.Init.EOCSelection          = DISABLE;

	HAL_ADC_Init(&AdcHandle);		//Initialise ADC

	// Configure ADC Channel
	AdcChanConfig.Channel = ADC_CHANNEL_13;					//PC0 has Analog Channel 10 connected
	AdcChanConfig.Rank         = 1;
	AdcChanConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
	AdcChanConfig.Offset       = 0;

	HAL_ADC_ConfigChannel(&AdcHandle, &AdcChanConfig);		//Initialise ADC Channel
}
void s4459843_reg_joystick_init3(void)  //Init Z
{
	// Enable GPIOC Clock
	__GPIOC_CLK_ENABLE();

    GPIOC->OSPEEDR |= (GPIO_SPEED_FAST << 3);	//Set fast speed.
	GPIOC->PUPDR &= ~(0x03 << (3 * 2));			//Clear bits for no push/pull
	GPIOC->MODER &= ~(0x03 << (3 * 2));			//Clear bits for input mode

	// Enable EXTI clock
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

	//select trigger source (port c, pin 13) on EXTICR4.
	SYSCFG->EXTICR[0] &= ~SYSCFG_EXTICR1_EXTI3;
	SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI3_PC;
	SYSCFG->EXTICR[0] &= ~(0x000F);

	EXTI->RTSR |= EXTI_RTSR_TR3;	//enable rising dedge
	EXTI->FTSR &= ~EXTI_FTSR_TR3;	//disable falling edge
	
	EXTI->IMR |= EXTI_IMR_IM3;		//Enable external interrupt

	//Enable priority (10) and interrupt callback. Do not set a priority lower than 5.
	HAL_NVIC_SetPriority(EXTI3_IRQn, 10, 0);
	HAL_NVIC_EnableIRQ(EXTI3_IRQn);

}
unsigned char joystick_readZ(void)
{
	unsigned char zstatus=0x00;
	if(s4459843_reg_iss_eventcounter_read(JOYSTICK_Z_CHANNEL)>0)
	{
		s4459843_reg_iss_eventcounter_reset(JOYSTICK_Z_CHANNEL);
		zstatus=0x01;
	}
	return zstatus;
}
void s4459843_reg_joystick_iss_isr(int GPIO_P)
{
	if(GPIO_P==GPIO_JOYSTICKZ)
	{
		s4459843_reg_iss_synchroniser(JOYSTICK_Z_CHANNEL);
	}
}
