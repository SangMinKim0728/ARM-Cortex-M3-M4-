/**
  ******************************************************************************
  * @file    USB_Device/HID_Standalone/Src/stm32f1xx_it.c 

  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
   */

#include "main.h"
#include "Nucleo_F429.h"
#include "stm32f4xx_it.h"

// -- <1> Key를 누를때 Mouse 커서의 이동량을 5 로 정의함
#define CURSOR_STEP     5

extern void Toggle_Leds(void);

extern USBD_HandleTypeDef		USBD_Device;
extern PCD_HandleTypeDef		hpcd;
extern uint32_t							Joy_Key;

// -- <2> 마우스의 이동량을 저장하는 변수
uint8_t     				HID_Buffer[4];

static void GetMoveData(uint8_t *pbuf);

// ----------------------------------------------------------------------------- //

void SysTick_Handler(void)
{
	
  static __IO uint32_t counter=0;
    
  HAL_IncTick();
  
	// -- <3> HID 클래스의 폴링시간 설정값(10ms)이 되면  
	if ( counter++ == USBD_HID_GetPollingInterval(&USBD_Device) )  {
			// -- <3-1> 마우스의 이동량(HID_Buffer)을 받아온다
			GetMoveData(HID_Buffer);
			
			// -- <3-2> 마우스의 이동량(HID_Buffer)이 0이 아니면
			if ( (HID_Buffer[1] != 0) || (HID_Buffer[2] != 0) ) {
						// -- <3-3> HID_Buffer 값을 PC로 보냄.
						USBD_HID_SendReport(&USBD_Device, HID_Buffer, 4);
			}
			counter =0;
	}

  // -- <4> LED를 Toggle 시킴		
  Toggle_LED();
  
}

/******************************************************************************/
/*                 STM32F1xx Peripherals Interrupt Handlers                   */
/******************************************************************************/


 // This function handles USB-On-The-Go FS global interrupt request.
void OTG_FS_IRQHandler(void)
{
	HAL_PCD_IRQHandler(&hpcd);
}


// This function handles USB OTG FS Wakeup IRQ Handler.
void OTG_FS_WKUP_IRQHandler(void)
{
  if((&hpcd)->Init.low_power_enable)  {
		/* Reset SLEEPDEEP bit of Cortex System Control Register */
		SCB->SCR &= (uint32_t)~((uint32_t)(SCB_SCR_SLEEPDEEP_Msk | SCB_SCR_SLEEPONEXIT_Msk));  
		
		//  -- <5>  System clock을 설정 
	    // Configures system clock after wake-up from STOP */
		SystemClock_Config(); 
	  
		/* ungate PHY clock */
		__HAL_PCD_UNGATE_PHYCLOCK((&hpcd)); 
  }
  
  /* Clear EXTI pending Bit*/
  __HAL_USB_OTG_FS_WAKEUP_EXTI_CLEAR_FLAG();
}

// ----------------------------------------------------------------------------- //
// -- <6> Mouse의 이동량 pbuf 를 설정하는 함수

static void GetMoveData(uint8_t *pbuf)
{
	  int8_t  x = 0, y = 0 ;

	  // -- <6-1> 눌러진 Key의 종류에 따라 대응되는 x, y 값을 설정함		
	  switch( Joy_Key )	  {
					case JOY_LEFT:
						x -= CURSOR_STEP;			//마우스 커서를  왼쪽으로 5  이동
					break;  
					
					case JOY_RIGHT:
						x += CURSOR_STEP;			//마우스 커서를 오른쪽으로 5  이동
					break;
					
					case JOY_UP:
						y -= CURSOR_STEP;			//마우스 커서를 위로 5  이동
					break;
					
					case JOY_DOWN:
						y += CURSOR_STEP;			//마우스 커서를 아래로 5 이동
					break;
					
					case JOY_NONE:					
					break;
		}

	// -- <6-2> pbuf의 값을 설정함
	//			pbuf[1] : x 방향(오른쪽, 왼쪽)으로 이동할 값
	//			pbuf[2] : y 방향(위, 아래)으로 이동할 값
	pbuf[0] = 0;
	pbuf[1] = x;
	pbuf[2] = y;
	pbuf[3] = 0;
		
}

void EXTI0_IRQHandler(void)
{	
		// -- <3-1> GPIO_PIN_0에서 EXTI가 발생한 경우는
		//				 함수 HAL_GPIO_EXTI_Callback(GPIO_PIN_0) 를 호출
		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);	
}

// -------------------------------------------------------------------------------- //
// -- <4>  EXTI1 인터럽트의 핸들러 함수

void EXTI1_IRQHandler(void)
{
		// -- <4-1> GPIO_PIN_1에서 EXTI가 발생한 경우는
		//				 함수 HAL_GPIO_EXTI_Callback(GPIO_PIN_1) 를 호출	
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_1);	
}

// -------------------------------------------------------------------------------- //
// -- <5>  EXTI2 인터럽트의 핸들러 함수

void EXTI2_IRQHandler(void)
{
		// -- <5-1> GPIO_PIN_2에서 EXTI가 발생한 경우는
		//				 함수 HAL_GPIO_EXTI_Callback(GPIO_PIN_2) 를 호출		
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_2);	
}

// -------------------------------------------------------------------------------- //
// -- <5>  EXTI3 인터럽트의 핸들러 함수

void EXTI3_IRQHandler(void)
{
		// -- <5-1> GPIO_PIN_3에서 EXTI가 발생한 경우는
		//				 함수 HAL_GPIO_EXTI_Callback(GPIO_PIN_3) 를 호출		
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_3);	
}

// -------------------------------------------------------------------------------- //
// -- <6>  EXTI13 인터럽트의 핸들러 함수

void EXTI15_10_IRQHandler(void)
{	
		// -- <6-1> GPIO_PIN_13에서 EXTI가 발생한 경우는
		//				 함수 HAL_GPIO_EXTI_Callback(GPIO_PIN_13) 를 호출		
		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_13);
}

// ----------------------------------------------------------------------------- //


