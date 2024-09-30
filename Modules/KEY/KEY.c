#include "KEY.h"
#include "multi_button.h"
#include "main.h"   
#include "gpio.h"

#include "stm32f1xx_hal.h"

uint8_t KEY_flag ;

struct Button button1;
struct Button button2;
struct Button button3;
struct Button button4;
struct Button button5;
struct Button button6;

uint8_t read_button1_GPIO()
{
    return HAL_GPIO_ReadPin(KEY1_GPIO_Port, KEY1_Pin);
}

uint8_t read_button2_GPIO()
{
    return HAL_GPIO_ReadPin(KEY2_GPIO_Port, KEY2_Pin);
}

uint8_t read_button3_GPIO()
{
    return HAL_GPIO_ReadPin(KEY3_GPIO_Port, KEY3_Pin);
}

uint8_t read_button4_GPIO()
{
    return HAL_GPIO_ReadPin(KEY4_GPIO_Port, KEY4_Pin);
}
uint8_t read_button5_GPIO()
{
    return HAL_GPIO_ReadPin(KEY5_GPIO_Port, KEY5_Pin);
}

uint8_t read_button6_GPIO()
{
    return HAL_GPIO_ReadPin(KEY6_GPIO_Port, KEY6_Pin);
}



void button1_callback(void *button)
{
    uint32_t btn_event_val;

    btn_event_val = get_button_event((struct Button *)button);

    switch (btn_event_val)
    {
    case PRESS_DOWN:

        break;

    case PRESS_UP:

        break;

    case PRESS_REPEAT:

        break;

    case SINGLE_CLICK:
			     HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
        
        break;

		
    case DOUBLE_CLICK:
			
        HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
        break;

    

    case LONG_PRESS_HOLD:

        break;
    }
}


void button2_callback(void *button)
{
    uint32_t btn_event_val;

    btn_event_val = get_button_event((struct Button *)button);

    switch (btn_event_val)
    {
    case PRESS_DOWN:

        break;

    case PRESS_UP:

        break;

    case PRESS_REPEAT:

        break;

    case SINGLE_CLICK:
			     HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
        
        break;
    case DOUBLE_CLICK:
			
        HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
        break;
    case LONG_PRESS_HOLD:

        break;
    }
}


void button3_callback(void *button)
{
    uint32_t btn_event_val;

    btn_event_val = get_button_event((struct Button *)button);

    switch (btn_event_val)
    {
    case PRESS_DOWN:

        break;

    case PRESS_UP:

        break;

    case PRESS_REPEAT:

        break;

    case SINGLE_CLICK:
			     HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
        
        break;

		
    case DOUBLE_CLICK:
			
        HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
        break;

    

    case LONG_PRESS_HOLD:

        break;
    }
}


void button4_callback(void *button)
{
    uint32_t btn_event_val;

    btn_event_val = get_button_event((struct Button *)button);

    switch (btn_event_val)
    {
    case PRESS_DOWN:

        break;

    case PRESS_UP:

        break;

    case PRESS_REPEAT:

        break;

    case SINGLE_CLICK:
			     HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
        
        break;

		
    case DOUBLE_CLICK:
			
        HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
        break;

    

    case LONG_PRESS_HOLD:

        break;
    }
}


void button5_callback(void *button)
{
    uint32_t btn_event_val;

    btn_event_val = get_button_event((struct Button *)button);

    switch (btn_event_val)
    {
    case PRESS_DOWN:

        break;

    case PRESS_UP:

        break;

    case PRESS_REPEAT:

        break;

    case SINGLE_CLICK:
			     HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
        
        break;

		
    case DOUBLE_CLICK:
			
        HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
        break;
    case LONG_PRESS_HOLD:

        break;
    }
}

void button6_callback(void *button)
{
    uint32_t btn_event_val;

    btn_event_val = get_button_event((struct Button *)button);

    switch (btn_event_val)
    {
    case PRESS_DOWN:

        break;

    case PRESS_UP:

        break;

    case PRESS_REPEAT:

        break;

    case SINGLE_CLICK:
			     HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
        
        break;

		
    case DOUBLE_CLICK:
			
        HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
        break;

    

    case LONG_PRESS_HOLD:

        break;
    }
}


void KEY_Init(void)
{

    button_init(&button1, read_button1_GPIO, 0);
    button_attach(&button1, 	SINGLE_CLICK, button1_callback);
    button_attach(&button1, DOUBLE_CLICK, button1_callback);
    button_attach(&button1, LONG_PRESS_START, button1_callback);
	
	  button_init(&button2, read_button2_GPIO, 0);
    button_attach(&button2, 	SINGLE_CLICK, button2_callback);
    button_attach(&button2, DOUBLE_CLICK, button2_callback);
    button_attach(&button2, LONG_PRESS_START, button2_callback);
	
	  button_init(&button3, read_button3_GPIO, 0);
    button_attach(&button3, 	SINGLE_CLICK, button3_callback);
    button_attach(&button3, DOUBLE_CLICK, button3_callback);
    button_attach(&button3, LONG_PRESS_START, button3_callback);
	
	  button_init(&button4, read_button4_GPIO, 0);
    button_attach(&button4, 	SINGLE_CLICK, button4_callback);
    button_attach(&button4, DOUBLE_CLICK, button4_callback);
    button_attach(&button4, LONG_PRESS_START, button4_callback);
	
	  button_init(&button5, read_button5_GPIO, 0);
    button_attach(&button5, 	SINGLE_CLICK, button5_callback);
    button_attach(&button5, DOUBLE_CLICK, button5_callback);
    button_attach(&button5, LONG_PRESS_START, button5_callback);
		
	  button_init(&button6, read_button6_GPIO, 0);
    button_attach(&button6, 	SINGLE_CLICK, button6_callback);
    button_attach(&button6, DOUBLE_CLICK, button6_callback);
    button_attach(&button6, LONG_PRESS_START, button6_callback);
	 
	
    button_start(&button1);
    button_start(&button2);
		button_start(&button3);
    button_start(&button4);
		button_start(&button5);
    button_start(&button6);
		
}




