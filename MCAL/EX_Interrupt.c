
#include "StdTypes.h"
#include "MemMap.h"
#include "EX_Interrupt_Int.h"


/****************************Pointer to functions to be assigned to ISR*********************************/

static void (*INT0_Fptr) (void)=Nullptr;
static void (*INT1_Fptr) (void)=Nullptr;
static void (*INT2_Fptr) (void)=Nullptr;




/*******************************ISR********************************/

ISR(INT0_vect)
{
	if (INT0_Fptr!=Nullptr)
	{
		INT0_Fptr();
	}
	
}
ISR(INT1_vect,ISR_NOBLOCK)
{
	if (INT1_Fptr!=Nullptr) 	
	{
    	INT1_Fptr();
	}
}
ISR(INT2_vect)
{
	if (INT2_Fptr!=Nullptr)
	{
		INT2_Fptr();
	}
	
}






/************************************Call back functions*********************************************/
void EX_SetCallBack(EX_Interrupt_t_ Interrupt,void(*LocalPtr)(void))
{
	switch(Interrupt){
		case INTR0:
		INT0_Fptr=LocalPtr;
		break;
		case INTR1:
		INT1_Fptr=LocalPtr;
		break;
		case INTR2:
		INT2_Fptr=LocalPtr;
		break;
		
	}
}

/*****************************************************Control function*************************************************/

void EX_Interrupt_TriggerEdge_ByNUM(EX_Interrupt_NUM Number,EX_Interrupt_ISC_t ISC)   // Configure all External interrupts with same sense control
{                                                                                     // INT2 has only two trigger edge falling & raising
	switch(Number)
	{
		case ONE:     // Interrupt 0
		switch(ISC)
		{
			case LOWLV:
			CLR_BIT(MCUCR,ISC00);    // Low Level
			CLR_BIT(MCUCR,ISC01);
			break;
			case ANYLOGIC:
			SET_BIT(MCUCR,ISC00);    // Any Logic
			CLR_BIT(MCUCR,ISC01);
			break;
			case FALLEDG:
			CLR_BIT(MCUCR,ISC00);    // Falling Edge
			SET_BIT(MCUCR,ISC01);
			break;
			case RAISEDG:
			SET_BIT(MCUCR,ISC00);    // Raising Edge
			SET_BIT(MCUCR,ISC01);
			break;
		}
		break;
		case TWO:    // Interrupt 0 & Interrupt 1
		switch(ISC)
		{
			case LOWLV:
			CLR_BIT(MCUCR,ISC10);    // Low Level
			CLR_BIT(MCUCR,ISC11);
			CLR_BIT(MCUCR,ISC00);
			CLR_BIT(MCUCR,ISC01);
			break;
			case ANYLOGIC:
			SET_BIT(MCUCR,ISC10);    // Any Logic
			CLR_BIT(MCUCR,ISC11);
			SET_BIT(MCUCR,ISC00);
			CLR_BIT(MCUCR,ISC01);
			break;
			case FALLEDG:
			CLR_BIT(MCUCR,ISC10);    // Falling Edge
			SET_BIT(MCUCR,ISC11);
			CLR_BIT(MCUCR,ISC00);
			SET_BIT(MCUCR,ISC01);
			break;
			case RAISEDG:
			SET_BIT(MCUCR,ISC10);    // Raising Edge
			SET_BIT(MCUCR,ISC11);
			SET_BIT(MCUCR,ISC00);
			SET_BIT(MCUCR,ISC01);
			break;
		}
		break;
		case THREE:   // Interrupt 0 & Interrupt 1 & Interrupt 2
		switch(ISC)
		{
			case LOWLV:
			CLR_BIT(MCUCR,ISC10);    // Low Level
			CLR_BIT(MCUCR,ISC11);
			CLR_BIT(MCUCR,ISC00);   
			CLR_BIT(MCUCR,ISC01);
			break;
			case ANYLOGIC:
			SET_BIT(MCUCR,ISC10);    // Any Logic
			CLR_BIT(MCUCR,ISC11);
			SET_BIT(MCUCR,ISC00);
			CLR_BIT(MCUCR,ISC01);
			break;
			case FALLEDG:
			CLR_BIT(MCUCR,ISC10);    // Falling Edge
			SET_BIT(MCUCR,ISC11);
			CLR_BIT(MCUCR,ISC00);
			SET_BIT(MCUCR,ISC01);
			CLR_BIT(MCUCSR,ISC2);
			break;
			case RAISEDG:
			SET_BIT(MCUCR,ISC10);    // Raising Edge
			SET_BIT(MCUCR,ISC11);
			SET_BIT(MCUCR,ISC00);
			SET_BIT(MCUCR,ISC01);
			SET_BIT(MCUCSR,ISC2);  
			break;
		}
		break;
	}
}


