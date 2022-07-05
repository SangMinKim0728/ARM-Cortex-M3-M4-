
/*******************************************************************************
  
  * File name :  GPIO_1 / main.c  
  
			* Application model : Nucleo_F103 Board  
  
			* Ver4.0
			* January 23. 2017
			* by Sang-min Kim, Jae-Il Kim  &  Dong-hyuk Cha
 
 ****************************************************************************** */

// -- <1> ���α׷��� ���࿡ �ʿ��� ������� 
#include "main.h"		
#include "Nucleo_F103.h"		// 	Nucleo_F103 ���� ����� ���� ��� ����

// -------------------------------------------------------------------------------- //

int main(void) 
{	
		// -- <2> MCU�� �ʱ�ȭ �Լ�
		HAL_Init(); 	
		// -- <3> system clock�� �ʱ�ȭ �Լ�
		SystemClock_Config();	
		// --<4>  �ǽ������� ��¿� LED�� �ʱ�ȭ �Լ�	
		LED_Config();

		// -- <5>  500msec ���� LED�� ��� On�� �Ŀ� Off �ϴ� �Լ�
		LED_OnOff(GPIO_PIN_LedAll, 500);
		
		// -- <6> ���� ������ ����
		while (1)  {		
				// -- <7> Nucleo Board�� ������ LED�� ��� ���� ���� 
				HAL_GPIO_TogglePin(GPIONucleo, GPIO_PIN_LedAll);
			
			  // -- <8> Ȯ�� IO ���忡 ������ LED�� ��� ���� ���� 
			  HAL_GPIO_TogglePin(GPIOExt, GPIO_PIN_LedAll);
			
				// -- <9> �ð����� �Լ� 
				HAL_Delay(200);		
		}		
}

// -------------------------------------------------------------------------------- //

