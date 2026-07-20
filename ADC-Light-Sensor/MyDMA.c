//#include "stm32f10x.h" // Device header
//void MyDMA_Init(uint32_t Addr1,uint32_t Addr2,uint16_t Size)
//{

//	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
//	
//	DMA_InitTypeDef  DMA_InitStructure;
//	
//	DMA_InitStructure.DMA_PeripheralBaseAddr=Addr1;
//	DMA_InitStructure.DMA_PeripheralDataSize=DMA_PeripheralDataSize_Byte;
//	DMA_InitStructure.DMA_PeripheralInc=DMA_PeripheralInc_Enable;
//	
//	DMA_InitStructure.DMA_MemoryBaseAddr=Addr2;
//	DMA_InitStructure.DMA_MemoryDataSize=DMA_MemoryDataSize_Byte;
//	DMA_InitStructure.DMA_MemoryInc=DMA_MemoryInc_Enable;

//	DMA_InitStructure.DMA_BufferSize=Size;
//	DMA_InitStructure.DMA_DIR=DMA_DIR_PeripheralSRC;
//	DMA_InitStructure.DMA_M2M=DMA_M2M_Enable;
//	DMA_InitStructure.DMA_Mode=DMA_Mode_Normal;
//	DMA_InitStructure.DMA_Priority=DMA_Priority_Medium;
//	DMA_Init(DMA1_Channel1,&DMA_InitStructure);
//	
//	DMA_Cmd(DMA1_Channel1,ENABLE);
//}

//#include "stm32f10x.h"
//uint16_t MySize;
//void MyDMA_Init(uint32_t Addr1,uint32_t Addr2,uint16_t Size)
//{
//	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
//	
//	DMA_InitTypeDef  DMA_InitStructure;
//	
//	DMA_InitStructure.DMA_PeripheralBaseAddr=Addr1;
//	// ==============================================
//	// 原来：Byte（1字节）→ 错！
//	// 现在：Word（4字节）→ 对！
//	// ==============================================
//	DMA_InitStructure.DMA_PeripheralDataSize=DMA_PeripheralDataSize_Word;
//	DMA_InitStructure.DMA_PeripheralInc=DMA_PeripheralInc_Enable;
//	
//	DMA_InitStructure.DMA_MemoryBaseAddr=Addr2;
//	DMA_InitStructure.DMA_MemoryDataSize=DMA_MemoryDataSize_Word;
//	DMA_InitStructure.DMA_MemoryInc=DMA_MemoryInc_Enable;
//	
//	DMA_InitStructure.DMA_BufferSize=Size;
//	DMA_InitStructure.DMA_DIR=DMA_DIR_PeripheralSRC;
//	DMA_InitStructure.DMA_M2M=DMA_M2M_Enable;
//	DMA_InitStructure.DMA_Mode=DMA_Mode_Normal;
//	DMA_InitStructure.DMA_Priority=DMA_Priority_Medium;
//	DMA_Init(DMA1_Channel1,&DMA_InitStructure);
//	
//	
//	DMA_Cmd(DMA1_Channel1,DISABLE);
//}

//void MyDMA_Transfer(void)
//{
//	DMA_Cmd(DMA1_Channel1,DISABLE);
//	DMA_SetCurrDataCounter(DMA1_Channel1,MySize);
//	DMA_Cmd(DMA1_Channel1,ENABLE);
//	while(DMA_GetFlagStatus(DMA1_FLAG_TC1)==RESET);
//	DMA_ClearFlag(DMA1_FLAG_TC1);
//}
#include "stm32f10x.h"

static uint16_t MyDMA_Size;

void MyDMA_Init(uint32_t Addr1, uint32_t Addr2, uint16_t Size)
{
	MyDMA_Size = Size;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	
	DMA_InitTypeDef DMA_InitStructure;
	
	DMA_InitStructure.DMA_PeripheralBaseAddr = Addr1;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Enable;
	
	DMA_InitStructure.DMA_MemoryBaseAddr = Addr2;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	
	DMA_InitStructure.DMA_BufferSize = Size;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Enable;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;
	
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);
}

void MyDMA_Transfer(void)
{
	// 关闭DMA
	DMA_Cmd(DMA1_Channel1, DISABLE);
	
	// 重新设置传输数量
	DMA_SetCurrDataCounter(DMA1_Channel1, MyDMA_Size);
	
	// 启动DMA
	DMA_Cmd(DMA1_Channel1, ENABLE);
	
	// 等待完成
	while (DMA_GetFlagStatus(DMA1_FLAG_TC1) == RESET);
	DMA_ClearFlag(DMA1_FLAG_TC1);
}