#include "button_motor.h"
#include "freertos.h"
#include "task.h"
#include "self_def_massage.h"
#include "KEY.h"
#include "bsp_usart.h"
#include "multi_button.h"
#include "OLED_IIC_Config.h"
#include "OLED_Function.h"
#include "OLED_Front.h"
#include "Buzzer.h"
#include "tim.h"
#include "stdio.h"
#include "usart.h"
#include "Buzzer.h"


uint8_t rx_data[BUF_SIZE];
  
extern USARTInstance Uart_frame;
extern uint8_t DataBuff[BUF_SIZE]; 
	


	
//freeRTOS执行按键任务
/***   执行按键任务  ***/
void button_task()
{
		while(1)
		{
			
		button_ticks();
		vTaskDelay(2);
		}
}
/***   执行蜂鸣器任务  ***/
void buzzer_task()
{
		while(1)
		{
			//Buzzer_SetFreq(1000);
			
		vTaskDelay(2);
		}
}

/***   执行OLED任务  ***/
void oled_task()
{

		while(1)
		{
			
			
		vTaskDelay(2);
		}
}




/*  空闲回调函数  */
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart,uint16_t Size)
{
	
	uint8_t cnt =0;
//	int commit;//接收传来的指令      
	memset(rx_data,0,sizeof(rx_data));
				
 if( huart->Instance == USART1)
   {   
				if(DataBuff[0] == usart_frame_hand1&&
					 DataBuff[1] == usart_frame_hand2&& 
					 DataBuff[2] == usart_frame_hand1  )   //检测是否是包头  DataBuff[%d]=
			 {  
		  	//  commit= DataBuff[3];                 //接收发来的命令，用来执行不同的代码，现在没写以后补充
					cnt =  DataBuff[4];
			
			 //CRC检验 && 检测是否是包尾
			uint16_t CRC16= CRC16_Check(rx_data,cnt);
		  uint16_t  crc=(DataBuff[cnt+5]<< 8) | DataBuff[cnt+6];

			if(CRC16==crc&&DataBuff[cnt+7] == usart_frame_end ) 
				{ 
					for(int i=0;i<=cnt;i++){
			uint8_t 		data= DataBuff[i+5];
						User_rx_Callback(data);		
					}						
				} 
			else  
			 {
					memset(rx_data,0,sizeof(rx_data));
			 } 
	  } 
  }
}



/*接收回调*/
void User_rx_Callback(uint8_t data)
{
	if( data==0x11){
HAL_GPIO_TogglePin (LED1_GPIO_Port,LED1_Pin);
	//代码
	
	}
	if( data== 0x22){
HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_SET);
	//代码
	}
	if( data== 0x33){
HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_RESET);
	//代码
	}
}



void HAL_UART_ErrorCallback(UART_HandleTypeDef * huart)
{
    if(huart->Instance == USART1)
    {
		  Uart_Idle_rcDMA(Uart_frame.usart_handle, DataBuff); // 接收发生错误后重启
      memset(DataBuff, 0, sizeof(DataBuff));
    }
}







