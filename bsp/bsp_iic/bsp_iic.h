#ifndef __BSP_IIC_H
#define __BSP_IIC_H

#include "gpio.h"
#include "tim.h"

typedef struct IIC_faction_t IIC_faction;

typedef enum
{
IIC_BLACK_MODE=0,//阻塞模式
IIC_IT_MODE,     //中断模式
IIC_DMA_MODE,     //DMA传输

}IIC_Work_Mode;

typedef enum
{
	IIC_Write_Mem = 0,//写寄存器
	IIC_Read_Mem,     //读寄存器
	
}IIC_Access_Mode;


typedef enum   //返回状态，语句是否为空，若函数执行完后返回IIC_OK
{
	IIC_error,
	IIC_OK,	
} IIC_Work_State;


typedef enum
{
	 IIC_SEQ_RELEASE= 0,     // 完成传输后释放总线占有权,这是默认的传输方式
   IIC_SEQ_HOLDON ,        // 保持总线占有权不释放,只支持IT和DMA模式	
} IIC_Seq_Mode;


typedef struct iic_temp_s
{
	I2C_HandleTypeDef* bsp_iic_Handle;
	
	GPIO_TypeDef*   BSP_IIC_SDA_GPIOX;//IIC GPIO类型
	uint16_t        BSP_IIC_SDA_PIN; //IIC GPIO引脚	 
	GPIO_TypeDef*   BSP_IIC_SCL_GPIOX;//IIC GPIO类型
	uint16_t        BSP_IIC_SCL_PIN; //IIC GPIO引脚	 
	
}IICInstance;

struct IIC_faction_t
{
	 IICInstance* bsp_iic;
	 void(*Send)(IICInstance* iic,uint16_t reg, uint8_t *pData, uint16_t Size, IIC_Work_Mode IIC_Seq,IIC_Work_Mode Work_Mode);
	 void(*Receive)(IICInstance* iic,uint16_t reg, uint8_t *pData, uint16_t Size, IIC_Work_Mode IIC_Seq,IIC_Work_Mode Work_Mode);
	 void(*AccessMem)( IICInstance* iic, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout,IIC_Access_Mode Access_Mode);
};


typedef void(*IICSend)(IICInstance* iic,uint16_t reg, uint8_t *pData, uint16_t Size, IIC_Work_Mode IIC_Seq,IIC_Work_Mode Work_Mode);
typedef void(*IICReceive)(IICInstance* iic,uint16_t reg, uint8_t *pData, uint16_t Size, IIC_Work_Mode IIC_Seq,IIC_Work_Mode Work_Mode);
typedef void(*IICAccessMem)( IICInstance* iic, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout,IIC_Access_Mode Access_Mode);


/*
*@brief IIC发送函数封装
*@param  iic      iic结构体指针
*@param  pData    发送数据首地址
*@param  Size     数据大小
*@param  IIC_Seq  IIC_SEQ_RELEASE 此次发送数据后释放总线
*                 IIC_SEQ_HOLDON  保持总线占有权不释放，可继续发送数据
*/
void IIC_Send(IICInstance* iic,uint16_t reg, uint8_t *pData, uint16_t Size, IIC_Work_Mode IIC_Seq,IIC_Work_Mode Work_Mode);

/*
*@brief IIC接收函数封装
*@param  iic      iic结构体指针
*@param  pData    接收数据首地址
*@param  Size     数据大小
*@param  IIC_Seq  IIC_SEQ_RELEASE 此次接收数据后释放总线
*                 IIC_SEQ_HOLDON  保持总线占有权不释放，可继续接收数据
*/
void IIC_Receive(IICInstance* iic,uint16_t reg, uint8_t *pData, uint16_t Size, IIC_Work_Mode IIC_Seq,IIC_Work_Mode Work_Mode);
/*
*@brief 对指定寄存器进行读写
*@param  iic           iic句柄
*@param  mem_addr      要读取的从机内存地址,目前只支持8位地址
*@param  pData         接收数据首地址
*@param  Size          要读取或写入的数据长度
*@param  mem8bit_flag  从机内存地址是否为8位
*/
void IIC_AccessMem( IICInstance* iic, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout,IIC_Access_Mode Access_Mode);


/* 初始化函数 */
IIC_Work_State bsp_iic_init(IIC_faction* iic,  
                            IICInstance* bsp_iic,
														IICSend Send,
														IICReceive Receive,
														IICAccessMem AccessMem );


#endif


