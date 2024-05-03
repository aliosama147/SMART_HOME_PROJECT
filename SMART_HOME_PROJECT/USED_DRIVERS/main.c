/*
 * Smart Home Final Project.c
 */ 

#define F_CPU 8000000

#include "BIT_MATH.h"
#include "TYPES.h"

#include "DIO_interface.h"
#include "LED_interface.h"
#include "LCD_interface.h"
#include "ADC_interface.h"
#include "LM35_interface.h"
#include "EEPROM_interface.h"
#include "UART_interface.h"
#include "Motor_Dirver.h"
#include "Timer.h"

#include "util/delay.h"
#include "RTOS/FreeRTOS.h"
#include "RTOS/task.h"
#include "RTOS/queue.h"

#define FIRST_TIME_RUNNING_EEPROM_ADDRESS   0x00
#define NUMBER_OF_USERS_EEPROM				0x01
#define ADMIN_EEPROM_ADDRESS				0x3f2
#define USERS_EEPROM_ADDRESS				0x0A


u8 NO_CHANGE =  'N';
u16 u16Degree;
u8 u8Speed;
u8 * resetCode = "*00*";
u8 numOfUsers=0;
u8 ExistUserAddress=0x50;
u8 User_EEPROM_Address='0';
u8 idChar,passwordChar;

void System_Init(void);
void VIEW_DATA(void *pvData);
void CHECK_COMMAND(void *pvData);
void CHECK_TEMP(void *pvData);

xQueueHandle QueueCOMMAND ;
u8 login(){
	u8 id[4],pass[4],passed=1;
	USART_vidSendString("\r\nEnter Id :\r\n");
	for (u8 i=0;i<4;i++)
	{
		id[i]=USART_u8RecieveByte();
	}
	
	USART_vidSendString("\r\nEnter Password :\r\n");
	
	for (u8 i=0;i<6;i++)
	{
		pass[i]=USART_u8RecieveByte();
	}
	
	for(u8 i=0;i<numOfUsers;i+=10)
	{
		if(EEPROM_u8Read(USERS_EEPROM_ADDRESS+i)==id[0])
		{
			for(u8 j=0;j<4;j++)
			{
				if(id[j]!=EEPROM_u8Read(USERS_EEPROM_ADDRESS+i+j))
				{
					passed=0;
				}
			}
			for(u8 j=0;j<6;j++)
			{
				if(pass[j]!=EEPROM_u8Read(USERS_EEPROM_ADDRESS+4+i+j))
				{
					passed=0;
				}
			}
		}
		
	}

	return passed;
}

int main(void)
{
	u8 firstTimeFlag,passed;
	
	System_Init();
	xTaskCreate(CHECK_COMMAND		,NULL,200,NULL,1,NULL);
	xTaskCreate(CHECK_TEMP			,NULL,200,NULL,2,NULL);
	xTaskCreate(VIEW_DATA			,NULL,200,NULL,3,NULL);
	QueueCOMMAND = xQueueCreate(5,sizeof(u8));
	
	LCD_vidSendString("Welcome Home :)");
	_delay_ms(500);
	LCD_vidSendCmd(LCD_CLEAR_SCREEN);
	
	
	firstTimeFlag=EEPROM_u8Read(FIRST_TIME_RUNNING_EEPROM_ADDRESS);
	
	if(firstTimeFlag !='Y'){
		EEPROM_vidWrite(NUMBER_OF_USERS_EEPROM,0);
		LCD_vidSendString("Registering ....");
		GenerateAdmin();
		LCD_vidSendCmd(LCD_CLEAR_SCREEN);
		LCD_vidSendString("Registering Done");
		_delay_ms(500);
		
	}
	numOfUsers=EEPROM_u8Read(NUMBER_OF_USERS_EEPROM);
	LCD_vidSendCmd(LCD_CLEAR_SCREEN);
	
	LCD_vidSendString("Logging ....");
	
	do{
		passed=login();
	}while(passed==0);
	
	vTaskStartScheduler();
}