void EX_Interrupt_TriggerEdge(EX_Interrupt_t_ T,EX_Interrupt_ISC_t ISC)      // Configure External interrupt individually
                                                                             // INT2 has only two trigger edge falling & raising
{
	switch(T)
	{
		case INTR0:   // Interrupt 0 
		switch(ISC)
		{
			case LOWLV:
			CLR_BIT(MCUCR,ISC00);    // Low Level
			CLR_BIT(MCUCR,ISC01);
			break;
			case ANYLOGIC:
			SET_BIT(MCUCR,ISC00);    // Any Logic
			CLR_BIT(MCUCR,ISC01);
			break;
			case FALLEDG:
			CLR_BIT(MCUCR,ISC00);    // Falling Edge
			SET_BIT(MCUCR,ISC01);
			break;
			case RAISEDG:
			SET_BIT(MCUCR,ISC00);    // Raising Edge
			SET_BIT(MCUCR,ISC01);
			break;
		}
		break;
		case INTR1:    // Interrupt 1
		switch(ISC)
		{
			case LOWLV:
			CLR_BIT(MCUCR,ISC10);    // Low Level
			CLR_BIT(MCUCR,ISC11);
			break;
			case ANYLOGIC:
			SET_BIT(MCUCR,ISC10);    // Any Logic
			CLR_BIT(MCUCR,ISC11);
			break;
			case FALLEDG:
			CLR_BIT(MCUCR,ISC10);    // Falling Edge
			SET_BIT(MCUCR,ISC11);
			break;
			case RAISEDG:
			SET_BIT(MCUCR,ISC10);    // Raising Edge
			SET_BIT(MCUCR,ISC11);
			break;
		}
		break;
		case INTR2:    // Interrupt 2
		switch(ISC)
		{
			case FALLEDG:
			CLR_BIT(MCUCSR,ISC2);      // Falling Edge
			break;
			case RAISEDG:
			SET_BIT(MCUCSR,ISC2);      // Raising Edge
			break;
		}
		break;
		
	}
}

/**********************************************Enable/Disable functions************************************************/

void EX_Interrupt_EN(EX_Interrupt_t_ IN)    // Enable External interrupt individually
{
	if(IN==INTR0)
	{
		SET_BIT(GICR,INT0);
	}
	if(IN==INTR1)
	{
		SET_BIT(GICR,INT1);
	}
	if(IN==INTR2)
	{
		SET_BIT(GICR,INT2);
	}
}
void EX_Interrupt_DIS(EX_Interrupt_t_ IN)   // Disable External interrupt individually
{ 
    if(IN==INTR0)
    {
	    CLR_BIT(GICR,INT0);
    }
    if(IN==INTR1)
    {
	    CLR_BIT(GICR,INT1);
    }
    if(IN==INTR2)
    {
	    CLR_BIT(GICR,INT2);
    }	
}

void EX_Interrupt_GlobalEnable(void) 
{
	sei();
}


void EX_Interrupt_GlobalDisable(void)  
{
   cli(); 
}