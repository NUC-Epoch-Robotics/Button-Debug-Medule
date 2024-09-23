/*
 * Copyright (c) 2016 Zibin Zheng <znbin@qq.com>
 * All rights reserved
 */

#ifndef _MULTI_BUTTON_H_
#define _MULTI_BUTTON_H_

#include <stdint.h>
#include <string.h>

//According to your need to modify the constants.
#define TICKS_INTERVAL    5	//ms
#define DEBOUNCE_TICKS    3	//MAX 7 (0 ~ 7)
#define SHORT_TICKS       (300 /TICKS_INTERVAL)
#define LONG_TICKS        (1000 /TICKS_INTERVAL)


typedef void (*BtnCallback)(void*);

typedef enum {
	PRESS_DOWN = 0,     // 按键按下，每次按下都触发
	PRESS_UP,			// 按键弹起，每次松开都触发			
	PRESS_REPEAT,		// 重复按下触发，变量repeat计数连击次数
	SINGLE_CLICK,		// 单击按键事件
	DOUBLE_CLICK,		// 双击按键事件
	LONG_PRESS_START,	// 达到长按时间阈值时触发一次
	LONG_PRESS_HOLD,	// 长按期间一直触发
	number_of_event,	//事件种类数
	NONE_PRESS
}PressEvent;

typedef struct Button {
	uint16_t ticks;
	uint8_t  repeat : 4; 					  // 记录连击次数
	uint8_t  event : 4;	  					  // 记录具体事件
	uint8_t  state : 3;	 					  // 下一个要跳转的状态，用于状态的切换
	uint8_t  debounce_cnt : 3;  			  // 记录持续次数（每次固定时间，用于去抖）
	uint8_t  active_level : 1; 				  // 有效电平（按键按下时的电平）
	uint8_t  button_level : 1;  			  // 记录当前的电平
	uint8_t  (*hal_button_Level)(void);		  // 函数指针（指向获取当前按键电平的函数）
	BtnCallback  cb[number_of_event];   	  // 函数指针数组：分别指向各个事件的回调函数
	struct Button* next;

}Button;

#ifdef __cplusplus
extern "C" {
#endif

void button_init(struct Button* handle, uint8_t(*pin_level)(), uint8_t active_level);
void button_attach(struct Button* handle, PressEvent event, BtnCallback cb);
PressEvent get_button_event(struct Button* handle);
int  button_start(struct Button* handle);
void button_stop(struct Button* handle);
void button_ticks(void);

#ifdef __cplusplus
}
#endif

#endif
