
/*******************************************************************************
  
  * File name :  TIM_2 / main.c  
  
			* Application model : Nucleo_F103 Board  
  
			* Ver4.0
			* January 23. 2017
			* by Sang-min Kim, Jae-Il Kim  &  Dong-hyuk Cha
 
 ****************************************************************************** */

#include "main.h"		
#include "Nucleo_F103.h"		// 	Nucleo_F103  Ȯ�庸��� ��� ����

// --------------------------------------------------------------------------------- //

int main(void) 
{
		HAL_Init(); 
		SystemClock_Config();
		LED_Config();
		
		LED_OnOff(GPIO_PIN_LedAll, 500);

	  // ���� ������ ��� ����
		while (1)  {
				// -- <1> HAL_Delay() �Լ��� �̿��Ͽ� 1000msec �ð� ������ ��
				HAL_Delay(1000);
			
				// -- <2>  LED�� ��� Toggle ��Ų��.
				HAL_GPIO_TogglePin(GPIONucleo, GPIO_PIN_LedAll);
				HAL_GPIO_TogglePin(GPIOExt, GPIO_PIN_LedAll);
		}	
}

// -------------------------------------------------------------------------------- //

