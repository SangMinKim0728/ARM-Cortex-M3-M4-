
/*******************************************************************************
  
  * File name :  DAC_1 / main.c  
  
			* Application model : Nucleo_F429 Board  
  
			* Ver2.0
			* January 23. 2017
			* by Sang-min Kim, Jae-Il Kim  &  Dong-hyuk Cha
 
 ****************************************************************************** */

#include "main.h"			
#include "Nucleo_F429.h"	  // Nucleo-F429 Ȯ�庸��� ��� ����	

// -- <1> DacHandler, sConfig ������ �ܺ����� ������ ����
extern DAC_HandleTypeDef								DacHandler;	
extern DAC_ChannelConfTypeDef			Dac_sConfig;
int dac_value =  0;

// -------------------------------------------------------------------------------- //

int main(void)
{
    HAL_Init(); 
    SystemClock_Config();
		LED_Config();

    // -- <3> DAC�� �ʱ⼳���� �Լ��� ȣ�� 
    DAC_Config();
	
		LED_OnOff(GPIO_PIN_LedAll, 500);

    // -- <4> ���� ����
    while (1)  
   {
					// -- <5> for������ DAC ���� ��(0x00 ~ 0xff)�� ����	
					for(dac_value = 0; dac_value<=255; dac_value++) 
					{
							// -- <6> DAC Channel 1���� ��ü���� ������ �������� ���� ����
							HAL_DAC_SetValue(&DacHandler, DAC_CHANNEL_1, DAC_ALIGN_8B_R, dac_value);

							// -- <7> DAC�� Ȱ��ȭ�ϰ� ��ȯ�� ����
							HAL_DAC_Start(&DacHandler, DAC_CHANNEL_1);

							// -- <8> 5ms Delay �Լ�
							HAL_Delay(5);
					}
    }
}

// -------------------------------------------------------------------------------- //

