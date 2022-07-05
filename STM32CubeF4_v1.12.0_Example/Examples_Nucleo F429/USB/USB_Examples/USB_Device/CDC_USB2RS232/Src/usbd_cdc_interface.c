
#include "main.h"
#include "Nucleo_F429.h"
#include <stdio.h>
#include <string.h>

#define APP_RX_DATA_SIZE  2048
#define APP_TX_DATA_SIZE  2048

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
uint8_t 		UserRxBuffer[APP_RX_DATA_SIZE];	/* Received Data over USB are stored in this buffer */
// 		-- <2-2> Received Data over UART (CDC interface) are stored in this buffer */
uint8_t 		UserTxBuffer[APP_TX_DATA_SIZE];	/* Received Data over UART (CDC interface) are stored in this buffer */

uint32_t 	BuffLength;

//		-- <2-3> UART의 수신 버퍼용 변수
uint32_t		UserTxBufPtrIn = 0;	/* Increment this pointer or roll it back to
													start address when data are received over USART */
uint32_t 	UserTxBufPtrOut = 0; /* Increment this pointer or roll it back to
													start address when data are sent over USB */

/* USB handler declaration */
extern USBD_HandleTypeDef  USBD_Device;

//		-- <2-4> UART 핸들링용 변수  
UART_HandleTypeDef 			UartHandler;
//		-- <2-5> TIM 핸들링용 변수
TIM_HandleTypeDef  				TimHandler;


/* Private function prototypes -----------------------------------------------*/
static int8_t 	CDC_Itf_Init (void);
static int8_t 	CDC_Itf_DeInit (void);
static int8_t 	CDC_Itf_Control (uint8_t cmd, uint8_t* pbuf, uint16_t length);
static int8_t 	CDC_Itf_Receive (uint8_t* pbuf, uint32_t *Len);

static void Error_Handler(void);

//		-- <2-6> UART, TIM 동작조건 설정용 함수
static void ComPort_Config(void);
static void TIM_Config(void);


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
  /* -- <3-1>  Configure the UART peripheral */
  /* Put the USART peripheral in the Asynchronous mode (UART Mode) */
  /* USART configured as follow:
      - Word Length = 8 Bits
      - Stop Bit    = One Stop bit
      - Parity      = No parity
      - BaudRate    = 115200 baud
      - Hardware flow control disabled (RTS and CTS signals) */
  UartHandler.Instance       		 = USARTx;
  UartHandler.Init.BaudRate   	= 115200;
  UartHandler.Init.WordLength 	= UART_WORDLENGTH_8B;
  UartHandler.Init.StopBits   		= UART_STOPBITS_1;
  UartHandler.Init.Parity     		= UART_PARITY_NONE;
  UartHandler.Init.HwFlowCtl  	= UART_HWCONTROL_NONE;
  UartHandler.Init.Mode       		= UART_MODE_TX_RX;
  
  if(HAL_UART_Init(&UartHandler) != HAL_OK)  {
		/* Initialization Error */
		Error_Handler();
  }
  
  /* -- <3-2>  Put UART peripheral in IT reception process  */
  /* Any data received will be stored in "UserTxBuffer" buffer  */
  if(HAL_UART_Receive_IT(&UartHandler, (uint8_t *)UserTxBuffer, 1) != HAL_OK)  {
		/* Transfer error in reception process */
		Error_Handler();
  }
  
  /* -- <3-3> Configure the TIM Base generation  */
  TIM_Config();
  
  /* -- <3-4> Start the TIM Base generation in interrupt mode */
  /* Start Channel1 */
  if(HAL_TIM_Base_Start_IT(&TimHandler) != HAL_OK)  {
		/* Starting Error */
		Error_Handler();
  }
  
  // -- <3-5>  실제 통신에 사용할 Buffer (UserTxBuffer, UserRxBuffer)를 설정
  USBD_CDC_SetTxBuffer(&USBD_Device, UserTxBuffer, 0);			// hcdc->TxBuffer = UserTxBuffer 로 설정
  USBD_CDC_SetRxBuffer(&USBD_Device, UserRxBuffer);			// hcdc->RxBuffer = UserRxBuffer   "
  
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
  /* DeInitialize the UART peripheral */
  if(HAL_UART_DeInit(&UartHandler) != HAL_OK)  {
		/* Initialization Error */
		Error_Handler();
  }
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
			LineCoding.bitrate    = (uint32_t) (pbuf[0] | (pbuf[1] << 8) |\
															(pbuf[2] << 16) | (pbuf[3] << 24) );
			LineCoding.format     = pbuf[4];
			LineCoding.paritytype = pbuf[5];
			LineCoding.datatype   = pbuf[6];
			
			/* Set the new configuration */
			ComPort_Config();
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
	char cp;		
	cp = Buf[0];
	
	// -- <4-1> 받은 데이터(Buf)를 UART로 송신함
	HAL_UART_Transmit_DMA(&UartHandler, Buf, *Len);
	
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
	
	return (USBD_OK);
}

