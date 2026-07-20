//#include "stm32f10x.h"

//// 定义 ADC 采集缓存，DMA 会自动把数据放这里
//uint16_t AD_Value[2];  

//void AD_Init(void)
//{
//    // 1. 开时钟：GPIOA + ADC1 + DMA1
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_ADC1, ENABLE);
//    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
//    
//    // 2. 设置 ADC 预分频器（必须 <14M）
//    RCC_ADCCLKConfig(RCC_PCLK2_Div6);  // 72M/6=12M
//    
//    // 3. 配置 PA0、PA4 为模拟输入
//    GPIO_InitTypeDef GPIO_InitStructure;
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_4;
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;  // 模拟输入
//    GPIO_Init(GPIOA, &GPIO_InitStructure);
//    
//    // 4. DMA 配置（ADC1 用 DMA1_Channel1）
//    DMA_InitTypeDef DMA_InitStructure;
//    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;  // 外设地址：ADC 数据寄存器
//    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)AD_Value;       // 内存地址：存放结果
//    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;               // 外设作为源
//    DMA_InitStructure.DMA_BufferSize = 2;                            // 两个通道：AD0、AD4
//    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; // 外设地址不自增
//    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;          // 内存地址自增
//    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; // 16 位
//    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
//    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;                  // 循环模式：自动反复采集
//    DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;
//    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
//    DMA_Init(DMA1_Channel1, &DMA_InitStructure);
//    
//    DMA_Cmd(DMA1_Channel1, ENABLE);  // 使能 DMA
//    
//    // 5. ADC 配置
//    ADC_InitTypeDef ADC_InitStructure;
//    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
//    ADC_InitStructure.ADC_ScanConvMode = ENABLE;        // 扫描模式（多通道）
//    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;  // 连续转换
//    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
//    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
//    ADC_InitStructure.ADC_NbrOfChannel = 2;              // 2 个通道
//    ADC_Init(ADC1, &ADC_InitStructure);
//    
//    // 规则通道配置
//    ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);
//    ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 2, ADC_SampleTime_55Cycles5);
//    
//    // 开启 ADC-DMA 模式！！！最关键
//    ADC_DMACmd(ADC1, ENABLE);
//    
//    // 上电 ADC
//    ADC_Cmd(ADC1, ENABLE);
//    
//    // 校准
//    ADC_ResetCalibration(ADC1);
//    while(ADC_GetResetCalibrationStatus(ADC1));
//    ADC_StartCalibration(ADC1);
//    while(ADC_GetCalibrationStatus(ADC1));
//    
//    // 启动转换
//    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
//}





#include "AD.h"
#include "stm32f10x.h"

void AD_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	ADC_InitTypeDef ADC_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_ADC1, ENABLE);
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStruct.ADC_ScanConvMode = DISABLE;
	ADC_InitStruct.ADC_ContinuousConvMode = DISABLE;
	ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStruct.ADC_NbrOfChannel = 1;
	ADC_Init(ADC1, &ADC_InitStruct);
	
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);
	ADC_Cmd(ADC1, ENABLE);
	
	// ADC校准
	ADC_ResetCalibration(ADC1);
	while(ADC_GetResetCalibrationStatus(ADC1));
	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1));
}

uint16_t AD_GetValue(void)
{
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
	ADC_ClearFlag(ADC1, ADC_FLAG_EOC);
	return ADC_GetConversionValue(ADC1);
}
