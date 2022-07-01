#include "STC15F2K60S2.H"
#include "sys.H"
#include "displayer.h"
#include "hall.H"

#define uchar unsigned char
#define uint unsigned int

code unsigned long SysClock = 11059200;

uchar led = 0x0f;

void myLED()
{
    LedPrint(led);
}

void myHall() {
    uchar he = GetHallAct();
    if (he == enumHallGetClose) {
        switch (led)
        {
        case 0xf0:
            led = 0xe1;
            break;
        case 0xe1:
            led = 0xc3;
            break;
        case 0xc3:
            led = 0x87;
            break;
        case 0x87:
            led = 0x0f;
            break;
        default:
            led <<= 1;
            break;
        }
    }
}


int main()
{
    HallInit();
    DisplayerInit();
	//SetDisplayerArea(0, 0);
    SetEventCallBack(enumEventSys100mS, myLED);
    SetEventCallBack(enumEventHall, myHall);

    MySTC_Init();
    while (1)
    {
        MySTC_OS();
    }
    
}