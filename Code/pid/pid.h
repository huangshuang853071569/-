/**-------------------------------------------------------------**/
//*	File name :	pid.h											
//* Author	  : Huangshuang										
//*	Data	  	:	2019/5/31										
//* Version	  : V1.0											
/**-------------------------------------------------------------**/

#ifndef _PID_H
#define	_PID_H

/*Including Here*/
/*------------------*/
#include "stm32f10x.h"
#include "math.h"
/*------------------*/

//#define ENABLE_INTEGRAL_SEPARATING		//是否使能积分分离（定义则使能）

/*extern parameters*/			//外环参数
#define KP_EXT 0.1f
#define KI_EXT 0.0f
#define KD_EXT 0.0f

/*inside parameters*/			//内环参数
#define KP_INS 35.0f
#define KI_INS 0.0f
#define KD_INS 2.0f

#define PID_MAX 			20000			//积分上限
#define PID_MIN 			-20000		//积分下限
#define ERR_TRD_INS 	500				//积分分离的误差阈值
#define	POS_DEAD 			200					//误差死区

float pid_control(float except,float current,float delta_T);
#endif
