
/*******************************************************************************
  
  * File name :  GPIO_1 / main.c  
  
			* Application model : Nucleo_F103 Board  
  
			* Ver4.0
			* January 23. 2017
			* by Sang-min Kim, Jae-Il Kim  &  Dong-hyuk Cha
 
 ****************************************************************************** */

// -- <1> 프로그램의 수행에 필요한 헤더파일 
#include "main.h"		
#include "Nucleo_F103.h"		// 	Nucleo_F103 보드 사용을 위한 헤더 파일

// -------------------------------------------------------------------------------- //

int main(void) 
{	
		// -- <2> MCU의 초기화 함수
		HAL_Init(); 	
		// -- <3> system clock의 초기화 함수
		SystemClock_Config();	
		// --<4>  실습보드의 출력용 LED의 초기화 함수	
		LED_Config();

		// -- <5>  500msec 동안 LED를 모두 On한 후에 Off 하는 함수
		LED_OnOff(GPIO_PIN_LedAll, 500);
		
		// -- <6> 무한 루프로 동작
		while (1)  {		
				// -- <7> Nucleo Board에 지정된 LED를 토글 모드로 동작 
				HAL_GPIO_TogglePin(GPIONucleo, GPIO_PIN_LedAll);
			
			  // -- <8> 확장 IO 보드에 지정된 LED를 토글 모드로 동작 
			  HAL_GPIO_TogglePin(GPIOExt, GPIO_PIN_LedAll);
			
				// -- <9> 시간지연 함수 
				HAL_Delay(200);		
		}		
}

// -------------------------------------------------------------------------------- //

