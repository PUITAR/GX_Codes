#include "STC15F2K60S2.H"        //���롣
#include "sys.H"                 //���롣
#include "beep.H" 
#include "music.H"

code unsigned long SysClock=11059200;         //���롣����ϵͳ����ʱ��Ƶ��(Hz)���û������޸ĳ���ʵ�ʹ���Ƶ�ʣ�����ʱѡ��ģ�һ��



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