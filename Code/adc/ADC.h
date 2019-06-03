/**------------------------------------------------------------------**/
//* File name ��ADC.h                                              
//* Author    : Huangshuang				             
//* Data      : 2019/5/31				             
//* Version   : V1.0				                     
/**------------------------------------------------------------------**/

#ifndef ADC_H
#define ADC_H
#define	ADC1_DR_Adress	((u32)0x40012400+0x4c)	//ADC1���ݼĴ����ĵ�ַ
#include "stm32f10x.h"

void ADC1_Config(void);									//ADC1��ʼ��
void ADC_GPIO_Config(void);							//ADC1�˿ڳ�ʼ��
void ADC_Mode_Config(void);							//ADCģʽ��ʼ��
void filter(void);											//ƽ�����˲�
float Get_Anolog_Voltage(u16 AD_VALUE);	//��ADC�ɼ��Ľ�������ʵ�������ģ���ѹֵ

#endif	/*ADC_H*/
