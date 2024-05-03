/*
 * Motor_Dirver.h
 *
 * Created: 10/28/2020 5:47:04 AM
 *  Author: yehia
 */ 


#ifndef MOTOR_DIRVER_H_
#define MOTOR_DIRVER_H_
#include "Timer.h"
#include "DIO_interface.h"
#include "Motor_Dirver_Config.h"
void motorA_vidInit();
void motorB_vidInit();
void Motor1_ClockWise(u8 u8Speed);
void Motor1_AntiClockWise(u8 u8Speed);
void Motor1_Stop();
void Motor2_ClockWise(u8 u8Speed);
void Motor2_AntiClockWise(u8 u8Speed);
void Motor2_Stop();




#endif /* MOTOR_DIRVER_H_ */