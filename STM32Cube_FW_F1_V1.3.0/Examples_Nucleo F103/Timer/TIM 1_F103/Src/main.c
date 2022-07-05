
/*******************************************************************************
  
  * File name :  TIM_1 / main.c  
  
			* Application model : Nucleo_F103 Board  
  
			* Ver4.0
			* January 23. 2017
			* by Sang-min Kim, Jae-Il Kim  &  Dong-hyuk Cha
 
 ****************************************************************************** */

#include "main.h"		
#include "Nucleo_F103.h"		// 	Nucleo_F103 보드 사용을 위한 헤더 파일

// -------------------------------------------------------------------------------- //

int main(void) 
{

		HAL_Init(); 
		SystemClock_Config();
		LED_Config();

		// -- <1> Timer의 초기설정용 함수를 호출	
		TIM2_Config(6399,9999);
		
		LED_OnOff(GPIO_PIN_LedAll, 500);

	  // -- <2> 무한 루프로 계속 동작
		while (1)  { }
	
}		

// -------------------------------------------------------------------------------- //
// -- <3> TIM 인터럽트 Callback 함수 : Period Elapsed Callback in non blocking mode.

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)  
{
		// -- <3-1> TIM 인터럽트가 발생하면 LED를 모두 Toggle 시킨다.
		HAL_GPIO_TogglePin(GPIONucleo, GPIO_PIN_LedAll);
	  HAL_GPIO_TogglePin(GPIOExt, GPIO_PIN_LedAll);
}

// -------------------------------------------------------------------------------- //

