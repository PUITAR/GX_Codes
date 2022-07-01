#include "STC15F2K60S2.H"        //���롣
#include "sys.H"                 //���롣
#include "StepMotor.H"
#include "displayer.h"
code unsigned long SysClock=11059200;         //���롣����ϵͳ����ʱ��Ƶ��(Hz)���û������޸ĳ���ʵ�ʹ���Ƶ�ʣ�����ʱѡ��ģ�һ��



void main() 
{   
	StepMotorInit();
	DisplayerInit();
	SetStepMotor(enumStepMotor2,10,10000);
	SetDisplayerArea(0, 7); // ����
	
	MySTC_Init();	    
	while(1)             	
	{ 
		MySTC_OS();    
	}	             
}                 