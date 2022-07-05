
/*******************************************************************************
  
  * File name :  UART_2 / main.c  
  
			* Application model : Nucleo_F103 Board  
  
			* Ver4.0
			* January 23. 2017
			* by Sang-min Kim, Jae-Il Kim  &  Dong-hyuk Cha
 
 ****************************************************************************** */

#include "main.h"			
#include "Nucleo_F103.h"			

// UartHandler ������ �ܺ����� ������ ����
extern UART_HandleTypeDef	UartHandle;		

// -- UART ����� ���� ����  
#define TxBufferSize	(countof(TxBuffer) - 1)
#define TxBufferSize_2	(countof(TxBuffer_2) - 1)
#define TxBufferSize_3	(countof(TxBuffer_3) - 1)
#define TxBufferSize_4	(countof(TxBuffer_4) - 1)
#define TxBufferSize_5	(countof(TxBuffer_5) - 1)
#define RxBufferSize	0xFF
#define countof(a)	(sizeof(a) / sizeof(*(a)))

// UART ��ſ� ���� ����
uint8_t TxBuffer[] = "\n\rUART Example 2 (Transmission  Success !!)\n\r\n\r";
uint8_t TxBuffer_2[] = "\n\r Button1 is pressed !! \n\r";
uint8_t TxBuffer_3[] = "\n\r Button2 is pressed !! \n\r";
uint8_t TxBuffer_4[] = "\n\r Button3 is pressed !! \n\r";
uint8_t TxBuffer_5[] = "\n\r Button4 is pressed !! \n\r";
uint8_t RxBuffer[RxBufferSize];

int main(void)
{

	HAL_Init(); 
	SystemClock_Config();
	SwEXTI_Config();
  LED_Config();
	// UART2�� �ʱ⼳���� �Լ��� ȣ�� 
	UART2_Config();

	LED_OnOff(GPIO_PIN_LedAll, 500);	

	// TxBuffer�� ����Ǿ� �ִ� ������ PC�� ������. 
	HAL_UART_Transmit(&UartHandle, (uint8_t*)TxBuffer, TxBufferSize, 0xFFFF);

	while (1) {  }
}

// -------------------------------------------------------------------------------- //

// -- <1> SW�� EXTI �Է� ó���� callback �Լ�
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)   
{
    // -- <2> NucleoSW, SW1 ~ SW4�� ������ �ش� �޽����� PC�� �۽��Ѵ�.
    switch(GPIO_Pin)
    {
					case GPIO_PIN_13:
						 HAL_UART_Transmit(&UartHandle, (uint8_t*)TxBuffer_2, TxBufferSize_2 , 0xFFFF); 
					break;
					case GPIO_PIN_8:
						 HAL_UART_Transmit(&UartHandle, (uint8_t*)TxBuffer_2, TxBufferSize_2 , 0xFFFF); 
					break;
					case GPIO_PIN_4:
						 HAL_UART_Transmit(&UartHandle, (uint8_t*)TxBuffer_3, TxBufferSize_3 , 0xFFFF); 
					break;
					case GPIO_PIN_5:
						 HAL_UART_Transmit(&UartHandle, (uint8_t*)TxBuffer_4, TxBufferSize_4 , 0xFFFF); 
					break;
					case GPIO_PIN_10:
						 HAL_UART_Transmit(&UartHandle, (uint8_t*)TxBuffer_5, TxBufferSize_5 , 0xFFFF); 
					break;
    }	
}

// -------------------------------------------------------------------------------- //
