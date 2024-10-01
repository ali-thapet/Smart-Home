
#include "MOTOR_Cfg.h"
#include "DIO_Int.h"

 /* M1_IN1  PINA0
    M1_IN2  PINA1

    M2_IN1  PINA2
    M2_IN2  PINA3

    M3_IN1  PINB0
    M3_IN2  PINB1

    M4_IN1  PIND6
    M4_IN2  PIND7 */
                                       
const u8 MOTOR_INArr[Num_M][INNum_M]={{PINA0,PINA1},{PINA2,PINA3},{PINB0,PINB1},{PIND6,PIND7}};