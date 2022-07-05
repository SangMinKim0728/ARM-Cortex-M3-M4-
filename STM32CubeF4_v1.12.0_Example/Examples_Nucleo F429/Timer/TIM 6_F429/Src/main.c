
/*******************************************************************************
  
  * File name :  TIM_6 / main.c  
  
			* Application model : Nucleo_F429 Board  
  
			* Ver2.0
			* January 23. 2017
			* by Sang-min Kim, Jae-Il Kim  &  Dong-hyuk Cha
 
 ****************************************************************************** */

#include "main.h"		
#include "Nucleo_F429.h"		// Nucleo_F429 확장보드용 헤더 파일

// -- <1> 주변장치 초기화용 구조체
GPIO_InitTypeDef				GPIO_Init; 
TIM_HandleTypeDef		TimHandler;					
TIM_OC_InitTypeDef		TIM_OC;					

// -------------------------------------------------------------------------------- //

int main(void) 
{
		HAL_Init(); 
		SystemClock_Config();
	
		// -- <2> GPIOA의 클럭을 enable		
		__HAL_RCC_GPIOA_CLK_ENABLE();
	
		// -- <3> 추가 LED 동작 조건을 설정
		GPIO_Init.Pin		= GPIO_PIN_6;						// GPIO에서사용할PIN 설정
		GPIO_Init.Mode  = GPIO_MODE_AF_PP; 			// Output Push-Pull 모드
		GPIO_Init.Pull  = GPIO_PULLUP; 					// Pull Up 모드
		GPIO_Init.Speed = GPIO_SPEED_FREQ_HIGH; 	// 동작속도를HIGH로
	
		// -- <4> GPIOA를 GPIO_Init에 설정된 조건으로 초기화함
		HAL_GPIO_Init(GPIOA, &GPIO_Init);  
	
		LED_Config();
		SwEXTI_Config();		
		TIM3_Config(0,9999);
		TIM_PWM_Poll_Config(9999);
	
		LED_OnOff(GPIO_PIN_LedAll, 500);
	
		while (1)  { }
}	

// -------------------------------------------------------------------------------- //

// -- <11> EXTI 인터럽트로 TIM PWM 설정 조건을 변경
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_PIN)
{
		// -- <11-1> SW1 ~ SW4가 눌러지면 TIM_OCInit.Pulse 값을 변경 
		if ( GPIO_PIN == GPIO_PIN_Sw1) 	TIM_OC.Pulse = 999;
	
		if ( GPIO_PIN == GPIO_PIN_Sw2)  TIM_OC.Pulse = 2999;
	
		if ( GPIO_PIN == GPIO_PIN_Sw3) 	TIM_OC.Pulse = 4999;
	
		if ( GPIO_PIN == GPIO_PIN_Sw4)  TIM_OC.Pulse = 9999;

		// -- <11-2> TIM PWM의 Channel을 TIM_OCInit에 설정된 값으로 초기화 함
		HAL_TIM_PWM_ConfigChannel(&TimHandler, &TIM_OC, TIM_CHANNEL_1);

		// -- <11-3> TIM PWM를 동작함
		HAL_TIM_PWM_Start(&TimHandler,TIM_CHANNEL_1);
}

// -------------------------------------------------------------------------------- //
