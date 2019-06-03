/**------------------------------------------------------------------**/
//* File name ��receiver.c                                              
//* Author    : Huangshuang				             
//* Data      : 2019/5/31				             
//* Version   : V1.0				                     
/**------------------------------------------------------------------**/
#include "receiver.h"

//  PB6 : CH1����

/*****************************************************************************************/
u8 TIM4CH1_CAPTURE_STA = 0;	//ͨ��1���벶���־������λ�������־����6λ�������־		
u16 TIM4CH1_CAPTURE_UPVAL;
u16 TIM4CH1_CAPTURE_DOWNVAL;


/*****************************************************************************************/

volatile u32 PWM_in1 = 0;	 //CH1  PWMֵ  PB6
u32 tim4_T1;
volatile u32 pwm_in_ch1; 				//���������


/**
	*@brief 	��ʱ��4ͨ��1~4���벶������
	*@param		NONE
	*@return	NONE
	*/
void TIM4_Cap_Init(u16 arr, u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM4_ICInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);	//ʹ��TIM4ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //ʹ��GPIOBʱ��

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 ;  	//PB6 ���֮ǰ����  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PB6 ���� 
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOB, GPIO_Pin_6);						//PB6  ����

	//��ʼ����ʱ��4 TIM4	 
	TIM_TimeBaseStructure.TIM_Period = arr; //�趨�������Զ���װֵ 
	TIM_TimeBaseStructure.TIM_Prescaler = psc; 	//Ԥ��Ƶ�� 
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

	//��ʼ��TIM4���벶����� ͨ��1
	TIM4_ICInitStructure.TIM_Channel = TIM_Channel_1; //CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
	TIM4_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//�����ز���
	TIM4_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI1��
	TIM4_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	  //���������Ƶ,����Ƶ 
	TIM4_ICInitStructure.TIM_ICFilter = 0x00;	  //IC1F=0000 ���������˲��� ���˲�
	TIM_ICInit(TIM4, &TIM4_ICInitStructure);

	//�жϷ����ʼ��
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  //TIM4�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
	//NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //�����ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);   //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ��� 

	TIM_ITConfig(TIM4, TIM_IT_CC1,ENABLE);   //����������жϣ�����CC1IE,CC2IE,CC3IE,CC4IE�����ж�	

	TIM_Cmd(TIM4, ENABLE); 		//ʹ�ܶ�ʱ��4

}


/**
	*@brief 	��ʱ��4�жϷ������CH1,CH2,CH3,CH4����
	*@param		NONE
	*@return	NONE
	*/
void TIM4_IRQHandler(void)
{
	if ((TIM4CH1_CAPTURE_STA & 0X80) == 0) 		//��δ�ɹ�����	
	{
		if (TIM_GetITStatus(TIM4, TIM_IT_CC1) != RESET) 		//����1���������¼�
		{
			TIM_ClearITPendingBit(TIM4, TIM_IT_CC1); 		//����жϱ�־λ
			if (TIM4CH1_CAPTURE_STA & 0X40)		//����һ���½���
			{
				TIM4CH1_CAPTURE_DOWNVAL = TIM_GetCapture1(TIM4);//��¼�´�ʱ�Ķ�ʱ������ֵ
				if (TIM4CH1_CAPTURE_DOWNVAL < TIM4CH1_CAPTURE_UPVAL)
				{
					tim4_T1 = 65535;
				}
				else
					tim4_T1 = 0;
				PWM_in1 = TIM4CH1_CAPTURE_DOWNVAL - TIM4CH1_CAPTURE_UPVAL
						+ tim4_T1;		//�õ��ܵĸߵ�ƽ��ʱ��
				pwm_in_ch1 = PWM_in1;		//�ܵĸߵ�ƽ��ʱ��
				TIM4CH1_CAPTURE_STA = 0;		//�����־λ����
				TIM_OC1PolarityConfig(TIM4, TIM_ICPolarity_Rising); //����Ϊ�����ز���		  
			}
			else //��������ʱ�䵫�����½��أ���һ�β��������أ���¼��ʱ�Ķ�ʱ������ֵ
			{
				TIM4CH1_CAPTURE_UPVAL = TIM_GetCapture1(TIM4);		//��ȡ����������
				TIM4CH1_CAPTURE_STA |= 0X40;		//����Ѳ���������
				TIM_OC1PolarityConfig(TIM4, TIM_ICPolarity_Falling);//����Ϊ�½��ز���
			}
		}
	}
}
