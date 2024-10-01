


#ifndef STEPPER_MOTOR_H_
#define STEPPER_MOTOR_H_

#include "StdTypes.h"

typedef enum{
	STEP1=1,    
	STEP2,      
	STEP3,       
	STEP4,
	STEP5,
	STEP6,
	STEP7,
	STEP8        
	}Stepper_Steps;

#define ORANGE_PIN  PINC4
#define YELLOW_PIN  PINC5
#define BINK_PIN    PINC6
#define BLUE_PIN    PINC7


void Stepper_ByStep(Stepper_Steps S);
void Stepper_Angle(u16 A);
#endif /* STEPPER_MOTOR_H_ */