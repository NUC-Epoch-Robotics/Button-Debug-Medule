#include "ring_buffer.h"
#include "stddef.h"



//判断数组是否写满
int IsRingBufferFull(stRingBuff *ringBuf)
{
  if (ringBuf == NULL)
    {
        return 0;    
    }
  if(((ringBuf->in+1) % RING_BUFF_SIZE) == ringBuf->out)
    {
        return 1;
    }
    return 0;
	}

	

void WriteOneByteToRingBuffer(stRingBuff *ringBuf,char data)
{
 if (ringBuf == NULL || IsRingBufferFull(ringBuf))//写之前先判断队列是否写满
    {     
        return;
    }
    ringBuf->buffer[ringBuf->in] = data;
    ringBuf->in = (++ringBuf->in) % RING_BUFF_SIZE;    //防止越界
 
}



//读写一节字节
void ReadOneByteFromRingBuffer(stRingBuff *ringBuf,char *data)
{
 if (ringBuf == NULL||IsRingBufferEmpty(ringBuf)) //读之前判断队列是否为空
    {
       
        return;
    }
		
    *data = ringBuf->buffer[ringBuf->out];
    ringBuf->out = (++ringBuf->out) % RING_BUFF_SIZE;    //防止越界 
}


//写入多个字节
void WriteRingBuffer(stRingBuff *ringBuf,char *writeBuf,unsigned int len)
{
    unsigned int i;
 
 if (ringBuf == NULL)
    {
        return ;
    }
    
    for(i = 0; i < len; i++)
    {
        WriteOneByteToRingBuffer(ringBuf,writeBuf[i]);
    }
}
	
	
//读入多个字节
void ReadRingBuffer(stRingBuff *ringBuf,char *readBuf,unsigned int len)
{
    unsigned int i;
	
 if (ringBuf == NULL)
    {       
        return;
    }
    for(i = 0; i < len; i++)
    {
        ReadOneByteFromRingBuffer(ringBuf,&readBuf[i]);
    }
}

//获取已经写入队列的数据长度
int GetRingBufferLength(stRingBuff *ringBuf)
{
    if (ringBuf == NULL)
    {
        return 0;
    }
 
    return (ringBuf->in - ringBuf->out + RING_BUFF_SIZE) % RING_BUFF_SIZE;
}

int IsRingBufferEmpty(stRingBuff *ringBuf)
{ 
 if (ringBuf == NULL)
    {     
        return 0;
    }
    
 if(ringBuf->in == ringBuf->out)   //写入位置和读出位置相等时为空
    {
        return 1;
    }
    return 0;
}

