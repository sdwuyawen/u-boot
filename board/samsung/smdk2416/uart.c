///////////////////////////////////////////////////////////////
// 本程序只供学习使用，未经本公司许可，不得用于其它任何商业用途
// 适用开发板型号:Tiny2416、Mini2451、Tiny2451
// 技术论坛:www.arm9home.net
// 修改日期:2013/7/1
// 版权所有，盗版必究。
// Copyright(C) 广州友善之臂计算机科技有限公司
// All rights reserved							
///////////////////////////////////////////////////////////////

// 功能:初始化串口
#include "uart.h" 
#define ULCON0   		( *((volatile unsigned long *)0x50000000) )
#define UCON0    		( *((volatile unsigned long *)0x50000004) )
#define UFCON0   	 	( *((volatile unsigned long *)0x50000008) )
#define UMCON0    		( *((volatile unsigned long *)0x5000000C) )
#define UTRSTAT0  		( *((volatile unsigned long *)0x50000010) )
#define UFSTAT0 		( *((volatile unsigned long *)0x50000018) )
#define UTXH0      		( *((volatile unsigned char *)0x50000020) )
#define URXH0      		( *((volatile unsigned char *)0x50000024) ) 
#define UBRDIV0    		( *((volatile unsigned short *)0x50000028) )
#define UDIVSLOT0  		( *((volatile unsigned short *)0x5000002C) )
#define GPHCON     		( *((volatile unsigned long *)0x56000070 ) )
#define TXD0READY   (1<<2)

//#define UART0_USING_FIFO

void uart_init(void)
{
	// 配置引脚  
	GPHCON = (GPHCON & ~0xffff ) | 0xaaaa;
		
	// 设置数据格式等  
	ULCON0 = 0x3;  					// 数据位:8, 无校验, 停止位: 1, 8n1 
	UCON0  = 0x5;  					// 时钟：PCLK，禁止中断，使能UART发送、接收 
#ifdef UART0_USING_FIFO
	UFCON0 = 0x01; 					// FIFO ENABLE
#else
	UFCON0 = 0x00; 					// FIFO DISABLE
#endif
	UMCON0 = 0;						// 无流控
	
	// 设置波特率  
	// DIV_VAL = (PCLK / (bps x 16 ) ) - 1 = (66500000/(115200x16))-1 = 35.08
	// DIV_VAL = 35.08 = UBRDIVn + (num of 1’s in UDIVSLOTn)/16 
	UBRDIV0   = 35;
	UDIVSLOT0 = 0x1;
}

// 接收一个字符  
char getchar(void)
{
#ifdef UART0_USING_FIFO
	while ((UFSTAT0 & 0x7f) == 0);  // 如果RX FIFO空，等待 
#else
	while ((UFSTAT0 & 0x7f) == 0);  // 如果RX FIFO空，等待 
#endif
	
	return URXH0;                   // 取数据 
}

// 发送一个字符  
void putchar(char c)
{
#ifdef UART0_USING_FIFO
	while (UFSTAT0 & (1<<14)); 		// 如果TX FIFO满，等待 
#else
	/* 等待，直到发送缓冲区中的数据已经全部发送出去 */
	while (!(UTRSTAT0 & TXD0READY));
#endif
	
	UTXH0 = c;                      // 写数据 
}

// 发送一个字符串
void putstring(char *string)
{
	while(*string != 0x00)
	{
		putchar(*string);
		string ++;
	}
}



void putinthex(unsigned int data)
{
	/*
	putchar((data /0x10000000)+ '0');
	putchar((data %0x10000000) / 0x01000000+ '0');
	putchar((data %0x01000000) / 0x00100000+ '0');
	putchar((data %0x00100000) / 0x00010000+ '0');
	putchar((data %0x00010000) / 0x00001000+ '0');
	putchar((data %0x00001000) / 0x00000100+ '0');
	putchar((data %0x00000100) / 0x00000010+ '0');
	putchar((data %0x00000010) / 0x00000001+ '0');
	putchar('\r');
	putchar('\n');
	*/

	unsigned int i;
	unsigned char data_char;

	for(i = 0; i < 8; i++)
	{
		data_char = (data >> (4 *(7 - i))) & 0x0F;
		if(data_char > 9)
		{
			putchar(data_char - 0x0A + 'A');
		}
		else
		{
			putchar(data_char + '0');
		}
	}
	putchar('\r');
	putchar('\n');
	
}

//发送启动信息
void put_start_info(unsigned int num)
{
//	putstring("starting----");
	putchar('p');
	putchar('a');
	putchar('r');
	putchar(num + '0');
//	putstring("\r\n");
	putchar('\r');
	putchar('\n');
}


int memory_test(void)
{
	
	volatile unsigned int *addr = (unsigned int *)0x30008000;
//	unsigned int data = 0x00000000;
	/*
	unsigned int i;

	for(i = 0; i < 1024; i++)
	{
		addr[i] = i;
	}

	for(i = 0; i < 1024; i++)
	{
		if(addr[i] != i)
		{
			break;
		}
	}

	if(i == 1024)
	{
		putstring("Mem Test OK\n");
	}
	else
	{
		putstring("Mem Test Error");
		
		putchar(i / 1000 + '0');
		putchar((i % 1000) / 100+ '0');
		putchar((i % 100) / 10+ '0');
		putchar((i % 10) / 1+ '0');
	}*/

	unsigned int i;
	
	/**addr = 0xAAAAAAAA;
	if(*addr == 0xAAAAAAAA)
	{
		putstring("Mem Test OK\r\n");
	}
	else
	{
		putstring("Mem Test Error\r\n");
	}*/

	/*addr = (unsigned int *)0x30008004;
	
	*addr= 0x12345678;
	data = *addr;
	
	if(data == 0x12345678)
	{
		putstring("Mem Test OK\r\n");
	}
	else
	{
		putstring("Mem Test Error\r\n");
	}
	putinthex(data);
	putstring("\r\n");
	putstring("\r\n");*/

	putchar('m');
	putchar('e');
	putchar('m');
	putchar('t');
	putchar('e');
	putchar('s');
	putchar('t');
	putchar('\r');
	putchar('\n');

	for(i = 0; i < 1024 * 1024; i++)
	{
		addr[i] = i;
	}
	/*
	*((unsigned int *)0x30000000) = 0xABCD1234;
	*((unsigned int *)0x30000004) = 0xABCD1235;*/

	for(i = 0; i < 1024 * 1024; i++)
	{
//		putinthex(addr[i]);
		if(addr[i] != i)
		{
			break;
		}
	}
	
	putinthex(i);
	putinthex(addr[0]);
	putinthex(addr[1]);
	putinthex(addr[2]);
	putinthex(addr[3]);
	putchar('\r');
	putchar('\n');
	
	if(i == 1024 * 1024)
	{
		putchar('m');
		putchar('e');
		putchar('m');
		putchar('o');
		putchar('k');
		putchar('\r');
		putchar('\n');
//		putstring("Mem Test ALL OK\r\n");
	}
	else
	{
		putchar('m');
		putchar('e');
		putchar('m');
		putchar('e');
		putchar('r');
		putchar('r');
		putchar('\r');
		putchar('\n');
//		putstring("Mem Test Error\r\n");
		putinthex(i);
		putinthex(addr[i]);
	}

//	while(1);

	return 0;

}