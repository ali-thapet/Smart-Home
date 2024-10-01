


#ifndef DHT22_INT_H_
#define DHT22_INT_H_

#include "StdTypes.h"

#define   DHT_Time_init                2000
#define   DHT_TimeLow_ms               18
#define   DHT_TimeHight_us             40
#define   DHT_WaitResponse_us          80
#define   DHT_Pin                      PIND6

#define   DHT_TimeLow_Bit              25
#define   DHT_TimeHigh_Bit             70

extern u8 DHTArr[40],Arr_Index;

void DHT22_Init(void);
void DHT22_Runnable(void);
s16 DHT22_GetTemp(void);
u16 DHT22_GetHumidity(void);

#endif /* DHT22_INT_H_ */