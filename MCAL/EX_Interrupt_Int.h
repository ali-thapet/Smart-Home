

#ifndef _EX_INTERRUPT_H_
#define _EX_INTERRUPT_H_



/*
#define INT0PIN    PIND2
#define INT1PIN    PIND3
#define INT2PIN    PINB2  */



	
typedef enum{
	LOWLV=0,    // Interrupt at Zero
	ANYLOGIC,   // Interrupt from zero to one and vice versa 
	FALLEDG,    // Interrupt at Falling Edge
	RAISEDG,    // Interrupt at Raising Edge
	}EX_Interrupt_ISC_t;

typedef enum{
	INTR0,     // INT0
	INTR1,     // INT1
	INTR2      // INT2
	}EX_Interrupt_t_;

typedef enum{
	ONE,      // INT0
 	TWO,      // INT0 & INT1
	THREE     // INT0 & INT1 & INT2
    }EX_Interrupt_NUM;
 
void EX_Interrupt_TriggerEdge_ByNUM(EX_Interrupt_NUM N,EX_Interrupt_ISC_t ISC);     // Configure all External interrupts with same sense control
void EX_Interrupt_TriggerEdge(EX_Interrupt_t_ T,EX_Interrupt_ISC_t ISC);            // Configure External interrupt individually
void EX_Interrupt_EN(EX_Interrupt_t_ IN);                                           // Enable External interrupt
void EX_Interrupt_DIS(EX_Interrupt_t_ IN);                                          // Disable External interrupt
void EX_Interrupt_GlobalEnable(void);                                               // Global interrupt flag enable
void EX_Interrupt_GlobalDisable(void);                                              // Global interrupt flag disable

void EX_SetCallBack(EX_Interrupt_t_ Interrupt,void(*LocalPtr)(void));

#endif /* INTERRUPT_H_ */