void System_Init(void)
{
	LCD_vidInit();
	LCD_vidMoveCursor(0,0);
	LM35_vidInit(ADC_CHANNEL0);
	USART_vidInit(9600);
	motorA_vidInit();
	motorB_vidInit();
	LED_vidInit(GPIOB,PIN0);
	LED_vidInit(GPIOB,PIN1);
	LED_vidInit(GPIOB,PIN2);
	LED_vidInit(GPIOD,PIN2);
	LED_vidInit(GPIOD,PIN3);
	LED_vidInit(GPIOD,PIN4);

}

void GenerateAdmin(){
	
	
	USART_vidSendString("\r\nEnter Admin Id :\r\n");
	for (u8 i=0;i<4;i++)
	{
		idChar=USART_u8RecieveByte();
		EEPROM_vidWrite(ADMIN_EEPROM_ADDRESS +i,idChar);
	}
	
	USART_vidSendString("\r\nEnter Admin Password :\r\n");
	for (u8 i=0;i<6;i++)
	{
		passwordChar=USART_u8RecieveByte();
		EEPROM_vidWrite(ADMIN_EEPROM_ADDRESS +4+i,passwordChar);
	}

	EEPROM_vidWrite(FIRST_TIME_RUNNING_EEPROM_ADDRESS,'Y');
}

void CHECK_COMMAND(void *pvData)
{
	u8 RECIEVED_COMMAND;
	while (1)
	{
		RECIEVED_COMMAND=USART_u8RecieveByte();
		if (RECIEVED_COMMAND != NO_CHANGE)
		{
			switch (RECIEVED_COMMAND) {
				case 'U' :
					GenerateUser();
					break;
				case 'D' :
					DeleteUser();
					break;
				case 'R' :
					ResetAdminPassword();
					break;
				case '1' :
					LED_vidLedToggle(GPIOB,PIN0);
					break;
				case '2' :
					LED_vidLedToggle(GPIOB,PIN1);
					break;
				case '3' :
					LED_vidLedToggle(GPIOB,PIN2);
					break;
				case '4' :
					LED_vidLedToggle(GPIOD,PIN2);
					break;
				case '5' :
					LED_vidLedToggle(GPIOD,PIN3);
					break;
				case '6' :
					LED_vidLedToggle(GPIOD,PIN4);
					break;
				case 'O' :
					Motor2_ClockWise(50);
					break;
				case 'C' :
					Motor2_Stop();
					break;
				default:
					break;
			}
		}
	}
}

void VIEW_DATA(void *pvData) {	LCD_vidSendString("Temp: ");
	LCD_vidSendNumber(u16Degree);
	LCD_vidSendChar((char)223);
	LCD_vidSendChar('C');
	LCD_vidMoveCursor(2,1);
	LCD_vidSendString("AC: ");
	LCD_vidSendNumber(u8Speed);	while (1)	{		LCD_vidMoveCursor(1,7);		LCD_vidSendNumber(u16Degree);
		LCD_vidSendChar((char)223);
		LCD_vidSendChar('C');		if (u16Degree<10)
		{
			LCD_vidMoveCursor(1,10);
			LCD_vidSendChar(' ');
		}		LCD_vidMoveCursor(2,5);		LCD_vidSendNumber(u8Speed);		if (u16Degree<100)
		{
			LCD_vidSendString("  ");
		}		vTaskDelay(30);	}}


void CHECK_TEMP(void *pvData)
{
	while (1)
	{
		u16Degree=LM35_u8LM35Read();
		if(u16Degree >=28 ){
			u8Speed=(((((u16Degree)-28)/2)+1)*10);
			if (u8Speed>=100)
			{
				u8Speed=100;
			}
			Motor1_ClockWise(u8Speed);
		}else
		{
			u8Speed=0;
			Motor1_Stop();
		}
		vTaskDelay(50);
	}
}

// Function for Login and Register

