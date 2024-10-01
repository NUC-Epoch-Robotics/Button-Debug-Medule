#include "button_motor.h"
//#include "freertos.h"
//#include "task.h"
#include "self_def_massage.h"
#include "KEY.h"
#include "multi_button.h"
#include "OLED_IIC_Config.h"
#include "OLED_Function.h"
#include "OLED_Front.h"
#include "Buzzer.h"
#include "tim.h"
#include "stdio.h"
#include "usart.h"
#include "ring_buffer.h"


//uint8_t rx_data[BUF_SIZE];
uint8_t ringbuff[RING_BUFF_SIZE];
//extern USARTInstance Uart_frame;
extern uint8_t DataBuff[BUF_SIZE]; 
	
stRingBuff Ring_Buff;

//放初始化的代码   之后在freertos中调用完成初始化
//void Buttonmotorinit()
//{



//}
	
////freeRTOS执行按键任务
///***   执行按键任务  ***/
//void button_task()
//{
//	uint8_t Data1[3];
//	Data1[0]=0x11;
//	FrameInstance frame1;
//  frameInstance_init(&frame1,usart_W_DATA);
//	frame_buf(&frame1,Data1,3);
//		while(1)
//		{
//			switch(key())
//	{				
//		case KEY1_PRES:
//      frame_buf(&frame1,Data1,3);			
//			HAL_GPIO_TogglePin(LED1_GPIO_Port,LED1_Pin);
//   printf("freertos发送\r\n");
//			
//			break;
//	}

//	//	button_ticks();
//		vTaskDelay(5);
//		}
//}
///***   执行蜂鸣器任务  ***/
//void buzzer_task()
//{
//		while(1)
//		{
//			//Buzzer_SetFreq(1000);
//			
//		vTaskDelay(2);
//		}
//}

///***   执行OLED任务  ***/
//void oled_task()
//{

//		while(1)
//		{
//			
//			
//		vTaskDelay(2);
//		}
//}






/*  空闲回调函数  */
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart,uint16_t Size)
{
 // printf("回调接收\r\n");
	uint8_t cnt =0;
	uint8_t ring_data[BUF_SIZE];
//	int commit;//接收传来的指令      
	memset(ring_data,0,sizeof(ring_data));
	
	WriteRingBuffer(&Ring_Buff,DataBuff, DataBuff[4]+6);
	ReadRingBuffer(&Ring_Buff,ring_data , DataBuff[4]+6);   
	
 if( huart->Instance == USART1)
   {   
				if(ring_data[0] == usart_frame_hand1&&
					 ring_data[1] == usart_frame_hand2&& 
					 ring_data[2] == usart_frame_hand1  )   //检测是否是包头  DataBuff[%d]=
		 
			 {  
		  	//  commit= DataBuff[3];                 //接收发来的命令，用来执行不同的代码，现在没写以后补充
					cnt =  ring_data[4];
			
			 //CRC检验 && 检测是否是包尾
//			uint16_t CRC16= CRC16_Check(rx_data,cnt);
//		  uint16_t  crc=(DataBuff[cnt+5]<< 8) | DataBuff[cnt+6];CRC16==crc&&

			if(ring_data[cnt+5] == usart_frame_end ) 
				{ 
					for(int i=0;i<=cnt;i++){
			uint8_t 		data= ring_data[i+5];
						User_rx_Callback(data);		
					}						
				} 
			else  
			 {
					memset(ring_data,0,sizeof(ring_data));
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
	 printf("电平反转\r\n");
	}
	if( data== 0x22){
HAL_GPIO_TogglePin (LED2_GPIO_Port,LED2_Pin);
	//代码
	}
	if( data== 0x33){
HAL_GPIO_TogglePin (LED3_GPIO_Port,LED3_Pin);
	//代码
	}
}









