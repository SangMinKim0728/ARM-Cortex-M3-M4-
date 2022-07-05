
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

			  // -- <9> Nucleo SW�� �������� -> led ��ü bit �� 1�� ���� (0xFF = 1111 1111)
				if( HAL_GPIO_ReadPin(GPIOSwNucleo, GPIO_PIN_Nucleo_Sw ) ==  RESET )  led = led | 0xFF; 
			
				// -- <9-1> SW1 �� �������� -> led ��ü bit �� 1�� ���� (0xFF = 1111 1111)
				if( HAL_GPIO_ReadPin(GPIOSw1, GPIO_PIN_Sw1 ) ==  RESET )  led = led | 0xFF; 
				
				 // -- <10> ���� led�� �ش��ϴ� LED�� ON�� �Ŀ� �ٽ� OFF �� 
				LED_OnOff(led, 100);	
		}		
}

// -------------------------------------------------------------------------------- //

