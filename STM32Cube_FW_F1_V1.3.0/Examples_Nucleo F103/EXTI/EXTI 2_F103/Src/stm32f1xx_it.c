
/*******************************************************************************
  
  * File name :  EXTI_2 / stm32f1xx_it.c  
  
			* Application model : Nucleo_F103 Board  
 
			* Ver4.0
			* January 23. 2017
			* by Sang-min Kim, Jae-Il Kim  &  Dong-hyuk Cha
 
 ****************************************************************************** */

// --  <1> 프로그램의 수행에 필요한 헤더 파일 
#include "main.h"
#include "stm32f1xx_it.h"					// 인터럽트 사용에 필요한 헤더 파일

// -------------------------------------------------------------------------------- //
// --  <2> SysTick 인터럽트의 핸들러 함수

void SysTick_Handler(void)
{	
		// -- <2-1> HAL_IncTick() 함수를 호출 
		HAL_IncTick();
}

// -------------------------------------------------------------------------------- //
// -- <3>  EXTI15_10 인터럽트의 핸들러 함수

void EXTI15_10_IRQHandler(void)
{	
		// -- <3-1> GPIO_PIN_10에서 EXTI가 발생한 경우는
		//				 함수 HAL_GPIO_EXTI_Callback(GPIO_PIN_10) 를 호출
		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_10);
		// -- <3-2> GPIO_PIN_13에서 EXTI가 발생한 경우는
		//				 함수 HAL_GPIO_EXTI_Callback(GPIO_PIN_13) 를 호출		
		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_13);
}

// -------------------------------------------------------------------------------- //
// -- <4>  EXTI4 인터럽트의 핸들러 함수

void EXTI4_IRQHandler(void)
{
		// -- <4-1> GPIO_PIN_0에서 EXTI가 발생한 경우는
		//				 함수 HAL_GPIO_EXTI_Callback(GPIO_PIN_4) 를 호출	
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_4);	
}

// -------------------------------------------------------------------------------- //
// -- <5>  EXTI5 ~ 9 인터럽트의 핸들러 함수

void EXTI9_5_IRQHandler(void)
{
		// -- <5-1> GPIO_PIN_5에서 EXTI가 발생한 경우는
		//				 함수 HAL_GPIO_EXTI_Callback(GPIO_PIN_5) 를 호출		
		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_5);
		// -- <5-2> GPIO_PIN_8에서 EXTI가 발생한 경우는
		//				 함수 HAL_GPIO_EXTI_Callback(GPIO_PIN_8) 를 호출		
		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_8);		
}

// -------------------------------------------------------------------------------- //
