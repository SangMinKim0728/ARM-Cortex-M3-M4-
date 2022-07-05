
/*******************************************************************************
  
  * File name :  UART_1 / stm32f4xx_it.c  
  
			* Application model : Nucleo_F429 Board  
 
			* Ver2.0
			* January 23. 2017
			* by Sang-min Kim, Jae-Il Kim  &  Dong-hyuk Cha
 
 ****************************************************************************** */

#include "main.h"
#include "stm32f4xx_it.h"					// 인터럽트 사용에 필요한 헤더 파일

// -- <1> UART 인터럽트 ISR을 위한 UartHandle 변수를 외부정의 변수로 선언   
extern UART_HandleTypeDef   UartHandle;

// -------------------------------------------------------------------------------- //

void SysTick_Handler(void)
{	
		HAL_IncTick();
}

// -------------------------------------------------------------------------------- //

void EXTI0_IRQHandler(void)
{	
		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);	
}

// -------------------------------------------------------------------------------- //

void EXTI1_IRQHandler(void)
{
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_1);	
}

// -------------------------------------------------------------------------------- //

void EXTI2_IRQHandler(void)
{
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_2);	
}

// -------------------------------------------------------------------------------- //

void EXTI3_IRQHandler(void)
{	
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_3);	
}

// -------------------------------------------------------------------------------- //

void EXTI15_10_IRQHandler(void)
{	
		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_13);
}

// -------------------------------------------------------------------------------- //

// -- <2> UART 인터럽트 Callback 함수 
void USART3_IRQHandler(void)
{
	// -- <2-1> UART 인터럽트 Callback 함수 
	HAL_UART_IRQHandler(&UartHandle);
}

// -------------------------------------------------------------------------------- //

