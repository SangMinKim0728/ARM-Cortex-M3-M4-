
/*******************************************************************************
  
  * File name :  TIM_2 / main.c  
  
			* Application model : Nucleo_F103 Board  
  
			* Ver4.0
			* January 23. 2017
			* by Sang-min Kim, Jae-Il Kim  &  Dong-hyuk Cha
 
 ****************************************************************************** */

#include "main.h"		
#include "Nucleo_F103.h"		// 	Nucleo_F103  확장보드용 헤더 파일

// --------------------------------------------------------------------------------- //

int main(void) 
{
		HAL_Init(); 
		SystemClock_Config();
		LED_Config();
		
		LED_OnOff(GPIO_PIN_LedAll, 500);

	  // 무한 루프로 계속 동작
		while (1)  {
				// -- <1> HAL_Delay() 함수를 이용하여 1000msec 시간 지연을 함
				HAL_Delay(1000);
			
				// -- <2>  LED를 모두 Toggle 시킨다.
				HAL_GPIO_TogglePin(GPIONucleo, GPIO_PIN_LedAll);
				HAL_GPIO_TogglePin(GPIOExt, GPIO_PIN_LedAll);
		}	
}

// -------------------------------------------------------------------------------- //

