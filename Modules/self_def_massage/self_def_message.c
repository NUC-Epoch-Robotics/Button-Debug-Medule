/**
  ******************************************************************************
  * @file     self_def_massage.c
  * @author   songzi
  * @version  
  * @date     
  * @brief   自定义串口通信 定义一个通信协议 实现不定长接收
  ******************************************************************************
  * @attention
  * 
  *
  *
  * 
  ******************************************************************************
  */ 
/* Includes -------------------------------------------------------------------*/
#include "self_def_massage.h"
#include "ring_buffer.h"
#include "bsp_usart.h"
#include "usart.h"
#include "bsp_usart.h"
#include "stdio.h"
#include "string.h"
#include "KEY.h"
/* Private  typedef -----------------------------------------------------------*/
/* Private  define ------------------------------------------------------------*/


/* Private  macro -------------------------------------------------------------*/
extern DMA_HandleTypeDef hdma_usart1_rx;
/* Private  variables ---------------------------------------------------------*/
void  uart_rcDMA(UART_HandleTypeDef *huart,uint8_t *DataBuff);
/* Extern   variables ---------------------------------------------------------*/
/* Extern   function prototypes -----------------------------------------------*/
/* Private  function prototypes -----------------------------------------------*/
/* Private  functions ---------------------------------------------------------*/



/**
  * @brief  
  * @param 
  * @param 
  * @retval 
  */
/*    发送数据参数    */
 uint8_t Usart_SendBuf[USART_PACKAGE_LEN];
 
/*    接收数据参数    */    
  uint8_t DataBuff[BUF_SIZE]; 
 
  
  USARTInstance Uart_frame;

/*初始化数据帧，配置所需要的发送命令，发送长度*/
void frameInstance_init(FrameInstance* frame,FrameCommand command)
{
  int test=	bsp_usart_init(&Uart_frame,&huart1,USART_TRANSFER_DMA);
	if(test==0)
	{frame->frame_hand1 = usart_frame_hand1;
	frame->frame_hand2 = usart_frame_hand2;
	frame->frame_hand3 = usart_frame_hand1;
	frame->command     = command;
	frame->frame_end = usart_frame_end;
	
	Uart_Idle_rcDMA(Uart_frame.usart_handle ,DataBuff);
  UART_Receive_IT_enable(&Uart_frame ,UART_IT_IDLE);//启用串口空闲中断	
	}
}



/**  把数据帧放在堆栈中  **/
void frame_buf(FrameInstance* frame,uint8_t* Data,int len)
{ 
	memset(Usart_SendBuf,0,sizeof(Usart_SendBuf));
	int i=0,t=0;
  Usart_SendBuf[t++] = frame->frame_hand1;
  Usart_SendBuf[t++] = frame->frame_hand2;
	Usart_SendBuf[t++] = frame->frame_hand3;
  Usart_SendBuf[t++] = frame->command;
	Usart_SendBuf[t++] = len;       
	for( i=t;i<len+t;i++)
	 {
	 Usart_SendBuf[i] = Data[i-t]; 
	 }
  t=len+t;
//	 crc=frame->CRC16_check(Data, len);
//  Usart_SendBuf[t++] = (crc>> 8)& 0xFF;
//	Usart_SendBuf[t++] = crc& 0xFF; 
  Usart_SendBuf[t] = usart_frame_end;
	 t=t+2;         //停止位

  UartSend(&Uart_frame, Usart_SendBuf,t,USART_TRANSFER_DMA ); //DMA传输
	 
 printf("发送\r\n");
}


/*   CRC校验   */
uint16_t CRC16_Check(const uint8_t *data,uint8_t len)
{
    uint16_t CRC16 = 0xFFFF;
    uint8_t state,i,j;
    for(i = 0; i < len; i++ )
    {
        CRC16 ^= data[i];
        for( j = 0; j < 8; j++)
        {
            state = CRC16 & 0x01;
            CRC16 >>= 1;
            if(state)
            {
                CRC16 ^= 0xA001;
            }
        }
    }
    return CRC16;
}
 

void HAL_UART_ErrorCallback(UART_HandleTypeDef * huart)
{
    if(huart->Instance == USART1)
    {
		  Uart_Idle_rcDMA(Uart_frame.usart_handle, DataBuff); // 接收发生错误后重启
      memset(DataBuff, 0, sizeof(DataBuff));
    }
}


