#ifndef __BSP_SPI_H
#define __BSP_SPI_H

#include "gpio.h"
#include "tim.h"

typedef struct SPI_faction_t  SPI_faction;

typedef enum
{
	SPI_Write_Mem = 0,//写寄存器
	SPI_Read_Mem,     //读寄存器	
}SPI_Access_Mode;

typedef enum
{
SPI_BLACK_MODE=0,//阻塞模式
SPI_IT_MODE,     //中断模式
SPI_DMA_MODE,     //DMA传输
}SPI_Work_Mode;


typedef enum
{
	SPI_error,
	SPI_OK,	
  
} SPI_Work_State;



typedef struct spi_temp_s
{
	SPI_HandleTypeDef* bsp_spi_Handle;
	
	GPIO_TypeDef*   BSP_SPI_MISO_GPIOX;//SPI 对应的GPIO
	uint16_t        BSP_SPI_MISO_PIN;  //SPI GPIO引脚号

	GPIO_TypeDef*   BSP_SPI_MOSI_GPIOX;//SPI 对应的GPIO
	uint16_t        BSP_SPI_MOSI_PIN;  //SPI GPIO引脚号	GPIO_TypeDef*   BSP_SPI_GPIOX;//SPI 对应的GPIO

	GPIO_TypeDef*   BSP_SPI_SCK_GPIOX;//SPI 对应的GPIO
	uint16_t        BSP_SPI_SCK_PIN;  //SPI GPIO引脚号
	
	GPIO_TypeDef*   BSP_SPI_IQR_GPIOX;//SPI 对应的GPIO
	uint16_t        BSP_SPI_IQR_PIN;  //SPI GPIO引脚号
	
	GPIO_TypeDef*   BSP_SPI_Chip_EN_GPIOX;//SPI 对应的GPIO
	uint16_t        BSP_SPI_Chip_EN_PIN;  //SPI GPIO引脚号
	
	GPIO_TypeDef*   BSP_SPI_Chip_Select_GPIOX;//SPI 对应的GPIO
	uint16_t        BSP_SPI_Chip_Select_PIN;  //SPI GPIO引脚号
} SPIInstance;


struct SPI_faction_t{
   SPIInstance* bsp_spi;
  SPI_Work_State (*Transmit)(SPIInstance* spi ,uint8_t *pData ,uint16_t size);
  SPI_Work_State (*Receive)(SPIInstance* spi ,uint8_t *pData ,uint16_t size);
  SPI_Work_State (*TransRecv)(SPIInstance* spi ,uint8_t *txData ,uint8_t *rxData,uint16_t size);

};

typedef SPI_Work_State (*SPITransmit)(SPIInstance* spi ,uint8_t *pData ,uint16_t size);
typedef SPI_Work_State (*SPIReceive)(SPIInstance* spi ,uint8_t *pData ,uint16_t size);
typedef SPI_Work_State (*SPITransRecv)(SPIInstance* spi ,uint8_t *txData ,uint8_t *rxData,uint16_t size);

/***spi发送函数***/
SPI_Work_State SPI_Transmit(SPIInstance* spi ,uint8_t *pData ,uint16_t size, SPI_Work_Mode Work_Mode);

/***spi接收函数***/
SPI_Work_State SPI_Receive(SPIInstance* spi ,uint8_t *pData ,uint16_t size, SPI_Work_Mode Work_Mode);

/***SPI同时接收同时发送函数***/
SPI_Work_State SPI_TransRecv(SPIInstance* spi ,uint8_t *txData ,uint8_t *rxData,uint16_t size, SPI_Work_Mode Work_Mode);


SPI_Work_State bsp_spi_init(SPI_faction* spi,
														SPIInstance* bsp_spi,
														SPITransmit   transmit,            
                            SPIReceive    receive,  
                            SPITransRecv  transRecv);
#endif

