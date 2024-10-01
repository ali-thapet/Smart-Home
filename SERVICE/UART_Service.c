#include "StdTypes.h"
#include "MemMap.h"
#include "UART_Int.h"
#include "String.h"
#include "UART_Service.h"
#include "RGB.h"
#include "SERVO_Int.h"
#include "LCD_Int.h"
#include "LEDS_Int.h"



/******SEND VARIABLES (BY QEUE)******/
static u8 *Qeue_Arr[STACKSIZE];
static u8 SP;
static u8 Pop_index;
/******RECEIVE VARIABLES (BY STACK)******/
static u8 data[30];
static c8 STACK_Arr[STACKSIZE][30];
static u8 Flag,Full_Flag,Empty_Flag,StrCompleteFlag;
static u8 Stack_index;
static u8 i=0;
u8 Finish_Flag;










static void TX_Func(void);
static void RX_Func(void);


void UART_Service_Init(void)
{
    UART_TX_SetCallBack(TX_Func);
    UART_RX_SetCallBack(RX_Func);
    UART_TX_InterruptEnable();
    UART_RX_InterruptEnable();
}







 void UART_SendString(c8*str)
 {	
	 u8 i;
	 for(i=0;str[i];i++)
	 {
		UART_Send(str[i]); 
	 }
 }







void UART_PushData(u8*str)
{
 	 u8 x;
	 if(Stack_index==STACKSIZE)
	 {
		 LCD_Clear();
		 LCD_SetCursor(1,0);
		 LCD_WriteString("STACK FULL");
		 Full_Flag=1;
	 }
	 else
	 {
		for(x=0;str[x];x++)
		{
			STACK_Arr[Stack_index][x]=str[x];
		}
		STACK_Arr[Stack_index][x]=0;
		Stack_index++; 
	 }
	Empty_Flag=0;
	
}


void UART_PopData(void)
{

	if(Stack_index==0)
	{
		LCD_Clear();
		LCD_SetCursor(1,0);
		LCD_WriteString("STACK IS EMPTY");
		Empty_Flag=1;
	}
	else
	{
		Stack_index--;
	    LCD_Clear();
		LCD_SetCursor(0,0);
		LCD_WriteString(STACK_Arr[Stack_index]);
		Remove_string(STACK_Arr[Stack_index]);
		Full_Flag=0;
	}
	
	
 
}


void UART_SendStringAsynch(u8*str)
{
	
	Qeue_Arr[SP]=str;
	if(SP==0)
	{
		UART_SendNoBlock(Qeue_Arr[SP][0]);
	}
	SP++;
	
	if(SP==STACKSIZE)
	{
		SP=0;
	}
	
}



 static void TX_Func(void)
 {
	
	static u8 x=1,Sec_ElementFlag=0;
	if(Sec_ElementFlag==1)
	{
		x++;
		Sec_ElementFlag=0;
	}
	if (Qeue_Arr[Pop_index][x]!=0)
	{
		UART_SendNoBlock(Qeue_Arr[Pop_index][x]);
		x++;
	}
	else
	{
		if(Pop_index<(SP-1))
		{
			Pop_index++;
			x=0;
			UART_SendNoBlock(Qeue_Arr[Pop_index][x]);
			Sec_ElementFlag=1;
		}
		else
		{
			x=1;
			Pop_index=0;
			SP=0;
		}
	}
	
}

static void RX_Func(void)
{
	
	data[i]=UART_ReceiveNoBlock();
	if(data[i]==0xd)
	{
		StrCompleteFlag=1;
	}
	else
	{
		i++;
		Flag++;
	}
	
}



 void UART_ReceiveStringAsynch(u8*str)
 {
	 u8 j=0;
	 if(StrCompleteFlag==1)
	 {
		 for(j=0;j<i;j++)
		 {
			 str[j]=data[j];
		 }
		 str[j]=0;
		 UART_PushData(str);
		 i=0;
		 StrCompleteFlag=0; 
		 Finish_Flag=1;
	 }
	
 }



 
void UART_ReceiveString(c8*str)
{
	u8 i=0;
	str[i]=UART_Receive();
	for(;str[i]!=0xd;)
	{
		i++;
		str[i]=UART_Receive();
	}
	str[i]=0;
}

void UART_SendNumber(u32 Num)
{
// 	u8 *p=&Num;
// 	UART_Send(p[0]);
// 	UART_Send(p[1]);
// 	UART_Send(p[2]);
// 	UART_Send(p[3]);
	
	UART_Send((u8)Num);
	UART_Send((u8)(Num>>8));
	UART_Send((u8)(Num>>16));
	UART_Send((u8)(Num>>24)) ; 
}

void UART_ReceiveNumber(u32 Num)
{
// 	u8 *p=&Num;
// 	p[0]=UART_Receive();
// 	p[1]=UART_Receive();
// 	p[2]=UART_Receive();
// 	p[3]=UART_Receive();
	
	u8 b0,b1,b2,b3;
	b0=UART_Receive();
	b1=UART_Receive();
	b2=UART_Receive();
	b3=UART_Receive(); 
	Num=(u32)b0|((u32)b1<<8)|((u32)b2<<16)|((u32)b3<<24);
	
}





void UART_SendStringCheckSum(c8*str)
{
	u8 i=0,databits=0;
	u16 sum=0;
	databits=string_length(str);
	UART_Send(databits);
	for(i=0;str[i];i++)
	{
		sum=sum+(str[i]);
		UART_Send(str[i]);
		
	}
	UART_Send((u8)sum); 
	UART_Send ((u8)(sum>>8));
	
}
u8 UART_ReceiveStringCheckSum(c8*str)
{
	u8 i=0,data_length=0,b0,b1;
	u16 sum=0,data_Sum=0;
	data_length=UART_Receive();
    for(i=0;i<data_length;i++)
	{
		str[i]=UART_Receive();
		sum+=str[i];
	}
	str[i]=0;
	b0=UART_Receive();
	b1=UART_Receive();
	data_Sum=(u16)b0|((u16)b1<<8);
	if(sum==data_Sum)
	{
		return Right_DATA;
	}
	else
	{
		return WRONG_DATA;
	}
	
}

u8 Endian_check(void)
{
	u32 Num=1;
	u8*p=&Num;
	if(p[0]==1)
	{
		return LITTLE;
	}
	else
	{
		return BIG;
	}
}

u32 Endian_Convert(u32 Num)
{
	Num=(Num>>24)|(Num<<24)|((Num<<8)&0x00ff0000)|((Num>>8)&0x0000ff00);
	return Num;
}
u16 Endian_Convert16(u16 Num)
{
	Num=(Num>>8)|(Num<<8);
	return Num;
} 
