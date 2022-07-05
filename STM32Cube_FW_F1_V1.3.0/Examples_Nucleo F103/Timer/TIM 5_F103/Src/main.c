
/*******************************************************************************
  
  * File name :  TIM_5 / main.c  
  
			* Application model : Nucleo_F103 Board  
  
			* Ver2.0
			* January 23. 2017
			* by Sang-min Kim, Jae-Il Kim  &  Dong-hyuk Cha
 
 ****************************************************************************** */

#include "main.h"		
#include "Nucleo_F103.h"		// Nucleo_F103 Ȯ�庸��� ��� ����

// TimHandler, TIM_OCInit ������ �ܺ����� ������ ����
extern TIM_HandleTypeDef		TimHandle;					
extern TIM_OC_InitTypeDef		TIM_OCInit;					

// -------------------------------------------------------------------------------- //
int main(void) 
{
		HAL_Init(); 
		SystemClock_Config();
		LED_Config();
		SwEXTI_Config();	
		TIM2_Config(0,9999);	
		TIM_OC_Config(9999);	
		
		LED_OnOff(GPIO_PIN_LedAll, 500);

	  // ���� ������ ��� ����
		while (1)  { }	
}		

// -------------------------------------------------------------------------------- //
// -- <3> Timer�� TIM_Base ���ͷ�Ʈ Callback �Լ�

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)  
{
		HAL_GPIO_WritePin(GPIOExt, GPIO_PIN_Led1 | GPIO_PIN_Led2
													| GPIO_PIN_Led7 | GPIO_PIN_Led8, GPIO_PIN_SET );	
}

// -------------------------------------------------------------------------------- //
// -- <4>  Timer�� OC ���ͷ�Ʈ Callback �Լ�

void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim)		
{		
		// -- <4-1>  CHANNEL_1���� ���ͷ�Ʈ�� �߻��� ���
		if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1) {
			  HAL_GPIO_WritePin(GPIOExt, GPIO_PIN_Led1 | GPIO_PIN_Led2, GPIO_PIN_RESET);
		}

		// <4-2>  CHANNEL_2���� ���ͷ�Ʈ�� �߻��� ���
		if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2) {
			  HAL_GPIO_WritePin(GPIOExt, GPIO_PIN_Led7 | GPIO_PIN_Led8, GPIO_PIN_RESET);
		}
}

// -------------------------------------------------------------------------------- //
// -- <5>  EXTI ���ͷ�Ʈ Callback �Լ��� ����

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_PIN)
{

		// -- <5-1> SW1�� �������� channel 1, 2�� TIM_OCInit.Pulse = 9999�� ����
		if ( GPIO_PIN == GPIO_PIN_Sw1 ) {
				TIM_OCInit.Pulse = 9999;
				HAL_TIM_OC_ConfigChannel(&TimHandle, &TIM_OCInit, TIM_CHANNEL_1);
				HAL_TIM_OC_ConfigChannel(&TimHandle, &TIM_OCInit, TIM_CHANNEL_2);
		}

		// -- <5-2> SW2�� �������� channel 1�� TIM_OCInit.Pulse = 2500���� ����	
		else if ( GPIO_PIN == GPIO_PIN_Sw2 ) {
				TIM_OCInit.Pulse = 2500;
				HAL_TIM_OC_ConfigChannel(&TimHandle, &TIM_OCInit, TIM_CHANNEL_1);
		}

		// -- <5-3> SW3�� �������� channel 2�� TIM_OCInit.Pulse = 5000���� ����
		else if ( GPIO_PIN == GPIO_PIN_Sw3 ) {
				TIM_OCInit.Pulse = 5000;
				HAL_TIM_OC_ConfigChannel(&TimHandle, &TIM_OCInit, TIM_CHANNEL_2);
		}

		// -- <5-4> SW4�� �������� channel 2�� TIM_OCInit.Pulse = 1200���� ����	
		else if ( GPIO_PIN == GPIO_PIN_Sw4 ) {
				TIM_OCInit.Pulse = 1200;
				HAL_TIM_OC_ConfigChannel(&TimHandle, &TIM_OCInit, TIM_CHANNEL_2);
		}    
}

// -------------------------------------------------------------------------------- //
