#include "STC15F2K60S2.H"        //���롣
#include "sys.H"                 //���롣
#include "Beep.H" 

code unsigned long SysClock=11059200;         //���롣����ϵͳ����ʱ��Ƶ��(Hz)���û������޸ĳ���ʵ�ʹ���Ƶ�ʣ�����ʱѡ��ģ�һ��



void main() 
{ 
	BeepInit();  
	SetBeep(1200, 180);	
	MySTC_Init();	    
	while(1)             	
	{ 
		MySTC_OS();    
	}	             
}                 