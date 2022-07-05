
/*******************************************************************************
  
  * File name :  TIM_5 / main.c  
  
			* Application model : Nucleo_F103 Board  
  
			* Ver2.0
			* January 23. 2017
			* by Sang-min Kim, Jae-Il Kim  &  Dong-hyuk Cha
 
 ****************************************************************************** */

#include "main.h"		
#include "Nucleo_F103.h"		// Nucleo_F103 확장보드용 헤더 파일

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
		TIM2_Config(0,9999);	
		TIM_OC_Config(9999);	
		
		LED_OnOff(GPIO_PIN_LedAll, 500);

	  // 무한 루프로 계속 동작
		while (1)  { }	
}		

// -------------------------------------------------------------------------------- //
// -- <3> Timer의 TIM_Base 인터럽트 Callback 함수

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)  
{
		HAL_GPIO_WritePin(GPIOExt, GPIO_PIN_Led1 | GPIO_PIN_Led2
													| GPIO_PIN_Led7 | GPIO_PIN_Led8, GPIO_PIN_SET );	
}

// -------------------------------------------------------------------------------- //
// -- <4>  Timer의 OC 인터럽트 Callback 함수

void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim)		
{		
		// -- <4-1>  CHANNEL_1에서 인터럽트가 발생한 경우
		if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1) {
			  HAL_GPIO_WritePin(GPIOExt, GPIO_PIN_Led1 | GPIO_PIN_Led2, GPIO_PIN_RESET);
		}

		// <4-2>  CHANNEL_2에서 인터럽트가 발생한 경우
		if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2) {
			  HAL_GPIO_WritePin(GPIOExt, GPIO_PIN_Led7 | GPIO_PIN_Led8, GPIO_PIN_RESET);
		}
}

// -------------------------------------------------------------------------------- //
// -- <5>  EXTI 인터럽트 Callback 함수의 구현

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_PIN)
{

		// -- <5-1> SW1이 눌러지면 channel 1, 2의 TIM_OCInit.Pulse = 9999로 변경
		if ( GPIO_PIN == GPIO_PIN_Sw1 ) {
				TIM_OCInit.Pulse = 9999;
				HAL_TIM_OC_ConfigChannel(&TimHandle, &TIM_OCInit, TIM_CHANNEL_1);
				HAL_TIM_OC_ConfigChannel(&TimHandle, &TIM_OCInit, TIM_CHANNEL_2);
		}

		// -- <5-2> SW2가 눌러지면 channel 1의 TIM_OCInit.Pulse = 2500으로 변경	
		else if ( GPIO_PIN == GPIO_PIN_Sw2 ) {
				TIM_OCInit.Pulse = 2500;
				HAL_TIM_OC_ConfigChannel(&TimHandle, &TIM_OCInit, TIM_CHANNEL_1);
		}

		// -- <5-3> SW3이 눌러지면 channel 2의 TIM_OCInit.Pulse = 5000으로 변경
		else if ( GPIO_PIN == GPIO_PIN_Sw3 ) {
				TIM_OCInit.Pulse = 5000;
				HAL_TIM_OC_ConfigChannel(&TimHandle, &TIM_OCInit, TIM_CHANNEL_2);
		}

		// -- <5-4> SW4가 눌러지면 channel 2의 TIM_OCInit.Pulse = 1200으로 변경	
		else if ( GPIO_PIN == GPIO_PIN_Sw4 ) {
				TIM_OCInit.Pulse = 1200;
				HAL_TIM_OC_ConfigChannel(&TimHandle, &TIM_OCInit, TIM_CHANNEL_2);
		}    
}

// -------------------------------------------------------------------------------- //
