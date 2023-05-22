#include "led.h"
#include <LPC21xx.H>

#define LED3_bm 1<<19
#define LED2_bm 1<<18
#define LED1_bm 1<<17
#define LED0_bm 1<<16

enum StepDirection {LEFT,RIGHT};

void LedInit()
{
	IO1DIR = IO1DIR | LED3_bm | LED2_bm | LED1_bm | LED0_bm;
	IO1SET = LED0_bm;
}

void LedOn(unsigned char ucLedIndeks)
{
	IO1CLR = LED3_bm | LED2_bm | LED1_bm | LED0_bm;
	
	switch(ucLedIndeks)
	{
		case 0:
			IO1SET = LED0_bm;
			break;
		case 1:
			IO1SET = LED1_bm;
			break;
		case 2:
			IO1SET = LED2_bm;
			break;
		case 3:
			IO1SET = LED3_bm;
			break;
	}
	
	return;
}



void LedStep( enum StepDirection eDirection )
{	
	static unsigned int uiLedState = 0;

	if (eDirection == LEFT )
	{
		uiLedState = uiLedState + 1;
	}else
	{
		uiLedState = uiLedState - 1;
	}
	
	uiLedState = uiLedState % 4;
	LedOn(uiLedState);
	return;
}

void LedStepLeft()
{
	LedStep(LEFT);
}

void LedStepRight()
{
	LedStep(RIGHT);
}
