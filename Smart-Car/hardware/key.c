#include "stm32f10x.h"                  // Device header
#include "Delay.h"



void key_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//开启时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//开启AFIO引脚复用
	
	GPIO_InitTypeDef GPIO_InitStructure;
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//开启时钟
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPD;//下拉输出默认低电平，上拉输入默认高电平
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);//初始化GPIO口
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;//推挽式输出
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);//初始化GPIO口
	
//	EXTI_InitTypeDef 	EXTI_InitStructure;
//	EXTI_InitStructure.EXTI_Line = EXTI_Line7;//
//	EXTI_InitStructure.EXTI_LineCmd = ENABLE;//
//	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//选择中断模式
//	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;//触发为上升沿根据PA7按键决定的
//	EXTI_Init(&EXTI_InitStructure);
//	
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
//	NVIC_InitTypeDef NVIC_InitStructure;
//	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
//	NVIC_Init(&NVIC_InitStructure);
//	
//	EXTI_InitStructure.EXTI_Line = EXTI_Line12;//
//	EXTI_InitStructure.EXTI_LineCmd = ENABLE;//
//	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//选择中断模式
//	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//触发为下降沿根据PA7按键决定的
//	EXTI_Init(&EXTI_InitStructure);
//	
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);
//	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =0;
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
//	NVIC_Init(&NVIC_InitStructure);
	
}
uint8_t key_GetNum(void)
{
	uint8_t key_GetNum=0;
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7)==1)
	{
		Delay_ms(20);
		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7)==1);
		Delay_ms(20);
		key_GetNum=1;
	}
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_12)==0)
	{
		Delay_ms(20);
		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_12)==0);
		Delay_ms(20);
		key_GetNum=2;
	}
	return key_GetNum;
}



//void EXTI15_10_IRQHandler(void)
//{
//	if(EXTI_GetITStatus(EXTI_Line12)==SET)
//	{
//		
//		
//		EXTI_ClearITPendingBit(EXTI_Line12);
//	}	
//	
//}

