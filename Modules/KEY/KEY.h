#ifndef __KEY_H__
#define __KEY_H__

#include "stm32f1xx_hal.h"

#define KEY1 1
#define KEY2 2
#define KEY3 3
#define KEY4 4
#define KEY5 5  
#define KEY6 6

uint8_t read_button_GPIO(uint8_t KEY_nun);
KEY_EVENT button1_callback(void *button);
KEY_EVENT button2_callback(void *button);
KEY_EVENT button3_callback(void *button);
KEY_EVENT button4_callback(void *button);
KEY_EVENT button5_callback(void *button);
KEY_EVENT button6_callback(void *button);

typedef enum
{
    KEY1_SINGLE_CLICK = 0,
    KEY1_DOUBLE_CLICK,
    KEY1_LONG_PRESS,
    KEY2_SINGLE_CLICK,
    KEY2_DOUBLE_CLICK,
    KEY2_LONG_PRESS,
    KEY3_SINGLE_CLICK,
    KEY3_DOUBLE_CLICK,
    KEY3_LONG_PRESS,
    KEY4_SINGLE_CLICK,
    KEY4_DOUBLE_CLICK,
    KEY4_LONG_PRESS,
    KEY5_SINGLE_CLICK,
    KEY5_DOUBLE_CLICK,
    KEY5_LONG_PRESS,
    KEY6_SINGLE_CLICK,
    KEY6_DOUBLE_CLICK,
    KEY6_LONG_PRESS,
} KEY_EVENT;
#endif



