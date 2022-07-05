/**
  ******************************************************************************
  * @file    USB_Device/CDC_Standalone/Src/usbd_cdc_interface.c
  * @author  MCD Application Team
  * @version V1.1.1
  * @date    20-November-2015
  * @brief   Source file for USBD CDC interface
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2015 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

#include "main.h"
#include "Nucleo_F429.h"
#include <stdio.h>
#include <string.h>

#define APP_RX_DATA_SIZE  	2048
#define APP_TX_DATA_SIZE  	2048

/* Private variables ---------------------------------------------------------*/

// -- <1> PC, 다른 MCU와의 UART(COM) 통신을 위한 설정값
USBD_CDC_LineCodingTypeDef 		LineCoding =  
  {
		115200, /* baud rate*/
		0x00,   /* stop bits-1*/
		0x00,   /* parity - none*/
		0x08    /* nb. of bits 8*/
  };

// -- <2> USB, UART의 송신, 수신 데이터용 변수
// 		-- <2-1>  Received Data over USB are stored in this buffer 
uint8_t 		UserRxBuffer[APP_RX_DATA_SIZE];	
// 		-- <2-2> Received Data over UART (CDC interface) are stored in this buffer */
uint8_t 		UserTxBuffer[APP_TX_DATA_SIZE];	
uint8_t 		UserTxBuffer2[APP_TX_DATA_SIZE];
uint8_t 		UserTxBuffer3[APP_TX_DATA_SIZE];
  
uint32_t 	BuffLength;
extern USBD_HandleTypeDef  USBD_Device;

/* Private function prototypes -----------------------------------------------*/
static int8_t 	CDC_Itf_Init (void);
static int8_t 	CDC_Itf_DeInit (void);
static int8_t 	CDC_Itf_Control (uint8_t cmd, uint8_t* pbuf, uint16_t length);
static int8_t 	CDC_Itf_Receive (uint8_t* pbuf, uint32_t *Len);

void My_Send_Data( uint8_t* UserTxBuffer2, int len );


USBD_CDC_ItfTypeDef 	USBD_CDC_fops = 
{
	  CDC_Itf_Init,
	  CDC_Itf_DeInit,
	  CDC_Itf_Control,
	  CDC_Itf_Receive
};


/*----------------------------------------------------------------------------*/
// -- <3>  CDC_Itf_Init :  Initializes the low layer CDC interface  
//				- 이 함수는 수정할 필요없이 그대로 사용하면 됨
/**
  * @param  None
  * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAIL
  */
/*----------------------------------------------------------------------------*/

static int8_t CDC_Itf_Init(void)
{

	// -- <3-1>  실제 통신에 사용할 Buffer (UserTxBuffer, UserRxBuffer)를 설정
			// hcdc->TxBuffer = UserTxBuffer 로 설정
	USBD_CDC_SetTxBuffer(&USBD_Device, UserTxBuffer, 0);			
			// hcdc->RxBuffer = UserRxBuffer 로 설정"
    USBD_CDC_SetRxBuffer(&USBD_Device, UserRxBuffer);			
  return (USBD_OK);
}

/*----------------------------------------------------------------------------*/
/**
  * @brief  CDC_Itf_DeInit
  *         DeInitializes the CDC media low layer
  * @param  None
  * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CDC_Itf_DeInit(void)
{
  return (USBD_OK);
}

/*----------------------------------------------------------------------------*/
/**
  * @brief  CDC_Itf_Control
  *         Manage the CDC class requests
  * @param  Cmd: Command code            
  * @param  Buf: Buffer containing command data (request parameters)
  * @param  Len: Number of data to be sent (in bytes)
  * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CDC_Itf_Control (uint8_t cmd, uint8_t* pbuf, uint16_t length)
{ 
  switch (cmd)  {
		  case CDC_SEND_ENCAPSULATED_COMMAND:
			/* Add your code here */
			break;

		  case CDC_GET_ENCAPSULATED_RESPONSE:
			/* Add your code here */
			break;

		  case CDC_SET_COMM_FEATURE:
			/* Add your code here */
			break;

		  case CDC_GET_COMM_FEATURE:
			/* Add your code here */
			break;

		  case CDC_CLEAR_COMM_FEATURE:
			/* Add your code here */
			break;

		  case CDC_SET_LINE_CODING:
//			LineCoding.bitrate    = (uint32_t) (pbuf[0] | (pbuf[1] << 8) |\
//															(pbuf[2] << 16) | (pbuf[3] << 24) );
			LineCoding.bitrate
				= (uint32_t) (pbuf[0] | (pbuf[1] << 8) | (pbuf[2] << 16) | (pbuf[3] << 24) );
			LineCoding.format     = pbuf[4];
			LineCoding.paritytype = pbuf[5];
			LineCoding.datatype   = pbuf[6];
			
			/* Set the new configuration */
			//ComPort_Config();
			break;

		  case CDC_GET_LINE_CODING:
			pbuf[0] = (uint8_t)(LineCoding.bitrate);
			pbuf[1] = (uint8_t)(LineCoding.bitrate >> 8);
			pbuf[2] = (uint8_t)(LineCoding.bitrate >> 16);
			pbuf[3] = (uint8_t)(LineCoding.bitrate >> 24);
			pbuf[4] = LineCoding.format;
			pbuf[5] = LineCoding.paritytype;
			pbuf[6] = LineCoding.datatype;     
			break;

		  case CDC_SET_CONTROL_LINE_STATE:
			/* Add your code here */
			break;

		  case CDC_SEND_BREAK:
			 /* Add your code here */
			break;    
			
		  default:
			break;
  }
  
  return (USBD_OK);
}


