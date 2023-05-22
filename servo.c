#include <LPC21xx.H>
#include "servo.h"
#include "led.h"
#include "keyboard.h"
#include "timer_interrupts.h"
#include "timer.h"
#define detector_bm 1<<10


struct Servo sServo;

void DetectorInit()
{
	IO0DIR &= ~detector_bm;
	return;
}

enum DetectorState eReadDetector()
{
	if ( detector_bm == (~IO0PIN & detector_bm)   )
	{
		return ACTIVE;
	}else
	{
		return INACTIVE;
	}
	
}

void Automat()
{
	
	DetectorInit();
	KeyboardInit();
	
	switch(sServo.eState)
	{
		case CALLIB:
			if ( ACTIVE == eReadDetector() )
			{
				sServo.uiCurrentPosition = 0;
				sServo.eState = OFFSET;
			}else
			{
				LedStepLeft();
			}
			break;
		case OFFSET:
			if ( 12 == sServo.uiCurrentPosition )
			{
				sServo.uiCurrentPosition = 0;
				sServo.uiDesiredPosition = 0;
				sServo.eState = IDLE;
			}else
			{
				LedStepRight();
				sServo.uiCurrentPosition += 1;
			}
			break;	
		case IDLE:
			if ( sServo.uiCurrentPosition != sServo.uiDesiredPosition )
			{
				sServo.eState = IN_PROGRESS;
			}
			break;
		case IN_PROGRESS:
			if ( sServo.uiCurrentPosition == sServo.uiDesiredPosition )
			{
				sServo.eState = IDLE;
			}else if ( sServo.uiCurrentPosition == -1 )
			{
				sServo.uiCurrentPosition = 47;
			}else if ( 24 >= ( sServo.uiDesiredPosition - sServo.uiCurrentPosition )  )
			{
				LedStepRight();
				sServo.uiCurrentPosition += 1;
			}else
			{
				LedStepLeft();
				sServo.uiCurrentPosition -= 1;
			}
		
			break;
		
	}
}

void ServoCallib()
{
	sServo.eState = CALLIB;
	while ( CALLIB == sServo.eState ) {}
	while ( OFFSET == sServo.eState ) {}
	return;
}

void ServoGoTo(unsigned int uiPosition)
{
	sServo.eState = IN_PROGRESS;
	sServo.uiDesiredPosition = uiPosition;
	while ( IN_PROGRESS == sServo.eState ) {}
	return;
}

void ServoInit(unsigned int uiServoFrequency)
{
	unsigned int uiPeriod = 1000000 / uiServoFrequency;
	//ServoCallib();
	sServo.eState = CALLIB;
	LedInit();
	Timer0Interrupts_Init( uiPeriod, &Automat); //20000
	return;
}
/*
void ServoOffset(unsigned int uiOffset)
{
	sServo.eState = CALLIB;
	ServoGoTo(uiOffset);
	return;
}

void ServoOffset2(unsigned int uiOffset)
{
	DetectorInit();
	KeyboardInit();
	sServo.eState = CALLIB;
	sServo.uiCurrentPosition = 0;
	sServo.uiDesiredPosition = uiOffset;
	while ( uiOffset != sServo.uiCurrentPosition ) {}
	return;
}
*/
