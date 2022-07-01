#include "STC15F2K60S2.H"        //必须。
#include "sys.H"                 //必须。
#include "Beep.H" 

code unsigned long SysClock=11059200;         //必须。定义系统工作时钟频率(Hz)，用户必须修改成与实际工作频率（下载时选择的）一致



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