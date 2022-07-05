
// -------------------------------------------------------------------------- //

// --  main.h �Լ�

/* Define to prevent recursive inclusion -----------------*/
#ifndef __MAIN_H
#define __MAIN_H

// -- <1> ���α׷��� ���࿡ �ʿ��� ��� ������ ��Ŭ��� ��
#include "stm32f4xx_hal.h"
#include "stm32f4xx_nucleo_144.h"
#include "usbd_core.h"
#include "usbd_desc.h"
#include "usbd_cdc.h"
#include "usbd_cdc_interface.h"

// -- <2> LED�� Toggle�ϴ� �Լ��� ����
void Toggle_Leds(void);

#endif /* __MAIN_H */

// -------------------------------------------------------------------------- //

