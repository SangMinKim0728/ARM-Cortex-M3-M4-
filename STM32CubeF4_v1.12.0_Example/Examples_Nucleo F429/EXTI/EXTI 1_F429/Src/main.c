
/*******************************************************************************
  
  * File name :  EXTI_1 / main.c  
  
			* Application model : Nucleo_F429 Board  
  
			* Ver2.0
			* January 23. 2017
			* by Sang-min Kim, Jae-Il Kim  &  Dong-hyuk Cha
 
 ****************************************************************************** */

// ���α׷��� ���࿡ �ʿ��� ������� 
#include "main.h"		
#include "Nucleo_F429.h"		// 	Nucleo_F429  Ȯ�庸��� �������

// -- <1> ���α׷� ���࿡ �ʿ��� ���������� ����
int		flag_Sw1 =0 ;

// -------------------------------------------------------------------------------- //

int main(void) 
{
		HAL_Init(); 
		SystemClock_Config();
		LED_Config();
		// -- <2> ����ġ�� �������� EXTI�� �߻���Ű���� ����
		SwEXTI_Config();
		
		LED_OnOff(GPIO_PIN_LedAll, 500);
		
		// ���� ������ ����
		while (1)  {
					if ( flag_Sw1 == 1 )  {
							// -- <3> SW1 �� �������� LED�� ��� On/Off �ϰ�,  flag_SW1 = 0 ���� ����
							LED_OnOff(GPIO_PIN_LedAll, 500);
							flag_Sw1 = 0;
					}		
		}	
}

// -------------------------------------------------------------------------------- //
// -- <4> EXTI ���ͷ�Ʈ Callback �Լ��� ����

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_PIN)
{
	  // -- <5> Nucleo-64 ���� SW�� �������� flag_Sw1 = 1 �� ����
		if ( GPIO_PIN == GPIO_PIN_Nucleo_Sw)  flag_Sw1 = 1;	
	
	 // -- <5-1> SW1�� �������� flag_Sw1 = 1 �� ����
		if ( GPIO_PIN == GPIO_PIN_Sw1)  flag_Sw1 = 1;
}

// -------------------------------------------------------------------------------- //

