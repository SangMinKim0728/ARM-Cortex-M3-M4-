
/*******************************************************************************
  
  * File name :  EXTI_4 / main.c  
  
			* Application model : Nucleo_F429 Board  
  
			* Ver2.0
			* January 23. 2017
			* by Sang-min Kim, Jae-Il Kim  &  Dong-hyuk Cha
 
 ****************************************************************************** */

// ���α׷��� ���࿡ �ʿ��� ������� 
#include "main.h"		
#include "Nucleo_F429.h"		// 	Nucleo-F429 Ȯ�庸��� ��� ����

// -------------------------------------------------------------------------------- //

int main(void) 
{

		HAL_Init(); 
		SystemClock_Config();
		LED_Config();
		SwEXTI_Config();

		LED_OnOff(GPIO_PIN_LedAll, 500);

		// -- <1> ���� ������ ���������� ���⼭�� �ƹ��� �ϵ� ���� ����	
		while (1)  { }
	
}

// -------------------------------------------------------------------------------- //
// -- <2> EXTI ���ͷ�Ʈ Callback �Լ��� ����
/*				�� �Լ��� HAL_GPIO_TogglePin() �Լ��� �̿��Ͽ� LED�� On/Off �Ѵ�.
				���� ���۽ÿ�  Switch�� Chattering �������� LED On/Off�� ������ �߻��� ���� �ִ�.
*/

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_PIN)
{
	// -- <3> SW1 �� �������� -> LED 1, 2�� Toggle
	if ( GPIO_PIN == GPIO_PIN_Sw1) {
			HAL_GPIO_TogglePin(GPIOExt, GPIO_PIN_Led1 | GPIO_PIN_Led2 );
	}
	// -- <4> SW2 �� �������� -> LED 3, 4�� Toggle	
	if ( GPIO_PIN == GPIO_PIN_Sw2) {
			HAL_GPIO_TogglePin(GPIOExt, GPIO_PIN_Led3 | GPIO_PIN_Led4);
	}
	// -- <5> SW3 �� �������� -> LED 5, 6�� Toggle	
	if ( GPIO_PIN == GPIO_PIN_Sw3) {
			HAL_GPIO_TogglePin(GPIOExt, GPIO_PIN_Led5 | GPIO_PIN_Led6);
	}
	// -- <6> SW4 �� �������� -> LED 7, 8�� Toggle	
	if ( GPIO_PIN == GPIO_PIN_Sw4) { 
			HAL_GPIO_TogglePin(GPIOExt, GPIO_PIN_Led7 | GPIO_PIN_Led8);
	}	
}

// -------------------------------------------------------------------------------- //
