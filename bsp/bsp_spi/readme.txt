
/***spi发送函数***/
SPI_Work_State SPI_Transmit(SPIInstance* spi ,uint8_t *pData ,uint16_t size, SPI_Work_Mode Work_Mode);

/***spi接收函数***/
SPI_Work_State SPI_Receive(SPIInstance* spi ,uint8_t *pData ,uint16_t size, SPI_Work_Mode Work_Mode);

/***SPI同时接收同时发送函数***/
SPI_Work_State SPI_TransRecv(SPIInstance* spi ,uint8_t *txData ,uint8_t *rxData,uint16_t size, SPI_Work_Mode Work_Mode);

每个函数有阻塞，中断，DMA三种模式，通过Work_Mode进行设置

SPIInstance结构体
 在高层代码直接进行相关引脚初始化

typedef struct SPI_faction_t  SPI_faction;结构体   封装函数和上一结构体

