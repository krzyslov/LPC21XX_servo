#include "keyboard.h"
#include <LPC21xx.H>


#define ButtonS0_bm 1<<4
#define ButtonS1_bm 1<<6
#define ButtonS2_bm 1<<5
#define ButtonS3_bm 1<<7

void KeyboardInit()
{
  IO0DIR = (IO0DIR & ~( ButtonS0_bm | ButtonS1_bm | ButtonS2_bm | ButtonS3_bm) );
	return;
}

enum KeyboardState eKeyboardRead()
{
	
	unsigned char ucKbdState = (~IO0PIN & (ButtonS0_bm | ButtonS1_bm | ButtonS2_bm | ButtonS3_bm));
	
	if ( ucKbdState & ButtonS0_bm )
	{
		return BUTTON_0;
	}else if ( ucKbdState & ButtonS1_bm )
	{
		return BUTTON_1;
	}else if ( ucKbdState & ButtonS2_bm )
	{
		return BUTTON_2;
	}else if ( ucKbdState & ButtonS3_bm )
	{
		return BUTTON_3;
	}
	
	return RELASED;
}
