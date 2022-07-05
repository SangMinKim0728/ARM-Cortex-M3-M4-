
/*******************************************************************************
  
  * File name :  EXTI_3 / main.c  
  
			* Application model : Nucleo_F429 Board  
  
			* Ver2.0
			* January 23. 2017
			* by Sang-min Kim, Jae-Il Kim  &  Dong-hyuk Cha
 
 ****************************************************************************** */

// ���α׷��� ���࿡ �ʿ��� ������� 
#include "main.h"		
#include "Nucleo_F429.h"		// 	Nucleo-F429 Ȯ�庸��� ��� ����

// -- <1> ���α׷� ���࿡ �ʿ��� ���������� ����
int	flag_Sw1, flag_Sw2, flag_Sw3, flag_Sw4;

// -------------------------------------------------------------------------------- //

int main(void) 
{
		// -- <2> LED�� �ѱ����� ����
		uint16_t  led = 0x01;	

		HAL_Init(); 
		SystemClock_Config();
		LED_Config();
		// -- <3> ����ġ�� �������� EXTI�� �߻���Ű���� ����
		SwEXTI_Config();
		
		LED_OnOff(GPIO_PIN_LedAll, 500);
		
		// ���� ������ ����
		while (1)  {
				led = 0x00;					// ���� led�� �ʱ�ȭ
					
				// -- <4> SW1 �� �������� -> led �� 1, 2��° bit �� 1�� ���� (0x03 = 0000 0011)
				if ( flag_Sw1 == 1 )  {
								led = led | 0x03;
								LED_OnOff(led, 300);
								flag_Sw1 = 0;
				}				
				// -- <5> SW2 �� �������� -> led �� 3, 4��° bit �� 1�� ���� (0x0c = 0000 1100)
				if ( flag_Sw2 == 1 )  {
								led = led | 0x0c;
								LED_OnOff(led, 300);
								flag_Sw2 = 0;
				}				
				// -- <6> SW3 �� �������� -> led �� 5, 6��° bit �� 1�� ����  (0x30 = 0011 0000)
				if ( flag_Sw3 == 1 )  {
								led = led | 0x30;
								LED_OnOff(led, 300);
								flag_Sw3 = 0;
				}				
				// -- <7> SW4 �� �������� -> led �� 7, 8��° bit �� 1�� ����  (0xc0 = 1100 0000)
				if ( flag_Sw4 == 1 )  {
								led = led | 0xc0; 
								LED_OnOff(led, 300);
								flag_Sw4 = 0;
				}		
		}	
}

// -------------------------------------------------------------------------------- //
// -- <8> EXTI ���ͷ�Ʈ Callback �Լ��� ����

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_PIN)
{
		// -- <9> SW1�� �������� flag_Sw1 = 1 ���� ����	
		if ( GPIO_PIN == GPIO_PIN_Sw1)  flag_Sw1 = 1;
		// -- <10> SW2�� �������� flag_Sw2 = 1 ���� ����			
		if ( GPIO_PIN == GPIO_PIN_Sw2)  flag_Sw2 = 1;
		// -- <11> SW3�� �������� flag_Sw3 = 1 ���� ����			
		if ( GPIO_PIN == GPIO_PIN_Sw3)  flag_Sw3 = 1;
		// -- <12> SW4�� �������� flag_Sw4 = 1 ���� ����			
		if ( GPIO_PIN == GPIO_PIN_Sw4)  flag_Sw4 = 1;	
}

// -------------------------------------------------------------------------------- //
