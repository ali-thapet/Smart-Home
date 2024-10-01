#include "StdTypes.h"
#include "MemMap.h"
#include "SPI_Int.h"

#define F_CPU 8000000
#include <util/delay.h>



void (*PF)(void)=Nullptr;


void SPI_Init(void)
{
  	/*Mode*/
	if(MODE==MASTER)
	{
		SET_BIT(SPCR,MSTR);
	}
	else
	{
		CLR_BIT(SPCR,MSTR);
	}
	
	/*Clock*/
	// 2 MHZ
	
	/*Enable SPI*/
	SET_BIT(SPCR,SPE);
	
}   


u8 SPI_SendReceive(u8*data)
{
	SPDR=*data;
	while(!GET_BIT(SPSR,SPIF));
	return SPDR;
}

u8 SPI_ReceiveSend_Timeout(u8*datain,u8*dataout,u16 Time)

{
	u16 c=0;
	SPDR=*datain;
	while((!GET_BIT(SPSR,SPIF))&&c<Time)
	{
		_delay_us(1);
		c++;
	}
	if (GET_BIT(SPSR,SPIF))
	{
		*dataout=SPDR;
		return 1;
	}
	else
	{
		return 0;
	}
}

void SPI_SendNoBlock(u8*data)
{
	SPDR=*data;
} 



u8 SPI_ReceivePerodic(u8*dataout)
{
	if (GET_BIT(SPSR,SPIF))
	{
		*dataout=SPDR;
		return 1;
	}
	return 0;
	
}



void SPI_InterruptEnable(void)
{
	SET_BIT(SPSR,SPIF);
	SET_BIT(SPCR,SPIE);
}
void SPI_InterruptDisable(void)
{
	CLR_BIT(SPSR,SPIF);
	CLR_BIT(SPCR,SPIE);
}



void SPI_SetCallBack(void (*LocalFptr)(void))
{
	PF=LocalFptr;
}


ISR (SPI_STC_vect)
{
	if(PF!=Nullptr)
	{
		PF();
	}
}
