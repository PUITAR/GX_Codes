#include "STC15F2K60S2.H"        //���롣
#include "sys.H"                 //���롣
#include "displayer.H" 
#include "key.H"  


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



code unsigned long SysClock=11059200;         //���롣����ϵͳ����ʱ��Ƶ��(Hz)���û������޸ĳ���ʵ�ʹ���Ƶ�ʣ�����ʱѡ��ģ�һ��

struct ti {
	int min;  //��
	int sec; //��
	int msec; //���룬�ֱ���Ϊ10ms
} time;


static status = 0;  //���״̬��0δ�߱�1�����߱�

void time_init();  //��ʼ��ʱ��
void time_inc();  //��10ms
void display();  //��ʱ��չʾ���������,�ص�
void key_event(); //�������������뿪ʼ����ͣ���ص�

void main()
{
	DisplayerInit();
	KeyInit();
	SetDisplayerArea(0,7);
	
	LedPrint(0);  //��led�ƣ������۾�
	time_init();
	
	SetEventCallBack(enumEventSys10mS, display);
	SetEventCallBack(enumEventKey, key_event);
	
	MySTC_Init();	    
	while(1){
		MySTC_OS();
	}	
}
void time_init(){
	time.min = time.sec = time.msec = 0;
	Seg7Print(0, 0, 12, 0, 0, 12, 0, 0);
}
//����10ms
void time_inc(){
	time.msec++;
	if(time.msec == 100){
		time.msec = 0;
		time.sec++;
	}
	if(time.sec == 60){
		time.sec = 0;
		time.min++;
	}
	if(time.min == 100){
		time.min = 0;
	}
}
void key_event(){
	char k;
	if( (k=GetKeyAct(enumKey1)) == enumKeyPress ){  //������ʱ������k1��ͣ������ͣʱ������k1��������
		status = !status;
	}
}
void display(){
	if(status){  //����״̬�¼���
		time_inc();	
		Seg7Print(time.min/10, time.min%10, 12, time.sec/10, time.sec%10, 12, time.msec/10, time.msec%10);
	}	
}