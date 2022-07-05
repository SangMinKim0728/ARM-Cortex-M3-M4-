
/*******************************************************************************
  
  * File name :  UART_2 / stm32f1xx_it.c  
  
			* Application model : Nucleo_F103 Board  
 
			* Ver4.0
			* January 23. 2017
			* by Sang-min Kim, Jae-Il Kim  &  Dong-hyuk Cha
 
 ****************************************************************************** */

#include "main.h"
#include "stm32f1xx_it.h"					// 인터럽트 사용에 필요한 헤더 파일

// -- <1> UART 인터럽트 ISR을 위한 UartHandle 변수를 외부정의 변수로 선언   
extern UART_HandleTypeDef   UartHandle;

// -------------------------------------------------------------------------------- //

void SysTick_Handler(void)
{	
		HAL_IncTick();
}

// -------------------------------------------------------------------------------- //

void EXTI15_10_IRQHandler(void)
{	
		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_10);
		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_13);
}

// -------------------------------------------------------------------------------- //

void EXTI4_IRQHandler(void)
{
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_4);	
}

// -------------------------------------------------------------------------------- //

void EXTI9_5_IRQHandler(void)
{
		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_5);
		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_8);		
}

// -------------------------------------------------------------------------------- //

// -- <2> UART 인터럽트 Callback 함수 
void USART2_IRQHandler(void)
{
	// -- <2-1> UART 인터럽트 Callback 함수 
	HAL_UART_IRQHandler(&UartHandle);
}

// -------------------------------------------------------------------------------- //
