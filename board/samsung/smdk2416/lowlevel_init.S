/*
 * Memory Setup stuff - taken from blob memsetup.S
 *
 * Copyright (C) 1999 2000 2001 Erik Mouw (J.A.K.Mouw@its.tudelft.nl) and
 *                     Jan-Derk Bakker (J.D.Bakker@its.tudelft.nl)
 *
 * Modified for the Samsung SMDK2410 by
 * (C) Copyright 2002
 * David Mueller, ELSOFT AG, <d.mueller@elsoft.ch>
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */


#include <config.h>
#include <version.h>

/* 20150316,发现启动内核后EPLL有问题
 * 新增加的，设置EPLL 
 * 复制自helper2416的u-boot-1.3.4的lowlevel_init.S
 */
//#include <asm/arch-s3c24x0/s3c24x0.h>
//#include <asm/arch/s3c2440.h>
/* 
 * 新增加的 结束
 */

/* some parameters for the board */

/*
 *
 * Taken from linux/arch/arm/boot/compressed/head-s3c2410.S
 *
 * Copyright (C) 2002 Samsung Electronics SW.LEE  <hitchcar@sec.samsung.com>
 *
 */

/* EPLL配置 */
#define ELFIN_CLOCK_POWER_BASE	0x4c000000
#define LOCKCON1_OFFSET		0x04
#define EPLLCON_OFFSET		0x18
#define CLKSRCCON_OFFSET	0x20

#if defined(CONFIG_BOOT_MOVINAND)
#define EPLL_VAL	(32<<16)|(1<<8)|(3<<0)
#else
#define EPLL_VAL	(32<<16)|(1<<8)|(2<<0)
#endif

_TEXT_BASE:
	.word	CONFIG_SYS_TEXT_BASE

.globl lowlevel_init
lowlevel_init:

/*led_blink_1:
	// 设置GPBDAT，使GPB_5/6引脚输出高电平，LED灭
	ldr r1, =0x56000014 					
	mov r0, #(0x1<<1)
	str r0, [r1]

	mov r0, #6
	bl put_start_info

	// 延时 
	bl delay_1

	mov r0, #7
	bl put_start_info

	// 设置GPBDAT，使GPB_5/6引脚输出低电平，LED亮
	ldr r1, =0x56000014 					
	mov r0, #(0x0<<1)
	str r0, [r1]

	// 延时
	bl delay_1

	mov r0, #8
	bl put_start_info

	b led_blink_1
delay_1:
	mov r0, #0x1000000
delay_loop_1:
	cmp r0, #0
	sub r0, r0, #1
	bne delay_loop_1
	mov pc, lr*/

	push {lr}

/* 3. 初始化SDRAM */
	mov r0, #6
	bl put_start_info
	
//	adr r0, sdram_bank_set_val		/* 当前地址 */
//	bl sdr_ctrl_asm_init
//	bl SDRAM_Init
//	bl memory_test
	
	mov r0, #8
	bl put_start_info

	/* 20150316,发现启动内核后EPLL有问题
	 * 新增加的，设置EPLL 
	 * 复制自helper2416的u-boot-1.3.4的lowlevel_init.S
	 */
	 
//#define EPLL_VAL	(32<<16)|(1<<8)|(2<<0)
#define EPLL_VAL	(32<<16)|(2<<8)|(2<<0)


	ldr	r0, =ELFIN_CLOCK_POWER_BASE
#if 1
	ldr	r1, =0x1780					/* EPLL lock time count value for UARTCLK, SPICLK and etc */
	str	r1, [r0, #LOCKCON1_OFFSET]

	ldr	r1, =EPLL_VAL				/*Set EPLL，见2416数据手册P79*/
	str	r1, [r0, #EPLLCON_OFFSET]

	ldr	r1, [r0, #CLKSRCCON_OFFSET]	/* EPLL output作为EsysClk */
	orr	r1, r1, #0x40
	str	r1, [r0, #CLKSRCCON_OFFSET]

#endif

	/* 
	 * 新增加的 结束
	 */


	/* everything is fine now */
	pop {lr}

	mov	pc, lr


