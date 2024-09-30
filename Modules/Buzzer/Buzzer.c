#include "Buzzer.h"
#include "tim.h"


void Buzzer_init()
{
  HAL_TIM_PWM_Init(&htim3);// 初始化定时器的PWM模式
  HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_3);// 启动定时器的PWM模式	
}

void Buzzer_off(void)
{	
	HAL_TIM_PWM_Stop(&htim3,TIM_CHANNEL_3);// 停止定时器的PWM输出
}

void Buzzzer_on(uint16_t Pulse)
{
  __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_3,Pulse);	
}









