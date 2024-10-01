#include "StdTypes.h"
#include "MemMap.h"
#include "UART_Int.h"
#include "UART_Cfg.h"

static void(*UART_RX_Fptr)(void)=Nullptr;
static void(*UART_TX_Fptr)(void)=Nullptr;

void UART_Init(void)
{
	/*baud rate*/
	UBRRL=51;              // 9600 bits/s
	/*mode*/
	CLR_BIT(UCSRA,U2X);   // normal speed 
	/*frame*/
	// default 8 bits data , no parity , 1 stop bit
	// SET_BIT(UCSRC,UPM1);  // even parity
	
	/*enable*/
	SET_BIT(UCSRB,TXEN);
	SET_BIT(UCSRB,RXEN);
	
	
}


void UART_Send(u8 data)
{
	while(!GET_BIT(UCSRA,UDRE));
	UDR=data;
}
u8 UART_Receive(void)
{
	while(!GET_BIT(UCSRA,RXC));
	return UDR;
}
u8 UART_ReceivePeriodic(u8*pdata)
{
    if(GET_BIT(UCSRA,RXC))
	{
	   *pdata=UDR;
	   return 1;	
	}
	return 0;
}

void UART_SendNoBlock(u8 data)
{
	UDR=data;
}

u8 UART_ReceiveNoBlock(void)
{
	return UDR;
}


void UART_RX_InterruptEnable(void)
{
	SET_BIT(UCSRB,RXCIE);
}

void UART_RX_InterruptDisable(void)
{
	CLR_BIT(UCSRB,RXCIE);
}

void UART_TX_InterruptEnable(void)
{
	SET_BIT(UCSRB,TXCIE);
}

void UART_TX_InterruptDisable(void)
{
	CLR_BIT(UCSRB,TXCIE);
}

void UART_RX_SetCallBack(void (*LocalFptr)(void))
{
	UART_RX_Fptr = LocalFptr;
}

void UART_TX_SetCallBack(void (*LocalFptr)(void))
{
	UART_TX_Fptr = LocalFptr;
}

ISR(UART_RX_vect)
{
	if (UART_RX_Fptr!=Nullptr)
	{
		UART_RX_Fptr();
	}
}

ISR(UART_TX_vect)
{
	if (UART_TX_Fptr!=Nullptr)
	{
		UART_TX_Fptr();
	}
}