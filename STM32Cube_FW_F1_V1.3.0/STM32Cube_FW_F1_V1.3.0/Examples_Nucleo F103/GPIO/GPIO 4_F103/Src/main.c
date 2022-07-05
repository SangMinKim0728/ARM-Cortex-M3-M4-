
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
			
				// -- <9-1> SW1 이 눌러지면 -> led 의 1, 2번째 bit 을 1로 설정 (0x03 = 0000 0011)
				if( HAL_GPIO_ReadPin(GPIOSw1, GPIO_PIN_Sw1 ) ==  RESET )  led = led | 0x03; 
				
				// -- <9-2> SW2 이 눌러지면 -> led 의 3, 4번째 bit 을 1로 설정 (0x0c = 0000 1100)
				if( HAL_GPIO_ReadPin(GPIOSw2, GPIO_PIN_Sw2 ) ==  RESET )  led = led | 0x0c; 
				
				// -- <9-3> SW3 이 눌러지면 -> led 의 5, 6번째 bit 을 1로 설정  (0x30 = 0011 0000)
				if( HAL_GPIO_ReadPin(GPIOSw3, GPIO_PIN_Sw3 ) ==  RESET )  led = led | 0x30; 
				
				// -- <9-4> SW4 이 눌러지면 -> led 의 7, 8번째 bit 을 1로 설정  (0xc0 = 1100 0000)
				if( HAL_GPIO_ReadPin(GPIOSw4, GPIO_PIN_Sw4 ) ==  RESET )  led = led | 0xc0; 
				
				 // -- <10> 변수 led에 해당하는 LED를 ON한 후에 다시 OFF 함 
				LED_OnOff(led, 100);	
		}		
}

// -------------------------------------------------------------------------------- //

