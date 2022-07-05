
/*******************************************************************************
  
  * File name :  EXTI_2 / stm32f1xx_it.c  
  
			* Application model : Nucleo_F103 Board  
 
			* Ver4.0
			* January 23. 2017
			* by Sang-min Kim, Jae-Il Kim  &  Dong-hyuk Cha
 
 ****************************************************************************** */

// --  <1> ���α׷��� ���࿡ �ʿ��� ��� ���� 
#include "main.h"
#include "stm32f1xx_it.h"					// ���ͷ�Ʈ ��뿡 �ʿ��� ��� ����

// -------------------------------------------------------------------------------- //
// --  <2> SysTick ���ͷ�Ʈ�� �ڵ鷯 �Լ�

void SysTick_Handler(void)
{	
		// -- <2-1> HAL_IncTick() �Լ��� ȣ�� 
		HAL_IncTick();
}

// -------------------------------------------------------------------------------- //
// -- <3>  EXTI15_10 ���ͷ�Ʈ�� �ڵ鷯 �Լ�

void EXTI15_10_IRQHandler(void)
{	
		// -- <3-1> GPIO_PIN_10���� EXTI�� �߻��� ����
		//				 �Լ� HAL_GPIO_EXTI_Callback(GPIO_PIN_10) �� ȣ��
		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_10);
		// -- <3-2> GPIO_PIN_13���� EXTI�� �߻��� ����
		//				 �Լ� HAL_GPIO_EXTI_Callback(GPIO_PIN_13) �� ȣ��		
		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_13);
}

// -------------------------------------------------------------------------------- //
// -- <4>  EXTI4 ���ͷ�Ʈ�� �ڵ鷯 �Լ�

void EXTI4_IRQHandler(void)
{
		// -- <4-1> GPIO_PIN_0���� EXTI�� �߻��� ����
		//				 �Լ� HAL_GPIO_EXTI_Callback(GPIO_PIN_4) �� ȣ��	
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_4);	
}

// -------------------------------------------------------------------------------- //
// -- <5>  EXTI5 ~ 9 ���ͷ�Ʈ�� �ڵ鷯 �Լ�

void EXTI9_5_IRQHandler(void)
{
		// -- <5-1> GPIO_PIN_5���� EXTI�� �߻��� ����
		//				 �Լ� HAL_GPIO_EXTI_Callback(GPIO_PIN_5) �� ȣ��		
		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_5);
		// -- <5-2> GPIO_PIN_8���� EXTI�� �߻��� ����
		//				 �Լ� HAL_GPIO_EXTI_Callback(GPIO_PIN_8) �� ȣ��		
		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_8);		
}

// -------------------------------------------------------------------------------- //
