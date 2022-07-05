
/*******************************************************************************
  
  * File name :  UART_1 / stm32f4xx_it.c  
  
			* Application model : Nucleo_F429 Board  
 
			* Ver2.0
			* January 23. 2017
			* by Sang-min Kim, Jae-Il Kim  &  Dong-hyuk Cha
 
 ****************************************************************************** */

#include "main.h"
#include "stm32f4xx_it.h"					// ���ͷ�Ʈ ��뿡 �ʿ��� ��� ����

// -- <1> UART ���ͷ�Ʈ ISR�� ���� UartHandle ������ �ܺ����� ������ ����   
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

// -- <2> UART ���ͷ�Ʈ Callback �Լ� 
void USART3_IRQHandler(void)
{
	// -- <2-1> UART ���ͷ�Ʈ Callback �Լ� 
	HAL_UART_IRQHandler(&UartHandle);
}

// -------------------------------------------------------------------------------- //

