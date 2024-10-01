
#include "StdTypes.h"
#include "MemMap.h"
#include "DIO_Int.h"
#include "ADC_Int.h"
#include "TIMERS.h"
#include "EEPROM_Int.h"
#include "WDT.h"
#include "UART_Int.h"
#include "MOTOR_Int.h"
#include "LCD_Int.h"
#include "KEYPAD_Int.h"
#include "Sensors_Int.h"
#include "SERVO_Int.h"
#include "LEDS_Int.h"
#include "UART_Service.h"
#include "Timers_Service.h"
#include "Filter_Int.h"
#include "SMART_HOUSE.h"



#define F_CPU 8000000
#include <util/delay.h>





int main(void)
{
    
    DIO_Init();
	ADC_Init();
	UART_Init();
	KEYPAD_Init();
    LCD_Init();
	Servo_Init();
	TIMER0_Init(TIMER0_FASTPWM_MODE,TIMER0_SCALER_8);
	TIMER0_OC0Mode(OC0_NON_INVERTING);
    UART_Service_Init();
	sei();
    u8 key=NO_KEY, PWS_Change=0,r=0,Correct_Pass=0,index=0;
    u8 pass[PASS_Length];
    u8 TempPass[PASS_Length];
    u16 address=0,WrongPass_Counter=0;
    u8 First_Time,FirstTime_address=5,UnFinished_Pass_address=6;
	u8 NormalFlag=0,VFlag=0,FireFlag=0,PassFlag=1,HeatFlag=0,UnFinished_Pass,LockFlag=0,OneTime_Flag=0,i=0,j=0;
	u16 F_temp=0,UnF_temp;
	u32 Gas;
    u16 str[20]={0};
    u8 data;
	First_Time=EEPROM_Read(FirstTime_address);
	
	/* check if we still use default password or not */
	
	if(First_Time!=0)
	{
		/* Password address from 0 -> 4 */
		for(index=0;index<PASS_Length;index++)
		{
			pass[index]=0;
			EEPROM_Write(pass[index],address);
			address++;
		}
		First_Time=0;
		EEPROM_Write(First_Time,FirstTime_address);
		UnFinished_Pass=0;
		EEPROM_Write(UnFinished_Pass,UnFinished_Pass_address);
	 }
	 else if (First_Time==0)
	 {
		 /* Password address from 0 -> 4 */
		 for(index=0;index<PASS_Length;index++)
		 {
			 pass[index]=EEPROM_Read(address);
			 address++;
		 }
		 UnFinished_Pass=EEPROM_Read(UnFinished_Pass_address);
	 }
	 
	 index=0;
    while(1)
    {
	   
	    while(NormalFlag==0)
	    {
			/*
			Check if the Microcontroller power was disconnected while changing the password 
			if it true so UnFinished_Pass=1
			if it false so UnFinished_Pass=0
			*/
			WDT_Reset(timeout_2100ms);
			if(UnFinished_Pass==1)    
			{
				LCD_SetCursor(0,0);
				LCD_WriteString("Your last pass didn't save");
				_delay_ms(800);     // to can see the message
				for(index=0;index<PASS_Length;index++)
				{
					pass[index]=0;
					EEPROM_Write(pass[index],address);
					address++;
				}
				UnFinished_Pass=0;
				EEPROM_Write(UnFinished_Pass,UnFinished_Pass_address);
			}
			
			
			key=KEYPAD_GetKey();
		    Filter_Runnable();
			UART_ReceiveStringAsynch(str);
		    if(VFlag==0)    
		    {
			    LCD_Clear();
			    LCD_SetCursor(0,0);
			    LCD_WriteString("     NORMAL ");
			    VFlag=1;
		    }
			if(OneTime_Flag==0)
			{
				LCD_SetCursor(1,0);
				LCD_WriteString("T:");
				LCD_SetCursor(1,6);
				LCD_WriteString("C");
				OneTime_Flag=1;
			}
			if(AIR_OFF_Flag==0)
			{
				Air_ConditionerOn(F_temp);
			}
			else if(AIR_OFF_Flag==1)
			{
				MOTOR_Stop(M4);
			}
		    F_temp=Filter_GetFilteredValue();
			F_temp=F_temp/10;
			LCD_SetCursor(1,2);
		    LCD_WriteNumber(F_temp);
		    LCD_WriteString(" ");
		
		    if((F_temp)>=50)
		    { 
			    NormalFlag=1;
				HeatFlag=1;
			    VFlag=0;
				OneTime_Flag=0;
			    LCD_Clear();
			    break;
		    }
			 
			 if(Finish_Flag==1)
			 {
				 UART_ReceiveTaskAndData(str,&data);
				 UART_Find_Task(str,data);
				 Finish_Flag=0;
				 
			 }
			 if(key=='c')     // Change password
			 {
				 PWS_Change=1;
				 index=0;
				 LCD_Clear();
				 LCD_SetCursor(0,0);
				 LCD_WriteString("Enter old Pass");
				 while(PWS_Change==1)
				 {
					 WDT_Reset(timeout_2100ms);
					 key=KEYPAD_GetKey();
					 if(key>='0' && key<='9')
					 {
						 if(Correct_Pass==0)
						 {
							 
							 TempPass[index]=key-'0';
							 LCD_SetCursor(1,index);
							 LCD_WriteNumber(TempPass[index]);
							 _delay_ms(20);
							 LCD_SetCursor(1,index);
							 LCD_WriteChar('*');
							 index++;
							 if(index==PASS_Length)
							 {
								 index=0;
								 r=Compare_pass(TempPass,pass);
								 if(r==1)
								 {
									 Correct_Pass=1;
									 index=0;
									 key=NO_KEY;
									 LCD_Clear();
									 LCD_SetCursor(0,0);
									 LCD_WriteString("Enter new Pass");
									 UnFinished_Pass=1;
									 EEPROM_Write(UnFinished_Pass,UnFinished_Pass_address);
									 
								 }
								 else
								 {
									 LCD_Clear();
									 LCD_SetCursor(0,0);
									 LCD_WriteString("wrong pass");
									 WrongPass_Counter++;
									 if(WrongPass_Counter==3)
									 {
										 LCD_Clear();
										 LCD_SetCursor(0,0);
										 LCD_WriteString("locked for 30 seconds");
										 LockFlag=1;
										 _delay_ms(30000);   // (30 seconds)*1000
										 LCD_Clear();
									     LockFlag=0;
										 VFlag=0;
										 PWS_Change=0;
										 WrongPass_Counter=0;
										 OneTime_Flag=0;
										 
									 }
									 
									 
								 }
							 }
						 }
						 
						else if(Correct_Pass==1)
						 {
							
							pass[index]=key-'0';
							LCD_SetCursor(1,index);
							LCD_WriteNumber(pass[index]);
							_delay_ms(20);
							LCD_SetCursor(1,index);
							LCD_WriteChar('*');
							index++;
							if(index==PASS_Length)
							{
								index=0;
								LCD_Clear();
								Correct_Pass=0;
								PWS_Change=0;
								address=0;
								for(index=0;index<PASS_Length;index++)        	/* Password address from 0 -> 4 */
								{
									EEPROM_Write(pass[index],address);
									address++;
								}
								UnFinished_Pass=0;
								EEPROM_Write(UnFinished_Pass,UnFinished_Pass_address);
								LCD_Clear();
								LCD_SetCursor(0,0);
								LCD_WriteString("DONE");
								_delay_ms(300);
								VFlag=0;
								OneTime_Flag=0;
							}
							 
							 
						 }
						 
						 
					 }
					 
					 
				 }
				 
			 }
		    
	    }
		while(HeatFlag==1)
		{
			WDT_Reset(timeout_2100ms);
			UART_ReceiveStringAsynch(str);
			Filter_Runnable();
			if(VFlag==0)
			{
				LCD_Clear();
				LCD_SetCursor(0,0);
				LCD_WriteString("     HEAT ");
				VFlag=1;
			}
			if(OneTime_Flag==0)
			{
				DIO_WritePin(GRN_LED,HIGH);    // Heat led is on
				LCD_SetCursor(1,0);
				LCD_WriteString("T:");
				LCD_SetCursor(1,6);
				LCD_WriteString("C");
				LCD_SetCursor(1,10);
				LCD_WriteString("S:");
				LCD_SetCursor(1,15);
				LCD_WriteChar('%');
				OneTime_Flag=1;
			}
			if(AIR_OFF_Flag==0)
			{
				Air_ConditionerOn(F_temp);
			}
			else if(AIR_OFF_Flag==1)
			{
				MOTOR_Stop(M4);
			}
			F_temp=Filter_GetFilteredValue();
			F_temp=F_temp/10;
			LCD_SetCursor(1,2);
			LCD_WriteNumber(F_temp);
			LCD_WriteString(" ");
			Gas=SENSOR_ReadGas();
			Gas=(Gas*100)/4995;
			LCD_SetCursor(1,12);
			LCD_WriteNumber(Gas);
			LCD_WriteString(" ");
			if(Gas>=50)
			{
				FireFlag=1;
				HeatFlag=0;
				OneTime_Flag=0;
				VFlag=0;
				DIO_WritePin(GRN_LED,LOW);
				i=0;
				LCD_Clear();
				break;
			}
			if((F_temp)<=40)
			{
				VFlag=0;
				NormalFlag=0;
				OneTime_Flag=0;
				DIO_WritePin(GRN_LED,LOW);
				LCD_Clear();
				break;
			}
			if(Finish_Flag==1)
			{
				UART_ReceiveTaskAndData(str,&data);
				UART_Find_Task(str,data);
				Finish_Flag=0;
				
			} 
			 
		}
		while(FireFlag==1)
		{
			WDT_Reset(timeout_2100ms);
			key=KEYPAD_GetKey();
			//UART_ReceiveStringAsynch(str);
			Filter_Runnable();
			if(VFlag==0)
			{
				LCD_Clear();
				LCD_SetCursor(0,0);
				LCD_WriteString("FIRE ");
				VFlag=1;
				Led_Off(ROOM1_LED_PIN);
				Led_Off(ROOM2_LED_PIN);
				
			}
			if(OneTime_Flag==0)
			{
				MOTOR_CW(M3);               // water pump motor
				DIO_WritePin(BUZ,HIGH);     // Fire alarm
				DIO_WritePin(RED_LED,HIGH); // Fire led is on
				LCD_SetCursor(1,0);
				LCD_WriteString("T:");
				LCD_SetCursor(1,6);
				LCD_WriteString("C");
				LCD_SetCursor(1,10);
				LCD_WriteString("S:");
				LCD_SetCursor(1,15);
				LCD_WriteChar('%');
				OneTime_Flag=1;
			}
			F_temp=Filter_GetFilteredValue();
			F_temp=F_temp/10;
		    LCD_SetCursor(1,2);
			LCD_WriteNumber(F_temp);
			LCD_WriteString(" ");
			Gas=SENSOR_ReadGas();
			Gas=(Gas*100)/4995;
			LCD_SetCursor(1,12);
			LCD_WriteNumber(Gas);
			LCD_WriteString(" ");
			if(key!=NO_KEY)
			{
				if(key>='0'&&key<='9')
				{
					TempPass[i]=key-'0';
					i++;
					if(i==5)
					{
						r=Compare_pass(TempPass,pass);
						if(r==1)
						{
							Correct_Pass=1;
						}
						else
						{
							LCD_Clear();
							LCD_SetCursor(0,0);
							LCD_WriteString("wrong pass");
							WrongPass_Counter++;
							if(WrongPass_Counter==3)
							{
								LCD_Clear();
								LCD_SetCursor(0,0);
								LCD_WriteString("locked for 30 seconds");
								LockFlag=1;
								_delay_ms(30000);   // (30 seconds)*1000
								LCD_Clear();
								LockFlag=0;
								VFlag=0;
								OneTime_Flag=0;
								PWS_Change=0;
						    }
						}
						i=0;
					}
				}
				if(key=='=')
				{
					if(Correct_Pass==1)
					{
						PassFlag=0;
						Correct_Pass=0;
					}
					
				}
				if(PassFlag==0)
				{
					FireFlag=0;
					NormalFlag=0;
					OneTime_Flag=0;
					VFlag=0;
					DIO_WritePin(BUZ,LOW);
					DIO_WritePin(RED_LED,LOW);
					MOTOR_Stop(M3);
					LCD_Clear();
					break;
				}
				
			}
			if(Finish_Flag==1)
			{
				UART_ReceiveTaskAndData(str,&data);
				UART_Find_Task(str,data);
				Finish_Flag=0;
				
			}
			
			
			
		}
	    
	    
    }
}

