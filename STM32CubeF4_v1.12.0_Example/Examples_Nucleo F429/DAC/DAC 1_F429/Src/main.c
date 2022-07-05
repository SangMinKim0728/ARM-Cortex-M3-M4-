
/*******************************************************************************
  
  * File name :  DAC_1 / main.c  
  
			* Application model : Nucleo_F429 Board  
  
			* Ver2.0
			* January 23. 2017
			* by Sang-min Kim, Jae-Il Kim  &  Dong-hyuk Cha
 
 ****************************************************************************** */

#include "main.h"			
#include "Nucleo_F429.h"	  // Nucleo-F429 확장보드용 헤더 파일	

// -- <1> DacHandler, sConfig 변수를 외부정의 변수로 선언
extern DAC_HandleTypeDef								DacHandler;	
extern DAC_ChannelConfTypeDef			Dac_sConfig;
int dac_value =  0;

// -------------------------------------------------------------------------------- //

int main(void)
{
    HAL_Init(); 
    SystemClock_Config();
		LED_Config();

    // -- <3> DAC의 초기설정용 함수를 호출 
    DAC_Config();
	
		LED_OnOff(GPIO_PIN_LedAll, 500);

    // -- <4> 무한 루프
    while (1)  
   {
					// -- <5> for문으로 DAC 설정 값(0x00 ~ 0xff)을 변경	
					for(dac_value = 0; dac_value<=255; dac_value++) 
					{
							// -- <6> DAC Channel 1번에 구체적인 데이터 레지스터 값을 설정
							HAL_DAC_SetValue(&DacHandler, DAC_CHANNEL_1, DAC_ALIGN_8B_R, dac_value);

							// -- <7> DAC를 활성화하고 변환을 시작
							HAL_DAC_Start(&DacHandler, DAC_CHANNEL_1);

							// -- <8> 5ms Delay 함수
							HAL_Delay(5);
					}
    }
}

// -------------------------------------------------------------------------------- //

