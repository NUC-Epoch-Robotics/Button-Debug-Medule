#ifndef __SELF_DEF_MASSAGE_H
#define __SELF_DEF_MASSAGE_H

#include "gpio.h"

#define usart_frame_hand1 0x5A    //帧头
#define usart_frame_hand2 0xA5    //帧头

#define usart_frame_end2  0xD0    //帧尾

#define usart_W_REG            0x80                     //USART写寄存器指令
#define usart_R_REG            0x81                     //USART读寄存器指令
#define usart_W_DATA           0x82                     //USART写数据指令
#define usart_R_DATA           0x83                     //USART读数据指令
 
#define USART_PACKAGE_LEN  1024

/*数据帧*/
/*串口帧发送结构体*/  
typedef struct 
{  
    uint16_t send_sum_len;          //要发送的帧数据长度  
    uint8_t  send_cur_len;          //当前已经发送的数据长度  
    uint8_t  send_flag;             //是否发送标志  
    uint8_t * send_data;            //指向要发送的数据缓冲区  
}uart_send_struct;  

typedef struct 
{  
    uint8_t * dst_buf;                  //指向接收缓存  
    uint8_t sfd;                        //帧首标志,为0xFF或者0xEE  
    uint8_t sfd_flag;                   //找到帧首,一般是3~5个FF或EE  
    uint8_t sfd_count;                  //帧首的个数,一般3~5个  
    uint8_t received_len;               //已经接收的字节数  
    uint8_t find_fram_flag;             //找到完整帧后,置1  
    uint8_t frame_len;                  //本帧数据总长度，这个区域是可选的  
}find_frame_struct;


#endif


