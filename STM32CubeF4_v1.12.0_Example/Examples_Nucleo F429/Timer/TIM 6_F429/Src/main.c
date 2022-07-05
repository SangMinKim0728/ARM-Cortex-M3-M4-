
/*******************************************************************************
  
  * File name :  TIM_6 / main.c  
  
			* Application model : Nucleo_F429 Board  
  
			* Ver2.0
			* January 23. 2017
			* by Sang-min Kim, Jae-Il Kim  &  Dong-hyuk Cha
 
 ****************************************************************************** */

#include "main.h"		
#include "Nucleo_F429.h"		// Nucleo_F429 Ȯ�庸��� ��� ����

// -- <1> �ֺ���ġ �ʱ�ȭ�� ����ü
GPIO_InitTypeDef				GPIO_Init; 
TIM_HandleTypeDef		TimHandler;					
TIM_OC_InitTypeDef		TIM_OC;					

// -------------------------------------------------------------------------------- //

int main(void) 
{
		HAL_Init(); 
		SystemClock_Config();
	
		// -- <2> GPIOA�� Ŭ���� enable		
		__HAL_RCC_GPIOA_CLK_ENABLE();
	
		// -- <3> �߰� LED ���� ������ ����
		GPIO_Init.Pin		= GPIO_PIN_6;						// GPIO���������PIN ����
		GPIO_Init.Mode  = GPIO_MODE_AF_PP; 			// Output Push-Pull ���
		GPIO_Init.Pull  = GPIO_PULLUP; 					// Pull Up ���
		GPIO_Init.Speed = GPIO_SPEED_FREQ_HIGH; 	// ���ۼӵ���HIGH��
	
		// -- <4> GPIOA�� GPIO_Init�� ������ �������� �ʱ�ȭ��
		HAL_GPIO_Init(GPIOA, &GPIO_Init);  
	
		LED_Config();
		SwEXTI_Config();		
		TIM3_Config(0,9999);
		TIM_PWM_Poll_Config(9999);
	
		LED_OnOff(GPIO_PIN_LedAll, 500);
	
		while (1)  { }
}	

// -------------------------------------------------------------------------------- //

// -- <11> EXTI ���ͷ�Ʈ�� TIM PWM ���� ������ ����
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_PIN)
{
		// -- <11-1> SW1 ~ SW4�� �������� TIM_OCInit.Pulse ���� ���� 
		if ( GPIO_PIN == GPIO_PIN_Sw1) 	TIM_OC.Pulse = 999;
	
		if ( GPIO_PIN == GPIO_PIN_Sw2)  TIM_OC.Pulse = 2999;
	
		if ( GPIO_PIN == GPIO_PIN_Sw3) 	TIM_OC.Pulse = 4999;
	
		if ( GPIO_PIN == GPIO_PIN_Sw4)  TIM_OC.Pulse = 9999;

		// -- <11-2> TIM PWM�� Channel�� TIM_OCInit�� ������ ������ �ʱ�ȭ ��
		HAL_TIM_PWM_ConfigChannel(&TimHandler, &TIM_OC, TIM_CHANNEL_1);

		// -- <11-3> TIM PWM�� ������
		HAL_TIM_PWM_Start(&TimHandler,TIM_CHANNEL_1);
}

// -------------------------------------------------------------------------------- //