/*----------------------------------------------------------------------------*/
// -- <5> HAL_UART_TxCpltCallback() : UART 송신완료 콜백함수 ( usbd_cdc_interface.c )
/**
  * @brief  Tx Transfer completed callback
  * @param  huart: UART handle
  * @retval None
  */
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	// -- <5-1> 데이터의 송신이 끝나면 USBD_CDC_ReceivePacket() 함수를 호출한다.
	//         이 함수는 host에 수신된 데이터 처리가 끝났음을 통보하고 다음 데이터 송신을 준비한다(?).
	/* Initiate next USB packet transfer once UART completes transfer
	    (transmitting data over Tx line) */
	// prepare OUT Endpoint for reception
	USBD_CDC_ReceivePacket(&USBD_Device);
}


/*----------------------------------------------------------------------------*/
//
//   여기서 부터는 PC로 데이터를 송신하는 부분임 
//
/*----------------------------------------------------------------------------*/

// -- <송신 1> UART (COM 포트) 초기 설정 함수

/* @brief  ComPort_Config
  *         Configure the COM Port with the parameters received from host.
  * @note   When a configuration is not supported, a default value is used.
  */
static void ComPort_Config(void)
{
  if(HAL_UART_DeInit(&UartHandler) != HAL_OK) {
		/* Initialization Error */
		Error_Handler();
  }
  
  /* set the Stop bit */
  switch (LineCoding.format)  {
	  case 0: 		UartHandler.Init.StopBits = UART_STOPBITS_1;		break;
	  case 2:		UartHandler.Init.StopBits = UART_STOPBITS_2;		break;
	  default :		UartHandler.Init.StopBits = UART_STOPBITS_1;		break;
  }
  
  /* set the parity bit*/
  switch (LineCoding.paritytype)  {
	  case 0:		UartHandler.Init.Parity = UART_PARITY_NONE;		break;
	  case 1:		UartHandler.Init.Parity = UART_PARITY_ODD;			break;
	  case 2:		UartHandler.Init.Parity = UART_PARITY_EVEN;		break;
	  default :		UartHandler.Init.Parity = UART_PARITY_NONE;		break;
  }
  
  /*set the data type : only 8bits and 9bits is supported */
  switch (LineCoding.datatype)  {
	  case 0x07:
		/* With this configuration a parity (Even or Odd) must be set */
		UartHandler.Init.WordLength = UART_WORDLENGTH_8B;
		break;
	  case 0x08:
		if(UartHandler.Init.Parity == UART_PARITY_NONE)	{
		  UartHandler.Init.WordLength = UART_WORDLENGTH_8B;
		}
		else {
		  UartHandler.Init.WordLength = UART_WORDLENGTH_9B;
		}		
		break;
	  default :
		UartHandler.Init.WordLength = UART_WORDLENGTH_8B;
		break;
  }
  
  UartHandler.Init.BaudRate = LineCoding.bitrate;
  UartHandler.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
  UartHandler.Init.Mode       = UART_MODE_TX_RX;

  // -- <1-1> 위에서 지정된 값으로 UART를 설정함  
  if(HAL_UART_Init(&UartHandler) != HAL_OK)  {
		/* Initialization Error */
		Error_Handler();
  }

  // -- <1-2> UART 수신을 시작함
  //                데이터가 수신되면 UserTxBuffer에 저장함
  /* Start reception: provide the buffer pointer with offset and the buffer size */
  HAL_UART_Receive_IT(&UartHandler, (uint8_t *)(UserTxBuffer + UserTxBufPtrIn), 1);
}


