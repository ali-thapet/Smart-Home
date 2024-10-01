
#include "StdTypes.h"
#include "LCD_Int.h"
#include "ADC_Int.h"
#include "Sensors_Int.h"
#include "UART_Int.h"
#include "RGB.h"
#include "LEDS_Int.h"
#include "String.h"
#include "MOTOR_Int.h"
#include "SERVO_Int.h"
#include "UART_Service.h"
#include "SMART_HOUSE.h"

volatile u8 AIR_OFF_Flag;

Task_Type Arr[8]={  {"DOOR",Open_Door},
	                {"GARAGE",Open_Garage},
                    {"RMON",Room_ON},
				    {"RMOFF",Room_OFF},
				    {"GON",Garage_ON},
				    {"GOFF",Garage_OFF},	   	   
                    {"AIRON",AIR_CON_ON},
					{"AIROFF",AIR_CON_OFF}	
	                                         };


void AIR_CON_ON(u8 data)
{
	AIR_OFF_Flag=0;
}

void AIR_CON_OFF(u8 data)
{
	AIR_OFF_Flag=1;
}


void Air_ConditionerOn(u8 Temp)
{
	if(Temp<20)
	{
		MOTOR_Stop(M4);
	}
	else if (Temp>=20 && Temp<30)
	{
		PWM_Duty_TIMER0(70);  // 70% duty cycle
		MOTOR_CW(M4);
	}
	else if (Temp>=30 && Temp<40)
	{
		PWM_Duty_TIMER0(80);  // 80% duty cycle
		MOTOR_CW(M4);
	}
	else if (Temp>=40 && Temp<50)
	{
		PWM_Duty_TIMER0(100);  // 100% duty cycle
		MOTOR_CW(M4);
	}
	else if (Temp>=50 )
	{
		MOTOR_Stop(M4);
	}
	
	
}



void UART_ReceiveTaskAndData(u8*str,u8*Data)
{
	u8 i=0;
	*Data=0;
	for(i=0;str[i];i++)
	{
		if(str[i]>='0'&& str[i]<='9')
		{
			*Data=((*Data)*10)+(str[i]-'0');
			str[i]=0;
		}
	}
}


u8 UART_Find_Task(u8*STR,u8 Data)
{
	u8 i,x;
	for(i=0;i<TASKS_NUM;i++)
	{
		x=string_compare((Arr[i].str),STR);
		if(x==1)
		{
			Arr[i].PF(Data);
			return i;
		}
		
	}
	return WRONG_DATA;
	
}




void Room_ON (u8 Room_Number)
{
	if(Room_Number==1)
	{
		Led_On(ROOM1_LED_PIN);
	}
	if(Room_Number==2)
	{
		Led_On(ROOM2_LED_PIN);
	}
}
void Room_OFF (u8 Room_Number)
{
	if(Room_Number==1)
	{
		Led_Off(ROOM1_LED_PIN);
	}
	if(Room_Number==2)
	{
		Led_Off(ROOM2_LED_PIN);
	}
}

void Garage_ON (u8 data)  // useless data
{
	Led_On(GARAGE_LED_PIN);
}
void Garage_OFF (u8 data)  // useless data 
{
	Led_Off(GARAGE_LED_PIN);
}

void Open_Door(u8 data)
{ 
	Servo1_SetAngle(data);
	if(data>=0)
	{    
		Led_On(DOOR_LED_PIN);
	}
	if(data==0)
	{
		Led_Off(DOOR_LED_PIN);
	}
	
}

void Open_Garage(u8 data)
{
	Servo2_SetAngle(data);
	if(data>=0)
	{
		Led_On(GARAGE_LED_PIN);
	}
	if(data==0)
	{
		Led_Off(GARAGE_LED_PIN);
	}
}

u8 Compare_pass(u8*Pass1,u8*Pass2)
{
	u8 x;
	for(x=0;x<PASS_Length;x++)
	{
		if(Pass1[x]!=Pass2[x])
		{
			return 0;
		}
	}
	return 1;
}