// u8 checkUser(u8 id[],u8 pass[]){
// 	u8 idC[4],passC[6],place,exist=1;
// 	for(u8 i=0;i<numOfUsers;i++){
// 		
// 		for(u8 g=0;g<4;g++){
// 			idC[g]=EEPROM_u8Read(USERS_EEPROM_ADDRESS + i + g);
// 		}
// 		for(u8 g=0;g<6;g++){
// 			passC[g]=EEPROM_u8Read(USERS_EEPROM_ADDRESS + i + 4 + g);
// 		}
// 		for(u8 j=0;j<4;j++){
// 			if (idC[j]!=id[j])
// 			{
// 				exist=0;
// 			}
// 		}
// 		if (exist==1)
// 		{
// 			place=i;
// 			break;
// 		}
// 	}
// 	
// 	if(exist==1){
// 		for(u8 j=0;j<4;j++){
// 			if (idC[j]!=id[j])
// 			{
// 				return 'F';
// 			}
// 		}
// 		for(u8 j=0;j<6;j++){
// 			if (passC[j]!=pass[j])
// 			{
// 				return 'F';
// 			}
// 		}
// 		}else{
// 		return 'F';
// 	}
// 	return place;
// }


void GenerateUser(){
	
	u8 idChar,passwordChar;
	
	USART_vidSendString("\r\nEnter User Id :\r\n");
	for (u8 i=0;i<4;i++)
	{
		idChar=USART_u8RecieveByte();
		EEPROM_vidWrite(USERS_EEPROM_ADDRESS+ NUMBER_OF_USERS_EEPROM +i,idChar);
	}
	
	USART_vidSendString("\r\nEnter User Password :\r\n");
	for (u8 i=0;i<6;i++)
	{
		passwordChar=USART_u8RecieveByte();
		EEPROM_vidWrite(USERS_EEPROM_ADDRESS+ NUMBER_OF_USERS_EEPROM +4+i,passwordChar);
	}
	EEPROM_vidWrite(NUMBER_OF_USERS_EEPROM,numOfUsers+1);
	USART_vidSendString("\r\nThank You :)");
}


void DeleteUser(){
	
	u8 idC[4],idChar[4],exist=1;
	USART_vidSendString("\r\nEnter User Id :\r\n");
	for (u8 i=0;i<4;i++)
	{
		idChar[i]=USART_u8RecieveByte();
	}
	
	for(u8 i=0;i<numOfUsers;i++){
		
		for(u8 g=0;g<4;g++){
			idC[g]=EEPROM_u8Read(USERS_EEPROM_ADDRESS + i + g);
		}
		for(u8 j=0;j<4;j++){
			if (idC[j]!=idChar[j])
			{
				exist=0;
			}
		}
		if(exist==1){
			for(u8 j=0;j<10;j++){
				EEPROM_vidWrite(USERS_EEPROM_ADDRESS+i+j,'A');
			}
			USART_vidSendString("User Has Been Deleted !\r\n");
			break;
		}
	}
	
	EEPROM_vidWrite(NUMBER_OF_USERS_EEPROM,numOfUsers-1);
	USART_vidSendString("\r\nThank You :)");
}

void ResetAdminPassword(){
	u8 recievedResetCode[4];
	u8 flag=0,passwordChar;
	USART_vidSendString("\r\nEnter Reset Code :\r\n");
	for (u8 i=0;i<4;i++)
	{
		recievedResetCode[i]=USART_u8RecieveByte();
		
		if(recievedResetCode[i] != resetCode[i])
		{
			flag=1;
		}
	}
	if(flag != 1)
	{
		USART_vidSendString("\r\nEnter New Password :\r\n");
		for (u8 i=0;i<6;i++)
		{
			passwordChar=USART_u8RecieveByte();
			EEPROM_vidWrite(ADMIN_EEPROM_ADDRESS + 4 + i,passwordChar);
		}
		
		USART_vidSendString("\r\nThank You :)\r\n");
		
	}else
	{
		USART_vidSendString("\r\nYour Reset Code is Wrong \r\n");
	}
	
}



//====================================


