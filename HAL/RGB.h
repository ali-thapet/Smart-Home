
#ifndef RGB_H_
#define RGB_H_

#include "StdTypes.h"

typedef enum{
	RED=0,
	GREEN,
	BLUE,
	WHITE,
	YELLOW,
	AQUA,
	PINK	
	}Colors_Table;
	
	


void RGB_SelectColor(Colors_Table C);
void RGB_GetColor_Values(u8 Red,u8 Green,u8 Blue);



#endif /* RGB_H_ */