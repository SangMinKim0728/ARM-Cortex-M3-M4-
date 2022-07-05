
/*******************************************************************************
  
  * File name :  EXTI_3 / stm32f4xx_it.c  
  
			* Application model : Nucleo_F429 Board  
 
			* Ver2.0
			* January 23. 2017
			* by Sang-min Kim, Jae-Il Kim  &  Dong-hyuk Cha
 
 ****************************************************************************** */

// --  <1> 프로그램의 수행에 필요한 헤더 파일 
#include "main.h"
#include "stm32f4xx_it.h"					// 인터럽트 사용에 필요한 헤더 파일

// -------------------------------------------------------------------------------- //
// --  <2> SysTick 인터럽트의 핸들러 함수

void SysTick_Handler(void)
{	
		// -- <2-1> HAL_IncTick() 함수를 호출 
		HAL_IncTick();
}

// -------------------------------------------------------------------------------- //
// -- <3>  EXTI0 인터럽트의 핸들러 함수

void EXTI0_IRQHandler(void)
{	
		// -- <3-1> GPIO_PIN_0에서 EXTI가 발생한 경우는
		//				 함수 HAL_GPIO_EXTI_Callback(GPIO_PIN_0) 를 호출
		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);	
}

// -------------------------------------------------------------------------------- //
// -- <4>  EXTI1 인터럽트의 핸들러 함수

void EXTI1_IRQHandler(void)
{
		// -- <4-1> GPIO_PIN_1에서 EXTI가 발생한 경우는
		//				 함수 HAL_GPIO_EXTI_Callback(GPIO_PIN_1) 를 호출	
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_1);	
}

// -------------------------------------------------------------------------------- //
// -- <5>  EXTI2 인터럽트의 핸들러 함수

void EXTI2_IRQHandler(void)
{
		// -- <5-1> GPIO_PIN_2에서 EXTI가 발생한 경우는
		//				 함수 HAL_GPIO_EXTI_Callback(GPIO_PIN_2) 를 호출		
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_2);	
}

// -------------------------------------------------------------------------------- //
// -- <6>  EXTI3 인터럽트의 핸들러 함수

void EXTI3_IRQHandler(void)
{
		// -- <6-1> GPIO_PIN_3에서 EXTI가 발생한 경우는
		//				 함수 HAL_GPIO_EXTI_Callback(GPIO_PIN_3) 를 호출		
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_3);	
}

// -------------------------------------------------------------------------------- //
// -- <7>  EXTI13 인터럽트의 핸들러 함수

void EXTI15_10_IRQHandler(void)
{	
		// -- <7-1> GPIO_PIN_13에서 EXTI가 발생한 경우는
		//				 함수 HAL_GPIO_EXTI_Callback(GPIO_PIN_13) 를 호출		
		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_13);
}

// -------------------------------------------------------------------------------- //
