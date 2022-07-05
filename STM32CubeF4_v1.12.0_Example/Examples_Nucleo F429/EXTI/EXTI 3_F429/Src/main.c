
/*******************************************************************************
  
  * File name :  EXTI_3 / main.c  
  
			* Application model : Nucleo_F429 Board  
  
			* Ver2.0
			* January 23. 2017
			* by Sang-min Kim, Jae-Il Kim  &  Dong-hyuk Cha
 
 ****************************************************************************** */

// 프로그램의 수행에 필요한 헤더파일 
#include "main.h"		
#include "Nucleo_F429.h"		// 	Nucleo-F429 확장보드용 헤더 파일

// -- <1> 프로그램 수행에 필요한 전역변수의 선언
int	flag_Sw1, flag_Sw2, flag_Sw3, flag_Sw4;

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
				led = 0x00;					// 변수 led를 초기화
					
				// -- <4> SW1 이 눌러지면 -> led 의 1, 2번째 bit 을 1로 설정 (0x03 = 0000 0011)
				if ( flag_Sw1 == 1 )  {
								led = led | 0x03;
								LED_OnOff(led, 300);
								flag_Sw1 = 0;
				}				
				// -- <5> SW2 이 눌러지면 -> led 의 3, 4번째 bit 을 1로 설정 (0x0c = 0000 1100)
				if ( flag_Sw2 == 1 )  {
								led = led | 0x0c;
								LED_OnOff(led, 300);
								flag_Sw2 = 0;
				}				
				// -- <6> SW3 이 눌러지면 -> led 의 5, 6번째 bit 을 1로 설정  (0x30 = 0011 0000)
				if ( flag_Sw3 == 1 )  {
								led = led | 0x30;
								LED_OnOff(led, 300);
								flag_Sw3 = 0;
				}				
				// -- <7> SW4 이 눌러지면 -> led 의 7, 8번째 bit 을 1로 설정  (0xc0 = 1100 0000)
				if ( flag_Sw4 == 1 )  {
								led = led | 0xc0; 
								LED_OnOff(led, 300);
								flag_Sw4 = 0;
				}		
		}	
}

// -------------------------------------------------------------------------------- //
// -- <8> EXTI 인터럽트 Callback 함수의 구현

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_PIN)
{
		// -- <9> SW1이 눌러지면 flag_Sw1 = 1 으로 설정	
		if ( GPIO_PIN == GPIO_PIN_Sw1)  flag_Sw1 = 1;
		// -- <10> SW2이 눌러지면 flag_Sw2 = 1 으로 설정			
		if ( GPIO_PIN == GPIO_PIN_Sw2)  flag_Sw2 = 1;
		// -- <11> SW3이 눌러지면 flag_Sw3 = 1 으로 설정			
		if ( GPIO_PIN == GPIO_PIN_Sw3)  flag_Sw3 = 1;
		// -- <12> SW4이 눌러지면 flag_Sw4 = 1 으로 설정			
		if ( GPIO_PIN == GPIO_PIN_Sw4)  flag_Sw4 = 1;	
}

// -------------------------------------------------------------------------------- //
