#include "STC15F2K60S2.H"        //���롣
#include "sys.H"                 //���롣
#include "displayer.H" 
#include "Key.H"
#include "adc.H"

code unsigned long SysClock=11059200;         //���롣����ϵͳ����ʱ��Ƶ��(Hz)���û������޸ĳ���ʵ�ʹ���Ƶ�ʣ�����ʱѡ��ģ�һ��
#ifdef _displayer_H_                          //��ʾģ��ѡ��ʱ���롣���������ʾ������Ñ����޸ġ����ӵȣ� 
code char decode_table[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x00,0x08,0x40,0x01, 0x41, 0x48, 
	              /* ���:   0   1    2	   3    4	    5    6	  7   8	   9	 10	   11		12   13    14     15     */
                /* ��ʾ:   0   1    2    3    4     5    6    7   8    9  (��)   ��-  ��-  ��-  ����-  ����-   */  
	                       0x3f|0x80,0x06|0x80,0x5b|0x80,0x4f|0x80,0x66|0x80,0x6d|0x80,0x7d|0x80,0x07|0x80,0x7f|0x80,0x6f|0x80 };  
             /* ��С����     0         1         2         3         4         5         6         7         8         9        */
#endif
/* ��ʼʱ�м���λled��������Key3ѡ����Ҫ�ƶ���led�� */
unsigned char l1 = 0x10;		
unsigned char l2 = 0x08;
char mode = 0;

void my10mS_callback(){
	char k;
	k = GetAdcNavAct(enumAdcNavKey3);
	if(k == enumKeyPress) mode = !mode; 			//�л���Ҫ�ƶ��ĵ�
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
	//��ʼ��
	AdcInit(ADCincEXT);
	DisplayerInit();  
	LedPrint(l1|l2);
	SetDisplayerArea(0,0);
	//���ûص�����
	SetEventCallBack(enumEventSys10mS, my10mS_callback);
  MySTC_Init();	    
	while(1)             	
	{ 
		MySTC_OS();    
	}	             
}                 