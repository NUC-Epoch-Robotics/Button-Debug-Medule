/**
  ******************************************************************************
  * @file     self_def_massage.c
  * @author   songzi
  * @version  �汾��
  * @date     ���ʱ��
  * @brief    �Զ���ͨ�ŷ�ʽ ,ͨ����Ϣ���з���
  ******************************************************************************
  * @attention
  * ע������
  *
  *
  * 
  ******************************************************************************
  */ 
/* Includes -------------------------------------------------------------------*/
#include "self_def_massage.h"
#include "bsp_usart.h"
#include "usart.h"
#include "bsp_usart.h"
#include "stdio.h"
/* Private  typedef -----------------------------------------------------------*/
/* Private  define ------------------------------------------------------------*/


/* Private  macro -------------------------------------------------------------*/
/* Private  variables ---------------------------------------------------------*/

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
	static  uint16_t Usart_SendBuf[USART_PACKAGE_LEN];
//��������
void Send_frame_data(uint8_t reg,uint16_t data)
{
 Usart_SendBuf[0]=usart_frame_hand1;
 Usart_SendBuf[1]=usart_frame_hand2;
 Usart_SendBuf[2]=usart_frame_hand1;
 Usart_SendBuf[3]=
 Usart_SendBuf[4]=
 Usart_SendBuf[3]=usart_frame_end2;
}

uint8_t RxBuff[1];      //�����жϽ������ݵ�����
uint8_t DataBuff[5000]; //������յ������ݵ�����
int RxLine=0;           //���յ������ݳ���

void HAL_UART_RxCpltCallback(UART_HandleTypeDef*UartHandle)
{
    RxLine++;                      //ÿ���յ�һ�����ݣ�����ص����ݳ��ȼ�1
    DataBuff[RxLine-1]=RxBuff[0];  //��ÿ�ν��յ������ݱ��浽��������
    
    if(RxBuff[0]==0xff)            //���ս�����־λ��������ݿ����Զ��壬����ʵ����������ֻ��ʾ��ʹ�ã���һ����0xff
    {      
        for(int i=0;i<RxLine;i++)                     
        memset(DataBuff,0,sizeof(DataBuff));  //��ջ�������
        RxLine=0;  //��ս��ճ���
    }
    
    //
    RxBuff[0]=0;
    HAL_UART_Receive_IT(&huart1, (uint8_t *)RxBuff, 1); //ÿ����һ�����ݣ��ʹ�һ�δ����жϽ��գ�����ֻ�����һ�����ݾ�ֹͣ����
}





	 
	






