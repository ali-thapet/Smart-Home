/*
 * SMART_HOUSE.h
 *
 * Created: 8/14/2024 4:26:02 AM
 *  Author: Administrator
 */ 


#ifndef SMART_HOUSE_H_
#define SMART_HOUSE_H_

extern volatile u8 AIR_OFF_Flag;

#define TASKS_NUM    8
#define PASS_Length  5


#define ROOM1_LED_PIN    PINC6 
#define ROOM2_LED_PIN    PIND3
#define GARAGE_LED_PIN   PINC7 
#define DOOR_LED_PIN     PIND2 

typedef struct{
	c8 str[30];
	void(*PF)(u8 Data);
}Task_Type;



u8 UART_Find_Task(u8*Str,u8 Data);
void UART_ReceiveTaskAndData(u8*str,u8*Data);
void Room_ON (u8 Room_Number);
void Room_OFF (u8 Room_Number);
void Garage_ON (u8 data);
void Garage_OFF (u8 data);
void AIR_CON_ON(u8 data);
void AIR_CON_OFF(u8 data);

void Open_Door(u8 data);
void Open_Garage(u8 data);
u8 Compare_pass(u8*Pass1,u8*Pass2);
void Air_ConditionerOn(u8 Temp);


#endif /* SMART_HOUSE_H_ */