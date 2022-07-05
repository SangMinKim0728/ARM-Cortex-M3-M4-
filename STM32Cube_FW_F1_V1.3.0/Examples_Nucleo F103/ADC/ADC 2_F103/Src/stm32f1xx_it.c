
/*******************************************************************************
  
  * File name :  ADC_2 / stm32f1xx_it.c  
  
			* Application model : Nucleo_F103 Board  

			* Ver2.0
			* January 23. 2017
			* by Sang-min Kim, Jae-Il Kim  &  Dong-hyuk Cha
 
 ****************************************************************************** */

#include "main.h"
#include "stm32f1xx_it.h"					// 인터럽트 사용에 필요한 헤더 파일

// -- <4> main.c에서 정의한 AdcHandler 변수를 외부정의변수로 선언 
extern ADC_HandleTypeDef    AdcHandler;

// -------------------------------------------------------------------------------- //

void SysTick_Handler(void)
{	
		HAL_IncTick();
}

// -------------------------------------------------------------------------------- //

// -- <5> 인터럽트가 발생하면 이를 처리하는 Handler 함수 
void ADC1_IRQHandler(void)
{
  HAL_ADC_IRQHandler(&AdcHandler);
}

// -------------------------------------------------------------------------------- //
