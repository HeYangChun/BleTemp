#ifndef DEFINES_H
#define DEFINES_H

#include "intrins.h"
#include "stc.h"


typedef unsigned char BYTE;
typedef unsigned int WORD;

#define FOSC 11059200L         	
#define BAUD 9600	//115200             	

//#define S1_S0 0x40              //P_SW1.6
//#define S1_S1 0x80              //P_SW1.7

#define MSG_LED_1    		P34
#define MSG_LED_2		P12
#define BLE_MOD_PWR  	P14
#define BLE_MOD_RST    	P15

#define TMP_SDA			P11
#define TMP_SCL			P10


void InitUart(unsigned char bUseP16);
void ToggleUartPin(unsigned char bUseP16);
void init_temp_IIC();

void SendData(BYTE dat);
void SendString(char *s);
void Delay100us();
void writetmp112();
int readtmp112(void);

void SetTempSendLastTm(BYTE tmpVal);
BYTE GetTempSendLastTm();

#endif