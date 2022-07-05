
/*******************************************************************************
  
  * File name :  ADC_1 / main.c  
  
			* Application model : Nucleo_F103 Board  
  
			* Ver2.0
			* January 23. 2017
			* by Sang-min Kim, Jae-Il Kim  &  Dong-hyuk Cha
 
 ****************************************************************************** */

#include "main.h"			
#include "Nucleo_F103.h"			

// -- <1> AdcHandler, sConfig 변수를 외부정의 변수로 선언
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
	
    // -- <2> ADC의 초기설정용 함수를 호출 
    ADC1_Polling_Config();   

    // -- <3> 폴링으로 ADC값 입력받기 
    while (1) 
    {
					// -- <4> 설정된 sConfig와 AdcHandler를 연관지어 초기화 함
					HAL_ADC_ConfigChannel(&AdcHandler, &Adc_sConfig);

					// -- <5> ADC를 동작시킴
					HAL_ADC_Start(&AdcHandler);
					
					// -- <6> 변환이 완료될 때까지 대기
					HAL_ADC_PollForConversion(&AdcHandler, 10);
					
					// -- <7> ADC 변환 결과 값을 저장 
					adc_value = HAL_ADC_GetValue(&AdcHandler)* 6000;
					
					// -- <8> 변환 결과 값을 지연함수로 구현하여 LED On/Off 제어 
					HAL_GPIO_WritePin (GPIOExt, GPIO_PIN_All, GPIO_PIN_SET);
					for(delay_time=0; delay_time<adc_value; delay_time++);
					HAL_GPIO_WritePin (GPIOExt, GPIO_PIN_All, GPIO_PIN_RESET);

					// -- <9> for문을 이용하여 delay시간을 0~1000000까지 구현  			
					for(delay_time=0; delay_time<1000000; delay_time++);
    }
}

// -------------------------------------------------------------------------------- //
