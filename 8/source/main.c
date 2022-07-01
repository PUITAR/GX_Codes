#include "STC15F2K60S2.H"        //必须。
#include "sys.H"                 //必须。
#include "displayer.H" 
#include "Key.H"
#include "adc.H"

code unsigned long SysClock=11059200;         //必须。定义系统工作时钟频率(Hz)，用户必须修改成与实际工作频率（下载时选择的）一致
#ifdef _displayer_H_                          //显示模块选用时必须。（数码管显示译码表，用戶可修改、增加等） 
code char decode_table[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x00,0x08,0x40,0x01, 0x41, 0x48, 
	              /* 序号:   0   1    2	   3    4	    5    6	  7   8	   9	 10	   11		12   13    14     15     */
                /* 显示:   0   1    2    3    4     5    6    7   8    9  (无)   下-  中-  上-  上中-  中下-   */  
	                       0x3f|0x80,0x06|0x80,0x5b|0x80,0x4f|0x80,0x66|0x80,0x6d|0x80,0x7d|0x80,0x07|0x80,0x7f|0x80,0x6f|0x80 };  
             /* 带小数点     0         1         2         3         4         5         6         7         8         9        */
#endif
/* 初始时中间两位led灯亮起，用Key3选择需要移动的led灯 */
unsigned char l1 = 0x10;		
unsigned char l2 = 0x08;
char mode = 0;

void my10mS_callback(){
	char k;
	k = GetAdcNavAct(enumAdcNavKey3);
	if(k == enumKeyPress) mode = !mode; 			//切换需要移动的灯
	k = GetAdcNavAct(enumAdcNavKeyLeft);
	if(k == enumKeyPress) {
		if(mode == 0) {
			l1 = l1 << 1;
			if(l1 == 0) l1 = 0x01;
		}
		else {
			l2 = l2 << 1;
			if(l2 == 0) l2 = 0x01;
		}
	}
	k = GetAdcNavAct(enumAdcNavKeyRight);
	if(k == enumKeyPress) {
		if(mode == 0) {
			l1 = l1 >> 1;
			if(l1 == 0) l1 = 0x80;
		}
		else {
			l2 = l2 >> 1;
			if(l2 == 0) l2 = 0x80;
		}
	}
	LedPrint(l1 | l2);
}

void main() 
{
	//初始化
	AdcInit(ADCincEXT);
	DisplayerInit();  
	LedPrint(l1|l2);
	SetDisplayerArea(0,0);
	//设置回调函数
	SetEventCallBack(enumEventSys10mS, my10mS_callback);
  MySTC_Init();	    
	while(1)             	
	{ 
		MySTC_OS();    
	}	             
}                 