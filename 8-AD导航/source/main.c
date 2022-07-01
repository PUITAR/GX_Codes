#include "STC15F2K60S2.H"        //���롣
#include "sys.H"                 //���롣
#include "displayer.H" 
#include "Key.H"
#include "adc.H"

code unsigned long SysClock=11059200;         //���롣����ϵͳ����ʱ��Ƶ��(Hz)���û������޸ĳ���ʵ�ʹ���Ƶ�ʣ�����ʱѡ��ģ�һ��


/* ��ʼʱ�м���λled��������Key3ѡ����Ҫ�ƶ���led�� */
unsigned char l1 = 0x10;		
unsigned char l2 = 0x08;
char lsel = 0;


void myLED() {
	LedPrint(l1 | l2);
}


void myMove(){
	char k;
	if((k = GetAdcNavAct(enumAdcNavKey3)) == enumKeyPress) 
		lsel = !lsel; 
	
	if((k = GetAdcNavAct(enumAdcNavKeyLeft)) == enumKeyPress) {
		if(lsel == 0) {
			l1 = l1 << 1;
			if(l1 == 0) l1 = 0x01;
		}
		else {
			l2 = l2 << 1;
			if(l2 == 0) l2 = 0x01;
		}
	}
	
	if((k = GetAdcNavAct(enumAdcNavKeyRight)) == enumKeyPress) {
		if(lsel == 0) {
			l1 = l1 >> 1;
			if(l1 == 0) l1 = 0x80;
		}
		else {
			l2 = l2 >> 1;
			if(l2 == 0) l2 = 0x80;
		}
	}
}

void main() 
{
	//��ʼ��
	AdcInit(ADCexpEXT);
	DisplayerInit();  
	LedPrint(0);
	SetDisplayerArea(8, 8);
	//���ûص�����
	SetEventCallBack(enumEventSys100mS, myLED);
	SetEventCallBack(enumEventNav, myMove);
	
	MySTC_Init();	    
	while(1)             	
	{ 
		MySTC_OS();    
	}	             
}                 