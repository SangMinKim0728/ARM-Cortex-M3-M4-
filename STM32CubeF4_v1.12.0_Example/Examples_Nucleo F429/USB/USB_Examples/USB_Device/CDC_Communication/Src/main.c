
/*******************************************************************************
  
  * File name :  CDC_Communication / main.c  
  
			* Application model : Nucleo_F429 Board  
  
			* Ver2.0
			* January 23. 2017
			* by Sang-min Kim, Jae-Il Kim  &  Dong-hyuk Cha
 
 ****************************************************************************** */
 
 
#include "main.h"
#include "Nucleo_F429.h"	

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
// --<1> USB ����̽��� �ڵ��ϱ� ���� ����ü ������ ����
USBD_HandleTypeDef  USBD_Device;

/* Private functions ---------------------------------------------------------*/ 

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
  HAL_Init();
	SystemClock_Config();
	LED_Config();
	SwEXTI_Config();	
	
	LED_OnOff(GPIO_PIN_LedAll, 1000);
  
  /* -- <2> Device stack�� �ʱ�ȭ�ϰ� class driver�� �ε��� */
  //			- USBD_Device, VCP_Desc�� �ʱ�ȭ ��	
  //			- VCP_Desc�� USBD_DescriptorsTypeDef ����ü�� ������
  USBD_Init(&USBD_Device, &VCP_Desc, 0);
  
  /* -- <3> class ����̹��� device core�� ��ũ�� */
   USBD_RegisterClass(&USBD_Device, USBD_CDC_CLASS);
  
  /* -- <4> CDC Interface Class�� ��� -> CDC_Itf_Init() �Լ��� ����� */
  //			-  USBD_CDC_fops ����ü ���� CDC_Itf_Init() �Լ��� ����
  USBD_CDC_RegisterInterface(&USBD_Device, &USBD_CDC_fops);
  
  /* -- <5> USB Device ������ ������ */
  USBD_Start(&USBD_Device);
  
  /* Run Application (Interrupt mode) */
  while (1)
  {  }
}

/* -------------------------------------------------------------------*/
/* -- <7> LED�� ������ �ִ� �Լ�
                ���α׷��� ����Ǵ� �߿��� ��� LED�� ������ �ش�.
				- LED 6, 7 : ��� On �Ǿ� ����
				- LED 5, 8 : On/Off�� �ݺ���
 */

void Toggle_Leds(void)
{
  static uint32_t ticks;
  if (ticks++ == 100)  {
  // -- <7-1> 100msec ���ݸ��� �Ʒ��� �۾��� �ݺ���
		HAL_GPIO_TogglePin(GPIOExt, GPIO_PIN_Led5);
		HAL_GPIO_WritePin   (GPIOExt, GPIO_PIN_Led6, GPIO_PIN_SET );
		HAL_GPIO_WritePin   (GPIOExt, GPIO_PIN_Led7, GPIO_PIN_SET );
		HAL_GPIO_TogglePin(GPIOExt, GPIO_PIN_Led8);
		ticks = 0;
  }
}

/* -------------------------------------------------------------------*/
