



#ifndef MOTOR_INT_H_
#define MOTOR_INT_H_

#include "StdTypes.h"
#include "MOTOR_Cfg.h"


typedef enum{
	M1,
	M2,
	M3,
	M4
}MOTOR_t;



void MOTOR_Stop(MOTOR_t m);
void MOTOR_CW(MOTOR_t m);
void MOTOR_CCW(MOTOR_t m);



#endif /* MOTOR_INT_H_ */