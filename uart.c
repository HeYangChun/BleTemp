
#include "defines.h"

//Busy flag
bit busy;

#define S1_S1 0x80              //P_SW1.7
#define S1_S0 0x40              //P_SW1.6
/*
void ToggleUartPin(unsigned char bUseP16){
	
	if(bUseP16){
		//Select Tx, Rx pin P1.6
		ACC = P_SW1;
		ACC &= ~(S1_S0 | S1_S1);    //S1_S0=0 S1_S1=1
		ACC |= S1_S1;               //(P1.6/RxD_3, P1.7/TxD_3)
		P_SW1 = ACC;  
	}
	else{
		//select Tx, Rx Pin P3.0
		ACC = P_SW1;
		ACC &= ~(S1_S0 | S1_S1);    //S1_S0=0 S1_S1=0
		P_SW1 =ACC;                //(P3.0/RxD, P3.1/TxD)  
	}
}
//*/
void InitUart(unsigned char bUseP16){

	//I don't use PARITY, always NONE_PARITY
	 SCON = 0x50;                // 0101 0000

	//Baudrate generator
  T2L = (65536 - (FOSC/4/BAUD));   
  T2H = (65536 - (FOSC/4/BAUD))>>8;
  AUXR = 0x14;                
  AUXR |= 0x01;              
	
	if(bUseP16){
		//Select Tx, Rx pin P1.6
		ACC = P_SW1;
		ACC &= ~(S1_S0 | S1_S1);    //S1_S0=0 S1_S1=1
		ACC |= S1_S1;               //(P1.6/RxD_3, P1.7/TxD_3)
		P_SW1 = ACC;  
	}
	else{
		//select Tx, Rx Pin P3.0
		ACC = P_SW1;
		ACC &= ~(S1_S0 | S1_S1);    //S1_S0=0 S1_S1=0
		P_SW1 =ACC;                //(P3.0/RxD, P3.1/TxD)  
	}
}


void Uart() interrupt 4 using 1
{
	if (RI)
	{
		RI = 0;                 
		//P0 = SBUF;            
		//P22 = RB8;            
	}
	if (TI)
	{
		TI = 0;                 
		busy = 0;             
	}
}


void SendData(BYTE dat)
{
	while (busy);               
	ACC = dat;                  
	busy = 1;
	SBUF = ACC;               
}

void SendString(char *s)
{
	while (*s)                 
	{
		SendData(*s++);        
	}
}