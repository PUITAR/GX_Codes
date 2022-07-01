#include "STC15F2K60S2.H"        //���롣
#include "sys.H"                 //���롣
#include "hall.H" 
#include "displayer.H" 

code unsigned long SysClock=11059200;         //���롣����ϵͳ����ʱ��Ƶ��(Hz)���û������޸ĳ���ʵ�ʹ���Ƶ�ʣ�����ʱѡ��ģ�һ��
#ifdef _displayer_H_                          //��ʾģ��ѡ��ʱ���롣���������ʾ������Ñ����޸ġ����ӵȣ� 
code char decode_table[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x00,0x08,0x40,0x01, 0x41, 0x48, 
	              /* ���:   0   1    2	   3    4	    5    6	  7   8	   9	 10	   11		12   13    14     15     */
                /* ��ʾ:   0   1    2    3    4     5    6    7   8    9  (��)   ��-  ��-  ��-  ����-  ����-   */  
	                       0x3f|0x80,0x06|0x80,0x5b|0x80,0x4f|0x80,0x66|0x80,0x6d|0x80,0x7d|0x80,0x07|0x80,0x7f|0x80,0x6f|0x80,
                /* ��С����     0         1         2         3         4         5         6         7         8         9        */
	                       0x76,0x38};
                /*        H     L         */
#endif

unsigned char b=0x00;
unsigned char a=0x0f;
void my100mS_callback()
{ 

	if( a==0x1E | a==0x3C | a==0x78 | a==0x0F ) a=a<<1;
	else if( a==0xF0 ) a=0xE1;
	else if( a==0xE1 ) a=0xC3;
	else if( a==0xC3 ) a=0x87;
	else a=0x0F;
	LedPrint(a&b);
	
}

void hall_callback()
{ 
	char k;
	k=GetHallAct();
	if( k == enumHallGetClose ) {
		a=0x0f;
	  b=0xFF;
	}
	else if( k == enumHallGetAway )
		b=0x00;
}

void main() 
{ 
 
	HallInit();
	DisplayerInit();
	SetDisplayerArea(0,7);
	Seg7Print(10,10,10,10,10,10,10,10);
	LedPrint(0);
	SetEventCallBack(enumEventSys100mS, my100mS_callback);
	SetEventCallBack(enumEventHall, hall_callback);
  MySTC_Init();	    
	while(1)             	
		{ 
			MySTC_OS();    
		}	             
}                 