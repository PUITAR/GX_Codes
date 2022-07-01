#include "STC15F2K60S2.H"        
#include "sys.H"                 
#include "displayer.H" 
#include "beep.H"
#include "adc.H"

code unsigned long SysClock=11059200;         

#ifdef _displayer_H_                          
code char decode_table[]={
		      0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f, 0x00, 0x08, 0x40, 0x01, 0x20, 0x02, 0x10, 0x04, 0x80,
	/*        0     1     2	    3     4	    5     6	    7     8	    9	  10	11	  12    13    14    15    16    17    18     */
    /*        0     1     2     3     4     5     6     7     8     9     null  down- mid-  up-   lu|   ru|   ld|   rd|   point  */  
	                0x3f|0x80, 0x06|0x80, 0x5b|0x80, 0x4f|0x80, 0x66|0x80, 0x6d|0x80, 0x7d|0x80, 0x07|0x80, 0x7f|0x80, 0x6f|0x80, 
	/*       		19         20         21         22         23         24         25         26         27         28        */
    /* 		        0          1          2          3          4          5          6          7          8          9         */
					0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71, 0x3d, 0x76, 0x0f, 0x0e,
	/*       		29    30    31    32    33    34    35    36    37    38                                                     */
	/*              A     B     C     D     E     F     G     H     I     J                                                      */
				    0x75, 0x38, 0x37, 0x54, 0x5c, 0x73, 0x67, 0x31, 0x49, 0x78,
	/*      		39    40    41    42    43    44    45    46    47    48                                                     */
	/*              K     L     M     N     O     P     Q     R     S     T                                                      */
					0x3e, 0x1c, 0x7e, 0x64, 0x6e, 0x59
	/*      		49    50    51    52    53    54                                                                             */
	/*              U     V     W     X     Y     Z                                                                              */
}; 
#endif

 
int num[3] = {0};

void myAlarm(){
	struct_ADC adc_data;
	adc_data = GetADC();
	num[0] = adc_data.Rop/100; num[1] = adc_data.Rop/10%10; num[2] = adc_data.Rop%10;
	if(adc_data.Rop < 20) SetBeep(1200,10);				//1.2KHz,100ms
	else if(adc_data.Rop > 100) SetBeep(2000,10);		//2KHz,100ms
}
void myLED(){
	Seg7Print(10,10,10,10,10,num[0],num[1],num[2]);
}

void main() 
{
	AdcInit(ADCexpEXT);
	DisplayerInit(); 
	BeepInit();
	LedPrint(0);
	SetDisplayerArea(5,7);
	Seg7Print(0, 0, 0, 0, 0, 0, 0);

	SetEventCallBack(enumEventSys100mS, myLED);
	SetEventCallBack(enumEventSys1S, myAlarm);
	
  	MySTC_Init();	    
	while(1)             	
	{ 
		MySTC_OS();    
	}	             
}                 