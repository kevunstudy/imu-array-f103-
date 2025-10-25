#ifndef __DELAT_H
#define __DELAT_H

#include <stdint.h>

#ifdef __cplusplus
 extern "C" {
#endif
#include "main.h"


// sysTick定时器初始化
void SysTick_Init(void);  
// 延时函数，单位us 
void SysTick_Delay_Us(__IO uint32_t us);
// 延时函数，单位ms
void SysTick_Delay_Ms(__IO uint32_t ms);


#ifdef __cplusplus
    }
#endif
#endif
