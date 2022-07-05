
/*******************************************************************************
  
  * File name :  UART_3 / main.c  
  
			* Application model : Nucleo_F103 Board  
  
			* Ver4.0
			* January 23. 2017
			* by Sang-min Kim, Jae-Il Kim  &  Dong-hyuk Cha
 
 ****************************************************************************** */

#include "main.h"			
#include "Nucleo_F103.h"			

// UartHandler ������ �ܺ����� ������ ����
extern UART_HandleTypeDef	UartHandle;		

// UART ����� ���� ����  
#define TxBufferSize	(countof(TxBuffer) - 1)
#define RxBufferSize	0xFF
#define countof(a)	(sizeof(a) / sizeof(*(a)))

// UART ��ſ� ���� ����
uint8_t TxBuffer[] = "\n\rUART Example 3 (Transmission  Success !!)\n\r\n\r";
uint8_t RxBuffer[RxBufferSize];

//------------------------------------------------------------------------------------//

int main(void)
{
	HAL_Init(); 
	SystemClock_Config();
	LED_Config();

	// UART�� �ʱ⼳���� �Լ��� ȣ�� 
	UART2_Config();	

	LED_OnOff(GPIO_PIN_LedAll, 500);

	// -- <1> TxBuffer�� ����Ǿ� �ִ� ������ PC�� ������. 
	HAL_UART_Transmit(&UartHandle, (uint8_t*)TxBuffer, TxBufferSize, 0xFFFF);

	// -- <2> PC���� �����͸� �޾� �״�� PC�� ����(echo) �Ѵ�. 
	while (1)  {

		// -- <3> PC�κ��� ���� �����͸� RxBuffer�� �����Ѵ�. 
		if(HAL_UART_Receive(&UartHandle, (uint8_t*)RxBuffer,1, 5000)== HAL_OK)
		{
			// --<4> RxBuffer�� PC�� �ٽ� ������. 
			HAL_UART_Transmit(&UartHandle, (uint8_t*)RxBuffer, 1, 5000);
		}
	}
	
}

// -------------------------------------------------------------------------------- //

