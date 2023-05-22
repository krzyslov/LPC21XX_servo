#include <LPC21xx.H>
#include "timer.h"

#define mCOUNTER_ENABLE 0x00000001
#define mCOUNTER_RESET  0x00000002
#define mINTERRUPT_ON_MR0 0x00000001
#define mRESET_ON_MR0  0x00000002
#define mMR0_INTERRUPT 0x0
#define mIR0_RESET 0x00000001

void InitTimer0()
{
	T0TCR |= mCOUNTER_ENABLE; //Counter Enable
	return;
}

void WaitOnTimer0(unsigned int uiTime)
{
	T0TCR &= mCOUNTER_RESET | mCOUNTER_ENABLE; //Counter Reset
	T0TC = 0;
	while ( T0TC != (uiTime * 15) ) { }
	//T0MCR = 0x0;
	return;
}

void InitTimer0Match0(unsigned int iDelayTime)
{
	T0MR0 = 15 * iDelayTime; //
	T0MCR = mINTERRUPT_ON_MR0 | mRESET_ON_MR0; 
	T0TCR &= mCOUNTER_RESET; //Counter Reset
	InitTimer0();
	return;
}

void WaitOnTimer0Match0()
{
	while ( T0IR == mMR0_INTERRUPT ) {}
	T0IR = mIR0_RESET;
	return;
}


