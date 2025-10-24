#include "usart.h"
#include <stdint.h>
#include <stdio.h>
uint8_t U1_RxBuf[U1_RX_SIZE];
uint8_t U1_TxBuf[U1_TX_SIZE];

UCB_CB U1CB;


void U1_Init(void)
{

    U1CB.URxCounter = 0;
    U1CB.URxDataIN = &U1CB.URxDataptr[0];
    U1CB.URxDataOUT = &U1CB.URxDataptr[0];
    U1CB.URxDataEND = &U1CB.URxDataptr[NUM-1];
    U1CB.URxDataIN->start = U1_RxBuf;
    __HAL_UART_CLEAR_IDLEFLAG(&huart1);       //清除串口空闲中断标志位
	__HAL_UART_ENABLE_IT(&huart1,UART_IT_IDLE);                //空闲中断使能
	__HAL_UART_ENABLE_IT(&huart1,UART_IT_RXNE); 							//接收中断使能
	__HAL_UART_CLEAR_IDLEFLAG(&huart1);       //清除串口空闲中断标志位
	HAL_UART_Receive_DMA(&huart1,U1CB.URxDataIN->start,U1_RX_MAX+1);
}



void UART1_SendByte(uint8_t byte)
{
    while (!(USART1->SR & USART_SR_TXE));  // 等待发送寄存器空
    USART1->DR = byte;                     // 写数据寄存器发送
}

void UART1_SendString(const char *str)
{
    for (size_t i = 0; i < strlen(str); i++)
    {
        while (!(USART1->SR & USART_SR_TXE));  // 等待发送寄存器空
        USART1->DR = str[i];                   // 写数据
    }
    while (!(USART1->SR & USART_SR_TC));       // 等待最后一位发送完成
}



void U1_printf(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    vsprintf((char *)U1_TxBuf, fmt, args);
    va_end(args);
    // HAL_UART_Transmit(&huart1, U1_TxBuf, strlen((char *)U1_TxBuf), HAL_MAX_DELAY);
    UART1_SendString((char *)U1_TxBuf);
}





// uint32_t log_count = 0;

void USER_UartDMAHandler(UART_HandleTypeDef* huart)
{

	if(huart->Instance == USART1)
	{
			if(__HAL_UART_GET_FLAG(huart,UART_FLAG_IDLE) != RESET)  //触发空闲中断
			{
					__HAL_UART_CLEAR_IDLEFLAG(huart);       //清除串口2空闲中断标志位
					HAL_UART_DMAStop(huart);                //关闭DMA
                    // log_count = (__HAL_DMA_GET_COUNTER(&hdma_usart1_rx));
                    U1CB.URxCounter+= (U1_RX_MAX+1) - (__HAL_DMA_GET_COUNTER(&hdma_usart1_rx)); //更新接收计数
                    // U1CB.URxCounter+= (__HAL_DMA_GET_COUNTER(&hdma_usart1_rx)); //更新接收计数
                    U1CB.URxDataIN->end = &U1_RxBuf[U1CB.URxCounter-1]; //更新数据指针

                    // fix bug: 当接收速度过快时，可能会出现数据覆盖的情况
                    while(U1CB.URxDataIN->start > U1CB.URxDataOUT->start && U1CB.URxDataIN->end < U1CB.URxDataOUT->start)
                    {
                        U1CB.URxDataOUT++;
                        if(U1CB.URxDataOUT == U1CB.URxDataEND) //如果指针到达末尾
                        {
                            U1CB.URxDataOUT = &U1CB.URxDataptr[0]; //重置指针
                        }
                    }

                    U1CB.URxDataIN++;
                    // 数据管理器的更新
                    if(U1CB.URxDataIN == U1CB.URxDataEND) //如果指针到达末尾
                    {
                        U1CB.URxDataIN = &U1CB.URxDataptr[0]; //重置指针
                    }
                    // 数据缓冲区接受指针管理
                    if(U1_RX_SIZE-U1CB.URxCounter >= U1_RX_MAX)
                    {
                        U1CB.URxDataIN->start = &U1_RxBuf[U1CB.URxCounter]; //更新数据起始指针
                    }
                    else {
                        U1CB.URxDataIN->start = U1_RxBuf;
                        U1CB.URxCounter = 0; //重置计数
                    }
                    HAL_UART_Receive_DMA(huart,U1CB.URxDataIN->start,U1_RX_MAX+1);  //使能DMA接收到buf1
			}
	}
}