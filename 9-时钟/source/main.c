#include "STC15F2K60S2.H"        //必须。
#include "sys.H"                 //必须。
#include "displayer.H" 
#include "key.H"  


#ifdef _displayer_H_                          //显示模块选用时必须。（数码管显示译码表，用戶可修改、增加等） 
code char decode_table[]={
		      0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f, 0x00, 0x08, 0x40, 0x01, 0x20, 0x02, 0x10, 0x04, 0x80,
	/* 序号:  0     1     2	    3     4	    5     6	    7     8	    9	  10	11	  12    13    14    15    16    17    18     */
    /* 显示:  0     1     2     3     4     5     6     7     8     9     (无)  下-   中-   上-   左上| 右上| 左下| 右下| 小数点 */  
	                0x3f|0x80, 0x06|0x80, 0x5b|0x80, 0x4f|0x80, 0x66|0x80, 0x6d|0x80, 0x7d|0x80, 0x07|0x80, 0x7f|0x80, 0x6f|0x80, 
	/* 序号:  		19         20         21         22         23         24         25         26         27         28        */
    /* 带小数点     0          1          2          3          4          5          6          7          8          9         */
					0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71, 0x3d, 0x76, 0x0f, 0x0e,
	/* 序号:  		29    30    31    32    33    34    35    36    37    38                                                     */
	/* 显示：       A     B     C     D     E     F     G     H     I     J                                                      */
				    0x75, 0x38, 0x37, 0x54, 0x5c, 0x73, 0x67, 0x31, 0x49, 0x78,
	/* 序号:  		39    40    41    42    43    44    45    46    47    48                                                     */
	/* 显示：       K     L     M     N     O     P     Q     R     S     T                                                      */
					0x3e, 0x1c, 0x7e, 0x64, 0x6e, 0x59
	/* 序号:  		49    50    51    52    53    54                                                                             */
	/* 显示：       U     V     W     X     Y     Z                                                                              */
}; 
#endif



code unsigned long SysClock=11059200;         //必须。定义系统工作时钟频率(Hz)，用户必须修改成与实际工作频率（下载时选择的）一致

struct ti {
	int min;  //分
	int sec; //秒
	int msec; //毫秒，分辨率为10ms
} time;


static status = 0;  //秒表状态，0未走表，1正在走表

void time_init();  //初始化时钟
void time_inc();  //加10ms
void display();  //将时间展示在数码管上,回调
void key_event(); //按键，控制走秒开始与暂停，回调

void main()
{
	DisplayerInit();
	KeyInit();
	SetDisplayerArea(0,7);
	
	LedPrint(0);  //关led灯，保护眼睛
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
//增加10ms
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
	if( (k=GetKeyAct(enumKey1)) == enumKeyPress ){  //当走秒时，按下k1暂停；当暂停时，按下k1继续走秒
		status = !status;
	}
}
void display(){
	if(status){  //走秒状态下计数
		time_inc();	
		Seg7Print(time.min/10, time.min%10, 12, time.sec/10, time.sec%10, 12, time.msec/10, time.msec%10);
	}	
}