#include <reg52.h>
#include "UART.h"

void uart_init()//9600bps@11.0592MHz
{
	// SCON = 0x50;		//8位数据,可变波特率
	// TMOD &= 0x0F;		//设定定时器1为16位自动重装方式
	// TL1 = 0xE0;		//设定定时初值
	// TH1 = 0xFE;		//设定定时初值
	// ET1 = 0;		//禁止定时器1中断
	// TR1 = 1;		//启动定时器1
	// PCON = 0x00;

	TMOD = 0x20;
    SCON = 0x50;
    TH1 = 0xfd;
    TL1 = TH1;
    PCON = 0x00;
    EA = 1;
    ES = 1;
    TR1 = 1;

    // SCON=0x50;
	// PCON |= 0x80;
	// TMOD &= 0x0F;		//设置定时器模式
	// TMOD |= 0x20;		//设置定时器模式
	// TL1 = 0xF3;		//设定定时初值
	// TH1 = 0xF3;		//设定定时器重装值
	// ET1 = 0;		//禁止定时器1中断
	// TR1 = 1;		//启动定时器1
	// EA=1;
	// ES=1;
}

void uart_sendByte(unsigned char byte)
{
	SBUF=byte;//
	while(TI==0);
	TI=0;

}

void UART_Routine() interrupt 4
{
	if(RI==1)					//如果接收标志位为1，接收到了数据
	{
		if(SBUF>0x2f&&SBUF<0x3a)
		{
			int k=SBUF-0x30;
			P0 = ~(1<<k);//test
			// uart_sendByte(k);	//将受到的数据发回串口

		};
		uart_sendByte(0x0D);	//换行符
		uart_sendByte(SBUF);	//将受到的数据发回串口
		uart_sendByte(0x0D);
		RI=0;					//接收标志位清0
	}

	// P2=0x00;
}
