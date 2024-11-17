#ifndef __BSP_USART_H
#define __BSP_USART_H

#include "gpio.h"


#define BUF_SIZE     64      //单次最大接收字节数
typedef enum
{
    USART_TRANSFER_NONE=0,
    USART_TRANSFER_BLOCKING,
    USART_TRANSFER_IT,
    USART_TRANSFER_DMA,
	  USART_TRANSFER_IDLE
} USART_TRANSFER_MODE;

typedef struct
{
  UART_HandleTypeDef   *usart_handle;
  USART_TRANSFER_MODE  TRANSFER_MODE;
} USARTInstance;

extern DMA_HandleTypeDef hdma_usart2_rx;

/***串口初始化***/
void bsp_usart_init(USARTInstance* usart , UART_HandleTypeDef   *usart_handle,USART_TRANSFER_MODE  TRANSFER_MODE);
              
/*** 发送模式 ***/
void UartSend(USARTInstance *usart, uint8_t *send_buf, uint16_t send_size,USART_TRANSFER_MODE mode);

/*** 接收模式 ***/
void UartReceive(USARTInstance *usart, uint8_t *send_buf, uint16_t send_size,USART_TRANSFER_MODE mode );

/*** 中断使能 ***/
void UART_Receive_IT_enable( USARTInstance *usart,uint32_t InterruptDefinitions);
/*
*@param InterruptDefinitions对应类型
* UART_IT_PE  奇偶校验错误中断
* UART_IT_TXE  传输数据寄存器空中断
* UART_IT_TC   传输完成中断
* UART_IT_RXNE 接收  数据区不空中断
* UART_IT_IDLE 空闲线检测中断
*/




/*** 空闲DMA接收 ***/
void  Uart_Idle_rcDMA(UART_HandleTypeDef *huart,uint8_t* DataBuff);
#endif


