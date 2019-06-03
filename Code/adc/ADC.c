/**------------------------------------------------------------------**/
//* File name ��ADC.c                                              
//* Author    : Huangshuang				             
//* Data      : 2019/5/31				             
//* Version   : V1.0				                     
/**------------------------------------------------------------------**/
#include	"ADC.h"
#include	"led.h"
#include	"stm32f10x.h"

#define N 30  //ÿ��ͨ������50��
#define M 9 	//ADC�õ���ͨ����

volatile vu16 AD_Value[N][M]; 	 //�������ADC��ת�������Ҳ���ڴ�Ļ���ַ
volatile vu16 After_filter[M];  //ƽ�����˲������������	

 
 /**
	* @brief ��  ��ʼ��ADC1ΪDMA��ʽ������ʼADת��,
               ת�����ֵADC_ConvertedValueͨ��DMA���䵽SRAM
	* @param ��  ��
	* @retval :  ��
*/
void ADC1_Config(void)
{
	ADC_GPIO_Config();
	ADC_Mode_Config();
}

/**
	*	@brief  :  ADC��GPIO��ʼ��
	*	@param  :  ��
	*	@retval	:	 ��
*/
void ADC_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStruction;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB, ENABLE);		//ʹ��GPIOA��GPIOBʱ��
	//PA1
	GPIO_InitStruction.GPIO_Mode=GPIO_Mode_AIN;
	GPIO_InitStruction.GPIO_Pin=GPIO_Pin_1; 
	GPIO_Init(GPIOA, &GPIO_InitStruction);

	}

/**
	* @brief  :  ADC1��ģʽ��ʼ��
	*	@param  :  ��
	* @retval :  ��
*/
void ADC_Mode_Config(void)
{
	DMA_InitTypeDef DMA_InitStructure;
	ADC_InitTypeDef ADC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);									//ʹ��ADC1ʱ��
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);										//ʹ��DMA1ʱ��
	
	//ADC1ģʽ��ʼ��
	ADC_DeInit(ADC1); 																										//�Ƚ�ADCģʽ��ʼΪȱʡֵ
	ADC_InitStructure.ADC_ScanConvMode=ENABLE;														//�ɼ����ͨ��ʱ�����뿪��ɨ��ģʽ
	ADC_InitStructure.ADC_Mode=ADC_Mode_Independent;											//�����ڶ���ADCģʽ
	ADC_InitStructure.ADC_ContinuousConvMode=ENABLE;											//ʹ����������ģʽ
	ADC_InitStructure.ADC_DataAlign=ADC_DataAlign_Right;									//�����Ҷ���
	ADC_InitStructure.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None;			//��ʹ���ⲿ�ж���ΪADC�Ĵ�����ʽ
	ADC_InitStructure.ADC_NbrOfChannel=M;																	//ʹ��9��ͨ��
	ADC_Init(ADC1, &ADC_InitStructure);
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div8);																			//����ADCʱ��ΪPCLK2��8��Ƶ
	
	//����ADC1��ͨ���������У���Ϊ55.5����������
	ADC_RegularChannelConfig( ADC1, ADC_Channel_1, 1, ADC_SampleTime_55Cycles5);
		
	ADC_DMACmd(ADC1,ENABLE);												//ʹ��ADC DMA	
	//ADC_ITConfig(ADC1, ADC_IT_EOC, ENABLE);				//ʹ��ADC1�ж�
	ADC_Cmd(ADC1,ENABLE);														//ʹ��ADC
	
	//ADC1У׼
	ADC_ResetCalibration(ADC1);											//��λУ׼�Ĵ���
	while(ADC_GetResetCalibrationStatus(ADC1));			//�ȴ��Ĵ�����λ
	ADC_StartCalibration(ADC1);											//��ʼУ׼
	while(ADC_GetCalibrationStatus(ADC1));					//�ȴ�У׼���
	
	/*****������DMA1ͨ��1���ò���*****/
	DMA_DeInit(DMA1_Channel1);																									//�Ƚ�DMA1��ģʽ�ָ�ȱʡֵ
	DMA_InitStructure.DMA_PeripheralBaseAddr=(u32)0x40012400+0x4c;//(u32)&ADC1->DR;										//����ĵ�ַ��ADC1�����ݼĴ���(u32)0x40012400+0x4c (u32)&ADC1->DR
	DMA_InitStructure.DMA_MemoryBaseAddr=(u32)&AD_Value;												//�ڴ�Ļ���ַ
	DMA_InitStructure.DMA_DIR=DMA_DIR_PeripheralSRC;														//DMA����ԴΪ����
	DMA_InitStructure.DMA_MemoryInc=DMA_MemoryInc_Enable ;											//�ڴ��ַ��Ҫ����
	DMA_InitStructure.DMA_PeripheralInc=DMA_PeripheralInc_Disable;							//�����ַʼ��ΪADC�����ݼĴ�����ַ��������
	DMA_InitStructure.DMA_BufferSize=N*M;																				//һ�δ����������Ĵ�С��DMAͨ����DMA�����С��
	DMA_InitStructure.DMA_MemoryDataSize=DMA_MemoryDataSize_HalfWord; 					//�ڴ����ݿ�ȣ����֣�16λ
	DMA_InitStructure.DMA_PeripheralDataSize=DMA_PeripheralDataSize_HalfWord;		//�������ݿ�ȣ����֣�16λ
	DMA_InitStructure.DMA_Mode=DMA_Mode_Circular;																//ѭ������
	DMA_InitStructure.DMA_Priority=DMA_Priority_High;														//����Ȩ���ߡ�ֻʹ��һ��DMAͨ��ʱû������
	DMA_InitStructure.DMA_M2M=DMA_M2M_Disable;																	//�����ڴ浽�ڴ�Ĵ���
	DMA_Init(DMA1_Channel1,&DMA_InitStructure);	
	
	DMA_Cmd(DMA1_Channel1, ENABLE);								//ʹ��DMA1ͨ��1
	
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);				//�������ADC1��ʼת��
	
}

/**
	*@brief : ƽ��ֵ�˲�
	*@param : ��
	*
**/
void filter(void)
{
	int sum=0;
	int i=0;
	u8 count=0;
	for(i=0;i<M;i++)
	{
		for(count=0;count<N;count++) sum+=AD_Value[count][i];
		After_filter[i]=sum/N;
		sum=0;
	}
}

/**
	*@brief : �����ģ���ѹֵ
	*@param : ADת���õ�������
	*@return: ʵ�������ģ���ѹֵ
**/
float Get_Anolog_Voltage(u16 AD_VALUE)
{
	return AD_VALUE*3.3/4096;
}

///**
//	*@brief	:	ADC1�жϺ���
//	*@param	:	��
//	*
//**/
//void ADC1_2_IRQHandler(void)
//{
//	if(ADC_GetITStatus(ADC1, ADC_IT_EOC)!=RESET)
//	{
//		LED2(ON)
//	}
//}
