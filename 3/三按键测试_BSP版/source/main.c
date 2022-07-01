#include "STC15F2K60S2.H"        //必须。
#include "sys.H"                 //必须。
#include "beep.H" 
#include "music.H"

code unsigned long SysClock=11059200;         //必须。定义系统工作时钟频率(Hz)，用户必须修改成与实际工作频率（下载时选择的）一致



code unsigned char song[]={0x21,0x10,0x22,0x10,0x23,0x10,0x24,0x10,0x25,0x10};
void main() 
{   
	BeepInit();
	MusicPlayerInit();
	SetMusic(100,0xFA,&song,sizeof(song),enumMscNull);
	SetPlayerMode(enumModePlay);
	
  MySTC_Init();	    
	while(1)             	
		{ 
			MySTC_OS();    
		}	             
}                 