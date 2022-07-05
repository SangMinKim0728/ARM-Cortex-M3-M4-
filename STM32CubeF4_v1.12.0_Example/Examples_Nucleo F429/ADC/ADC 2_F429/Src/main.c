
/*******************************************************************************
  
  * File name :  ADC_2 / main.c  
  
			* Application model : Nucleo_F429 Board  
  
			* Ver2.0
			* January 23. 2017
			* by Sang-min Kim, Jae-Il Kim  &  Dong-hyuk Cha
 
 ****************************************************************************** */

#include "main.h"			
#include "Nucleo_F429.h"			

// -- <1> AdcHandler, sConfig ������ �ܺ����� ������ ����
extern ADC_HandleTypeDef							AdcHandler;	
extern ADC_ChannelConfTypeDef   	Adc_sConfig; 

int adc_value;
int delay_time = 0;

// -------------------------------------------------------------------------------- //

int main(void)
{
    HAL_Init(); 
    SystemClock_Config();
    LED_Config();
    
		// -- <2> ADC�� Interrupt�� �ʱ⼳�� �Լ��� ȣ�� 
		ADC1_Interrupt_Config();  

    while (1) { }
}

// -------------------------------------------------------------------------------------//

// -- <3> ADC ���ͷ�Ʈ Callback �Լ� 
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *AdcHandler)
{
    // ADC ��ȯ ��� ���� ����
    adc_value = HAL_ADC_GetValue(AdcHandler)* 6000;

    // ��ȯ ��� ���� �����Լ��� �����Ͽ� LED On/Off ���� 
    HAL_GPIO_WritePin (GPIOExt, GPIO_PIN_All, GPIO_PIN_SET);
    for(delay_time=0; delay_time<adc_value; delay_time++);		
    HAL_GPIO_WritePin (GPIOExt, GPIO_PIN_All, GPIO_PIN_RESET);

    // for���� �̿��Ͽ� delay�ð��� 0~1000000���� ����  	
    for(delay_time=0;delay_time<1000000;delay_time++);
}

