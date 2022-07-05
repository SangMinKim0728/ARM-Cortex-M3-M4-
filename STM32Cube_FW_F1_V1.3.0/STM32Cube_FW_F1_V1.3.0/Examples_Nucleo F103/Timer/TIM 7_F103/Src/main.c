
/*******************************************************************************
  
  * File name :  TIM_7 / main.c  
  
			* Application model : Nucleo_F103 Board  
  
			* Ver2.0
			* January 23. 2017
			* by Sang-min Kim, Jae-Il Kim  &  Dong-hyuk Cha
 
 ****************************************************************************** */

#include "main.h"		
#include "Nucleo_F103.h"		// Nucleo-F103 확장보드용 헤더 파일

// TimHandler, TIM_OCInit 변수를 외부정의 변수로 선언
extern TIM_HandleTypeDef		TimHandle;					
extern TIM_OC_InitTypeDef		TIM_OCInit;					

// -------------------------------------------------------------------------------- //

int main(void) 
{
		HAL_Init(); 
		SystemClock_Config();
		LED_Config();
		SwEXTI_Config();		
		TIM2_Config(6399,9999);	
		TIM_PWM_IT_Config(999);
	
		LED_OnOff(GPIO_PIN_LedAll, 500);
	
		while (1)  { }
}		

// -------------------------------------------------------------------------------- //

// -- <1> TIM 인터럽트 TIM_BASE 인터럽트 Callback 함수
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)  
{
		HAL_GPIO_WritePin(GPIONucleo, GPIO_PIN_All, GPIO_PIN_SET );
		HAL_GPIO_WritePin(GPIOExt, GPIO_PIN_All, GPIO_PIN_SET );	
}

// -- <2> TIM 인터럽트 TIM PWM 인터럽트 callback 함수
void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)		
{
		HAL_GPIO_WritePin(GPIONucleo, GPIO_PIN_All, GPIO_PIN_RESET );
		HAL_GPIO_WritePin(GPIOExt, GPIO_PIN_All, GPIO_PIN_RESET );
}

// -------------------------------------------------------------------------------- //
