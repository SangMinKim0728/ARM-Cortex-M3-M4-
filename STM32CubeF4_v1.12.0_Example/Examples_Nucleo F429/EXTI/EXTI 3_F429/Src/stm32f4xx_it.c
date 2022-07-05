
/*******************************************************************************
  
  * File name :  EXTI_3 / stm32f4xx_it.c  
  
			* Application model : Nucleo_F429 Board  
 
			* Ver2.0
			* January 23. 2017
			* by Sang-min Kim, Jae-Il Kim  &  Dong-hyuk Cha
 
 ****************************************************************************** */

// --  <1> ���α׷��� ���࿡ �ʿ��� ��� ���� 
#include "main.h"
#include "stm32f4xx_it.h"					// ���ͷ�Ʈ ��뿡 �ʿ��� ��� ����

// -------------------------------------------------------------------------------- //
// --  <2> SysTick ���ͷ�Ʈ�� �ڵ鷯 �Լ�

void SysTick_Handler(void)
{	
		// -- <2-1> HAL_IncTick() �Լ��� ȣ�� 
		HAL_IncTick();
}

// -------------------------------------------------------------------------------- //
// -- <3>  EXTI0 ���ͷ�Ʈ�� �ڵ鷯 �Լ�

void EXTI0_IRQHandler(void)
{	
		// -- <3-1> GPIO_PIN_0���� EXTI�� �߻��� ����
		//				 �Լ� HAL_GPIO_EXTI_Callback(GPIO_PIN_0) �� ȣ��
		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);	
}

// -------------------------------------------------------------------------------- //
// -- <4>  EXTI1 ���ͷ�Ʈ�� �ڵ鷯 �Լ�

void EXTI1_IRQHandler(void)
{
		// -- <4-1> GPIO_PIN_1���� EXTI�� �߻��� ����
		//				 �Լ� HAL_GPIO_EXTI_Callback(GPIO_PIN_1) �� ȣ��	
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_1);	
}

// -------------------------------------------------------------------------------- //
// -- <5>  EXTI2 ���ͷ�Ʈ�� �ڵ鷯 �Լ�

void EXTI2_IRQHandler(void)
{
		// -- <5-1> GPIO_PIN_2���� EXTI�� �߻��� ����
		//				 �Լ� HAL_GPIO_EXTI_Callback(GPIO_PIN_2) �� ȣ��		
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_2);	
}

// -------------------------------------------------------------------------------- //
// -- <6>  EXTI3 ���ͷ�Ʈ�� �ڵ鷯 �Լ�

void EXTI3_IRQHandler(void)
{
		// -- <6-1> GPIO_PIN_3���� EXTI�� �߻��� ����
		//				 �Լ� HAL_GPIO_EXTI_Callback(GPIO_PIN_3) �� ȣ��		
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_3);	
}

// -------------------------------------------------------------------------------- //
// -- <7>  EXTI13 ���ͷ�Ʈ�� �ڵ鷯 �Լ�

void EXTI15_10_IRQHandler(void)
{	
		// -- <7-1> GPIO_PIN_13���� EXTI�� �߻��� ����
		//				 �Լ� HAL_GPIO_EXTI_Callback(GPIO_PIN_13) �� ȣ��		
		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_13);
}

// -------------------------------------------------------------------------------- //
