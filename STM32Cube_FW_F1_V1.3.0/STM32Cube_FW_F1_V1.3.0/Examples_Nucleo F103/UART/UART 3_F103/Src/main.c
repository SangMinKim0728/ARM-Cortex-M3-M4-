
/*******************************************************************************
  
  * File name :  UART_3 / main.c  
  
			* Application model : Nucleo_F103 Board  
  
			* Ver4.0
			* January 23. 2017
			* by Sang-min Kim, Jae-Il Kim  &  Dong-hyuk Cha
 
 ****************************************************************************** */

#include "main.h"			
#include "Nucleo_F103.h"			

// UartHandler 변수를 외부정의 변수로 선언
extern UART_HandleTypeDef	UartHandle;		

// UART 통신을 위한 정의  
#define TxBufferSize	(countof(TxBuffer) - 1)
#define RxBufferSize	0xFF
#define countof(a)	(sizeof(a) / sizeof(*(a)))

// UART 통신용 변수 선언
uint8_t TxBuffer[] = "\n\rUART Example 3 (Transmission  Success !!)\n\r\n\r";
uint8_t RxBuffer[RxBufferSize];

//------------------------------------------------------------------------------------//

int main(void)
{
	HAL_Init(); 
	SystemClock_Config();
	LED_Config();

	// UART의 초기설정용 함수를 호출 
	UART2_Config();	

	LED_OnOff(GPIO_PIN_LedAll, 500);

	// -- <1> TxBuffer에 저장되어 있는 내용을 PC로 보낸다. 
	HAL_UART_Transmit(&UartHandle, (uint8_t*)TxBuffer, TxBufferSize, 0xFFFF);

	// -- <2> PC에서 데이터를 받아 그대로 PC로 전송(echo) 한다. 
	while (1)  {

		// -- <3> PC로부터 받은 데이터를 RxBuffer에 저장한다. 
		if(HAL_UART_Receive(&UartHandle, (uint8_t*)RxBuffer,1, 5000)== HAL_OK)
		{
			// --<4> RxBuffer를 PC로 다시 보낸다. 
			HAL_UART_Transmit(&UartHandle, (uint8_t*)RxBuffer, 1, 5000);
		}
	}
	
}

// -------------------------------------------------------------------------------- //

