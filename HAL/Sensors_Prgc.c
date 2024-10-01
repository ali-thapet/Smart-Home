#include "StdTypes.h"
#include "ADC_Int.h"
#include "Sensors_Int.h"
#include "Sensors_Cfg.h"


u16 SENSOR_ReadTemp(void)
{
	u16 volt =ADC_ReadVolt1(LM35_CH);
	u16 temp;
	temp=volt;
	return temp;
	
}

u16 SENSOR_ReadGas(void)
{
	u16 volt =ADC_ReadVolt1(MQ2);
	u16 Gas;
	Gas=volt;
	return Gas;
	
}


/* u8 SENSOR_Interpolation(u8 X,u8 X1,u8 Y,u8 Y1)
{
	u8 Slope=(1000*(Y-Y1))/(X-X1); 
	return Slope;
} 
*/


u16 SENSOR_ReadPressre(void)
{
	u16 volt =ADC_ReadVolt(MPX4115);
	u16 Pressure;
	u8 slope;
	slope= 46;            // y-y1=s(x-x1)  4.8-0.2=s(115-15)     s*1000
	Pressure=(volt/slope)+15;
	return Pressure;
	
}

u16 SENSOR_ReadDistanc(void)
{
	u16 volt =ADC_ReadVolt(MPX4115);
	u16 Distance;
	Distance=(volt)+15;
	return Distance;
	
}
