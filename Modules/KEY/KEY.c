#include "KEY.h"
#include "stdio.h"
#include "usart.h"


/**************************************************************************************************** 
*                             长按、单击、双击定义
* 长按事件：任何大于 KEY_LONG_PRESS_TIME 
* 单击事件：按下时间不超过 KEY_LONG_PRESS_TIME 且 释放后 KEY_WAIT_DOUBLE_TIME 内无再次按下的操作
* 双击事件：俩次短按时间间隔小于KEY_WAIT_DOUBLE_TIME，俩次短按操作合并为一次双击事件。
* 特殊说明：
*          1.短按和长按时间间隔小于 KEY_WAIT_DOUBLE_TIME，响应一次单击和长按事件，不响应双击事件
*          2.连续2n次短按，且时间间隔小于 KEY_WAIT_DOUBLE_TIME，响应为n次双击
*          3.连续2n+1次短按，且时间间隔小于 KEY_WAIT_DOUBLE_TIME，且最后一次KEY_WAIT_DOUBLE_TIME内无操作，
*				响应为n次双击 和 一次单击事件
****************************************************************************************************/
#define KEY_LONG_PRESS_TIME           50 // 20ms*50 = 1s  
#define KEY_LONG_SECOND_PRESS_TIME  50// 20ms*50 = 1s 
#define KEY_WAIT_DOUBLE_TIME 25// 20ms*25 = 500   
#define KEY_PRESSED_LEVEL     0     //  按键按下是电平为低    
                                                    
/**************************************************************************************************** 
*                            按键配置信息的全局结构体变量
****************************************************************************************************/
static KEY_PinLevel_TypeDef KEY_ReadPin(void);   // 按键读取按键的电平函数
static void KEY_GetAction(void); // 获取按键是按下还是释放，保存到结构体
/**************************************************************************************************** 
*                             全局变量
*******************************************
*********************************************************/
KEY_Configure_TypeDef KeyCfg;

void key_init(KEY_Configure_TypeDef* key)
{

key->KEY_Count  =		0,						        //按键长按计数
key->KEY_Action =		KEY_Action_Release;		//按键动作，按下或者抬起
key->KEY_Status =		KEY_Status_Idle;      //按键状态
key->KEY_Event  =		KEY_Event_Null;       //按键事件
key ->KEY_ReadPin_Fcn =		KEY_ReadPin;    //读IO电平函数
}




/**************************************************************************************************** 
*                             函数定义
****************************************************************************************************/
// 按键读取按键的电平函数，更具实际情况修改
static KEY_PinLevel_TypeDef KEY_ReadPin(void) //按键读取函数
{
  return (KEY_PinLevel_TypeDef) HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin);
}
             

// 获取按键动作，按下或释放，保存到结构体
static void KEY_GetAction(void) 
{
	if(KeyCfg.KEY_ReadPin_Fcn() == KEY_PRESSED_LEVEL)
	{
		KeyCfg.KEY_Action = KEY_Action_Press;
	}
	else
	{
		KeyCfg.KEY_Action =  KEY_Action_Release;
	}
 
}




