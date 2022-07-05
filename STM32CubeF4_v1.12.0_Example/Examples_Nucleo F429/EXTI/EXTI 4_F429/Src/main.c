
/*******************************************************************************
  
  * File name :  EXTI_4 / main.c  
  
			* Application model : Nucleo_F429 Board  
  
			* Ver2.0
			* January 23. 2017
			* by Sang-min Kim, Jae-Il Kim  &  Dong-hyuk Cha
 
 ****************************************************************************** */

// 프로그램의 수행에 필요한 헤더파일 
#include "main.h"		
#include "Nucleo_F429.h"		// 	Nucleo-F429 확장보드용 헤더 파일

// -------------------------------------------------------------------------------- //

int main(void) 
{

		HAL_Init(); 
		SystemClock_Config();
		LED_Config();
		SwEXTI_Config();

		LED_OnOff(GPIO_PIN_LedAll, 500);

		// -- <1> 무한 루프로 동작하지만 여기서는 아무런 일도 하지 않음	
		while (1)  { }
	
}

// -------------------------------------------------------------------------------- //
// -- <2> EXTI 인터럽트 Callback 함수의 구현
/*				이 함수는 HAL_GPIO_TogglePin() 함수를 이용하여 LED를 On/Off 한다.
				따라서 동작시에  Switch의 Chattering 현상으로 LED On/Off가 여러번 발생할 수도 있다.
*/

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_PIN)
{
	// -- <3> SW1 이 눌러지면 -> LED 1, 2를 Toggle
	if ( GPIO_PIN == GPIO_PIN_Sw1) {
			HAL_GPIO_TogglePin(GPIOExt, GPIO_PIN_Led1 | GPIO_PIN_Led2 );
	}
	// -- <4> SW2 이 눌러지면 -> LED 3, 4를 Toggle	
	if ( GPIO_PIN == GPIO_PIN_Sw2) {
			HAL_GPIO_TogglePin(GPIOExt, GPIO_PIN_Led3 | GPIO_PIN_Led4);
	}
	// -- <5> SW3 이 눌러지면 -> LED 5, 6를 Toggle	
	if ( GPIO_PIN == GPIO_PIN_Sw3) {
			HAL_GPIO_TogglePin(GPIOExt, GPIO_PIN_Led5 | GPIO_PIN_Led6);
	}
	// -- <6> SW4 이 눌러지면 -> LED 7, 8를 Toggle	
	if ( GPIO_PIN == GPIO_PIN_Sw4) { 
			HAL_GPIO_TogglePin(GPIOExt, GPIO_PIN_Led7 | GPIO_PIN_Led8);
	}	
}

// -------------------------------------------------------------------------------- //
