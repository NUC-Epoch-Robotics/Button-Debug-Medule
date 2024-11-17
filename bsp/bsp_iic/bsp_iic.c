#include "bsp_iic.h"
#include "i2c.h"
#include "stm32f1xx_hal.h"



#define iic_clog_time 100


IIC_Work_State bsp_iic_init(IIC_faction* iic,  
                            IICInstance* bsp_iic,
														IICSend Send,
														IICReceive Receive,
														IICAccessMem AccessMem )
{
	if(iic ==NULL | bsp_iic== NULL )
	{
	  return IIC_error;
	 }
	if(Send==NULL | Receive==NULL |Receive==NULL )
	{
	  return IIC_error;
	}	
	 iic->bsp_iic              =bsp_iic;
	 iic->AccessMem            =AccessMem;
	 iic->Receive              =Receive;
	 iic->Send                 =Send;
	return IIC_OK;
}    


/*
*@brief IIC发送函数封装
*@param  iic      iic句柄
*@param  pData    发送数据首地址
*@param  Size     数据大小
*@param  IIC_Seq  IIC_SEQ_RELEASE 此次发送数据后释放总线
*                 IIC_SEQ_HOLDON  保持总线占有权不释放，可继续发送数据
*/
void IIC_Send(IICInstance* iic,uint16_t reg, uint8_t *pData, uint16_t Size, IIC_Work_Mode IIC_Seq,IIC_Work_Mode Work_Mode)
{

  switch (Work_Mode)
	{
	 case IIC_BLACK_MODE://阻塞模式
  	 if(IIC_Seq== IIC_SEQ_RELEASE)
    {
      HAL_I2C_Master_Transmit(iic->bsp_iic_Handle ,  reg , pData, Size, iic_clog_time );
	  }
		break;
	case IIC_IT_MODE:   //中断模式
	   if(IIC_Seq== IIC_SEQ_RELEASE)
    {
       HAL_I2C_Master_Seq_Transmit_IT(iic->bsp_iic_Handle ,  reg , pData, Size, I2C_OTHER_AND_LAST_FRAME);
    } 
     else if(IIC_Seq== IIC_SEQ_HOLDON)
	  {
	  	 HAL_I2C_Master_Seq_Transmit_IT(iic->bsp_iic_Handle ,  reg , pData, Size, I2C_OTHER_FRAME );
	  }
		break;
	case IIC_DMA_MODE: //DMA传输
		 if(IIC_Seq== IIC_SEQ_RELEASE)
    {
       HAL_I2C_Master_Seq_Transmit_DMA(iic->bsp_iic_Handle ,  reg , pData, Size, I2C_OTHER_AND_LAST_FRAME );
    } 
     else if(IIC_Seq== IIC_SEQ_HOLDON)
	  {
	  	 HAL_I2C_Master_Seq_Transmit_DMA(iic->bsp_iic_Handle ,  reg , pData, Size, I2C_OTHER_FRAME );
	  }
		break;
		default:
			while(1); //状态不在所设模式，停止传输；		
	}

}
/*
*@brief IIC接收函数封装，
*@param  iic      iic句柄
*@param  pData    接收数据首地址
*@param  Size     数据大小
*@param  IIC_Seq  IIC_SEQ_RELEASE 此次接收数据后释放总线
*                 IIC_SEQ_HOLDON  保持总线占有权不释放，可继续接收数据
*/

void IIC_Receive(IICInstance* iic,uint16_t reg, uint8_t *pData, uint16_t Size, IIC_Work_Mode IIC_Seq,IIC_Work_Mode Work_Mode)
{
  switch (Work_Mode)
	{
	 case IIC_BLACK_MODE://阻塞模式
  	 if(IIC_Seq== IIC_SEQ_RELEASE)
    {
      HAL_I2C_Master_Receive(iic->bsp_iic_Handle ,  reg, pData, Size, iic_clog_time );
    } 
     else if(IIC_Seq== IIC_SEQ_HOLDON)
	  {
	  	HAL_I2C_Master_Receive(iic->bsp_iic_Handle ,  reg , pData, Size, iic_clog_time );
	  }
		break;
	case IIC_IT_MODE:   //中断模式
	   if(IIC_Seq== IIC_SEQ_RELEASE)
    {
      HAL_I2C_Master_Seq_Receive_IT(iic->bsp_iic_Handle , reg , pData, Size, I2C_OTHER_AND_LAST_FRAME);
    } 
     else if(IIC_Seq== IIC_SEQ_HOLDON)
	  {
	  	HAL_I2C_Master_Seq_Receive_IT(iic->bsp_iic_Handle ,reg, pData, Size, I2C_OTHER_FRAME );
	  }
		break;
	case IIC_DMA_MODE: //DMA接收
		 if(IIC_Seq== IIC_SEQ_RELEASE)
    {
      HAL_I2C_Master_Seq_Receive_DMA(iic->bsp_iic_Handle , reg , pData, Size, I2C_OTHER_AND_LAST_FRAME );
    } 
     else if(IIC_Seq== IIC_SEQ_HOLDON)
	  {
	  	HAL_I2C_Master_Seq_Receive_DMA(iic->bsp_iic_Handle , reg , pData, Size, I2C_OTHER_FRAME );
	  }
		break;
		default:
			while(1); //状态不在所设模式，停止传输；
		
	}
}

//对寄存器操作
void IIC_AccessMem( IICInstance* iic, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout,IIC_Access_Mode Access_Mode)
{
	switch(Access_Mode)
	{
	case IIC_Write_Mem:
		HAL_I2C_Mem_Write(iic->bsp_iic_Handle,DevAddress, MemAddress,  MemAddSize,  pData,  Size,  Timeout);
    break;
   
	case IIC_Read_Mem:
		HAL_I2C_Mem_Read(iic->bsp_iic_Handle , DevAddress,  MemAddress,  MemAddSize,  pData,  Size,  Timeout);
    break;
	
	default:
	  while(1); //状态不在所设模式，停止传输；
	  
  }
}