/*----------------------------------------------------------------------------*/
//  -- <4>  CDC_Itf_Receive() 
//				- USB host(PC)로 부터 받은 데이터를 처리하는 함수
//                USB host로 부터 데이터가 수신되면 USBD_CDC_DataOut() 함수내에서 이 함수를 호출함
//
//				- 이 함수는 필요시 변경하여 사용하면 됨
/**
  *  CDC_Itf_DataRx
  *         Data received over USB OUT endpoint are sent over CDC interface 
  *         through this function.
  *   Buf		: Buffer of data to be transmitted
  *   Len	: Number of data received (in bytes)
  *   retval 	: Result of the operation: USBD_OK if all operations are OK else USBD_FAIL
  */

static int8_t CDC_Itf_Receive(uint8_t* Buf, uint32_t *Len)
{
	char cp;		// 일단, 1글자만 받자 !!, 나중에 문자열을 받을수 있도록 수정하자 ! 
	// -- <4-1> 받은 데이터의 첫번째 문자를 cp에 대입
	cp = Buf[0];
	
	
	// -- <4-2> 받은 데이터가 1~4이면 해당되는 LED를 Toggle함
	if (cp == '1') {
			HAL_GPIO_TogglePin(GPIONucleo, GPIO_PIN_Led1);
			HAL_GPIO_TogglePin(GPIOExt, GPIO_PIN_Led1);
	}
	if (cp == '2') {
			HAL_GPIO_TogglePin(GPIOExt, GPIO_PIN_Led2);
	}
	if (cp == '3') {
			HAL_GPIO_TogglePin(GPIOExt, GPIO_PIN_Led3);
	}
	if (cp == '4') {
			HAL_GPIO_TogglePin(GPIOExt, GPIO_PIN_Led4);
	}

	// -- <4-3> 받은 데이터를 UserTxBuffer3에 대입한 후에 My_Send_Data() 함수를 호출함
	*UserTxBuffer3 = *Buf;
	My_Send_Data( UserTxBuffer3, strlen(UserTxBuffer3)); 
	//USBD_CDC_SetTxBuffer(&USBD_Device, UserTxBuffer3, strlen(UserTxBuffer3) );   
	//USBD_CDC_TransmitPacket(&USBD_Device) ;
	
	// --  <4-4> 데이터의 송신이 끝나면 USBD_CDC_ReceivePacket() 함수를 호출한다.
	//         이 함수는 host에 수신된 데이터 처리가 끝났음을 통보하고 다음 데이터 송신을 준비한다.
	/* Initiate next USB packet transfer  */
	// prepare OUT Endpoint for reception
	USBD_CDC_ReceivePacket(&USBD_Device);	
	return (USBD_OK);
}


// ------------------------------------------------------------------------
// -- <5> GPIO의 EXTI 가 발생하면 (즉, Key가 눌러지면) 호출되는 함수
//
// ------------------------------------------------------------------------

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{

  // -- <5-1> 눌러지는 Key 값에 따라  대응하는 문자를 UserTxBuffer2에 대입		
	 if (GPIO_Pin == GPIO_PIN_Nucleo_Sw)  {
		sprintf( (char*) UserTxBuffer2,  "\n\r SW1 is pressed !!  \n\r ");
  }
  if (GPIO_Pin == GPIO_PIN_Sw1)  {
		sprintf( (char*) UserTxBuffer2,  "\n\r SW1 is pressed !!  \n\r ");
  }
  if (GPIO_Pin == GPIO_PIN_Sw2)  {
		sprintf( (char*) UserTxBuffer2,  "\n\r SW2 is pressed !!  \n\r ");	  
  }
  if (GPIO_Pin == GPIO_PIN_Sw3)  {
		sprintf( (char*) UserTxBuffer2,  "\n\r SW3 is pressed !!  \n\r ");	  
  }
  if (GPIO_Pin == GPIO_PIN_Sw4)  {
		sprintf( (char*) UserTxBuffer2,  "\n\r SW4 is pressed !!  \n\r ");	  
  }

  // -- <5-2>  My_Send_Data() 함수를 호출함
  My_Send_Data( UserTxBuffer2, strlen(UserTxBuffer2));  
 
  // -- <5-3> Key의 chattering 현상을 방지하기 위해 시간지연을 준다   
  for (int i=0; i<=100000; i++) ;
 
}

// ------------------------------------------------------------------------
// -- <6> USB host(PC)로 데이터를 전송하는 함수
//
//		UserTxBuffer2	: Buffer of data to be transmitted
//		len					: 전송할 데이터의 길이
// ------------------------------------------------------------------------

void My_Send_Data(uint8_t* UserTxBuffer2, int len )
{

	// -- <6-1> TxBuffer에 전송할 data를 대입함
	USBD_CDC_SetTxBuffer(&USBD_Device, UserTxBuffer2, len);  
	// -- <6-2> data를 전송함
	USBD_CDC_TransmitPacket(&USBD_Device); 
}