/**************************************************************************************************** 
*                             读取按键状态机
****************************************************************************************************/
void KEY_ReadStateMachine(void)
{
    KEY_GetAction();
//			KeyCfg.KEY_Event = KEY_Event_Null;
//	    KeyCfg.KEY_Count = 0;
	switch(KeyCfg.KEY_Status)
	{
		
		//状态：没有按键按下
		case KEY_Status_Idle:
			if(KeyCfg.KEY_Action == KEY_Action_Press)
			{
				KeyCfg.KEY_Status = KEY_Status_Debounce;
				KeyCfg.KEY_Event = KEY_Event_Null;
				//KeyCfg.KEY_Count++;
			}
			else
			{
				KeyCfg.KEY_Status = KEY_Status_Idle;
				KeyCfg.KEY_Event = KEY_Event_Null;
			}
			break;
			
		//状态：消抖
		case KEY_Status_Debounce:
			if(KeyCfg.KEY_Action == KEY_Action_Press)
			{
				KeyCfg.KEY_Status = KEY_Status_ConfirmPress;
				KeyCfg.KEY_Event = KEY_Event_Null;
			}
			else
			{
				KeyCfg.KEY_Status = KEY_Status_Idle;
				KeyCfg.KEY_Event = KEY_Event_Null;
			}
			break;	


		//状态：继续按下
		case KEY_Status_ConfirmPress:
			if( (KeyCfg.KEY_Action == KEY_Action_Press) && ( KeyCfg.KEY_Count >= KEY_LONG_PRESS_TIME))
			{
				KeyCfg.KEY_Status = KEY_Status_ConfirmPressLong;
				KeyCfg.KEY_Event = KEY_Event_Null;
				KeyCfg.KEY_Count = 0;
			}
		else if( (KeyCfg.KEY_Action == KEY_Action_Press) && (KeyCfg.KEY_Count < KEY_LONG_PRESS_TIME))
			{
				KeyCfg.KEY_Count++;
				KeyCfg.KEY_Status = KEY_Status_ConfirmPress;
				KeyCfg.KEY_Event = KEY_Event_Null;
			}
		else
			{
				KeyCfg.KEY_Count = 0;
				KeyCfg.KEY_Status = KEY_Status_WaiteAgain;// 按短了后释放
				KeyCfg.KEY_Event = KEY_Event_Null;

			}
		break;	
			
		//状态：一直长按着
		case KEY_Status_ConfirmPressLong:
			if(KeyCfg.KEY_Action == KEY_Action_Press) 
			{   // 一直等待其放开
				KeyCfg.KEY_Status = KEY_Status_ConfirmPressLong;
				KeyCfg.KEY_Event = KEY_Event_Null;
				KeyCfg.KEY_Count = 0;
			}
		  else
			{
				KeyCfg.KEY_Status = KEY_Status_Idle;
				KeyCfg.KEY_Event = KEY_Event_LongPress;//33333333333333
				KeyCfg.KEY_Count = 0;
			}
		break;	
			
		//状态：等待是否再次按下
		case KEY_Status_WaiteAgain:
			if((KeyCfg.KEY_Action != KEY_Action_Press) && ( KeyCfg.KEY_Count >= KEY_WAIT_DOUBLE_TIME))
			{   // 第一次短按,且释放时间大于KEY_WAIT_DOUBLE_TIME
				KeyCfg.KEY_Count = 0;
				KeyCfg.KEY_Status = KEY_Status_Idle;  
				KeyCfg.KEY_Event = KEY_Event_SingleClick;// 响应单击11111
				
			}
			else if((KeyCfg.KEY_Action != KEY_Action_Press) && ( KeyCfg.KEY_Count < KEY_WAIT_DOUBLE_TIME))
			{// 第一次短按,且释放时间还没到KEY_WAIT_DOUBLE_TIME
				KeyCfg.KEY_Count ++;
				KeyCfg.KEY_Status = KEY_Status_WaiteAgain;// 继续等待
				KeyCfg.KEY_Event = KEY_Event_Null;
				
			}
			else  if((KeyCfg.KEY_Action == KEY_Action_Press) && ( KeyCfg.KEY_Count < KEY_WAIT_DOUBLE_TIME))// 第一次短按,且还没到KEY_WAIT_DOUBLE_TIME 第二次被按下
			{
				KeyCfg.KEY_Count = 0;
			//	KeyCfg.KEY_Count++;
				KeyCfg.KEY_Status = KEY_Status_SecondPress;// 第二次按下
				KeyCfg.KEY_Event = KEY_Event_Null;
			}
			break;		
		case KEY_Status_SecondPress:
			if( (KeyCfg.KEY_Action == KEY_Action_Press) && ( KeyCfg.KEY_Count >= KEY_LONG_SECOND_PRESS_TIME))
			{
				KeyCfg.KEY_Status =KEY_Status_ConfirmPressLong;// KEY_Status_Idle;//第二次按的时间大于 KEY_LONG_PRESS_TIME
				KeyCfg.KEY_Event = KEY_Event_SingleClick; // 先响应单击11111111
				KeyCfg.KEY_Count = 0;
			}
			else if( (KeyCfg.KEY_Action == KEY_Action_Press) && ( KeyCfg.KEY_Count < KEY_LONG_SECOND_PRESS_TIME))
			{
        KeyCfg.KEY_Count ++;
				KeyCfg.KEY_Status = KEY_Status_SecondPress;
				KeyCfg.KEY_Event = KEY_Event_Null;
			}
            else 
            {// 第二次按下后在 KEY_LONG_PRESS_TIME内释放
        KeyCfg.KEY_Count = 0;
				KeyCfg.KEY_Status = KEY_Status_Idle;
				KeyCfg.KEY_Event = KEY_Event_DoubleClick; // 响应双击222222222222
            }
			break;	
		default:
			break;
	}
}

void user_TIM2_IRQHandler(void)   //TIM3中断
{
	KEY_ReadStateMachine();  //调用状态机
			
			if(KeyCfg.KEY_Event == KEY_Event_SingleClick)
			{
		//	HAL_GPIO_TogglePin(LED1_GPIO_Port,LED1_Pin);
				printf("111\r\n");//事件处理
			}
			else if(KeyCfg.KEY_Event == KEY_Event_DoubleClick)
			{
				printf("222\r\n");//事件处理
			//HAL_GPIO_TogglePin(LED2_GPIO_Port,LED2_Pin);
			}

			else if(KeyCfg.KEY_Event == KEY_Event_LongPress)
			{
				printf("333\r\n");//事件处理
			//	HAL_GPIO_TogglePin(LED3_GPIO_Port,LED3_Pin);
			}
			

}

