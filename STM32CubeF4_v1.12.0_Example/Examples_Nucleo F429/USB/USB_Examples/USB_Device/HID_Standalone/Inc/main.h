
// -------------------------------------------------------------------------- //

// --  main.h 함수

/* Define to prevent recursive inclusion -----------------*/
#ifndef __MAIN_H
#define __MAIN_H

// -- 프로그램의 수행에 필요한 헤더 파일을 인클루드 함
#include "stm32f4xx_hal.h"
#include "usbd_core.h"
#include "usbd_desc.h"
#include "usbd_hid.h" 
#include "stm32f4xx_nucleo_144.h"

// -- LED를 Toggle하는 함수를 선언
void Toggle_LED(void);

#endif /* __MAIN_H */

// -------------------------------------------------------------------------- //


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
