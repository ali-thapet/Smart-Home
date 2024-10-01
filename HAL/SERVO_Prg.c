#include "StdTypes.h"
#include "MemMap.h"
#include "TIMERS.h"


void Servo_Init(void)
{
	Timer1_Init( TIMER1_FASTPWM_ICR_TOP_MODE,TIMER1_SCALER_8);
	Timer1_OCRB1Mode(OCRB_NON_INVERTING);
	Timer1_OCRA1Mode(OCRA_NON_INVERTING);
	ICR1=19999;
}

void Servo1_SetAngle(u8 angle)
{
	OCR1A=(angle*(u32)1000)/180;
	OCR1A+=999;
}
void Servo2_SetAngle(u8 angle)
{
	OCR1B=(angle*(u32)1000)/180;
	OCR1B+=999;
}