void HAL_UART_ErrorCallback(UART_HandleTypeDef *UartHandle)
{
  /* Transfer error occured in reception and/or transmission process */
  Error_Handler();
}

static void Error_Handler(void)
{
  /* Add your own code here */
}

/*----------------------------------------------------------------------------*/
// -- <송신 2> Timer 초기 설정 함수

static void TIM_Config(void)
{  
  /* Set TIMx instance */
  TimHandler.Instance = TIMx;
  
  /* Initialize TIM3 peripheral as follow:
       + Period = 10000 - 1
       + Prescaler = ((SystemCoreClock/2)/10000) - 1
       + ClockDivision = 0
       + Counter direction = Up
  */
	// CDC_POLLING_INTERVAL = 5 ms 로 define 됨
  TimHandler.Init.Period = (CDC_POLLING_INTERVAL*1000) - 1;
  TimHandler.Init.Prescaler = 84-1;
  TimHandler.Init.ClockDivision = 0;
  TimHandler.Init.CounterMode = TIM_COUNTERMODE_UP;
  if(HAL_TIM_Base_Init(&TimHandler) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
}

/*----------------------------------------------------------------------------*/
// -- <송신 3> UART 수신이 완료되면 호출되는 콜백함수
/**
  * @brief  Rx Transfer completed callback
  * @param  huart: UART handle
  * @retval None
  */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	// -- <3-1> 수신 버퍼(UserTxBuffer)의 인덱스를 1만큼 증가시킴
	/* Increment Index for buffer writing */
  UserTxBufPtrIn++;
  
  /* To avoid buffer overflow */
  if(UserTxBufPtrIn == APP_RX_DATA_SIZE)  {
		UserTxBufPtrIn = 0;
  }
  
  // -- <3-2> 다시 UART 수신을 시작함
  //                데이터가 수신되면 UserTxBuffer에 저장함
  /* Start another reception: provide the buffer pointer with offset and the buffer size */
  HAL_UART_Receive_IT(huart, (uint8_t *)(UserTxBuffer + UserTxBufPtrIn), 1);
  
}


/*----------------------------------------------------------------------------*/
// -- <송신 4> 일정한 시간마다 호출되는 Timer 콜백함수
/**
  * @brief  TIM period elapsed callback
  * @param  htim: TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  uint32_t buffptr;
  uint32_t buffsize;
  
  if(UserTxBufPtrOut != UserTxBufPtrIn)  {
		if(UserTxBufPtrOut > UserTxBufPtrIn) { 								// Rollback
				buffsize = APP_RX_DATA_SIZE - UserTxBufPtrOut;
		}
		else { 
				buffsize = UserTxBufPtrIn - UserTxBufPtrOut;
		}
    
		buffptr = UserTxBufPtrOut;
    
		// -- <4-1> UserTxBuffer를 USB의 TxBuffer로 설정
		USBD_CDC_SetTxBuffer(&USBD_Device, (uint8_t*)&UserTxBuffer[buffptr], buffsize);
    
		// -- <4-2> USB 포트로 데이터(TxBuffer)를 내보냄 
		if(USBD_CDC_TransmitPacket(&USBD_Device) == USBD_OK) {
				UserTxBufPtrOut += buffsize;
				if (UserTxBufPtrOut == APP_RX_DATA_SIZE)  {
						UserTxBufPtrOut = 0;
			}
		}
	
  }
  
}
