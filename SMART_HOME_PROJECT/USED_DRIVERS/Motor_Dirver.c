
#include "Motor_Dirver.h"
void motorA_vidInit()
{
	//IN1,IN2,IN3,IN4   output
	DIO_vidSetPinMode(IN1_PORT,IN1,OUTPUT);
	DIO_vidSetPinMode(IN2_PORT,IN2,OUTPUT);
	DIO_vidSetPinMode(ENA_PORT,ENA,OUTPUT);
	PWM2_vidInit();
	PWM2_vidStart();

}
void motorB_vidInit()
{
	DIO_vidSetPinMode(ENB_PORT,ENB,OUTPUT);
	DIO_vidSetPinMode(IN3_PORT,IN3,OUTPUT);
	DIO_vidSetPinMode(IN4_PORT,IN4,OUTPUT);
	PWM0_vidInit();
	PWM0_vidStart();
		
}
//u8speed from 0 - 100 percentage 
void Motor1_ClockWise(u8 u8Speed)
{
	DIO_vidWritePin(IN1_PORT,IN1,HIGH);
	DIO_vidWritePin(IN2_PORT,IN2,LOW);
	PWM0_vidGenerate(u8Speed);
}
void Motor1_AntiClockWise(u8 u8Speed)
{
	DIO_vidWritePin(IN1_PORT,IN1,LOW);
	DIO_vidWritePin(IN2_PORT,IN2,HIGH);
	PWM0_vidGenerate(u8Speed);
	
}
void Motor1_Stop()
{
		DIO_vidWritePin(IN1_PORT,IN1,HIGH);
		DIO_vidWritePin(IN2_PORT,IN2,HIGH);
}
void Motor2_ClockWise(u8 u8Speed)
{
	DIO_vidWritePin(IN3_PORT,IN3,HIGH);
	DIO_vidWritePin(IN4_PORT,IN4,LOW);
	PWM2_vidGenerate(u8Speed);
	
}
void Motor2_AntiClockWise(u8 u8Speed)
{
	DIO_vidWritePin(IN3_PORT,IN3,LOW);
	DIO_vidWritePin(IN4_PORT,IN4,HIGH);
	PWM2_vidGenerate(u8Speed);
	
}
void Motor2_Stop()
{
	DIO_vidWritePin(IN3_PORT,IN3,HIGH);
	DIO_vidWritePin(IN4_PORT,IN4,HIGH);
	
}
