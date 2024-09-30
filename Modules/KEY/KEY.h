#ifndef __KEY_H
#define __KEY_H

#include "stm32f1xx_hal.h"

 uint8_t read_button1_GPIO(void);
 uint8_t read_button2_GPIO(void);
 uint8_t read_button3_GPIO(void);
 uint8_t read_button4_GPIO(void);
 uint8_t read_button5_GPIO(void);
 uint8_t read_button6_GPIO(void);
 
typedef enum {
	KEY1_PRESS_DOWN = 0,
	KEY1_PRESS_UP,
  KEY1_PRESS_REPEAT,
	KEY1_SINGLE_CLICK,
	KEY1_DOUBLE_CLICK,
	KEY1_LONG_PRESS_START,
	KEY1_LONG_PRESS_HOLD,
	KEY1_number_of_event,
	KEY1_NONE_PRESS
}Key1PressEvent;


void button1_callback(void *button);
void button2_callback(void *button);
void button3_callback(void *button);
void button4_callback(void *button);
void button5_callback(void *button);
void button6_callback(void *button);
void KEY_Init(void);

#endif  

