
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
// --<1> USB 디바이스를 핸들하기 위한 구조체 변수를 선언
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
  
  /* -- <2> Device stack을 초기화하고 class driver를 로드함 */
  //			- USBD_Device, VCP_Desc를 초기화 함	
  //			- VCP_Desc는 USBD_DescriptorsTypeDef 구조체형 변수임
  USBD_Init(&USBD_Device, &VCP_Desc, 0);
  
  /* -- <3> class 드라이버를 device core에 링크함 */
   USBD_RegisterClass(&USBD_Device, USBD_CDC_CLASS);
  
  /* -- <4> CDC Interface Class를 등록 -> CDC_Itf_Init() 함수가 실행됨 */
  //			-  USBD_CDC_fops 구조체 내에 CDC_Itf_Init() 함수가 있음
  USBD_CDC_RegisterInterface(&USBD_Device, &USBD_CDC_fops);
  
  /* -- <5> USB Device 동작을 시작함 */
  USBD_Start(&USBD_Device);
  
  /* Run Application (Interrupt mode) */
  while (1)
  {  }
}

/* -------------------------------------------------------------------*/
/* -- <7> LED를 깜빡여 주는 함수
                프로그램이 수행되는 중에는 계속 LED를 깜빡여 준다.
				- LED 6, 7 : 계속 On 되어 있음
				- LED 5, 8 : On/Off를 반복함
 */

void Toggle_Leds(void)
{
  static uint32_t ticks;
  if (ticks++ == 100)  {
  // -- <7-1> 100msec 간격마다 아래의 작업이 반복됨
		HAL_GPIO_TogglePin(GPIOExt, GPIO_PIN_Led5);
		HAL_GPIO_WritePin   (GPIOExt, GPIO_PIN_Led6, GPIO_PIN_SET );
		HAL_GPIO_WritePin   (GPIOExt, GPIO_PIN_Led7, GPIO_PIN_SET );
		HAL_GPIO_TogglePin(GPIOExt, GPIO_PIN_Led8);
		ticks = 0;
  }
}

/* -------------------------------------------------------------------*/
