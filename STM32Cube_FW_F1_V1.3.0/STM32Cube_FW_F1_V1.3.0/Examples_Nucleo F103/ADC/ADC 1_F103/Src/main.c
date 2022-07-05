
/*******************************************************************************
  
  * File name :  ADC_1 / main.c  
  
			* Application model : Nucleo_F103 Board  
  
			* Ver2.0
			* January 23. 2017
			* by Sang-min Kim, Jae-Il Kim  &  Dong-hyuk Cha
 
 ****************************************************************************** */

#include "main.h"			
#include "Nucleo_F103.h"			

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
	
    // -- <2> ADC�� �ʱ⼳���� �Լ��� ȣ�� 
    ADC1_Polling_Config();   

    // -- <3> �������� ADC�� �Է¹ޱ� 
    while (1) 
    {
					// -- <4> ������ sConfig�� AdcHandler�� �������� �ʱ�ȭ ��
					HAL_ADC_ConfigChannel(&AdcHandler, &Adc_sConfig);

					// -- <5> ADC�� ���۽�Ŵ
					HAL_ADC_Start(&AdcHandler);
					
					// -- <6> ��ȯ�� �Ϸ�� ������ ���
					HAL_ADC_PollForConversion(&AdcHandler, 10);
					
					// -- <7> ADC ��ȯ ��� ���� ���� 
					adc_value = HAL_ADC_GetValue(&AdcHandler)* 6000;
					
					// -- <8> ��ȯ ��� ���� �����Լ��� �����Ͽ� LED On/Off ���� 
					HAL_GPIO_WritePin (GPIOExt, GPIO_PIN_All, GPIO_PIN_SET);
					for(delay_time=0; delay_time<adc_value; delay_time++);
					HAL_GPIO_WritePin (GPIOExt, GPIO_PIN_All, GPIO_PIN_RESET);

					// -- <9> for���� �̿��Ͽ� delay�ð��� 0~1000000���� ����  			
					for(delay_time=0; delay_time<1000000; delay_time++);
    }
}

// -------------------------------------------------------------------------------- //
