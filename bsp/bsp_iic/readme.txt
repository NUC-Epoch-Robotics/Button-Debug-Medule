IIC封装
分为

@brief IIC发送函数封装
void IIC_Send(IICInstance* iic,uint16_t reg, uint8_t *pData, uint16_t Size, IIC_Work_Mode IIC_Seq,IIC_Work_Mode Work_Mode);


@brief IIC接收函数封装
void IIC_Receive(IICInstance* iic,uint16_t reg, uint8_t *pData, uint16_t Size, IIC_Work_Mode IIC_Seq,IIC_Work_Mode Work_Mode);

@brief 对指定寄存器进行读写
void IIC_AccessMem( IICInstance* iic, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout,IIC_Access_Mode Access_Mode);

IICInstance结构体
 在高层代码直接进行相关引脚初始化

typedef struct IIC_faction_t IIC_faction;结构体 封装函数和上一结构体





