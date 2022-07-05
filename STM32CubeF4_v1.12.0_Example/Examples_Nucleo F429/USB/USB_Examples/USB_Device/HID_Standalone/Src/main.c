
/*******************************************************************************
  
  * File name :  HID_Standalone / main.c  
  
			* Application model : Nucleo_F429 Board  
  
			* Ver2.0
			* January 23. 2017
			* by Sang-min Kim, Jae-Il Kim  &  Dong-hyuk Cha
 
 ****************************************************************************** */
 

#include "main.h"
#include "Nucleo_F429.h"

// --<1> USB ����̽��� �ڵ��ϱ� ���� ����ü ������ ����
USBD_HandleTypeDef    USBD_Device;			// USB Device�� �ڵ�

uint32_t                        	Joy_Key = 0;				// ������ ����ġ �Է¿� ����

// -----------------------------------------------------------------------------

int main(void)
{
		HAL_Init(); 
		SystemClock_Config();
		LED_Config();
		Sw_Config();	
		//SwEXTI_Config();
		
		LED_OnOff(GPIO_PIN_LedAll, 1000);
		
		/* -- <2>  USB ����̽��� �ʱ�ȭ : Device stack�� �ʱ�ȭ�ϰ� class driver�� �ε��� */
		//			- USBD_Device, HID_Desc�� �ʱ�ȭ ��	
		//			- HID_Desc�� USBD_HIDDescriptorsTypeDef ����ü�� ������
			USBD_Init(&USBD_Device, &HID_Desc, 0);
		
		/* -- <3> class ����̹��� device core�� ��ũ�� */
			USBD_RegisterClass(&USBD_Device, USBD_HID_CLASS);	

		/* -- <4> USB Device ������ ������ */
			USBD_Start(&USBD_Device);  											
		
		/* -- <5> Infinite loop */
			while (1) {
					 
					// -- <5-1> Nucleo SW�� �������� ���
					if (HAL_GPIO_ReadPin(GPIOSwNucleo, GPIO_PIN_Nucleo_Sw ) == SET) {
										HAL_GPIO_TogglePin(GPIOExt, GPIO_PIN_Led1 );		// LED1 ����							
										Joy_Key = JOY_LEFT;													// ���콺 ��������  ����							
					}
					// -- <5-2> Key1 �� �������� ���
					else if (HAL_GPIO_ReadPin(GPIOSw1, GPIO_PIN_Sw1 ) == RESET) {         
										HAL_GPIO_TogglePin(GPIOExt, GPIO_PIN_Led1 );		// LED1 ����		
										Joy_Key = JOY_LEFT;													// ���콺 ��������  ����							
					}
						
						// -- <5-3> Key2 �� �������� ���					
					else if (HAL_GPIO_ReadPin(GPIOSw2, GPIO_PIN_Sw2 ) ==  RESET)  {       
										HAL_GPIO_TogglePin(GPIOExt, GPIO_PIN_Led2);			// LED2 ����		
										Joy_Key = JOY_UP;													// ���콺 �������� ����
					}
						
					// -- <5-5> Key3 �� �������� ���
					else if ( HAL_GPIO_ReadPin(GPIOSw3, GPIO_PIN_Sw3 ) == RESET)   {    
										HAL_GPIO_TogglePin(GPIOExt, GPIO_PIN_Led3  );		// LED3 ����			
										Joy_Key = JOY_DOWN;												// ���콺 �Ʒ�������  ����
					}
						
					// -- <5-6> Key4 �� �������� ���
					else if (HAL_GPIO_ReadPin(GPIOSw4, GPIO_PIN_Sw4 ) == RESET)  { 
										HAL_GPIO_TogglePin(GPIOExt, GPIO_PIN_Led4  );		// LED4 ����		
										Joy_Key = JOY_RIGHT;												// ���콺 ���������� ����
					}
						
					// -- <5-6>Key�� �������� ���� ���	
					else
										Joy_Key = JOY_NONE;       
			}  
}

// -----------------------------------------------------------------------------
/* -- <6> LED 8�� Toggle�� ��� ON/OFF �ϴ� �Լ�
 *			-- ���α׷��� �����ϸ� LED8�� ��� ON/OFF �Ѵ�.
 */

void Toggle_LED(void)
{
  static uint32_t ticks;

  if (ticks++ == 100) {
			// -- <6-1> tick = 100�϶� (��, 100msec ��������) LED 8�� toggle ��Ŵ 
				HAL_GPIO_TogglePin(GPIOExt, GPIO_PIN_Led8);	  
				ticks = 0;
  }	
}

// ----------------------------------------------------------------------------- //

