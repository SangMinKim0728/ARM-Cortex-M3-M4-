
/*******************************************************************************
  
  * File name :  UART_4 / main.c  
  
			* Application model : Nucleo_F103 Board  
  
			* Ver4.0
			* January 23. 2017
			* by Sang-min Kim, Jae-Il Kim  &  Dong-hyuk Cha
 
 ****************************************************************************** */

#include "main.h"			
#include "Nucleo_F103.h"			

// UartHandle 변수를 외부정의 변수로 선언
extern UART_HandleTypeDef	UartHandle;		

// UART 통신용 변수 선언
#define TxBufferSize   	(countof(TxBuffer) - 1)
#define TxBufferSize_3 	(countof(TxBuffer_3) - 1)
#define RxBufferSize   	0xFF
#define countof(a)   	(sizeof(a) / sizeof(*(a)))

// UART 통신을 위한 정의   
uint8_t TxBuffer[] = "\n\rUART Example 4 (Transmission  Success !!)\n\r\n\r";
uint8_t TxBuffer_3[] = "\n\r A Message from HAL_UART_TxCpltCallback() !!\n\r\n\r";
uint8_t RxBuffer[RxBufferSize];

// -------------------------------------------------------------------------------- //

int main(void)
{
	HAL_Init(); 
	SystemClock_Config();
	LED_Config();
	UART2_Config();

	// TxBuffer에 저장되어 있는 내용을 PC로 보낸다. 
	HAL_UART_Transmit(&UartHandle, (uint8_t*)TxBuffer, TxBufferSize , 0xFFFF); 

	while (1)  
	{
		// -- <1> PC로부터 데이터를 수신할 때 인터럽트로 구현
		HAL_UART_Receive_IT(&UartHandle, (uint8_t*)RxBuffer,1);	
	}
	
}

// -------------------------------------------------------------------------------- //

// -- <2> Interrupt 모드 송신이 완료되면 호출되는 callback 함수 
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *UartHandler)
{
	// -- <3> 송신(INT 모드)이 완료되면 TxBuffer_3에 저장된 메시지를 PC로 송신 
	HAL_UART_Transmit(UartHandler, (uint8_t*)TxBuffer_3, TxBufferSize_3 , 0xFFFF);
}

// -------------------------------------------------------------------------------- //

// -- <4> Interrupt 모드 수신이 완료되면 호출되는 callback 함수 
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandler)
{
	/* -- <5> 수신(INT 모드)이 완료되면 수신된 데이터(RxBuffer)를 그대로 송신 */
	HAL_UART_Transmit_IT(UartHandler, (uint8_t*)RxBuffer, 1);	  
}


// -------------------------------------------------------------------------------- //
