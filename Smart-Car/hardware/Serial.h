#ifndef __SERIAL_H
#define __SERIAL_H
#include <string.h>
#include <stdio.h>
void Serial_Init(void);
void Serial_SendByte(uint8_t Byte);
void Serial_SendArray(uint8_t *Array,uint8_t Length);
void Serial_SendString(uint8_t *String);
uint16_t Serial_Pow(uint8_t Y,uint8_t X);
void Serial_SendNum(uint16_t Num,uint8_t Length);
void Serial_Printf(char *format, ...);
uint8_t GetRxFlag(void);
int fputc(int ch, FILE *f);
//void Serial_SendPacket(void);
#endif
