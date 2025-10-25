
#ifndef	__LED_H
#define __LED_H
#include "main.h"
#include <stdarg.h>
#include <string.h>

#define LED_RED_ON()     HAL_GPIO_WritePin(LED_RED_GPIO_Port,LED_RED_Pin,GPIO_PIN_RESET)       //红灯亮
#define LED_RED_OFF()    HAL_GPIO_WritePin(LED_RED_GPIO_Port,LED_RED_Pin,GPIO_PIN_SET)         //红灯灭
#define LED_RED_TOGGLE() HAL_GPIO_TogglePin(LED_RED_GPIO_Port,LED_RED_Pin)                     //红灯翻转   
#define LED_GREEN_ON()     HAL_GPIO_WritePin(LED_GREEN_GPIO_Port,LED_GREEN_Pin,GPIO_PIN_RESET) //绿灯亮
#define LED_GREEN_OFF()    HAL_GPIO_WritePin(LED_GREEN_GPIO_Port,LED_GREEN_Pin,GPIO_PIN_SET)   //绿灯灭
#define LED_GREEN_TOGGLE() HAL_GPIO_TogglePin(LED_GREEN_GPIO_Port,LED_GREEN_Pin)               //绿灯翻转



void LED_Init(void);//初始化


#endif
