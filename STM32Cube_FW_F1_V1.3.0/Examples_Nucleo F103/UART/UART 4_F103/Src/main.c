
/*******************************************************************************
  
  * File name :  UART_4 / main.c  
  
			* Application model : Nucleo_F103 Board  
  
			* Ver4.0
			* January 23. 2017
			* by Sang-min Kim, Jae-Il Kim  &  Dong-hyuk Cha
 
 ****************************************************************************** */

#include "main.h"			
#include "Nucleo_F103.h"			

// UartHandle ������ �ܺ����� ������ ����
extern UART_HandleTypeDef	UartHandle;		

// UART ��ſ� ���� ����
#define TxBufferSize   	(countof(TxBuffer) - 1)
#define TxBufferSize_3 	(countof(TxBuffer_3) - 1)
#define RxBufferSize   	0xFF
#define countof(a)   	(sizeof(a) / sizeof(*(a)))

// UART ����� ���� ����   
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

	// TxBuffer�� ����Ǿ� �ִ� ������ PC�� ������. 
	HAL_UART_Transmit(&UartHandle, (uint8_t*)TxBuffer, TxBufferSize , 0xFFFF); 

	while (1)  
	{
		// -- <1> PC�κ��� �����͸� ������ �� ���ͷ�Ʈ�� ����
		HAL_UART_Receive_IT(&UartHandle, (uint8_t*)RxBuffer,1);	
	}
	
}

// -------------------------------------------------------------------------------- //

// -- <2> Interrupt ��� �۽��� �Ϸ�Ǹ� ȣ��Ǵ� callback �Լ� 
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *UartHandler)
{
	// -- <3> �۽�(INT ���)�� �Ϸ�Ǹ� TxBuffer_3�� ����� �޽����� PC�� �۽� 
	HAL_UART_Transmit(UartHandler, (uint8_t*)TxBuffer_3, TxBufferSize_3 , 0xFFFF);
}

// -------------------------------------------------------------------------------- //

// -- <4> Interrupt ��� ������ �Ϸ�Ǹ� ȣ��Ǵ� callback �Լ� 
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandler)
{
	/* -- <5> ����(INT ���)�� �Ϸ�Ǹ� ���ŵ� ������(RxBuffer)�� �״�� �۽� */
	HAL_UART_Transmit_IT(UartHandler, (uint8_t*)RxBuffer, 1);	  
}


// -------------------------------------------------------------------------------- //
