
/*******************************************************************************
  
  * File name :  UART_1 / main.c  
  
			* Application model : Nucleo_F429 Board  
  
			* Ver2.0
			* January 23. 2017
			* by Sang-min Kim, Jae-Il Kim  &  Dong-hyuk Cha
 
 ****************************************************************************** */

#include "main.h"			
#include "Nucleo_F429.h"			

// -- <1> UartHandler ������ �ܺ����� ������ ����
extern UART_HandleTypeDef	UartHandle;			

// -- <2> UART ����� ���� ���� 
#define TxBufferSize	(countof(TxBuffer) - 1)
#define RxBufferSize	0xFF
#define countof(a)	(sizeof(a) / sizeof(*(a)))

// -- <3> UART ��ſ� ���� ���� 
uint8_t TxBuffer[] = "\n\rUART Example 1 (Transmission  Success !!)\n\r\n\r";
uint8_t RxBuffer[RxBufferSize];

// -------------------------------------------------------------------------------- //

int main(void)
{
	HAL_Init(); 
	SystemClock_Config();
	LED_Config();

	// -- <4> Timer�� �ʱ⼳���� �Լ��� ȣ�� 
	UART3_Config();	
	
	LED_OnOff(GPIO_PIN_LedAll, 500);

	// -- <5> TxBuffer�� ����Ǿ� �ִ� ������ PC�� ������. 
	HAL_UART_Transmit(&UartHandle, (uint8_t*)TxBuffer, TxBufferSize , 0xFFFF); 

	// -- <6> ���� ���� 
	while (1) { }
}

// -------------------------------------------------------------------------------- //

