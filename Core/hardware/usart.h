#ifndef __USART_H
#define __USART_H 


#include <stdint.h>
#ifdef __cplusplus
 extern "C" {
#endif
#include "main.h"
#include <stdarg.h>
#include <string.h>


#define U1_RX_SIZE 2048
#define U1_TX_SIZE 2048


#define U1_RX_MAX 256
#define NUM 10

extern UART_HandleTypeDef huart1;
extern DMA_HandleTypeDef hdma_usart1_rx;




typedef struct {
    uint8_t *start;
    uint8_t *end;
} UCB_URxBuffptr; 


typedef struct {
    uint16_t URxCounter; // Number of bytes in the buffer
    UCB_URxBuffptr URxDataptr[NUM]; // Pointers to the data in the buffer
    // uint16_t URxDataSize; // Size of the data in the buffer
    UCB_URxBuffptr *URxDataIN;
    UCB_URxBuffptr *URxDataOUT;
    UCB_URxBuffptr *URxDataEND;
} UCB_CB; 


extern UCB_CB U1CB;
extern uint8_t U1_RxBuf[U1_RX_SIZE];
extern uint8_t U1_TxBuf[U1_TX_SIZE];



void U1_Init(void);
void USER_UartDMAHandler(UART_HandleTypeDef* huart);
void U1_printf(const char *fmt, ...);

#ifdef __cplusplus
    }
#endif
#endif
