
/*******************************************************************************
  
  * File name :  ADC_2 / stm32f1xx_it.c  
  
			* Application model : Nucleo_F103 Board  

			* Ver2.0
			* January 23. 2017
			* by Sang-min Kim, Jae-Il Kim  &  Dong-hyuk Cha
 
 ****************************************************************************** */

#include "main.h"
#include "stm32f1xx_it.h"					// ���ͷ�Ʈ ��뿡 �ʿ��� ��� ����

// -- <4> main.c���� ������ AdcHandler ������ �ܺ����Ǻ����� ���� 
extern ADC_HandleTypeDef    AdcHandler;

// -------------------------------------------------------------------------------- //

void SysTick_Handler(void)
{	
		HAL_IncTick();
}

// -------------------------------------------------------------------------------- //

// -- <5> ���ͷ�Ʈ�� �߻��ϸ� �̸� ó���ϴ� Handler �Լ� 
void ADC1_IRQHandler(void)
{
  HAL_ADC_IRQHandler(&AdcHandler);
}

// -------------------------------------------------------------------------------- //
