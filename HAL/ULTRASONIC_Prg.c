
#include "StdTypes.h"
#include "TIMERS.h"
#include "ULTRASONIC_Int.h"
#include "ULTRASONIC_Cfg.h"
#include "DIO_Int.h"

#define F_CPU 8000000
#include <util/delay.h>

volatile u16 t1,t2;
u16 DistanceArr[4];
u16 BufferArr[4];   
volatile u8 Flag,Undetected_Flag,F2,F3;


void ULTRASONIC_Init(void)
{
	Timer1_ICU_SetCallBack(ULTRASONIC_Func2);
}

void ULTRASONIC_Runnable(void)
{ 
	static u8 i=PINC0;
		
	
	/* Trigger for 10us */
	if(F2==0)
	{
		TCNT1=0;
		Timer1_InputCaptureEdge(RISING);
		Timer1_ICU_InterruptEnable();
		Flag=0;
		
		DIO_WritePin(i,HIGH);
		_delay_us(10);
		DIO_WritePin(i,LOW);
		F2=1;
		i++;
		if(i==PINC4)
		{
			i=PINC0;
		}
	}
	

}
void ULTRASONIC_Periodic_Ceck(void)
{
	static u8 x=0,c2=0;
	u8 i=0;
	u16 D,TimeOut_C=0;
	
	while(Flag<2 && TimeOut_C<TIMEOUT)
	{
		TimeOut_C++;
	}
	if(Flag==2)
	{
		D=(t2-t1)/58;
		BufferArr[x]=D;
		F2=0;
		F3=1;
		x++;
		TimeOut_C=0;
		c2++ ;
		if(x==ULTRASONIC_NUM)
		{
			x=0;
			c2=0;
			for(i=0;i<ULTRASONIC_NUM;i++)
			{
				DistanceArr[i]=BufferArr[i];
			}
		}
		
	}
	else
	{
		Undetected_Flag=1;
	}

}


u16 ULTRASONIC_GetDistance(ULTRASONIC_t U)
{
	return DistanceArr[U];		
}


void ULTRASONIC_Func2(void)
{
	if (Flag==0)
	{
		t1=ICR1;
		Timer1_InputCaptureEdge(FALLING);
		Flag=1;
	}
	else if (Flag==1)
	{
		t2=ICR1;
		Timer1_ICU_InterruptDisable();
		Flag=2;
	}
}