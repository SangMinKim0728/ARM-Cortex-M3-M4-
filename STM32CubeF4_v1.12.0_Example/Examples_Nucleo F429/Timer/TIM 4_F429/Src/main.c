
/*******************************************************************************
  
  * File name :  TIM_4 / main.c  
  
			* Application model : Nucleo_F429 Board  
  
			* Ver2.0
			* January 23. 2017
			* by Sang-min Kim, Jae-Il Kim  &  Dong-hyuk Cha
 
 ****************************************************************************** */

#include "main.h"		
#include "Nucleo_F429.h"		// Nucleo_F429 확장보드용 헤더 파일

// -- <1> TimHandler, TIM_OCInit 변수를 외부정의 변수로 선언
extern TIM_HandleTypeDef    TimHandle;
extern TIM_OC_InitTypeDef		TIM_OCInit;		

// -------------------------------------------------------------------------------- //
int main(void) 
{
		HAL_Init(); 
		SystemClock_Config();
		LED_Config();
		// -- <2> SW의 EXTI 입력 발생을 위한 초기설정 함수
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
		// 인터럽트가 발생하면 LED를 모두 ON 시킨다.
		HAL_GPIO_WritePin(GPIONucleo, GPIO_PIN_All, GPIO_PIN_SET );
    HAL_GPIO_WritePin(GPIOExt, GPIO_PIN_All, GPIO_PIN_SET );	
}

// -- <4>  Timer의 OC 인터럽트 Callback 함수

void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim)		
{
		// 인터럽트가 발생하면 LED를 모두 OFF 시킨다.
		HAL_GPIO_WritePin(GPIONucleo, GPIO_PIN_All, GPIO_PIN_RESET );
    HAL_GPIO_WritePin(GPIOExt, GPIO_PIN_All, GPIO_PIN_RESET );	
}

// -------------------------------------------------------------------------------- //
// -- <5> EXTI 인터럽트 Callback 함수의 구현

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_PIN)
{	
		// -- <5-1> SW1 ~ SW4가 눌러지면 TIM_OCInit.Pulse 값을 변경
	  if ( GPIO_PIN == GPIO_PIN_Nucleo_Sw) 	TIM_OCInit.Pulse =  999;	
		if ( GPIO_PIN == GPIO_PIN_Sw1) 							TIM_OCInit.Pulse =  999;	
		if ( GPIO_PIN == GPIO_PIN_Sw2)  						TIM_OCInit.Pulse = 2999;	
		if ( GPIO_PIN == GPIO_PIN_Sw3) 							TIM_OCInit.Pulse = 4999;	
		if ( GPIO_PIN == GPIO_PIN_Sw4)  						TIM_OCInit.Pulse = 9999;
	 
		// -- <5-2> TIM OC의 Channel을 TIM_OCInit에 설정된 값으로 초기화함     
		HAL_TIM_OC_ConfigChannel(&TimHandle, &TIM_OCInit, TIM_CHANNEL_1);
		// -- <5-3> TIM OC를 동작함
		HAL_TIM_OC_Start_IT(&TimHandle,TIM_CHANNEL_1);    
}

// -------------------------------------------------------------------------------- //
