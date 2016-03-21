/*---------------------------------------------------------------------*/
/* --- STC MCU Limited ------------------------------------------------*/
/* --- STC15F4K60S4 ?? ???2????1?????????------------*/
/* --- Mobile: (86)13922805190 ----------------------------------------*/
/* --- Fax: 86-0513-55012956,55012947,55012969 ------------------------*/
/* --- Tel: 86-0513-55012928,55012929,55012966-------------------------*/
/* --- Web: www.STCMCU.com --------------------------------------------*/
/* --- Web: www.GXWMCU.com --------------------------------------------*/

#include "defines.h"
#include "stdio.h"
#include "string.h"
#include "math.h"

const int VER_NUM=26;

#define TMP_FORMAT_STR	"TMP:%d,PRE:%d,V%d\r\n"

#define UART_USE_P17 1
#define UART_USE_P30 0

#define BLE_POWER_ON		BLE_MOD_PWR=1	
#define BLE_POWER_OFF		BLE_MOD_PWR=0

void InitPort(){

//By HeYC	P1M0=0xb7;  //p1 mode	1011 0111
	P1M0=0xB4;//By HeYC	1011 0100
	P1M1=0x00;
	P3M0=0x13;  //p3 mode 0001 0011
	P3M1=0x00;
	
	P3=0x00;//
	MSG_LED_2=0;
	//BLE_MOD_RST=0;
}

void Delay100us()		//@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	_nop_();
	i = 2;
	j = 15;
	do
	{
		while (--j);
	} while (--i);
}


void DelayMS(int imsCnt)		//@11.0592MHz
{
	int k=0,m=0;
//	unsigned char i, j;

	for(m=0;m<imsCnt;m++){
		for(k=0;k<10;k++){
			Delay100us();
		}
	}
}

void main()
{
	  //int i=0,j=0,sCnt=0,
	int tmpRead=0,tmpSendLastTm=0,absTmpVal=0;
	char strBuf[24]={0};

	//Init port for IO use
	InitPort();
	
	BLE_MOD_PWR=1;
	MSG_LED_1=1;

  while(1){
		
  }
}

