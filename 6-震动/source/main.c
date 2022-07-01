#include "STC15F2K60S2.H"        //���롣
#include "sys.H"                 //���롣
#include "beep.H" 
#include "Vib.h"
code unsigned long SysClock=11059200;         //���롣����ϵͳ����ʱ��Ƶ��(Hz)���û������޸ĳ���ʵ�ʹ���Ƶ�ʣ�����ʱѡ��ģ�һ��


#ifdef _displayer_H_                          //��ʾģ��ѡ��ʱ���롣���������ʾ������Ñ����޸ġ����ӵȣ� 
code char decode_table[]={
		      0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f, 0x00, 0x08, 0x40, 0x01, 0x20, 0x02, 0x10, 0x04, 0x80,
	/* ���:  0     1     2	    3     4	    5     6	    7     8	    9	  10	11	  12    13    14    15    16    17    18     */
    /* ��ʾ:  0     1     2     3     4     5     6     7     8     9     (��)  ��-   ��-   ��-   ����| ����| ����| ����| С���� */  
	                0x3f|0x80, 0x06|0x80, 0x5b|0x80, 0x4f|0x80, 0x66|0x80, 0x6d|0x80, 0x7d|0x80, 0x07|0x80, 0x7f|0x80, 0x6f|0x80, 
	/* ���:  		19         20         21         22         23         24         25         26         27         28        */
    /* ��С����     0          1          2          3          4          5          6          7          8          9         */
					0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71, 0x3d, 0x76, 0x0f, 0x0e,
	/* ���:  		29    30    31    32    33    34    35    36    37    38                                                     */
	/* ��ʾ��       A     B     C     D     E     F     G     H     I     J                                                      */
				    0x75, 0x38, 0x37, 0x54, 0x5c, 0x73, 0x67, 0x31, 0x49, 0x78,
	/* ���:  		39    40    41    42    43    44    45    46    47    48                                                     */
	/* ��ʾ��       K     L     M     N     O     P     Q     R     S     T                                                      */
					0x3e, 0x1c, 0x7e, 0x64, 0x6e, 0x59
	/* ���:  		49    50    51    52    53    54                                                                             */
	/* ��ʾ��       U     V     W     X     Y     Z                                                                              */
}; 
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
	SetEventCallBack(enumEventVib, Vib_callback);
	
	MySTC_Init();	   
	while(1)             	
	{ 
		MySTC_OS();    
	}	             
}                 