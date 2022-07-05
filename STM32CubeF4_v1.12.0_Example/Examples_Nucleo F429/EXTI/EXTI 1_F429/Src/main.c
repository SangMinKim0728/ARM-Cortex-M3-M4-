
/*******************************************************************************
  
  * File name :  EXTI_1 / main.c  
  
			* Application model : Nucleo_F429 Board  
  
			* Ver2.0
			* January 23. 2017
			* by Sang-min Kim, Jae-Il Kim  &  Dong-hyuk Cha
 
 ****************************************************************************** */

// 프로그램의 수행에 필요한 헤더파일 
#include "main.h"		
#include "Nucleo_F429.h"		// 	Nucleo_F429  확장보드용 헤더파일

// -- <1> 프로그램 수행에 필요한 전역변수의 선언
int		flag_Sw1 =0 ;

// -------------------------------------------------------------------------------- //

int main(void) 
{
		HAL_Init(); 
		SystemClock_Config();
		LED_Config();
		// -- <2> 스위치가 눌러지면 EXTI를 발생시키도록 설정
		SwEXTI_Config();
		
		LED_OnOff(GPIO_PIN_LedAll, 500);
		
		// 무한 루프로 동작
		while (1)  {
					if ( flag_Sw1 == 1 )  {
							// -- <3> SW1 이 눌러지면 LED를 모두 On/Off 하고,  flag_SW1 = 0 으로 설정
							LED_OnOff(GPIO_PIN_LedAll, 500);
							flag_Sw1 = 0;
					}		
		}	
}

// -------------------------------------------------------------------------------- //
// -- <4> EXTI 인터럽트 Callback 함수의 구현

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_PIN)
{
	  // -- <5> Nucleo-64 보드 SW가 눌러지면 flag_Sw1 = 1 로 설정
		if ( GPIO_PIN == GPIO_PIN_Nucleo_Sw)  flag_Sw1 = 1;	
	
	 // -- <5-1> SW1이 눌러지면 flag_Sw1 = 1 로 설정
		if ( GPIO_PIN == GPIO_PIN_Sw1)  flag_Sw1 = 1;
}

// -------------------------------------------------------------------------------- //

