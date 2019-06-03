/**------------------------------------------------------------------**/
//* File name ��PWM.c                                              
//* Author    : Huangshuang				             
//* Data      : 2019/5/31				             
//* Version   : V1.0				                     
/**------------------------------------------------------------------**/

#include"PWM.h"

/**
	*@brief 	TIM3��ʼ��
	*@param		NONE
	*@return	NONE
	*/
void TIM3_Config(void)
{
	TIM3_GPIO_Config(); //GPIO��ʼ��
	TIM3_Mode_Config();	//ģʽ��ʼ��
}


/**
	*@brief 	TIM3��ʱ��GPIO��ʼ��������PWM���������
	*@param		NONE
	*@return	NONE
	*/
 void TIM3_GPIO_Config(void)
{
	
	GPIO_InitTypeDef GPIO_InitStructure;  
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB,ENABLE); // ��GPIOA,GPIOBʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); // ��TIM3ʱ��
	
	// GPIO��ʼ��
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6;     //CH1���:PA6
	GPIO_Init(GPIOA,&GPIO_InitStructure);
}

/**
	*@brief 	TIM3��ʱ��ģʽ��ʼ��
	*@param 	NONE
	*@return  NONE
	*/
void TIM3_Mode_Config(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

	/****************ʱ����ʼ��***************/
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;//ʱ�ӷ�Ƶϵ��������Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;//���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_Period=17999;//��ʱ����0������999����1000��Ϊһ����ʱ����
	TIM_TimeBaseStructure.TIM_Prescaler=80;//����Ԥ��Ƶ����Ԥ��Ƶ
	//TIM_TimeBaseStructure.TIM_RepetitionCounter=
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);//���ó�ʼ������
}


/**
	*@brief 	����PA6���PWM
	*@param		u16 CCR1_Val:�ߵ�ƽ��ռ����ֵ
	*@return	NONE
	*/
 void PWM1_Out(u16 CCR1_Val)
{

	TIM_OCInitTypeDef TIM_OCInitStructure;
	
	/****************ʹ��TIM3_CH1����****************/
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;//ʹ�ܶ�ʱ�����
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;//����ΪPWM1ģʽ
	TIM_OCInitStructure.TIM_Pulse=CCR1_Val; //ֱ��Ϊ���䣬�����ñȽϼĴ����е���ֵ
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;

	TIM_OC1Init(TIM3,&TIM_OCInitStructure);//д��ṹ��
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);//ʹ��TIM3��CCR1�ϵ�Ԥװ�ؼĴ���
	
	TIM_ARRPreloadConfig(TIM3,ENABLE);  //ʹ��װ�ؼĴ���
	TIM_Cmd(TIM3,ENABLE);  //ʹ�ܶ�ʱ��3
}
