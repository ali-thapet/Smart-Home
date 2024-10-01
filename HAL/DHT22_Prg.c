
#include "StdTypes.h"
#include "DIO_Int.h"
#include "MemMap.h"
#include "DHT22_Int.h"
#include "TIMERS.h"


#define F_CPU 8000000
#include <util/delay.h>

static u16 t1,t2,ton,Humidity,Temp,Total_Sum;
u8 DHTArr[40],Arr_Index;
static u8 Signed_Flag,flag;

static void ICU_Func(void)
{
	
	if (flag==0)
	{
		t1=TIMER1_get();
		Timer1_InputCaptureEdge(FALLING);
		flag=1;
		
	}
	else if (flag==1)
	{
		t2=TIMER1_get();
		Timer1_InputCaptureEdge(RISING);
		flag=0;
	}
	ton=(t2-t1);
	if(ton<=(DHT_TimeLow_Bit+5))
	{
		DHTArr[Arr_Index]=0;
		Arr_Index++;
	}
	else if(ton<= (DHT_TimeHigh_Bit+5))
	{
		DHTArr[Arr_Index]=1;
		Arr_Index++;
	}
	if(Arr_Index==40)
	{
		Arr_Index=0;
	}

}

void DHT22_Init(void)
{
	Timer1_ICU_SetCallBack(ICU_Func);
	_delay_ms(DHT_Time_init);
}


 void DHT22_SendRequest(void)
 {
	 Timer1_ICU_InterruptDisable();
	 DIO_InitPin(DHT_Pin,OUTPUT);
	 DIO_WritePin(DHT_Pin,LOW);
	 _delay_ms(DHT_TimeLow_ms);
	 DIO_WritePin(DHT_Pin,HIGH);
	 _delay_us(DHT_TimeHight_us);
	 DIO_InitPin(DHT_Pin,INPULL);
	 _delay_us(DHT_WaitResponse_us);
 }


 void DHT22_Calc(void)
{
	u8 i;
	for(i=0;i<40;i++)
	{
		if(i<=15)
		{
			if(DHTArr[i]==1)
			{
				SET_BIT(Humidity,(15-i));
			}
			else
			{
				CLR_BIT(Humidity,(15-i));
			}
		}
		else if(i<=31)
		{
			if(DHTArr[i]==1)
			{
				SET_BIT(Temp,(31-i));
			}
			else
			{
				CLR_BIT(Temp,(31-i));
			}
			if(GET_BIT(Temp,15)==1)
			{
				CLR_BIT(Temp,15);
				Signed_Flag=1;
			}
		}
		else if(i<=39)
		{
			if(DHTArr[i]==1)
			{
				SET_BIT(Total_Sum,(39-i));
			}
			else
			{
				CLR_BIT(Total_Sum,(39-i));
			}
		}
		
	}
}


void DHT22_Runnable(void)
{
	TIMER1_set(0);    // TCNT1=0
	DHT22_SendRequest();
	Timer1_ICU_InterruptEnable();
	Timer1_InputCaptureEdge(RISING);
	DHT22_Calc();
}


s16 DHT22_GetTemp(void)
{
	if(Signed_Flag==1)
	{
		Temp*=-1;
		Signed_Flag=0;
	}
	return Temp;
}
u16 DHT22_GetHumidity(void)
{
	return Humidity;
}

