/*
 * Sensors_Int.h
 *
 * Created: 5/4/2024 7:15:41 PM
 *  Author: Administrator
 */ 


#ifndef SENSORS_INT_H_
#define SENSORS_INT_H_



/*return c*10 */
u16 SENSOR_ReadTemp(void);
u16 SENSOR_ReadPressre(void);
u16 SENSOR_ReadGas(void);

#endif /* SENSORS_INT_H_ */