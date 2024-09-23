#include "bsp_usart.h"
#include "usart.h"
#include "stm32f1xx_hal.h"
#include "stdio.h"

/*参考CSDN
*原文链接：https://blog.csdn.net/m0_63954303/article/details/139794861
*
*/


/* bsp_usart_init：串口接收初始化函数
 * huart	 	想要初始化的串口的句柄
 * huart_type	想要初始化的串口编号，BSP_USART
 * return		成功返回0，失败返回-1 */
int bsp_usart_init(	USARTInstance* usart, uint8_t *buf )
{
	
	if(usart->usart_handle!=NULL )
	{
			  /* 开启串口接收中断 */
				HAL_UART_Receive_IT(usart->usart_handle, buf, USART_BUF_SIZE);	
				/* 使能空闲中断 */
		  	__HAL_UART_ENABLE_IT(usart->usart_handle, UART_IT_IDLE);	
				/* 清除第一次空闲中断标志，方便后续接收数据 */
				__HAL_UART_CLEAR_IDLEFLAG(usart->usart_handle);													
				return 0;
	 }
	return -1;
}                      
/*
*对usart进行底层封装
*对串口重定向
*
*/


//基于HAL库usart发送函数封装
 void SensorUartSend(USARTInstance *usart, uint8_t *send_buf, uint16_t send_size,USART_TRANSFER_MODE mode )
{
    switch (mode)
    {
    case USART_TRANSFER_BLOCKING:
        HAL_UART_Transmit(usart->usart_handle, send_buf, send_size, 100);
        break;
    case USART_TRANSFER_IT:
        HAL_UART_Transmit_IT(usart->usart_handle, send_buf, send_size);
        break;
    case USART_TRANSFER_DMA:
        HAL_UART_Transmit_DMA(usart->usart_handle, send_buf, send_size);
        break;
    default:
        while (1)
            ; // illegal mode! check your code context! 检查定义instance的代码上下文,可能出现指针越界
        break;
    }
}

void UART_Receive_IT_enable( USARTInstance *usart,uint8_t *pData,uint16_t Size)
	{
    UART_Start_Receive_IT(usart->usart_handle ,pData ,Size);
	}
	





