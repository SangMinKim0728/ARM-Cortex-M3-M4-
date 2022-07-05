
/*******************************************************************************
  
  * File name :  TIM_3 / main.c  
  
			* Application model : Nucleo_F103 Board  
  
			* Ver2.0
			* January 23. 2017
			* by Sang-min Kim, Jae-Il Kim  &  Dong-hyuk Cha
 
 ****************************************************************************** */

#include "main.h"		
#include "Nucleo_F103.h"		// 	Nucleo_F103 Ȯ�庸��� ��� ����

// -------------------------------------------------------------------------------- //

int main(void) 
{

		HAL_Init(); 
		SystemClock_Config();
		LED_Config();
		SwEXTI_Config();				//	�� �Լ��� �� ���������� ������ �ʴ´�.
	
		// -- <1> Timer�� �ʱ⼳���� �Լ��� ȣ��	
		TIM2_Config(6399,9999);						
	
		// -- <2> Timer�� Output Compare �ʱ⼳���� �Լ��� ȣ��	
		TIM_OC_Config(999);

		// -- <3> ���� ������ ��� ����
		while (1)  { }
	
}		
		
// -------------------------------------------------------------------------------- //

// -- <4> Timer�� TIM_Base ���ͷ�Ʈ Callback �Լ�

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)  
{
		// -- <4-1> ���ͷ�Ʈ�� �߻��ϸ� LED�� ��� ON ��Ų��.
		HAL_GPIO_WritePin(GPIONucleo, GPIO_PIN_All, GPIO_PIN_SET );	
	  HAL_GPIO_WritePin(GPIOExt, GPIO_PIN_All, GPIO_PIN_SET );	
}

// -- <5>  Timer�� OC ���ͷ�Ʈ Callback �Լ�

void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim)		
{
		// -- <5-1> ���ͷ�Ʈ�� �߻��ϸ� LED�� ��� OFF ��Ų��.
		HAL_GPIO_WritePin(GPIONucleo, GPIO_PIN_All, GPIO_PIN_RESET );	
	  HAL_GPIO_WritePin(GPIOExt, GPIO_PIN_All, GPIO_PIN_RESET );	
}

// -------------------------------------------------------------------------------- //
