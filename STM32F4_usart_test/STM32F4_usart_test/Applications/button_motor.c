#include "button_motor.h"
#include "freertos.h"
#include "task.h"
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
#include "cmsis_os.h"
#include "queue.h"
#include "event_groups.h"
#include "cmsis_armcc.h"
//#include "elog.h"
//#include "elog_cfg.h"
//#include "event_groups.h"
//#include "shell_port.h"

#define LOG_TAG         "Button_mottor"
/*************** freeRTOS任、队列、事件组 extern定义 ****************/
extern osThreadId LED1_taskHandle;
extern osThreadId LED2_taskHandle;
extern osThreadId LED3_taskHandle;
extern osEventFlagsId_t EventKey1Handle;
extern osMessageQId queuekey1Handle;

/** 事件组宏定义 **/
#define Event_0 (1<<0)
#define Event_1 (1<<1)
#define Event_2 (1<<2)
#define Event_3 (1<<3)
#define Event_4 (1<<4)

/*********串口发送变量参数*****************/
FrameInstance frame1;
uint8_t Data1[18];
	
/*********串口接收变量参数*****************/
extern uint8_t DataBuff[BUF_SIZE]; 
stRingBuff Ring_Buff;            //循环数组
uint8_t ringbuff[RING_BUFF_SIZE];


//放初始化的代码   之后在freertos中调用完成初始化
void Buttonmotorinit()
{
  RingBufferinit(&Ring_Buff,ringbuff,RING_BUFF_SIZE );
	Data1[0]=0x11;
	Data1[1]=0x12;
	Data1[2]=0x13;
	Data1[3]=0x21;
	Data1[4]=0x22;
	Data1[5]=0x23;
	Data1[6]=0x31;
	Data1[7]=0x32;
	Data1[8]=0x33;
	Data1[9]=0x41;
	Data1[10]=0x42;
	Data1[11]=0x43;
	Data1[12]=0x51;
	Data1[13]=0x52;
	Data1[14]=0x53;
	Data1[15]=0x61;
	Data1[16]=0x62;
	Data1[17]=0x63;

   printf("init\r\n");
  frameInstance_init(&frame1,usart_W_DATA);
}



//freeRTOS执行按键任务
/***   执行按键任务  ***/
void button_task()
{

  osThreadSuspend(LED1_taskHandle);//单个任务挂起
	osThreadSuspend(LED2_taskHandle);//单个任务挂起
	osThreadSuspend(LED3_taskHandle);//单个任务挂起
	EventBits_t myEventBits_1=0;

		while(1)
		{
			myEventBits_1=xEventGroupWaitBits(EventKey1Handle,Event_0|Event_1|Event_2|Event_3|Event_4,pdTRUE,	pdFALSE,portMAX_DELAY);
				printf("myEventBits_1=%d\r\n",myEventBits_1);
		
				if(myEventBits_1 & Event_0)
					{
					osThreadSuspend(LED2_taskHandle);//单个任务挂起
					osThreadSuspend(LED3_taskHandle);//单个任务挂起
					osThreadResume(LED1_taskHandle);
					printf("任务1恢复，其余任务挂起\r\n");
				  }
		
				if(myEventBits_1 & Event_1)
				 { 
					osThreadSuspend(LED1_taskHandle);//单个任务挂起
					osThreadSuspend(LED3_taskHandle);//单个任务挂起
					osThreadResume(LED2_taskHandle);	
					printf("任务2恢复，其余任务挂起\r\n");
			   }
				 
				if(myEventBits_1 & Event_2)
				 {
					osThreadSuspend(LED2_taskHandle);//单个任务挂起
					osThreadSuspend(LED1_taskHandle);//单个任务挂起
					osThreadResume(LED3_taskHandle);
					printf("任务3恢复，其余任务挂起\r\n");
			   }
		
				if(myEventBits_1 & Event_3)//复位
				 { 
				 Stm32_SoftReset();
					 printf("ret\r\n");
				 }
				 
				 if(myEventBits_1 & Event_4)//驱动主控板向模块发送数据
				 { 
				
				 }
				 
         myEventBits_1=0;
				 vTaskDelay(200);
    }      
				
}
/***   执行蜂鸣器任务  ***/
void buzzer_task()
{	
	while(1)
	{		
		vTaskDelay(2000);	
	}
}

