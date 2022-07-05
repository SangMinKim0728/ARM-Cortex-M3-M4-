
// -------------------------------------------------------------------------- //

// --  main.h 함수

/* Define to prevent recursive inclusion -----------------*/
#ifndef __MAIN_H
#define __MAIN_H

// -- <1> 프로그램의 수행에 필요한 헤더 파일을 인클루드 함
#include "stm32f4xx_hal.h"
#include "stm32f4xx_nucleo_144.h"
#include "usbd_core.h"
#include "usbd_desc.h"
#include "usbd_cdc.h"
#include "usbd_cdc_interface.h"

// -- <2> LED를 Toggle하는 함수를 선언
void Toggle_Leds(void);

#endif /* __MAIN_H */

// -------------------------------------------------------------------------- //

