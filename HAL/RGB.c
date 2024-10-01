#include "StdTypes.h"
#include "MemMap.h"
#include "RGB.h"
#include "TIMERS.h"
#include "DIO_Int.h"


//RGB COLORS: red,green,blue
u8 ColorsArr[7][3]={ {255,0,0},      //0- red
	                 {0,255,0},      //1- green
	                 {0,0,255},      //2- blue
			         {255,255,255},  //3- white
	                 {255,255,0},    //4- yellow
			         {0,255,255},    //5- aqua
			         {255,20,147}    //6- pink 
	             };


void RGB_SelectColor(Colors_Table C)
{
	static u8 flag=0;
	if(flag==0)
	{
		TIMER0_Init(TIMER0_FASTPWM_MODE,TIMER0_SCALER_8);
		Timer1_Init(TIMER1_FASTPWM_ICR_TOP_MODE,TIMER1_SCALER_8);
		TIMER0_OC0Mode(OC0_NON_INVERTING);
		Timer1_OCRA1Mode(OCRA_NON_INVERTING);
		Timer1_OCRB1Mode(OCRB_NON_INVERTING);
		ICR1=255;
		flag=1;
	}
    OCR0=ColorsArr[C][0];   // RED 
	OCR1A=ColorsArr[C][1];  // GREEN 
	OCR1B=ColorsArr[C][2];  // BLUE 
}

void RGB_GetColor_Values(u8 Red,u8 Green,u8 Blue)
{
	static u8 flag1=0;
	if(flag1==0)
	{
		TIMER0_Init(TIMER0_FASTPWM_MODE,TIMER0_SCALER_8);
		Timer1_Init(TIMER1_FASTPWM_ICR_TOP_MODE,TIMER1_SCALER_8);
		TIMER0_OC0Mode(OC0_NON_INVERTING);
		Timer1_OCRA1Mode(OCRA_NON_INVERTING);
		Timer1_OCRB1Mode(OCRB_NON_INVERTING);
		ICR1=255;
		flag1=1;
	}
	OCR0=Red;     
	OCR1A=Green; 
	OCR1B=Blue; 
}

