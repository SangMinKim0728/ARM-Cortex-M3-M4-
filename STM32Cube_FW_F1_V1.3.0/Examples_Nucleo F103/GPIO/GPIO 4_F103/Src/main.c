
/*******************************************************************************
  
  * File name :  GPIO_3 / main.c  
  
			* Application model : Nucleo_F103 Board  
  
			* Ver4.0
			* January 23. 2017
			* by Sang-min Kim, Jae-Il Kim  &  Dong-hyuk Cha
 
 ****************************************************************************** */

// -- <1> ���α׷��� ���࿡ �ʿ��� ������� 
#include "main.h"		
#include "Nucleo_F103.h"		// 	Nucleo_F103 ���� ����� ���� ��� ����

// -------------------------------------------------------------------------------- //

int main(void) 
{	
		// -- <2> LED�� On/Off �ϱ� ���� ����  (0x01 = 0000 0001) 
		uint16_t led = 0x01;
		
		// -- <3> MCU�� �ʱ�ȭ �Լ�
		HAL_Init(); 	
		// -- <4> system clock�� �ʱ�ȭ �Լ�
		SystemClock_Config();	
		// --<5>  �ǽ������� ��¿� LED�� �ʱ�ȭ �Լ�	
		LED_Config();
		// --<6>  �ǽ������� �Է¿� Switch�� �ʱ�ȭ �Լ�	
		Sw_Config();

		LED_OnOff(GPIO_PIN_LedAll, 500);
		
		// -- <7> ���� ������ ����
		while (1) {
				// -- <8>  ���� led �� 0���� �ʱ�ȭ
				led = 0x00;
			
				// -- <9-1> SW1 �� �������� -> led �� 1, 2��° bit �� 1�� ���� (0x03 = 0000 0011)
				if( HAL_GPIO_ReadPin(GPIOSw1, GPIO_PIN_Sw1 ) ==  RESET )  led = led | 0x03; 
				
				// -- <9-2> SW2 �� �������� -> led �� 3, 4��° bit �� 1�� ���� (0x0c = 0000 1100)
				if( HAL_GPIO_ReadPin(GPIOSw2, GPIO_PIN_Sw2 ) ==  RESET )  led = led | 0x0c; 
				
				// -- <9-3> SW3 �� �������� -> led �� 5, 6��° bit �� 1�� ����  (0x30 = 0011 0000)
				if( HAL_GPIO_ReadPin(GPIOSw3, GPIO_PIN_Sw3 ) ==  RESET )  led = led | 0x30; 
				
				// -- <9-4> SW4 �� �������� -> led �� 7, 8��° bit �� 1�� ����  (0xc0 = 1100 0000)
				if( HAL_GPIO_ReadPin(GPIOSw4, GPIO_PIN_Sw4 ) ==  RESET )  led = led | 0xc0; 
				
				 // -- <10> ���� led�� �ش��ϴ� LED�� ON�� �Ŀ� �ٽ� OFF �� 
				LED_OnOff(led, 100);	
		}		
}

// -------------------------------------------------------------------------------- //

