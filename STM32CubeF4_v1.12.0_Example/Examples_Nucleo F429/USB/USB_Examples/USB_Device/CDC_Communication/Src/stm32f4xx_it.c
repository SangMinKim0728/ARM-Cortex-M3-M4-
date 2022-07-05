/**
  ******************************************************************************
  * @file    USB_Device/CDC_Communication/Src/stm32f1xx_it.c 

			* Application model : Nucleo_F429 Board  
 
			* Ver2.0
			* January. 23. 2017
			* by Sang Min Kim, Jae Il Kim  &  Dong-hyuk Cha.
  ******************************************************************************
   */

#include "main.h"
#include "stm32f4xx_it.h"

extern PCD_HandleTypeDef 	hpcd;

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

void SysTick_Handler(void)
{

  HAL_IncTick();
  // -- <1> LED를 깜박여 준다
  Toggle_Leds();
}

/******************************************************************************/
/*                 STM32F4xx Peripherals Interrupt Handlers                   */
/******************************************************************************/

 //  This function handles USB-On-The-Go FS global interrupt request.
void OTG_FS_IRQHandler(void)
{
  HAL_PCD_IRQHandler(&hpcd);
}

// -----------------------------------------------------------------------------
// -- <2> SW를 누르면 발생하는 EXTI의 핸들러 함수

void EXTI0_IRQHandler(void)
{	
		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);	
}

// -------------------------------------------------------------------------------- //

void EXTI1_IRQHandler(void)
{
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_1);	
}

// -------------------------------------------------------------------------------- //

void EXTI2_IRQHandler(void)
{
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_2);	
}

// -------------------------------------------------------------------------------- //

void EXTI3_IRQHandler(void)
{
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_3);	
}

// -------------------------------------------------------------------------------- //

void EXTI15_10_IRQHandler(void)
{
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_13);	
}

// -------------------------------------------------------------------------------- //
