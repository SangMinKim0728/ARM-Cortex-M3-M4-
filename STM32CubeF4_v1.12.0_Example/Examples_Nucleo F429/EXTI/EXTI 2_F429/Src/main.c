
/*******************************************************************************
  
  * File name :  EXTI_2 / main.c  
  
			* Application model : Nucleo_F429 Board  
  
			* Ver2.0
			* January 23. 2017
			* by Sang-min Kim, Jae-Il Kim  &  Dong-hyuk Cha
 
 ****************************************************************************** */

// 프로그램의 수행에 필요한 헤더파일 
#include "main.h"		
#include "Nucleo_F429.h"		// 	Nucleo-F429 확장보드용 헤더 파일

// -- <1> 프로그램 수행에 필요한 전역변수의 선언
int	flag_Sw1 = 0, flag_Sw2 = 0;

// -------------------------------------------------------------------------------- //

int main(void) 
{
		// -- <2> LED를 켜기위한 변수
		uint16_t  led = 0x01;	

		HAL_Init(); 
		SystemClock_Config();
		LED_Config();
		// -- <3> 스위치가 눌러지면 EXTI를 발생시키도록 설정
		SwEXTI_Config();
		
		LED_OnOff(GPIO_PIN_LedAll, 500);
		
		// 무한 루프로 동작
		while (1)  {
				// -- <4> SW1 이 눌러지면 -> LED를 1번 → 2번 → 3번 → … → 8번 순서로 점멸하는 동작을 반복
				if ( flag_Sw1 == 1 )  {
						led <<= 1;
						if ( led > 0x80 ) led = 0x01;
						LED_OnOff(led, 100);			
				}
				
				// -- <5> SW2 이 눌러지면 -> LED를 8번 → 7번 → … → 1번 순서로 점멸하는 동작을 반복
				else if ( flag_Sw2 == 1 )  {
						led >>= 1; 
						if ( led < 0x01 ) led = 0x80;
						LED_OnOff(led, 100);
				}		
		}	
}

// -------------------------------------------------------------------------------- //
// -- <6> EXTI 인터럽트 Callback 함수의 구현

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_PIN)
{
		// -- <7> SW1이 눌러지면 flag_Sw1 = 1 , flag_Sw2 =  0 으로 설정	
		if ( GPIO_PIN == GPIO_PIN_Sw1)  {
				flag_Sw1 = 1;
				flag_Sw2 = 0;
		}

		// -- <8> SW2이 눌러지면 flag_Sw1 = 0 , flag_Sw2 =  1 로 설정		
		else if ( GPIO_PIN == GPIO_PIN_Sw2)  {
				flag_Sw1 = 0;
				flag_Sw2 = 1;
		}	
}

// -------------------------------------------------------------------------------- //
