
/*******************************************************************************
  
  * File name :  GPIO_2 / main.c  
  
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
		unsigned char led = 0x01;
		
		// -- <3> MCU의 초기화 함수
		HAL_Init(); 	
		// -- <4> system clock의 초기화 함수
		SystemClock_Config();	
		// --<5>  실습보드의 출력용 LED의 초기화 함수	
		LED_Config();

		// -- <6>  500msec 동안 LED를 모두 On한 후에 Off 하는 함수
		LED_OnOff(GPIO_PIN_LedAll, 500);
		
		// -- <7> 무한 루프로 동작
		while (1) {
			
				 // -- <8> LED1 -> LED2  -> .. -> LED8 의 순서로 쉬프트하며 LED를  On/Off 함
				do {
						  // -- <8-1> 변수 led에 해당하는 LED를 ON한 후에 다시 OFF 함
						LED_OnOff(led, 200);
						// -- <8-2> 변수 led를 왼쪽으로 쉬프트시키는 비트연산 
						led = led << 1;
						led = led & 0xfe;
				} while (led != 0x80); 				// -- <8-3> led = 0x80 (1000 0000) 될 때까지 동작  
									              
				 // -- <9> LED8 -> LED7  -> .. -> LED1 의 순서로 쉬프트 시키며 On/Off 함
				do {
						 // -- <9-1> 변수 led에 해당하는 LED를 ON한 후에 다시 OFF 함 
						LED_OnOff(led, 200);
						// -- <9-2>  변수 led를 오른쪽으로 쉬프트시키는 비트연산 			
						led = led >> 1;
						led = led & 0x7f;
				} while (led != 0x01);				// --  <9-3> led = 0x01 (0000 0001) 될 때까지 동작 		
		}		
}

// -------------------------------------------------------------------------------- //

