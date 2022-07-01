#include "STC15F2K60S2.H"        //���롣
#include "sys.H"                 //���롣
#include "displayer.H" 
#include "key.H" 
#include "beep.H" 
#include "music.h"
#include "hall.H"
#include "Vib.h"
code unsigned long SysClock=11059200;         //���롣����ϵͳ����ʱ��Ƶ��(Hz)���û������޸ĳ���ʵ�ʹ���Ƶ�ʣ�����ʱѡ��ģ�һ��
#ifdef _displayer_H_                          //��ʾģ��ѡ��ʱ���롣���������ʾ��������Ñ����޸ġ����ӵȣ� 
code char decode_table[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x00,0x08,0x40,0x01, 0x41, 0x48, 
	              /* ���:   0   1    2	   3    4	    5    6	  7   8	   9	 10	   11		12   13    14     15     */
                /* ��ʾ:   0   1    2    3    4     5    6    7   8    9  (��)   ��-  ��-  ��-  ����-  ����-   */  
	                       0x3f|0x80,0x06|0x80,0x5b|0x80,0x4f|0x80,0x66|0x80,0x6d|0x80,0x7d|0x80,0x07|0x80,0x7f|0x80,0x6f|0x80 };  
             /* ��С����     0         1         2         3         4         5         6         7         8         9        */
#endif

void Vib_callback()
{
	if(GetVibAct()==enumVibQuake)//�����
	{
	if(GetBeepStatus()==enumBeepFree)//�������������
		SetBeep(100,100);//��������������һ��������Ƶ�ʣ��ڶ�����������10Ϊ����ʱ�䣬��λΪms
	}
}
void main() 
{ 
	BeepInit();
	VibInit();
	displayerInit();
	SetDisplayerArea(1,7);
	SetEventCallBack(enumEventVib, Vib_callback);
  MySTC_Init();	   
	while(1)             	
		{ 
			MySTC_OS();    
		}	             
}                 