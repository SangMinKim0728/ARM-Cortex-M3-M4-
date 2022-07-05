
/*******************************************************************************
  
  * File name :  TIM_1 / main.c  
  
			* Application model : Nucleo_F103 Board  
  
			* Ver4.0
			* January 23. 2017
			* by Sang-min Kim, Jae-Il Kim  &  Dong-hyuk Cha
 
 ****************************************************************************** */

#include "main.h"		
#include "Nucleo_F103.h"		// 	Nucleo_F103 ���� ����� ���� ��� ����

// -------------------------------------------------------------------------------- //

int main(void) 
{

		HAL_Init(); 
		SystemClock_Config();
		LED_Config();

		// -- <1> Timer�� �ʱ⼳���� �Լ��� ȣ��	
		TIM2_Config(6399,9999);
		
		LED_OnOff(GPIO_PIN_LedAll, 500);

	  // -- <2> ���� ������ ��� ����
		while (1)  { }
	
}		

// -------------------------------------------------------------------------------- //
// -- <3> TIM ���ͷ�Ʈ Callback �Լ� : Period Elapsed Callback in non blocking mode.

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)  
{
		// -- <3-1> TIM ���ͷ�Ʈ�� �߻��ϸ� LED�� ��� Toggle ��Ų��.
		HAL_GPIO_TogglePin(GPIONucleo, GPIO_PIN_LedAll);
	  HAL_GPIO_TogglePin(GPIOExt, GPIO_PIN_LedAll);
}

// -------------------------------------------------------------------------------- //

