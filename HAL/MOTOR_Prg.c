
#include "StdTypes.h"
#include "MemMap.h"
#include "DIO_Int.h" 

#include "MOTOR_Cfg.h"
#include "MOTOR_Int.h"




void MOTOR_Stop(MOTOR_t m)
{
	  MOTOR_t i;
	  for(i=M1;i<Num_M;i++)
	  {
		  if(m==i)
		  {
			  DIO_WritePin(MOTOR_INArr[i][0],LOW); 
			  DIO_WritePin(MOTOR_INArr[i][1],LOW);
		  }
	  }
}



void MOTOR_CW(MOTOR_t m)
{
    MOTOR_t i;
	for(i=M1;i<Num_M;i++)
	{
	   if(m==i)
	   {    
		    DIO_WritePin(MOTOR_INArr[i][0],HIGH);
		    DIO_WritePin(MOTOR_INArr[i][1],LOW);
	   }	
	}	
}


void MOTOR_CCW(MOTOR_t m)
{
	 MOTOR_t i;
	 for(i=M1;i<Num_M;i++)
	 {
		 if(m==i)
		 {
			 DIO_WritePin(MOTOR_INArr[i][0],LOW);
			 DIO_WritePin(MOTOR_INArr[i][1],HIGH);
		 }
	 }
}

