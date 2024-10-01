


#ifndef FILTER_INT_H_
#define FILTER_INT_H_

extern u16 FilterArr[10],F_Value,UNF_Value; // u16
extern u8 Filter_INDEX; // u8
     

void Filter_Init(void);
void Filter_Runnable(void);  // 200 us
u16 Filter_GetFilteredValue(void);  // 2 us
u16 Filter_GetUnFilteredValue(void); // 2 us


#endif /* FILTER_INT_H_ */