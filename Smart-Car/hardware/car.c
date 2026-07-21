#include "stm32f10x.h"                  // Device header
#include "motor.h"

void car_Init(void)
{
	Motor_Init();
}

void car_stop(void)
{
	Motor_SetLeftSpeed(0);
	Motor_SetRightSpeed(0);
}

void car_forward(int8_t Speed)
{
	Motor_SetLeftSpeed(Speed);
	Motor_SetRightSpeed(Speed);
}

void car_retreat(int8_t Speed)
{
	Motor_SetLeftSpeed(-Speed);
	Motor_SetRightSpeed(-Speed);
}

void car_left(int8_t Speed)
{
	Motor_SetLeftSpeed(-Speed);
	Motor_SetRightSpeed(Speed);
}

void car_lefts(int8_t Speed)
{
	Motor_SetLeftSpeed(0);
	Motor_SetRightSpeed(Speed);
}
void car_right(int8_t Speed)
{
	Motor_SetLeftSpeed(Speed);
	Motor_SetRightSpeed(-Speed);
}

void car_rights(int8_t Speed)
{
	Motor_SetLeftSpeed(Speed);
	Motor_SetRightSpeed(0);
}

