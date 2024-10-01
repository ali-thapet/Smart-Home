
#include "StdTypes.h"
#include "DIO_Int.h"
#include "MemMap.h"
#include "STEPPER_MOTOR.h"



/*8 steps each step is 45 degree*/
void Stepper_ByStep(Stepper_Steps S)
{
	switch(S)
    {
		case STEP1:
		DIO_WritePin(ORANGE_PIN,LOW);
		DIO_WritePin(YELLOW_PIN,HIGH);
		DIO_WritePin(BINK_PIN,HIGH);
		DIO_WritePin(BLUE_PIN,HIGH);	
		break;
		case STEP2:
		DIO_WritePin(ORANGE_PIN,LOW);
		DIO_WritePin(YELLOW_PIN,LOW);
		DIO_WritePin(BINK_PIN,HIGH);
		DIO_WritePin(BLUE_PIN,HIGH);
		break;
		case STEP3:
		DIO_WritePin(ORANGE_PIN,HIGH);
		DIO_WritePin(YELLOW_PIN,LOW);
		DIO_WritePin(BINK_PIN,HIGH);
		DIO_WritePin(BLUE_PIN,HIGH);
		break;
		case STEP4:
		DIO_WritePin(ORANGE_PIN,HIGH);
		DIO_WritePin(YELLOW_PIN,LOW);
		DIO_WritePin(BINK_PIN,LOW);
		DIO_WritePin(BLUE_PIN,HIGH);
		break;
		case STEP5:
		DIO_WritePin(ORANGE_PIN,HIGH);
		DIO_WritePin(YELLOW_PIN,HIGH);
		DIO_WritePin(BINK_PIN,LOW);
		DIO_WritePin(BLUE_PIN,HIGH);
		break;
		case STEP6:
		DIO_WritePin(ORANGE_PIN,HIGH);
		DIO_WritePin(YELLOW_PIN,HIGH);
		DIO_WritePin(BINK_PIN,LOW);
		DIO_WritePin(BLUE_PIN,LOW);
		break;
		case STEP7:
		DIO_WritePin(ORANGE_PIN,HIGH);
		DIO_WritePin(YELLOW_PIN,HIGH);
		DIO_WritePin(BINK_PIN,HIGH);
		DIO_WritePin(BLUE_PIN,LOW);
		break;
		case STEP8:
		DIO_WritePin(ORANGE_PIN,LOW);
		DIO_WritePin(YELLOW_PIN,HIGH);
		DIO_WritePin(BINK_PIN,HIGH);
		DIO_WritePin(BLUE_PIN,LOW);
		break;
	}
}

