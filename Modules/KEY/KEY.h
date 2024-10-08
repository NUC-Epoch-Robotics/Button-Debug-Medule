#ifndef __KEY_H
#define __KEY_H

#include "stm32f1xx_hal.h"

// uint8_t read_button1_GPIO();
// uint8_t read_button2_GPIO();

void button1_callback(void *button);
void button2_callback(void *button);

void KEY_Init(void);

#endif
