#include "STC15F2K60S2.H"        //���롣
#include "sys.H"                 //���롣
#include "displayer.H" 
#include "beep.H"
#include "adc.H"

code unsigned long SysClock=11059200;         //���롣����ϵͳ����ʱ��Ƶ��(Hz)���û������޸ĳ���ʵ�ʹ���Ƶ�ʣ�����ʱѡ��ģ�һ��
#ifdef _displayer_H_                          //��ʾģ��ѡ��ʱ���롣���������ʾ��������Ñ����޸ġ����ӵȣ� 
code char decode_table[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x00,0x08,0x40,0x01, 0x41, 0x48, 
	              /* ���:   0   1    2	   3    4	    5    6	  7   8	   9	 10	   11		12   13    14     15     */
                /* ��ʾ:   0   1    2    3    4     5    6    7   8    9  (��)   ��-  ��-  ��-  ����-  ����-   */  
	                       0x3f|0x80,0x06|0x80,0x5b|0x80,0x4f|0x80,0x66|0x80,0x6d|0x80,0x7d|0x80,0x07|0x80,0x7f|0x80,0x6f|0x80 };  
             /* ��С����     0         1         2         3         4         5         6         7         8         9        */
#endif
 
int num[3] = {0};
void my100mS_callback(){
	struct_ADC adc_data;
	adc_data = GetADC();
	num[0] = adc_data.Rop/100; num[1] = adc_data.Rop/10%10; num[2] = adc_data.Rop%10;
	if(adc_data.Rop < 20) SetBeep(1200,10);					//1.2KHz,100ms
	else if(adc_data.Rop > 100) SetBeep(2000,10);		//2KHz,100ms
}
void my1S_callback(){
	Seg7Print(10,10,10,10,10,num[0],num[1],num[2]);
}

void main() 
{
	//��ʼ��
	AdcInit(ADCincEXT);
	DisplayerInit(); 
	BeepInit();
	LedPrint(0);
	SetDisplayerArea(5,7);
	//���ûص�����
	SetEventCallBack(enumEventSys10mS, my100mS_callback);
	SetEventCallBack(enumEventSys1S, my1S_callback);
  	MySTC_Init();	    
	while(1)             	
	{ 
		MySTC_OS();    
	}	             
}                 