#include "stm32f10x.h"                  // Device header
#include "PWM.h"
#include "IC.h"
#include "OLED.h"
#include "led.h"
#include "Delay.h"
#include "Beep.h"
#include "key.h"
#include "Timer.h"
#include "motor.h"
#include "car.h"
#include "HCSR04.h"
#include "servo.h"
#include "Track.h"
#include "Serial.h"
#include <string.h>
#include <ctype.h>
#include "adc.h"
#include "DMA.h"
#define  X1  GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_5)
#define  X2  GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_4)
#define  X3  GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_3)
#define  X4  GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_15)
#define  X5  GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_5)

uint8_t keynum=0;
float Angle=0;
float Angle1=0;
int8_t Speed=0;
uint16_t T;
int8_t ch;
uint8_t RxData;
uint8_t RxFlag;
uint8_t DataA[]={0x01,0x02,0x03,0x04};
uint8_t DataB[]={0,0,0,0};
char  Serial_RxPacket[100];
char  Serial_TxPacket[100];

int main(void)
{
		
		Serial_Init();
		Beep_Init();
		Motor_Init();
		key_Init();
//		Servo_Init();
		LED_Init();
		OLED_Init();
		AD_Init();
//		PWM_Init();
		car_Init();
	
		
//		Infrared_Init();
//		HCSR04_Init();
//		OLED_ShowString(0, 32, "distance:",OLED_8X16);
//		OLED_ShowString(96, 32, "cm",OLED_8X16);
//		uint8_t MyArray[]={0x42,0x43,0x44,0x45};
//		Serial_SendNum(1234,4);
//		Serial_Printf("你好,世界");
//		Serial_SendArray(MyArray,4);
//		Serial_SendString("hellow  world!");
//		Serial_SendPacket();
		
//		Serial_TxPacket[0] = 0x01;
//		Serial_TxPacket[1] = 0x02;
//		Serial_TxPacket[2] = 0x03;
//		Serial_TxPacket[3] = 0x04;
		
		
	while (1)
	{
		DataA[0]++;
		DataA[1]++;
		DataA[2]++;
		DataA[3]++;
//		OLED_ShowHexNum(0,0,DataA[0],2,OLED_8X16);
//		OLED_ShowHexNum(24,0,DataA[1],2,OLED_8X16);
//		OLED_ShowHexNum(48,0,DataA[2],2,OLED_8X16);
//		OLED_ShowHexNum(72,0,DataA[3],2,OLED_8X16);
//		OLED_ShowHexNum(0,16,DataB[0],2,OLED_8X16);
//		OLED_ShowHexNum(24,16,DataB[1],2,OLED_8X16);
//		OLED_ShowHexNum(48,16,DataB[2],2,OLED_8X16);
//		OLED_ShowHexNum(72,16,DataB[3],2,OLED_8X16);
		OLED_Update();
		Delay_ms(1000);
		MyDMA_Init((uint32_t)DataA,(uint32_t)DataB,4);
		MyDMA_Transfer();
		OLED_ShowHexNum(0,16,DataA[0],2,OLED_8X16);
		OLED_ShowHexNum(24,16,DataA[1],2,OLED_8X16);
		OLED_ShowHexNum(48,16,DataA[2],2,OLED_8X16);
		OLED_ShowHexNum(72,16,DataA[3],2,OLED_8X16);
		OLED_ShowHexNum(0,48,DataB[0],2,OLED_8X16);
		OLED_ShowHexNum(24,48,DataB[1],2,OLED_8X16);
		OLED_ShowHexNum(48,48,DataB[2],2,OLED_8X16);
		OLED_ShowHexNum(72,48,DataB[3],2,OLED_8X16);
		OLED_Update();
//		Delay_ms(1000);
//			Angle = AD_GetValue(ADC_Channel_0);
//			Angle1 = AD_GetValue(ADC_Channel_4);
//			OLED_ShowFloatNum(0,0,Angle/4095*3.3,1,1,OLED_8X16);
//			OLED_ShowFloatNum(0,16,Angle1/4095*3.3,1,1,OLED_8X16);
//			OLED_Update();
//		keynum=key_GetNum();
//		if(keynum==1)
//		{
//			Serial_SendString("Key1_Pressed\r\n");
//			OLED_ShowString(0, 16, "Key1_Pressed",OLED_8X16);
//			OLED_Update();
//		}
//		
//		if (RxFlag == 1)
//		{
//			
//			if (strcmp(Serial_RxPacket, "LED_ON") == 0)
//			{
//				LED1_ON();
//				Serial_SendString("LED_ON_OK\r\n");
//				OLED_ShowString(0, 16, "LED_ON_OK",OLED_8X16);
//				OLED_Update();
//			}
//				
//			else if (strcmp(Serial_RxPacket, "LED_OFF") == 0)
//			{
//				LED1_OFF();
//				Serial_SendString("LED_OFF_OK\r\n");
//				OLED_ShowString(0, 16, "LED_OFF_OK",OLED_8X16);
//				OLED_Update();
//			}
//			else if (strcmp(Serial_RxPacket, "BEEP_ON") == 0)
//			{
//				Beep_On();
//				Serial_SendString("BEEP_ON_OK\r\n");
//				OLED_ShowString(0, 16, "BEEP_ON_OK",OLED_8X16);
//				OLED_Update();
//			}
//			else if (strcmp(Serial_RxPacket, "BEEP_OFF") == 0)
//			{
//				Beep_OFF();
//				Serial_SendString("BEEP_OFF_OK\r\n");
//				OLED_ShowString(0, 16, "BEEP_OFF_OK",OLED_8X16);
//				OLED_Update();
//			}
//			else if (strcmp(Serial_RxPacket, "CAR_ON") == 0)
//			{
//				car_forward(Speed);
//				Serial_SendString("CAR_ON_OK\r\n");
//				OLED_ShowString(0, 16, "CAR_ON_OK",OLED_8X16);
//				OLED_Update();
//			}
//			else if (strcmp(Serial_RxPacket, "CAR_BACK") == 0)
//			{
//				car_retreat(Speed);
//				Serial_SendString("CAR_BACK_OK\r\n");
//				OLED_ShowString(0, 16, "CAR_BACK_OK",OLED_8X16);
//				OLED_Update();
//			}
//			else if (strcmp(Serial_RxPacket, "CAR_OFF") == 0)
//			{
//				car_stop();
//				Serial_SendString("CAR_OFF_OK\r\n");
//				OLED_ShowString(0, 16, "CAR_OFF_OK",OLED_8X16);
//				OLED_Update();
//			}
//			
//			else
//			{
//				Serial_SendString("ERROR_COMMAND\r\n");
//				OLED_ShowString(0, 16, "ERROR_COMMAND",OLED_8X16);
//				OLED_Update();
//			}
//			
//			RxFlag = 0;
//		}
			
//		OLED_ShowString(0, 0, "Serial_TxPacket:",OLED_8X16);
//		OLED_ShowString(0, 32, "Serial_RxPacket:",OLED_8X16);
//		keynum =key_GetNum();
//		if(keynum == 1)
//		{
//		Serial_SendPacket();
//		OLED_ShowHexNum(0,16,Serial_TxPacket[0],2,OLED_8X16);
//		OLED_ShowHexNum(24,16,Serial_TxPacket[1],2,OLED_8X16);
//		OLED_ShowHexNum(48,16,Serial_TxPacket[2],2,OLED_8X16);
//		OLED_ShowHexNum(72,16,Serial_TxPacket[3],2,OLED_8X16);
//		OLED_Update();
//			for (uint8_t i = 0;i < 4;i ++)
//			{
//				Serial_TxPacket[i]=Serial_TxPacket[i]+1;
//			}
//		}
//		if(GetRxFlag() ==  1)
//		{	
//		
//		OLED_ShowHexNum(0,48,Serial_RxPacket[0],2,OLED_8X16);
//		OLED_ShowHexNum(24,48,Serial_RxPacket[1],2,OLED_8X16);
//		OLED_ShowHexNum(48,48,Serial_RxPacket[2],2,OLED_8X16);
//		OLED_ShowHexNum(72,48,Serial_RxPacket[3],2,OLED_8X16);
//		
//		OLED_Update();
//		}
//		
//		
//		T = HCSR04_GetValue();//超声波测距

//		if(X1 == 1 && X2 == 1&& X4 == 1&& X5 == 1)
//		{car_forward(Speed);T=2;}
//		else if(X1 == 1 && X2 == 0&& X4 == 1&& X5 == 1)
//		{car_forward(Speed);Delay_ms(20);T=4;}
//		else if(X1 == 1 && X2 == 1&& X4 == 0&& X5 == 1)
//		{car_lefts(Speed);Delay_ms(20);T=4;}
//		else if(X1 == 1 && X2 == 1&& X4 == 1&& X5 == 0)
//		{car_left(Speed);Delay_ms(20);T=5;}
//		else if(X1 == 1 && X2 == 0&& X4 == 1&& X5 == 1)
//		{car_right(Speed);T=6;Delay_ms(20);}
//		else if(X1 == 0 && X2 == 1&& X4 == 1&& X5 == 1)
//		{car_right(Speed);Delay_ms(20);T=6;}
//		else car_forward(Speed);
//		if(X4 == 0)
//		{car_lefts(Speed);T=2;}
//		else if(X2 == 0)
//		{car_rights(Speed);T=4;}
//		else if( X5 == 0)
//		{car_left(Speed);T=6;}
//		else if(X1 == 0 )
//		{car_right(Speed);T=7;}
//		else car_forward(Speed);
//		OLED_ShowNum(72, 48, T, 3,OLED_8X16);
//		OLED_ShowNum(0, 48, keynum, 3,OLED_8X16);
//		Delay_ms(100);
//		OLED_ShowString(0,0,"Speed:",OLED_8X16);
//		OLED_ShowString(0,16,"direction:",OLED_8X16);
//		Servo_SetAngle(Angle);	
//		
//		OLED_ShowSignedNum(48,0, Speed,3,OLED_8X16);	//OLED显示速度变量
//		OLED_ShowSignedNum(0,48, Angle,3,OLED_8X16);	//OLED显示速度变量
//			
		
	}
					
					
}

//void EXTI9_5_IRQHandler(void)
//{
//	Delay_ms(20);
//	if(EXTI_GetITStatus(EXTI_Line7)==SET)
//	Delay_ms(20);
//	{	
//		Speed += 20;
//		if (Speed >= 100)				
//		Speed = 0;													
//		OLED_ShowSignedNum(48,0, Speed,4,OLED_8X16);
//		OLED_Update();	
//		EXTI_ClearITPendingBit(EXTI_Line7);
//	}	
//	
//}
//void EXTI15_10_IRQHandler(void)
//{	
//	Delay_ms(20);
//	if(EXTI_GetITStatus(EXTI_Line12)==SET)
//	Delay_ms(20);
//	{
//		keynum++;
//		if(keynum>3)
//		keynum=0;
//		EXTI_ClearITPendingBit(EXTI_Line12);
//	}
//}

