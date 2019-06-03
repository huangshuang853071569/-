/**------------------------------------------------------------------**/
//* File name ��Motor.c                                              
//* Author    : Huangshuang				             
//* Data      : 2019/6/3				             
//* Version   : V1.0				                     
/**------------------------------------------------------------------**/

#include "motor.h"

extern float except_pos;																	//����λ�� 0~33000
extern float current_pos;																//��ǰλ�� 0~33000
extern float PID_Control_Out;

void Motor_init(void)
{

	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_3|GPIO_Pin_4;
	
	GPIO_Init(GPIOA,&GPIO_InitStructure);

	GPIO_ResetBits(GPIOA,GPIO_Pin_3|GPIO_Pin_4);	//��0

}

/**
	*	@breif Control	
	* @param 
	* @return PID_Contol_Out PID�����������
	*/
void Motor_Control(void)
{
	
	if(PID_Control_Out>0)
	{
		Roll_N	//��ת
		PWM1_Out((u16)PID_Control_Out);
	}
	else if(PID_Control_Out==0)
	{
		PWM1_Out(0);
		ROLL_STOP	//ֹͣ
	}
	else
	{
		PWM1_Out((u16)(-1*PID_Control_Out));
		Roll_R	//��ת
	}
}
