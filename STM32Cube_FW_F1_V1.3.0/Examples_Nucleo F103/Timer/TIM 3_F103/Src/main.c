
/*******************************************************************************
  
  * File name :  TIM_3 / main.c  
  
			* Application model : Nucleo_F103 Board  
  
			* Ver2.0
			* January 23. 2017
			* by Sang-min Kim, Jae-Il Kim  &  Dong-hyuk Cha
 
 ****************************************************************************** */

#include "main.h"		
#include "Nucleo_F103.h"		// 	Nucleo_F103 확장보드용 헤더 파일

// -------------------------------------------------------------------------------- //

int main(void) 
{

		HAL_Init(); 
		SystemClock_Config();
		LED_Config();
		SwEXTI_Config();				//	이 함수는 이 예제에서는 사용되지 않는다.
	
		// -- <1> Timer의 초기설정용 함수를 호출	
		TIM2_Config(6399,9999);						
	
		// -- <2> Timer의 Output Compare 초기설정용 함수를 호출	
		TIM_OC_Config(999);

		// -- <3> 무한 루프로 계속 동작
		while (1)  { }
	
}		
		
// -------------------------------------------------------------------------------- //

// -- <4> Timer의 TIM_Base 인터럽트 Callback 함수

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)  
{
		// -- <4-1> 인터럽트가 발생하면 LED를 모두 ON 시킨다.
		HAL_GPIO_WritePin(GPIONucleo, GPIO_PIN_All, GPIO_PIN_SET );	
	  HAL_GPIO_WritePin(GPIOExt, GPIO_PIN_All, GPIO_PIN_SET );	
}

// -- <5>  Timer의 OC 인터럽트 Callback 함수

void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim)		
{
		// -- <5-1> 인터럽트가 발생하면 LED를 모두 OFF 시킨다.
		HAL_GPIO_WritePin(GPIONucleo, GPIO_PIN_All, GPIO_PIN_RESET );	
	  HAL_GPIO_WritePin(GPIOExt, GPIO_PIN_All, GPIO_PIN_RESET );	
}

// -------------------------------------------------------------------------------- //
