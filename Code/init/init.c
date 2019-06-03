/**------------------------------------------------------------------**/
//* File name ��init.c                                              
//* Author    : Huangshuang				             
//* Data      : 2019/6/3				             
//* Version   : v1.0				                     
/**------------------------------------------------------------------**/
#include "init.h"

/**
	*	@breif	device init
	* @param
	* @ruturn
	*/
void init()
{
	delay_init();																		//��ʱ������ʼ��
	
	ADC1_Config();																	//��ʼ��ADC1������ADת��
	
	TIM4_Cap_Init(0xffff,72-1);											//TIM4��ʼ�������ջ�PWM����
	
	TIM3_GPIO_Config();															//PWM�����ʼ��
	
	Motor_init();
	
	uart_init(115200);															//USART1��ʼ��
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//�����ж����ȼ�����
}
	