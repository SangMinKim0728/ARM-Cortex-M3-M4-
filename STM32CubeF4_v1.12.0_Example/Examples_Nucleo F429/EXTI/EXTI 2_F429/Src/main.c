
/*******************************************************************************
  
  * File name :  EXTI_2 / main.c  
  
			* Application model : Nucleo_F429 Board  
  
			* Ver2.0
			* January 23. 2017
			* by Sang-min Kim, Jae-Il Kim  &  Dong-hyuk Cha
 
 ****************************************************************************** */

// ���α׷��� ���࿡ �ʿ��� ������� 
#include "main.h"		
#include "Nucleo_F429.h"		// 	Nucleo-F429 Ȯ�庸��� ��� ����

// -- <1> ���α׷� ���࿡ �ʿ��� ���������� ����
int	flag_Sw1 = 0, flag_Sw2 = 0;

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
				// -- <4> SW1 �� �������� -> LED�� 1�� �� 2�� �� 3�� �� �� �� 8�� ������ �����ϴ� ������ �ݺ�
				if ( flag_Sw1 == 1 )  {
						led <<= 1;
						if ( led > 0x80 ) led = 0x01;
						LED_OnOff(led, 100);			
				}
				
				// -- <5> SW2 �� �������� -> LED�� 8�� �� 7�� �� �� �� 1�� ������ �����ϴ� ������ �ݺ�
				else if ( flag_Sw2 == 1 )  {
						led >>= 1; 
						if ( led < 0x01 ) led = 0x80;
						LED_OnOff(led, 100);
				}		
		}	
}

// -------------------------------------------------------------------------------- //
// -- <6> EXTI ���ͷ�Ʈ Callback �Լ��� ����

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_PIN)
{
		// -- <7> SW1�� �������� flag_Sw1 = 1 , flag_Sw2 =  0 ���� ����	
		if ( GPIO_PIN == GPIO_PIN_Sw1)  {
				flag_Sw1 = 1;
				flag_Sw2 = 0;
		}

		// -- <8> SW2�� �������� flag_Sw1 = 0 , flag_Sw2 =  1 �� ����		
		else if ( GPIO_PIN == GPIO_PIN_Sw2)  {
				flag_Sw1 = 0;
				flag_Sw2 = 1;
		}	
}

// -------------------------------------------------------------------------------- //
