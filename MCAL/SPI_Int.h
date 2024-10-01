


#ifndef SPI_INT_H_
#define SPI_INT_H_

#include "StdTypes.h"

#define  MASTER  1
#define  SLAVE   0
#define   MODE  SLAVE



void SPI_Init(void);
u8 SPI_SendReceive(u8* data);
void SPI_SendNoBlock(u8* data);
u8 SPI_ReceivePerodic(u8*dataout);

void SPI_InterruptEnable(void);
void SPI_InterruptDisable(void);
void SPI_SetCallBack(void (*LocalFptr)(void));

#endif /* SPI_INT_H_ */