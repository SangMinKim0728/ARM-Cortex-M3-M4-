
/*******************************************************************************
  
  * File name :  GPIO_3 / main.c  
  
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
		// -- <2> LED를 On/Off 하기 위한 변수  (0x01 = 0000 0001) 
		uint16_t led = 0x01;
		
		// -- <3> MCU의 초기화 함수
		HAL_Init(); 	
		// -- <4> system clock의 초기화 함수
		SystemClock_Config();	
		// --<5>  실습보드의 출력용 LED의 초기화 함수	
		LED_Config();
		// --<6>  실습보드의 입력용 Switch의 초기화 함수	
		Sw_Config();

		LED_OnOff(GPIO_PIN_LedAll, 500);
		
		// -- <7> 무한 루프로 동작
		while (1) {
				// -- <8>  변수 led 를 0으로 초기화
				led = 0x00;

			  // -- <9> Nucleo SW가 눌러지면 -> led 전체 bit 을 1로 설정 (0xFF = 1111 1111)
				if( HAL_GPIO_ReadPin(GPIOSwNucleo, GPIO_PIN_Nucleo_Sw ) ==  RESET )  led = led | 0xFF; 
			
				// -- <9-1> SW1 이 눌러지면 -> led 전체 bit 을 1로 설정 (0xFF = 1111 1111)
				if( HAL_GPIO_ReadPin(GPIOSw1, GPIO_PIN_Sw1 ) ==  RESET )  led = led | 0xFF; 
				
				 // -- <10> 변수 led에 해당하는 LED를 ON한 후에 다시 OFF 함 
				LED_OnOff(led, 100);	
		}		
}

// -------------------------------------------------------------------------------- //

