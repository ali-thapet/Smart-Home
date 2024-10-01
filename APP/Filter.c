#include "StdTypes.h"


u16 FilterArr[10],F_Value,UNF_Value;
u8 static flag;
u8 Filter_INDEX;

//void Filter_Init(void);

/*
	if we got 10 samples of temperature in filter array
	so we put Filter_INDEX=0
*/

void Filter_Runnable(void)  // 200 us
{
	u8 i=0,x=0;
	F_Value=0;
	UNF_Value = SENSOR_ReadTemp();
	if(Filter_INDEX>=10)
	{
		Filter_INDEX=0;
	}
	FilterArr[Filter_INDEX]=UNF_Value;
	for (i=0;i<10;i++)
	{
		F_Value=F_Value+FilterArr[i];
	}
	if(flag==0)
	{
		x=Filter_INDEX+1;
		F_Value=F_Value/(x);
		if(Filter_INDEX==9)
		{
			flag=1;
		}
	}
	else if(flag==1)
	{
		F_Value=F_Value/(10);
	}
	Filter_INDEX++;
}

u16 Filter_GetFilteredValue(void)  // 2 us
{
	return F_Value;
}

u16 Filter_GetUnFilteredValue(void) // 2 us
{
	return UNF_Value;
}


