#include "bsp_spi.h"

SPI_Work_State bsp_spi_init(SPI_faction* spi,
														SPIInstance* bsp_spi,
														SPITransmit   transmit,            
                            SPIReceive    receive,  
                            SPITransRecv  transRecv)
{                                    
	
	if(spi->bsp_spi->bsp_spi_Handle ==NULL )                                        
	{                                                                               
	  return SPI_error;                                                             
	 }
	 spi->Receive      =receive;
	 spi->Transmit     =transmit;
	 spi->TransRecv    =transRecv;
   spi->bsp_spi      = bsp_spi;	 
	return SPI_OK;
}    



//基于HAL库的SPI发送函数的封装
SPI_Work_State SPI_Transmit(SPIInstance* spi, uint8_t *pData, uint16_t size, SPI_Work_Mode Work_Mode)
{
		HAL_GPIO_WritePin(spi->BSP_SPI_Chip_Select_GPIOX,spi->BSP_SPI_Chip_Select_PIN ,GPIO_PIN_RESET );
		switch(Work_Mode )
		{
      case SPI_IT_MODE:
			 HAL_SPI_Transmit_IT(spi->bsp_spi_Handle , pData, size);
			return SPI_OK;
			
			 case SPI_DMA_MODE:
			 HAL_SPI_Transmit_DMA(spi->bsp_spi_Handle , pData, size);
			return SPI_OK;
			
			case SPI_BLACK_MODE:
		  	HAL_SPI_Transmit(spi->bsp_spi_Handle , pData, size,100);
		 	HAL_GPIO_WritePin(spi->BSP_SPI_Chip_Select_GPIOX,spi->BSP_SPI_Chip_Select_PIN ,GPIO_PIN_SET );
		return SPI_OK;
			
			default:
	   return SPI_error;
			
		}
}
//基于HAL库的SPI接收函数的封装
SPI_Work_State SPI_Receive(SPIInstance* spi, uint8_t *pData, uint16_t size, SPI_Work_Mode Work_Mode)
{
		HAL_GPIO_WritePin(spi->BSP_SPI_Chip_Select_GPIOX,spi->BSP_SPI_Chip_Select_PIN ,GPIO_PIN_RESET );
		switch( Work_Mode )
		{
      case SPI_IT_MODE:
			 HAL_SPI_Receive_IT(spi->bsp_spi_Handle , pData, size);
		  		return SPI_OK;
			
			case SPI_DMA_MODE:
			 HAL_SPI_Receive_DMA(spi->bsp_spi_Handle , pData, size);
			 	return SPI_OK;
			
			case SPI_BLACK_MODE:
		   HAL_SPI_Receive(spi->bsp_spi_Handle , pData, size,100);
			 // 阻塞模式不会调用回调函数,传输完成后直接拉高片选结束
		 	 HAL_GPIO_WritePin(spi->BSP_SPI_Chip_Select_GPIOX,spi->BSP_SPI_Chip_Select_PIN ,GPIO_PIN_SET );
		   	return SPI_OK;
			
		  default:
	      return SPI_error;
			 
		}
}

//基于HAL库的SPI读写字节函数
SPI_Work_State SPI_TransRecv(SPIInstance* spi, uint8_t *txData, uint8_t *rxData, uint16_t size, SPI_Work_Mode Work_Mode)
{
 	HAL_GPIO_WritePin(spi->BSP_SPI_Chip_Select_GPIOX,spi->BSP_SPI_Chip_Select_PIN ,GPIO_PIN_RESET );
		switch(Work_Mode )
		{
      case SPI_IT_MODE:
			 HAL_SPI_TransmitReceive_IT(spi->bsp_spi_Handle , txData, rxData, size);
		  return SPI_OK;
			
			case SPI_DMA_MODE:
			 HAL_SPI_TransmitReceive_DMA(spi->bsp_spi_Handle , txData, rxData, size);
			 return SPI_OK;
			
			case SPI_BLACK_MODE:
		   HAL_SPI_TransmitReceive(spi->bsp_spi_Handle, txData, rxData, size,1000);
			 // 阻塞模式不会调用回调函数,传输完成后直接拉高片选结束
		 	 HAL_GPIO_WritePin(spi->BSP_SPI_Chip_Select_GPIOX,spi->BSP_SPI_Chip_Select_PIN ,GPIO_PIN_SET );
		   return SPI_OK;
			
		  default:
	       return SPI_error;
		
		}
	}




