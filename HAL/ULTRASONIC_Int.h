

#ifndef ULTRASONIC_INT_H_
#define ULTRASONIC_INT_H_

extern volatile u8 Flag,Undetected_Flag,F3;
extern u16 DistanceArr[4];
typedef enum{
	ULTR0=0,        //pinc0
	ULTR1,          //pinc1
	ULTR2,          //pinc2
	ULTR3,          //pinc3
	}ULTRASONIC_t ;

void ULTRASONIC_Init(void);
void ULTRASONIC_Runnable(void);
void ULTRASONIC_Periodic_Ceck(void);
u16 ULTRASONIC_GetDistance(ULTRASONIC_t U);
void ULTRASONIC_Func2(void);


#endif /* ULTRASONIC_INT_H_ */