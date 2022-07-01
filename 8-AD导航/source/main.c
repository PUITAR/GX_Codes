#include "STC15F2K60S2.H"        //必须。
#include "sys.H"                 //必须。
#include "displayer.H" 
#include "Key.H"
#include "adc.H"

code unsigned long SysClock=11059200;         //必须。定义系统工作时钟频率(Hz)，用户必须修改成与实际工作频率（下载时选择的）一致


/* 初始时中间两位led灯亮起，用Key3选择需要移动的led灯 */
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
	//初始化
	AdcInit(ADCexpEXT);
	DisplayerInit();  
	LedPrint(0);
	SetDisplayerArea(8, 8);
	//设置回调函数
	SetEventCallBack(enumEventSys100mS, myLED);
	SetEventCallBack(enumEventNav, myMove);
	
	MySTC_Init();	    
	while(1)             	
	{ 
		MySTC_OS();    
	}	             
}                 