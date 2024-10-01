
 


#ifndef UART_SERVICE_H_
#define UART_SERVICE_H_

#include "StdTypes.h"

#define STACKSIZE 20


#define WRONG_DATA  -1
#define Right_DATA  1

#define LITTLE 1
#define BIG 0



extern u8 Finish_Flag;

void UART_Service_Init(void);

void UART_SendString(c8*str);
void UART_ReceiveString(c8*str);
void UART_SendStringAsynch(u8*str);
void UART_ReceiveStringAsynch(u8*str);
void UART_SendNumber(u32 Num);
void UART_ReceiveNumber(u32 Num);

void UART_SendStringCheckSum(c8*str);
u8 UART_ReceiveStringCheckSum(c8*str);

void UART_PushData(u8*str);
void UART_PopData(void);




u8 Endian_check(void);
u32 Endian_Convert(u32 Num);
u16 Endian_Convert16(u16 Num);

#endif /* UART_SERVICE_H_ */