/*   执行LED */
void led1_task()
{
		while(1)
		{
      printf("电平反转1\r\n");			
	    vTaskDelay(200);
		}
}
		
void led2_task()
{
	while(1)
		{
      printf("电平反转2\r\n");			
	    vTaskDelay(200);
		}
}

void led3_task()
{
	while(1)
		{
      printf("电平反转3\r\n");			
	    vTaskDelay(200);
		}
}

/*串口接收回调*/
/* 主控板可在这使用挂起函数使任务单个执行*/
/*通过构造队列，接收到数据后写队列，之后在单独的一个任务中进行任务挂起*/
/****   使用事件组控制任务单个或多个执行    *****/
void User_rx_Callback(uint8_t data)
{
	xEventGroupClearBitsFromISR(EventKey1Handle,Event_0|Event_1|Event_2|Event_3 );
  BaseType_t xHigherPriorityTaskWoken;      
//	uint8_t queue_flag=0;    
	 
	if( data==0x11)
	 {
	  //代码
		/* 事件组 */
    xHigherPriorityTaskWoken = pdFALSE;
   	xEventGroupSetBitsFromISR(EventKey1Handle,Event_0,&xHigherPriorityTaskWoken);
    printf("data1\r\n");

		/* 写队列 */
//		 	queue_flag=1;
//	xQueueSendFromISR(queuekey1Handle, &queue_flag, NULL);
	 }
	 
	if( data== 0x12)
	 {
	  //代码
	/* 事件组 */
    xHigherPriorityTaskWoken = pdFALSE;
	  xEventGroupSetBitsFromISR(EventKey1Handle,Event_1,&xHigherPriorityTaskWoken);
   printf("data2\r\n");
		/* 写队列 */
	//	xQueueSendFromISR(queuekey1Handle, &queue_flag, NULL);
	 }
	 
	if( data== 0x13)
	 {
	  //代码
		/* 事件组 */
    xHigherPriorityTaskWoken = pdFALSE;
	  xEventGroupSetBitsFromISR(EventKey1Handle,Event_2,&xHigherPriorityTaskWoken);
    printf("data3\r\n");

		/* 写队列 */
	//	xQueueSendFromISR(queuekey1Handle, &queue_flag, NULL);
 	 }
	 
	 if( data== 0x21)//复位
	 {	 
    xHigherPriorityTaskWoken = pdFALSE;
	  xEventGroupSetBitsFromISR(EventKey1Handle,Event_3,&xHigherPriorityTaskWoken);
		  printf("data4\r\n");
 	 }
	 
	 if( data== 0x22)//驱动主控板向模块发送数据
	 {	 
    xHigherPriorityTaskWoken = pdFALSE;
	  xEventGroupSetBitsFromISR(EventKey1Handle,Event_4,&xHigherPriorityTaskWoken);
		  printf("data5\r\n");
 	 }
}


/*  空闲回调函数  */
/*主板任务多的话可使用commit发送不同的命令来操控更多的任务实现不同功能*/
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart,uint16_t Size)
{
	uint8_t cnt =0;
	uint8_t ring_data[RING_BUFF_SIZE];	
	
	WriteRingBuffer(&Ring_Buff,DataBuff, DataBuff[4]+6);
	memset(ring_data,0,sizeof(ring_data));
	ReadRingBuffer(&Ring_Buff,ring_data , DataBuff[4]+6);   

 if( huart->Instance == UART7)
   {   
				if(ring_data[0] == usart_frame1_hand&&
					 ring_data[1] == usart_frame2_hand&& 
					 ring_data[2] == usart_frame1_hand  )   //检测是否是包头  //DataBuff[%d]=	 
			 {  
			cnt = ring_data[4];
			cnt+=4;

			if(ring_data[cnt+1] == usart_frame_end ) 
				{ 
					  for(int i=0;i<=cnt;i++){
			      uint8_t data= ring_data[i+5];
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



/*  软件复位  */
void Stm32_SoftReset(void)
 {
  __set_FAULTMASK(1);//禁止所有的可屏蔽中断
   HAL_NVIC_SystemReset();//软件复位
 }

