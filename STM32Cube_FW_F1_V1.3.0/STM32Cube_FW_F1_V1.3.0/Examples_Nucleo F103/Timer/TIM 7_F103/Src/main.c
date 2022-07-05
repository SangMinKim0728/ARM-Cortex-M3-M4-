
/*******************************************************************************
  
  * File name :  TIM_7 / main.c  
  
			* Application model : Nucleo_F103 Board  
  
			* Ver2.0
			* January 23. 2017
			* by Sang-min Kim, Jae-Il Kim  &  Dong-hyuk Cha
 
 ****************************************************************************** */

#include "main.h"		
#include "Nucleo_F103.h"		// Nucleo-F103 Ȯ�庸��� ��� ����

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
		TIM2_Config(6399,9999);	
		TIM_PWM_IT_Config(999);
	
		LED_OnOff(GPIO_PIN_LedAll, 500);
	
		while (1)  { }
}		

// -------------------------------------------------------------------------------- //

// -- <1> TIM ���ͷ�Ʈ TIM_BASE ���ͷ�Ʈ Callback �Լ�
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)  
{
		HAL_GPIO_WritePin(GPIONucleo, GPIO_PIN_All, GPIO_PIN_SET );
		HAL_GPIO_WritePin(GPIOExt, GPIO_PIN_All, GPIO_PIN_SET );	
}

// -- <2> TIM ���ͷ�Ʈ TIM PWM ���ͷ�Ʈ callback �Լ�
void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)		
{
		HAL_GPIO_WritePin(GPIONucleo, GPIO_PIN_All, GPIO_PIN_RESET );
		HAL_GPIO_WritePin(GPIOExt, GPIO_PIN_All, GPIO_PIN_RESET );
}

// -------------------------------------------------------------------------------- //
