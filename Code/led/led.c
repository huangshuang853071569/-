/**------------------------------------------------------------------**/
//* File name ��led.c                                              
//* Author    : Huangshuang				             
//* Data      : 2019/5/31				             
//* Version   : V1.0				                     
/**------------------------------------------------------------------**/

#include "led.h"
	    
/**
	*@breif 	LED��ʼ��
	*@param		NONE
	*@return 	NONE
	*/
void LED_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //ʹ��PB�˿�ʱ��
	
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 	 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 	 //IO���ٶ�Ϊ50MHz

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;						 	 //����ָʾ�� PB11
 GPIO_Init(GPIOB, &GPIO_InitStructure);					 			  
 GPIO_SetBits(GPIOB,GPIO_Pin_10);						 					  
	
 GPIO_InitStructure.GPIO_Pin =GPIO_Pin_13|GPIO_Pin_14;		//ģʽ�л�ָʾ�� PB13 PB14
 GPIO_Init(GPIOB, &GPIO_InitStructure);	
 GPIO_ResetBits(GPIOB,GPIO_Pin_13|GPIO_Pin_14);					

}
 