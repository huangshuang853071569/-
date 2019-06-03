/**------------------------------------------------------------------**/
//* File name ��motor.h                                              
//* Author    : Huangshuang				             
//* Data      : 2019/5/31				             
//* Version   : V1.0				                     
/**------------------------------------------------------------------**/

#ifndef _MOTOR_H
#define _MOTOR_H
#include "stm32f10x.h"
#include "PWM.h"
#define Roll_N 		{GPIO_ResetBits(GPIOA,GPIO_Pin_3);GPIO_SetBits(GPIOA,GPIO_Pin_4);}	  //��ת
#define Roll_R 		{GPIO_SetBits(GPIOA,GPIO_Pin_3);GPIO_ResetBits(GPIOA,GPIO_Pin_4);}		//��ת
#define ROLL_STOP {GPIO_ResetBits(GPIOA,GPIO_Pin_3);GPIO_ResetBits(GPIOA,GPIO_Pin_4);}	//ɲ��

void Motor_init(void);
void Motor_Control(void);

#endif 
