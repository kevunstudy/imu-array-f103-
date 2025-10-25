#ifndef __KEY_H
#define __KEY_H
#include "main.h"
#include <stdarg.h>
#include <string.h>

#define KEY1  HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin) //按键1
#define KEY2  HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin) //按键2
#define KEY3  HAL_GPIO_ReadPin(KEY3_GPIO_Port,KEY3_Pin) //按键3
void KEY_Init(void);//IO初始化



#endif