/*
// void ResetUserPassword(){
// 	u8 recievedResetCode[4];
// 	u8 flag=0,passwordChar;
// 	LCD_vidSendString("Reset Code :");
// 	LCD_vidMoveCursor(2,1);
// 	for (u8 i=0;i<4;i++)
// 	{
// 		do
// 		{
// 			recievedResetCode[i] = KPD_u8GetKey(GPIOC);
// 			while(KPD_u8GetKey(GPIOC)==recievedResetCode[i]);
// 		} while (KPD_u8GetKey(GPIOC)==NOT_PRESSED);
// 		LCD_vidSendChar(recievedResetCode[i]);
// 		if(recievedResetCode[i] != resetCode[i])
// 		{
// 			flag=1;
// 		}
// 	}
// 	if(flag != 1)
// 	{
// 		LCD_vidSendCmd(LCD_CLEAR_SCREEN);
// 		LCD_vidMoveCursor(1,1);
// 		LCD_vidSendString("New Password :");
// 		LCD_vidMoveCursor(2,1);
// 		for (u8 i=0;i<6;i++)
// 		{
// 			do
// 			{
// 				passwordChar = KPD_u8GetKey(GPIOC);
// 				while(KPD_u8GetKey(GPIOC)==passwordChar);
// 			} while (KPD_u8GetKey(GPIOC)==NOT_PRESSED);
//
// 			LCD_vidSendChar('*');
// 			EEPROM_vidWrite(ExistUserAddress + 4 + i,passwordChar);
// 		}
//
// 		LCD_vidSendCmd(LCD_CLEAR_SCREEN);
// 		LCD_vidMoveCursor(1,1);
// 		LCD_vidSendString("Thank You :)");
//
// 	}else
// 	{
// 		LCD_vidSendCmd(LCD_CLEAR_SCREEN);
// 		LCD_vidMoveCursor(1,1);
// 		LCD_vidSendString("Wrong Code !");
// 	}
//
// }
*/


//
// void LoginKpd(void){
// 	u8 flag,logined;
// 	LCD_vidSendCmd(LCD_CLEAR_SCREEN);
// 	LCD_vidMoveCursor(1,1);
// 	LCD_vidSendString("1_ Reset Pass");
// 	LCD_vidMoveCursor(2,1);
// 	LCD_vidSendString("2_ Enter Pass");
//
// 	do
// 	{
// 		flag = KPD_u8GetKey(GPIOC);
// 		while(KPD_u8GetKey(GPIOC)==flag);
// 	} while (KPD_u8GetKey(GPIOC)==NOT_PRESSED);
//
// 	switch (flag) {
// 		case '1':
// 			ResetUserPassword();
// 			break;
// 		case '2':
// 			LoginUser();
// 			break;
// 	}
//
// }
//

// void LoginUser(void){
// 	u8 place,idChar[4],passwordChar[6];
// 	LCD_vidSendCmd(LCD_CLEAR_SCREEN);
// 	LCD_vidMoveCursor(1,1);
// 	LCD_vidSendString("Enter Id :");
// 	LCD_vidMoveCursor(2,1);
// 	for (u8 i=0;i<4;i++)
// 	{
// 		do
// 		{
// 			idChar[i] = KPD_u8GetKey(GPIOC);
// 			while(KPD_u8GetKey(GPIOC)==idChar[i]);
// 		} while (KPD_u8GetKey(GPIOC)==NOT_PRESSED);
// 		LCD_vidSendChar(idChar[i]);
// 	}
//
// 	LCD_vidSendString("Enter Pass :");
// 	for (u8 i=0;i<6;i++)
// 	{
// 		do
// 		{
// 			passwordChar[i] = KPD_u8GetKey(GPIOC);
// 			while(KPD_u8GetKey(GPIOC)==passwordChar[i]);
// 		} while (KPD_u8GetKey(GPIOC)==NOT_PRESSED);
// 		LCD_vidSendChar('*');
// 	}
// 	place=checkUser(idChar,passwordChar);
// 	if(place=='F'){
// 		LCD_vidSendCmd(LCD_CLEAR_SCREEN);
// 		LCD_vidMoveCursor(1,1);
// 		LCD_vidSendString("User Not Found !");
// 		return;
// 	}
// 	User_EEPROM_Address=place;
// 	LCD_vidSendCmd(LCD_CLEAR_SCREEN);
// 	LCD_vidMoveCursor(1,1);
// 	LCD_vidSendString("Welcome ");
// 	for (u8 i=0;i<4;i++)
// 	{
// 		LCD_vidSendChar(idChar[i]);
// 	}
// 	_delay_ms(1000);
// }