
/*******************************************************************************
  
  * File name :  HID_Standalone / main.c  
  
			* Application model : Nucleo_F429 Board  
  
			* Ver2.0
			* January 23. 2017
			* by Sang-min Kim, Jae-Il Kim  &  Dong-hyuk Cha
 
 ****************************************************************************** */
 

#include "main.h"
#include "Nucleo_F429.h"

// --<1> USB 디바이스를 핸들하기 위한 구조체 변수를 선언
USBD_HandleTypeDef    USBD_Device;			// USB Device용 핸들

uint32_t                        	Joy_Key = 0;				// 보드의 스위치 입력용 변수

// -----------------------------------------------------------------------------

int main(void)
{
		HAL_Init(); 
		SystemClock_Config();
		LED_Config();
		Sw_Config();	
		//SwEXTI_Config();
		
		LED_OnOff(GPIO_PIN_LedAll, 1000);
		
		/* -- <2>  USB 디바이스를 초기화 : Device stack을 초기화하고 class driver를 로드함 */
		//			- USBD_Device, HID_Desc를 초기화 함	
		//			- HID_Desc는 USBD_HIDDescriptorsTypeDef 구조체형 변수임
			USBD_Init(&USBD_Device, &HID_Desc, 0);
		
		/* -- <3> class 드라이버를 device core에 링크함 */
			USBD_RegisterClass(&USBD_Device, USBD_HID_CLASS);	

		/* -- <4> USB Device 동작을 시작함 */
			USBD_Start(&USBD_Device);  											
		
		/* -- <5> Infinite loop */
			while (1) {
					 
					// -- <5-1> Nucleo SW가 눌러지는 경우
					if (HAL_GPIO_ReadPin(GPIOSwNucleo, GPIO_PIN_Nucleo_Sw ) == SET) {
										HAL_GPIO_TogglePin(GPIOExt, GPIO_PIN_Led1 );		// LED1 반전							
										Joy_Key = JOY_LEFT;													// 마우스 왼쪽으로  설정							
					}
					// -- <5-2> Key1 이 눌러지는 경우
					else if (HAL_GPIO_ReadPin(GPIOSw1, GPIO_PIN_Sw1 ) == RESET) {         
										HAL_GPIO_TogglePin(GPIOExt, GPIO_PIN_Led1 );		// LED1 반전		
										Joy_Key = JOY_LEFT;													// 마우스 왼쪽으로  설정							
					}
						
						// -- <5-3> Key2 이 눌러지는 경우					
					else if (HAL_GPIO_ReadPin(GPIOSw2, GPIO_PIN_Sw2 ) ==  RESET)  {       
										HAL_GPIO_TogglePin(GPIOExt, GPIO_PIN_Led2);			// LED2 반전		
										Joy_Key = JOY_UP;													// 마우스 위쪽으로 설정
					}
						
					// -- <5-5> Key3 이 눌러지는 경우
					else if ( HAL_GPIO_ReadPin(GPIOSw3, GPIO_PIN_Sw3 ) == RESET)   {    
										HAL_GPIO_TogglePin(GPIOExt, GPIO_PIN_Led3  );		// LED3 반전			
										Joy_Key = JOY_DOWN;												// 마우스 아래쪽으로  설정
					}
						
					// -- <5-6> Key4 이 눌러지는 경우
					else if (HAL_GPIO_ReadPin(GPIOSw4, GPIO_PIN_Sw4 ) == RESET)  { 
										HAL_GPIO_TogglePin(GPIOExt, GPIO_PIN_Led4  );		// LED4 반전		
										Joy_Key = JOY_RIGHT;												// 마우스 오른쪽으로 설정
					}
						
					// -- <5-6>Key가 눌러지지 않은 경우	
					else
										Joy_Key = JOY_NONE;       
			}  
}

// -----------------------------------------------------------------------------
/* -- <6> LED 8을 Toggle로 계속 ON/OFF 하는 함수
 *			-- 프로그램이 동작하면 LED8은 계속 ON/OFF 한다.
 */

void Toggle_LED(void)
{
  static uint32_t ticks;

  if (ticks++ == 100) {
			// -- <6-1> tick = 100일때 (즉, 100msec 간격으로) LED 8을 toggle 시킴 
				HAL_GPIO_TogglePin(GPIOExt, GPIO_PIN_Led8);	  
				ticks = 0;
  }	
}

// ----------------------------------------------------------------------------- //

