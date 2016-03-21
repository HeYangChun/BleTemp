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
//#include "math.h"

const int VER_NUM=28;

#define TMP_FORMAT_STR	"TMP:%d,V:%d\r\n"

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
	//Init for UART used
	InitUart(UART_USE_P17);
	
	//
	init_temp_IIC();

	//Flags of IE register
  ES = 1;                     
  EA = 1;

	WKTCL = 0x03;                     //设置唤醒周期为488us*(49+1) = 24.4ms
  WKTCH = 0x98;                   //使能掉电唤醒定时器

	//Make ready for the 1st sleep...
	BLE_MOD_PWR=0;
	MSG_LED_1=0;
	MSG_LED_2=0;

  while(1){

		//////////////////////////////////////////
		//Begin enter sleep mode.
		PCON = 0x02;                //进入掉电模式
		
		//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		//WAKED UP FROM SLEEP
		//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		
		//Read temp , check if need to be send out...
		DelayMS(100);
		tmpRead=readtmp112();
		tmpRead=tmpRead*0.0625;
		//get temp value saved in eeprom
		tmpSendLastTm=GetTempSendLastTm();
		
		//if the abs value is less than 5 degree, don't send to save power
		absTmpVal=tmpSendLastTm-tmpRead;
		//absTmpVal=abs(absTmpVal);
		
		//compare with the value of previous
		if(absTmpVal>=3  || absTmpVal<=-3)//			MSG_LED_1=1;
		{
			//send out, else not send
			//make ready for BLE module to send...
			P16=1;
			P17=1;
			InitUart(UART_USE_P17);
		
			//Power ON for BLE
			BLE_MOD_PWR=1;

			//wait for BLE power and connected by master
			DelayMS(2000);
		
			//Format the message send out
			memset(strBuf,0,sizeof(strBuf));
			sprintf(strBuf,TMP_FORMAT_STR,tmpRead,VER_NUM);
		
			//Send out
			//MSG_LED_1=1;
			SendString(strBuf);
			
			//Save current read temp into eeprom
			SetTempSendLastTm(tmpRead);

			//wait ble complete sending...
			DelayMS(100);
			//SendString(strBuf);
			//DelayMS(100);
			//MAKE READY FOR SLEEP AGAIN...
			P3=0x00;
			InitUart(UART_USE_P30);
			P16=0;
			P17=0;
		}
		
		//before enter sleep;
		BLE_MOD_PWR=0;
		MSG_LED_1=0;
		MSG_LED_2=0;
	}
}

