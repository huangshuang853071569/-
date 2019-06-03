/**----------------------------------------------------------**/
//*	File name : data_process.c									 
//*	Author	  : Huangshuang 								 
//*	Data 	    : 2019/5/31									 
//*	Vertion	  : V1.0										 
/**----------------------------------------------------------**/
#include "data_process.h"

float Anolog_Voltage_1;												    //�����õ��ĵ�ѹ
extern vu16 After_filter[];  											//ƽ�����˲������������
extern  u32 pwm_in_ch1;														//�����PWM����

volatile float except_pos;																//����λ�� 0~33000
volatile float current_pos;																//��ǰλ�� 0~33000
volatile float PID_Control_Out;														//PID���ƺ�����ֵ										

/**
	*	@breif ����PWMֵӳ��Ϊ����λ��	
	* @param pwm_in:PWM��������
	* @return ����λ��
	*/
float get_except_pos(float pwm_in)
{
	if(pwm_in<1000)pwm_in=1000;
	if(pwm_in>2000)pwm_in=2000;
	return ((float)(33*pwm_in-49500));					//��1000~2000ӳ��Ϊ-16500~16500
}
							
/**
	*	@breif ����PWMֵӳ��Ϊ����λ��	
	* @param float vol : ��ѹ
	* @return ����λ��
	*/
float get_current_pos(void)
{
	filter();	//��ֵ�˲�																			
	Anolog_Voltage_1=Get_Anolog_Voltage(After_filter[0]); 	//��ȡADC��ѹ	
	return Anolog_Voltage_1*10000-16500; 										//���㵱ǰλ��	//��0~3.3ӳ��Ϊ-16500~16500
}

/**
	*	@breif data_process	
	* @param float vol : ��ѹ
	* @return ����λ��
	*/
void data_process(void)
{
	except_pos=get_except_pos((float)pwm_in_ch1);	//��ȡ����λ��
	current_pos=get_current_pos();								//��ȡ��ǰλ��
}
	