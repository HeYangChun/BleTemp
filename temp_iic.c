
#include "defines.h"

//sbit sda=P2^0;                          //IO口定义
//sbit scl=P2^1;

//uint  temper;
//uchar aa;

void nop()
{
	_nop_();
	_nop_();
	_nop_();
	_nop_();

//Bgn:By HeYC
	//_nop_();
	//_nop_();
	//_nop_();
	//_nop_();
//End:By HeYC
						
}

//void delay(int count)      //delay
//{
//  int i;
//  while(count)
//  {
//    //By heYC	i=200;
//    i=400;//By HeYC
//    while(i>0)
//    i--;
//    count--;
//  }
//}

void init_temp_IIC()  //TMP112初始化子程序
{
	TMP_SCL=1;
	nop();
	TMP_SDA=1;
	nop();
}

void start()        //启动I2C总线
{
	TMP_SDA=1;
	nop();
	TMP_SCL=1;
	nop();
	TMP_SDA=0;
	nop();
	TMP_SCL=0;
	nop();
}

void stop()         //停止I2C总线
{
	TMP_SDA=0;
	nop();
	TMP_SCL=1;
	nop();
	TMP_SDA=1;
	nop();
	TMP_SCL=0;//By heYC
	
	TMP_SDA=0;//By HeYC
}

unsigned char writebyte(unsigned char j)  //写一个字节
{
	unsigned char i,temp;
   	temp=j;
   	for (i=0;i<8;i++)
   {
	   //temp=temp<<1;
	   //By HeYC 	TMP_SCL=0;
	   //By HeYC	nop();
		 //Bgn:By HeYC
		 if((temp<<i)&0x80)
			 TMP_SDA=1;
		 else
			 TMP_SDA=0;
		 //End:By HeYC
	   //By heYC TMP_SDA=CY;		//temp左移时，移出的值放入了CY中
	   nop();
	   TMP_SCL=1;		//待sda线上的数据稳定后，将scl拉高
	   nop();
	   
	 //Bgn:By heYC
	 TMP_SCL=0;
	  nop();
	 //End:By heYC
   }
//By heYC   TMP_SCL=0;
   nop();
   TMP_SDA=1;
   nop();

   TMP_SCL=1;
   nop();
   //check ack
   i=TMP_SDA;

   TMP_SCL=0;

   return i;
}

unsigned char readbyte()   //读一个字节
{
   unsigned char i,j,k=0;
   TMP_SCL=0; nop(); TMP_SDA=1;
   for (i=0;i<8;i++)
   {  
		nop(); TMP_SCL=1; nop();
      	if(TMP_SDA==1) 
		j=1;
      	else
		j=0;
		
      	k=(k<<1)|j;
	  TMP_SCL=0;
	}
   	nop();
	return(k);
}

/*void clock()         //I2C总线时钟
{
   unsigned char i=0;
   TMP_SCL=1;
   nop();
   while((TMP_SDA==1)&&(i<255))
   	  i++;
   TMP_SCL=0;
   nop();

}	*/ 

/*NOT USe, BUT DON'T DELETE
void writetmp112(void)
{
	start();
	writebyte(0x90);
//	clock();
	writebyte(0x01);
//	clock();
	writebyte(0x60);
//	clock();
	writebyte(0xa0);
//	clock();
	stop();
}
//*/
int readtmp112(void)
{ 
	BYTE i ,j;
	int temper;
	start();
	writebyte(0x90);
	//clock();
	writebyte(0x00);
	//clock();
//	stop();

	start();
	writebyte(0x91);
	//clock();
	i=readbyte();
	//clock();
	j=readbyte();
	//clock();
	stop();
		temper |= i;
		temper <<= 8;
		temper |= j;	
		temper >>=4;	 
		//temper=temper*0.0625  ;
		return temper;
;


}
/*
void main (void)
{
	uchar m;
	init();
	buzz=1;	

	while(1)
	{
		writetmp112();
		for(m=10;m>0;m--)
  		{   
 			display(readtmp112());	
  		}
	}
}//*/








#include "defines.h"
