//#include "stm32f10x.h"
//#include "Delay.h"
//#include "OLED.h"
//#include "AD.h"
//#include "Serial.h"

//uint8_t RxData;
//uint8_t RxFlag;
//uint8_t Serial_RxFlag;
//char Serial_RxPacket[100];
//uint8_t Serial_TxPacket[4];
//uint32_t DataA[] = {0X01, 0X02, 0X03, 0X04};
//uint32_t DataB[] = {0, 0, 0, 0};
//float Voltage; 

//int main(void)
//{
//    OLED_Init();
//    AD_Init();  
//    Serial_Init();  
//    
//    OLED_ShowString(0,0,"AD0:",OLED_8X16);
//    OLED_ShowString(0,16,"AD4:",OLED_8X16);
//	OLED_ShowString(0,32,"Voltage:0.00V",OLED_8X16);
//    OLED_ShowString(0,48,"State:Normal",OLED_8X16);
//    
//    while(1)
//    {		
//		Voltage = (float)AD_Value[1] / 4095 * 3.3;
//		
//        OLED_ShowNum(32, 0, AD_Value[0], 4, OLED_8X16);
//        OLED_ShowNum(32,16, AD_Value[1], 4, OLED_8X16);
//		OLED_ShowNum(64,32, Voltage,1, OLED_8X16);
//		OLED_ShowNum(80,32, (uint16_t)(Voltage*100)%100,2, OLED_8X16);

//        // OLED显示阈值状态
//        if(Voltage > 0.9f)
//        {
//            OLED_ClearArea(48,48,128,64);
//            OLED_ShowString(0,48,"State:Alarm ",OLED_8X16);
//            Serial_Printf("电压超出阈值!\r\n");
//        }
//        else
//        {
//            OLED_ClearArea(48,48,128,64);
//            OLED_ShowString(0,48,"State:Normal",OLED_8X16);
//            Serial_Printf("当前电压：%.2f V\r\n", Voltage);
//        }
//        OLED_Update();
//		Delay_ms(1000);
//    }
//}



//#include "stm32f10x.h"
//#include "Delay.h"
//#include "OLED.h"
//#include "Fire.h"   // 现在是 Fire.h 不报错！

//uint8_t RxData;
//uint8_t RxFlag;
//uint8_t Serial_RxFlag;
//char Serial_RxPacket[100];
//uint8_t Serial_TxPacket[4];

//uint32_t DataA[] = {0X01,0X02,0X03,0X04};
//uint32_t DataB[] = {0,0,0,0};

//int main(void)
//{
//    OLED_Init();
//    Fire_Init();   // 火焰传感器初始化

//    OLED_ShowString(0, 0, "Flame Status:", OLED_8X16);
//    OLED_Update();

//    while (1)
//    {
//        FireStatus status = Fire_GetStatus();

//        // ========== OLED 只显示火焰状态 ==========
//        if (status == FIRE_YES)
//        {
//            OLED_ShowString(0, 16, "FIRE!!!        ", OLED_8X16);
//        }
//        else
//        {
//            OLED_ShowString(0, 16, "NO FIRE        ", OLED_8X16);
//        }

//        OLED_Update();
//        Delay_ms(200);
//    }
//}







//#include "stm32f10x.h"
//#include "Delay.h"
//#include "OLED.h"
//#include "AD.h"
//#include "LEDD.h"


//uint8_t RxData;
//uint8_t RxFlag;
//uint8_t Serial_RxFlag;
//char Serial_RxPacket[100];
//uint8_t Serial_TxPacket[4];

//uint32_t DataA[] = {0X01,0X02,0X03,0X04};
//uint32_t DataB[] = {0,0,0,0};


//uint16_t AD_Value;
//float Voltage;

//int main(void)
//{
//	AD_Init();
//	LED_Init();
//	OLED_Init();
//	
//	OLED_ShowString(0, 0, "AD:    ", OLED_8X16);
//	OLED_ShowString(0, 16, "Volt:  V", OLED_8X16);
//	
//	while(1)
//	{
//		// 1.读取ADC原始值
//		AD_Value = AD_GetValue();
//		// 2.换算电压 参考电压3.3V 12位ADC(0~4095)
//		Voltage = (float)AD_Value * 3.3f / 4095.0f;
//		
//		// OLED实时显示AD值与电压
//		OLED_ShowNum(32, 0, AD_Value, 4, OLED_8X16);
//		OLED_ShowNum(32, 16, (uint16_t)Voltage, 1, OLED_8X16);
//		OLED_ShowString(40, 16, ".", OLED_8X16);
//		OLED_ShowNum(48, 16, (uint16_t)(Voltage * 100) % 100, 2, OLED_8X16);
//		OLED_Update();
//		
//		// 3.阈值判断
//		if(Voltage > 2.0f)
//		{
//			// 强光：LED1亮，LED2灭
//			LED1_ON();
//			LED2_OFF();
//		}
//		else if(Voltage < 1.0f)
//		{
//			// 弱光：LED2亮，LED1灭
//			LED1_OFF();
//			LED2_ON();
//		}
//		else
//		{
//			// 中间亮度：两灯全部熄灭
//			LED1_OFF();
//			LED2_OFF();
//		}
//		
//		Delay_ms(200);
//	}
//}

#include "stm32f10x.h"
#include "Delay.h"
#include "OLED.h"
#include "AD.h"
#include "LEDD.h"
uint8_t RxData;
uint8_t RxFlag;
uint8_t Serial_RxFlag;
char Serial_RxPacket[100];
uint8_t Serial_TxPacket[4];

uint16_t AD_Value;
float Voltage_Collect;  // 直接采集的电压
float Voltage_Real;     // 反向换算后的实际电压

int main(void)
{
	AD_Init();
	LED_Init();
	OLED_Init();
	
	OLED_ShowString(0, 0, "AD:     ", OLED_8X16);
	OLED_ShowString(0, 16, "Volt:  V", OLED_8X16);
	
	while(1)
	{
		AD_Value = AD_GetValue();
		Voltage_Collect = (float)AD_Value * 3.3f / 4095.0f;
		// 电压反向，实现：光照越强，最终电压越大
		Voltage_Real = 3.3f - Voltage_Collect;
		
		OLED_ShowNum(32, 0, AD_Value, 4, OLED_8X16);
		OLED_ShowNum(32, 16, (uint16_t)Voltage_Real, 1, OLED_8X16);
		OLED_ShowString(40, 16, ".", OLED_8X16);
		OLED_ShowNum(48, 16, (uint16_t)(Voltage_Real * 100) % 100, 2, OLED_8X16);
		OLED_Update();
		
		// 按照题目要求逻辑判断
		if(Voltage_Real > 2.0f)
		{
			// 强光，电压＞2V：LED1亮
			LED1_ON();
			LED2_OFF();
		}
		else if(Voltage_Real < 1.0f)
		{
			// 弱光，电压＜1V：LED2亮
			LED1_OFF();
			LED2_ON();
		}
		else
		{
			// 中间亮度，两灯熄灭
			LED1_OFF();
			LED2_OFF();
		}
		
		Delay_ms(200);
	}
}
