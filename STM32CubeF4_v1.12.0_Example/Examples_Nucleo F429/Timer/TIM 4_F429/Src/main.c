
/*******************************************************************************
  
  * File name :  TIM_4 / main.c  
  
			* Application model : Nucleo_F429 Board  
  
			* Ver2.0
			* January 23. 2017
			* by Sang-min Kim, Jae-Il Kim  &  Dong-hyuk Cha
 
 ****************************************************************************** */

#include "main.h"		
#include "Nucleo_F429.h"		// Nucleo_F429 Ȯ�庸��� ��� ����

// -- <1> TimHandler, TIM_OCInit ������ �ܺ����� ������ ����
extern TIM_HandleTypeDef    TimHandle;
extern TIM_OC_InitTypeDef		TIM_OCInit;		

// -------------------------------------------------------------------------------- //
int main(void) 
{
		HAL_Init(); 
		SystemClock_Config();
		LED_Config();
		// -- <2> SW�� EXTI �Է� �߻��� ���� �ʱ⼳�� �Լ�
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
		// ���ͷ�Ʈ�� �߻��ϸ� LED�� ��� ON ��Ų��.
		HAL_GPIO_WritePin(GPIONucleo, GPIO_PIN_All, GPIO_PIN_SET );
    HAL_GPIO_WritePin(GPIOExt, GPIO_PIN_All, GPIO_PIN_SET );	
}

// -- <4>  Timer�� OC ���ͷ�Ʈ Callback �Լ�

void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim)		
{
		// ���ͷ�Ʈ�� �߻��ϸ� LED�� ��� OFF ��Ų��.
		HAL_GPIO_WritePin(GPIONucleo, GPIO_PIN_All, GPIO_PIN_RESET );
    HAL_GPIO_WritePin(GPIOExt, GPIO_PIN_All, GPIO_PIN_RESET );	
}

// -------------------------------------------------------------------------------- //
// -- <5> EXTI ���ͷ�Ʈ Callback �Լ��� ����

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_PIN)
{	
		// -- <5-1> SW1 ~ SW4�� �������� TIM_OCInit.Pulse ���� ����
	  if ( GPIO_PIN == GPIO_PIN_Nucleo_Sw) 	TIM_OCInit.Pulse =  999;	
		if ( GPIO_PIN == GPIO_PIN_Sw1) 							TIM_OCInit.Pulse =  999;	
		if ( GPIO_PIN == GPIO_PIN_Sw2)  						TIM_OCInit.Pulse = 2999;	
		if ( GPIO_PIN == GPIO_PIN_Sw3) 							TIM_OCInit.Pulse = 4999;	
		if ( GPIO_PIN == GPIO_PIN_Sw4)  						TIM_OCInit.Pulse = 9999;
	 
		// -- <5-2> TIM OC�� Channel�� TIM_OCInit�� ������ ������ �ʱ�ȭ��     
		HAL_TIM_OC_ConfigChannel(&TimHandle, &TIM_OCInit, TIM_CHANNEL_1);
		// -- <5-3> TIM OC�� ������
		HAL_TIM_OC_Start_IT(&TimHandle,TIM_CHANNEL_1);    
}

// -------------------------------------------------------------------------------- //
