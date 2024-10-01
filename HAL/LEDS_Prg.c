

#include "StdTypes.h"
#include "LEDS_Int.h"
#include "DIO_Int.h"


/*Data=1,2,3 */

// pin 0-7
void Led_On(DIO_Pin_t pin)
{
	DIO_WritePin(pin,HIGH);
}
void Led_Off(DIO_Pin_t pin)
{
	DIO_WritePin(pin,LOW);
}
/*
void Leds_On(u8 Data)
{
	if(Data==1)
	{
		DIO_WritePin(PINC6,HIGH);
	}
	if(Data==2)
	{
		DIO_WritePin(PIND3,HIGH);
	}
	if(Data==3)
	{
		DIO_WritePin(PINC7,HIGH);
	}
	if(Data==4)
	{
		DIO_WritePin(PIND2,HIGH);
	}
	if(Data==0)
	{
		DIO_WritePin(PINC6,HIGH);
		DIO_WritePin(PIND3,HIGH);
	} 
}

/ *Data=1,2,3 * /
void Leds_Off(u8 Data)
{
	if(Data==1)
	{
		DIO_WritePin(PINC6,LOW);
	}
	if(Data==2)
	{
		DIO_WritePin(PINC7,LOW);
	}
	if(Data==3)
	{
		DIO_WritePin(PIND2,LOW);
	}
	if(Data==0)
	{
		DIO_WritePin(PINC6,LOW);
		DIO_WritePin(PINC7,LOW);
	}
}*/


