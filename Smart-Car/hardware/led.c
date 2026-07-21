#include "stm32f10x.h"                  // Device header
void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//开启时钟
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;//推挽式输出
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4| GPIO_Pin_2 |GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);//初始化GPIO口
}
void LED1_ON(void)
{
	GPIO_SetBits(GPIOA,GPIO_Pin_4);
}
void LED1_OFF(void)
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_4);
}	
void LED1_turn(void)
{
	if(GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_4)==0)
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_4);
	}
	else
	{
		GPIO_ResetBits(GPIOA,GPIO_Pin_4);
	}
	
}	
void LED2_ON(void)
{
	GPIO_SetBits(GPIOA,GPIO_Pin_2);
}
void LED2_OFF(void)
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_2);
}	
void LED2_turn(void)
{
	if(GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_2)==0)
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_2);
	}
	else
	{
		GPIO_ResetBits(GPIOA,GPIO_Pin_2);
	}
	
}	
void LED3_ON(void)
{
	GPIO_SetBits(GPIOA,GPIO_Pin_3);
}
void LED3_OFF(void)
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_3);
}	
void LED3_turn(void)
{
	if(GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_3)==0)
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_3);
	}
	else
	{
		GPIO_ResetBits(GPIOA,GPIO_Pin_3);
	}
	
}	
