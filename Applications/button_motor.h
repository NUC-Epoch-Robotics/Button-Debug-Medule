#ifndef __BUTTON_MOTOR_H
#define __BUTTON_MOTOR_H

#include "gpio.h"


void Buttonmotorinit(void);
void User_rx_Callback(uint8_t data);
void user_TIM2_IRQHandler(void);
#endif

