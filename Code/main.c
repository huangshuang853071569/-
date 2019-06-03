/**------------------------------------------------------------------**/
//* File name �� main.c                                              
//* Author    : Huangshuang				             
//* Data      : 2019/5/31				             
//* Version   : V1.0				                     
/**------------------------------------------------------------------**/
#include "include.h"

extern float except_pos;			//����λ��
extern float current_pos;			//��ǰλ��
extern float PID_Contol_Out;	//pid��������������ֵ
extern float integral_ins;		//������ֵ

extern float PID_Control_Out;	//pid���ƺ�����ֵ
int main(void)
{
	init();						//Ӳ����ʼ��
	
	while(1)
	{
		data_process();	//�������ݴ���
		
			
		PID_Control_Out=pid_control(except_pos,current_pos,5);
		
		Motor_Control();			//PID����

		delay_ms(1);

	}		
}

/***������ݴ�ӡ***/
/*
	printf("%f \r\n",except_pos);												//����λ��
	printf("%f \r\n",integral_ins);											//������ֵ
	printf("%f \r\n",current_pos);											//��ǰλ��
	printf("err = %f \r\n",except_pos-current_pos);			//���
	printf("%f \r\n",PID_Contol_Out);										//PID������ֵ
*/
