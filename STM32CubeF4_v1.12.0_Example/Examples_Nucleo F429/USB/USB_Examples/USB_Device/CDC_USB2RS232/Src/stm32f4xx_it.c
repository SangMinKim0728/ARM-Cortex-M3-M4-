/**
  ******************************************************************************
  * @file    USB_Device/CDC_Communication/Src/stm32f1xx_it.c 

			* Application model : STM32F107 Board  
 
			* Ver2.0
			* April. 25. 2016
			* by Jae Il Kim, Sang Min Kim  &  Dong-hyuk Cha.
  ******************************************************************************
   */

#include "main.h"
#include "stm32f4xx_it.h"

extern PCD_HandleTypeDef 	hpcd;

//  -- <1> UART�� TIM �� �ڵ鸵�� ���� ���� ����
//		<1-1> UART handler declared in "usbd_cdc_interface.c" file */
extern UART_HandleTypeDef 	UartHandler;
//      <1-2> TIM handler declared in "usbd_cdc_interface.c" file */
extern TIM_HandleTypeDef 	TimHandler;

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

void SysTick_Handler(void)
{

  HAL_IncTick();
  // -- <1> LED�� ���ڿ� �ش�
  Toggle_Leds();
}

/******************************************************************************/
/*                 STM32F2xx Peripherals Interrupt Handlers                   */
/******************************************************************************/

 //  This function handles USB-On-The-Go FS global interrupt request.
void OTG_FS_IRQHandler(void)
{
  HAL_PCD_IRQHandler(&hpcd);
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -- <2> USARTx_DMA_TX ���ͷ�Ʈ �ڵ鷯 �Լ�
//

void USARTx_DMA_TX_IRQHandler(void)
{
  HAL_DMA_IRQHandler(UartHandler.hdmatx);
}

// -----------------------------------------------------------------------------
// -- <3> USARTx ���ͷ�Ʈ �ڵ鷯 �Լ�
//

void USARTx_IRQHandler(void)
{
  HAL_UART_IRQHandler(&UartHandler);
}

// -----------------------------------------------------------------------------
// -- <4> TIMx ���ͷ�Ʈ �ڵ鷯 �Լ�
//

void TIMx_IRQHandler(void)
{
  HAL_TIM_IRQHandler(&TimHandler);
}

// -----------------------------------------------------------------------------

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