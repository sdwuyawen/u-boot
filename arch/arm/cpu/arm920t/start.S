/*
 *  armboot - Startup Code for ARM920 CPU-core
 *
 *  Copyright (c) 2001	Marius Gr枚ger <mag@sysgo.de>
 *  Copyright (c) 2002	Alex Z眉pke <azu@sysgo.de>
 *  Copyright (c) 2002	Gary Jennejohn <garyj@denx.de>
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

#include <asm-offsets.h>
#include <common.h>
#include <config.h>


/* 时钟配置 */
#define ELFIN_CLOCK_POWER_BASE	0x4c000000
#define LOCKCON0_OFFSET			0x00
#define MPLLCON_OFFSET			0x10
#define CLKSRCCON_OFFSET		0x20
#define CLKDIV0CON_OFFSET		0x24

// 400-133-66
// ARMCLK-HCLK-PCLK
#define	Startup_MDIV			400
#define	Startup_PDIV			3
#define	Startup_SDIV			1
#define	Startup_MPLLSTOP		0

#define	Startup_ARMCLKdiv		1
#define	Startup_PREdiv			0x2
#define	Startup_HCLKdiv			0x1
#define	Startup_PCLKdiv			1
#define	CLK_DIV_VAL				((Startup_ARMCLKdiv<<9)|(Startup_PREdiv<<4)|(Startup_PCLKdiv<<2)|(Startup_HCLKdiv))
#define	MPLL_VAL				((Startup_MPLLSTOP<<24)|(Startup_MDIV<<14)|(Startup_PDIV<<5)|(Startup_SDIV))

/*
 *************************************************************************
 *
 * Jump vector table as in table 3.1 in [1]
 *
 *************************************************************************
 */


.globl _start
_start:	b	start_code
	ldr	pc, _undefined_instruction
	ldr	pc, _software_interrupt
	ldr	pc, _prefetch_abort
	ldr	pc, _data_abort
	ldr	pc, _not_used
	ldr	pc, _irq
	ldr	pc, _fiq

_undefined_instruction:	.word undefined_instruction
_software_interrupt:	.word software_interrupt
_prefetch_abort:	.word prefetch_abort
_data_abort:		.word data_abort
_not_used:		.word not_used
_irq:			.word irq
_fiq:			.word fiq

	.balignl 16,0xdeadbeef


/*
 *************************************************************************
 *
 * Startup Code (called from the ARM reset exception vector)
 *
 * do important init only if we don't start from memory!
 * relocate armboot to ram
 * setup stack
 * jump to second stage
 *
 *************************************************************************
 */

.globl _TEXT_BASE
_TEXT_BASE:
	.word	CONFIG_SYS_TEXT_BASE

/*
 * These are defined in the board-specific linker script.
 * Subtracting _start from them lets the linker put their
 * relative position in the executable instead of leaving
 * them null.
 */
.globl _bss_start_ofs
_bss_start_ofs:
	.word __bss_start - _start

.globl _bss_end_ofs
_bss_end_ofs:
	.word __bss_end__ - _start

.globl _end_ofs
_end_ofs:
	.word _end - _start

#ifdef CONFIG_USE_IRQ
/* IRQ stack memory (calculated at run-time) */
.globl IRQ_STACK_START
IRQ_STACK_START:
	.word	0x0badc0de

/* IRQ stack memory (calculated at run-time) */
.globl FIQ_STACK_START
FIQ_STACK_START:
	.word 0x0badc0de
#endif

/* IRQ stack memory (calculated at run-time) + 8 bytes */
.globl IRQ_STACK_START_IN
IRQ_STACK_START_IN:
	.word	0x0badc0de

/* 全局变量，在board.c里面赋值 */
.global base_sp
base_sp:
	.long 0

/*
 * the actual start code
 */

start_code:
	/*
	 * set the cpu to SVC32 mode
	 */
	mrs	r0, cpsr
	bic	r0, r0, #0x1f
	orr	r0, r0, #0xd3
	msr	cpsr, r0

#if	defined(CONFIG_AT91RM9200DK) || defined(CONFIG_AT91RM9200EK)
	/*
	 * relocate exception table
	 */
	ldr	r0, =_start
	ldr	r1, =0x0
	mov	r2, #16
copyex:
	subs	r2, r2, #1
	ldr	r3, [r0], #4
	str	r3, [r1], #4
	bne	copyex
#endif

#ifdef CONFIG_S3C24X0
	/* turn off the watchdog */

# if defined(CONFIG_S3C2400)
#  define pWTCON	0x15300000
#  define INTMSK	0x14400008	/* Interrupt-Controller base addresses */
#  define CLKDIVN	0x14800014	/* clock divisor register */
#else
#  define pWTCON	0x53000000
#  define INTMSK	0x4A000008	/* Interrupt-Controller base addresses */
#  define INTSUBMSK	0x4A00001C
#  define CLKDIVN	0x4C000014	/* clock divisor register */
# endif

/*1. 关看门狗 */
	ldr	r0, =pWTCON
	mov	r1, #0x0
	str	r1, [r0]

	// 设置GPBCON
	ldr r1, =0x56000010  					
	ldr r0, =( 0x1<<(2*1) )													  
	str r0, [r1]
	// 设置GPBSEL
	ldr r1, =0x5600001c 
	ldr r0, =0x0
	str r0, [r1]
	// LED灭
	/*ldr r1, =0x56000014 					
	mov r0, #(0x1<<1)
	str r0, [r1]*/
	// LED亮
	ldr r1, =0x56000014 					
	mov r0, #(0x0<<1)
	str r0, [r1]

	/*
	 * mask all IRQs by setting all bits in the INTMR - default
	 */
	mov	r1, #0xffffffff
	ldr	r0, =INTMSK
	str	r1, [r0]
	ldr	r0, =INTSUBMSK		/* by wu */
	str	r1, [r0]				/* by wu */
/*# if defined(CONFIG_S3C2410)
	ldr	r1, =0x3ff
	ldr	r0, =INTSUBMSK
	str	r1, [r0]
# endif*/

/* 2. 设置时钟 */

	ldr	r0, =ELFIN_CLOCK_POWER_BASE
	// 设置分频
	// ARMCLK = MPLLout/ARMCLK Ratio = MPLLout/(ARMDIV+1) = 800/2 = 400MHz
	// HCLK = MPLLout/HCLK Ratio = MPLLout/( (PREDIV+1) * (HCLKDIV + 1) ) = 800/(3*2) = 133MHz
	// PCLK = HCLK/PCLKDIV = 133/2 = 66MHz
	ldr	r1, [r0, #CLKDIV0CON_OFFSET]
	bic	r1, r1, #0x37							// clear HCLKDIV,PCLKDIV,PREDIV
	bic	r1, r1, #(0xf<<9) 					// clear ARMCLKDIV
	ldr	r2, =CLK_DIV_VAL
	orr	r1, r1, r2
	str	r1, [r0, #CLKDIV0CON_OFFSET]

	// 设置locktime
	ldr	r1, =0xffff
	str	r1, [r0, #LOCKCON0_OFFSET]

	// 设置MPLL
	ldr	r1, =MPLL_VAL							// MPLLout = 400*12/(3*2^1) = 400*2 =  800MHz
	str	r1, [r0, #MPLLCON_OFFSET]

	// 设置时钟源
	ldr	r1, [r0, #CLKSRCCON_OFFSET]
	orr	r1, r1, #0x10
	str	r1, [r0, #CLKSRCCON_OFFSET]

//	/* 启动ICACHE */
//	mrc	p15, 0, r0, c1, c0, 0		/* read control reg */
//	orr r0, r0, #(1<<12)
//	mcr	p15, 0, r0, c1, c0, 0		/* write it back */

	ldr sp, =0x00002000			/* 栈底地址，8K */

	bl uart_init					/* C语言初始化UART，需要先设置SP */

	mov r0, #0
	bl put_start_info

	mov r0, #1
	bl put_start_info

/* 3. 初始化SDRAM */
	bl sdr_ctrl_asm_init			/* 友善之臂的SDRAM初始化 */
//	bl SDRAM_Init					/* csdn裸机教程的SDRAM初始化 */
	bl memory_test				/* 测试SDRAM */

#endif	/* CONFIG_S3C24X0 */

	/*
	 * we do sys-critical inits only at reboot,
	 * not when booting from ram!
	 */
#ifndef CONFIG_SKIP_LOWLEVEL_INIT
	/* 清I/D Cache
	 * 关闭MMU
	 */
	bl	cpu_init_crit
#endif

//loop:
//	b loop
/*
led_blink:
	// 设置GPBDAT，使GPB_5/6引脚输出高电平，LED灭
	ldr r1, =0x56000014 					
	mov r0, #(0x1<<1)
	str r0, [r1]

	mov r0, #2
	bl put_start_info

	// 延时 
	bl delay

	mov r0, #3
	bl put_start_info

	// 延时
	bl delay	

	mov r0, #4
	bl put_start_info

	b led_blink
delay:
	mov r0, #0x1000000
delay_loop:
	cmp r0, #0
	sub r0, r0, #1
	bne delay_loop
	mov pc, lr	*/
	
	mov r0, #5
	bl put_start_info

	ldr	sp, =(CONFIG_SYS_INIT_SP_ADDR)	/* 设置栈在SDRAM */
	bic	sp, sp, #7 /* 8-byte alignment for ABI compliance */

	bl nand_init_ll				/* 调用mybootloader中的nand初始化函数 */

	mov r0, #0					/* NAND启动时，bootloader存放在NANDFLASH的地址 */
//	ldr r1, =_start				/* 链接的起始地址，带"="的ldr是伪汇编，会把_start的值存在 */
								/* 一个地方，再从这个地方取值，而这个地方的地址是不确定的 */
								/* 可能在8KB之外。 */
	ldr r1, _TEXT_BASE			/* _TEXT_BASE在代码最前边，地址不会在8KB之外。而且这句 */
								/* ldr不是伪汇编 */
	ldr r2, _bss_start_ofs			/* 获取bootloader总长度(不包含bss段) */
	
	/* 把代码从NAND复制到SDRAM */
	bl copy_code_to_sdram		/* nand src, sdram dst, len */
	bl clean_bss

	mov r0, #5
	bl put_start_info
	mov r0, #5
	bl put_start_info
	mov r0, #5
	bl put_start_info

	/* 从stepping stone跳转到SDRAM运行 */
	ldr pc, =call_board_init_f		/* 伪指令，编译成mov pc,数值 或者 ldr pc,label
									跳转到SDRAM继续执行 */

	
/* Set stackpointer in internal RAM to call board_init_f */
call_board_init_f:

	mov r0, #6
	bl put_start_info
	mov r0, #6
	bl put_start_info
	mov r0, #6
	bl put_start_info
	
	/* 这里仍未开启MMU，会设置base_sp */
	ldr	r0,=0x00000000
	bl	board_init_f

	/* unsigned int 的值存在R0里，正好给board_init_r
	 * r1 = 0x33f00000
	 */
	ldr r1, _TEXT_BASE
	/* 重新设置栈 */
	ldr sp, base_sp
	
	/* 调用第二阶段代码，启动MMU */
	bl board_init_r

/*
 * We are done. Do not return, instead branch to second part of board
 * initialization, now running from RAM.
 */
#ifdef CONFIG_NAND_SPL
	ldr     r0, _nand_boot_ofs
	mov	pc, r0

_nand_boot_ofs:
	.word nand_boot
#else
	ldr	r0, _board_init_r_ofs
	adr	r1, _start
	add	lr, r0, r1
	add	lr, lr, r9
	/* setup parameters for board_init_r */
	mov	r0, r5		/* gd_t */
	mov	r1, r6		/* dest_addr */
	/* jump to it ... */
	mov	pc, lr

_board_init_r_ofs:
	.word board_init_r - _start
#endif

_rel_dyn_start_ofs:
	.word __rel_dyn_start - _start
_rel_dyn_end_ofs:
	.word __rel_dyn_end - _start
_dynsym_start_ofs:
	.word __dynsym_start - _start

/*
 *************************************************************************
 *
 * CPU_init_critical registers
 *
 * setup important registers
 * setup memory timing
 *
 *************************************************************************
 */


#ifndef CONFIG_SKIP_LOWLEVEL_INIT
cpu_init_crit:
	/*
	 * flush v4 I/D caches
	 */
	mov	r0, #0
	mcr	p15, 0, r0, c7, c7, 0	/* flush v3/v4 cache */
	mcr	p15, 0, r0, c8, c7, 0	/* flush v4 TLB */

	/*
	 * disable MMU stuff and caches
	 */
	mrc	p15, 0, r0, c1, c0, 0
	bic	r0, r0, #0x00002300	@ clear bits 13, 9:8 (--V- --RS)
	bic	r0, r0, #0x00000087	@ clear bits 7, 2:0 (B--- -CAM)
	orr	r0, r0, #0x00000002	@ set bit 2 (A) Align
	orr	r0, r0, #0x00001000	@ set bit 12 (I) I-Cache
	mcr	p15, 0, r0, c1, c0, 0

	/*
	 * before relocating, we have to setup RAM timing
	 * because memory timing is board-dependend, you will
	 * find a lowlevel_init.S in your board directory.
	 */

	
	
//	mov	ip, lr
	push {lr}

	mov r0, #2
	bl put_start_info

	bl	lowlevel_init

	mov r0, #7
	bl put_start_info

//	mov	lr, ip

	pop {lr}
	
	mov	pc, lr
#endif /* CONFIG_SKIP_LOWLEVEL_INIT */

/*
 *************************************************************************
 *
 * Interrupt handling
 *
 *************************************************************************
 */

@
@ IRQ stack frame.
@
#define S_FRAME_SIZE	72

#define S_OLD_R0	68
#define S_PSR		64
#define S_PC		60
#define S_LR		56
#define S_SP		52

#define S_IP		48
#define S_FP		44
#define S_R10		40
#define S_R9		36
#define S_R8		32
#define S_R7		28
#define S_R6		24
#define S_R5		20
#define S_R4		16
#define S_R3		12
#define S_R2		8
#define S_R1		4
#define S_R0		0

#define MODE_SVC	0x13
#define I_BIT		0x80

/*
 * use bad_save_user_regs for abort/prefetch/undef/swi ...
 * use irq_save_user_regs / irq_restore_user_regs for IRQ/FIQ handling
 */

	.macro	bad_save_user_regs
	sub	sp, sp, #S_FRAME_SIZE
	stmia	sp, {r0 - r12}			@ Calling r0-r12
	ldr	r2, IRQ_STACK_START_IN
	ldmia	r2, {r2 - r3}			@ get pc, cpsr
	add	r0, sp, #S_FRAME_SIZE		@ restore sp_SVC

	add	r5, sp, #S_SP
	mov	r1, lr
	stmia	r5, {r0 - r3}			@ save sp_SVC, lr_SVC, pc, cpsr
	mov	r0, sp
	.endm

	.macro	irq_save_user_regs
	sub	sp, sp, #S_FRAME_SIZE
	stmia	sp, {r0 - r12}			@ Calling r0-r12
	add	r7, sp, #S_PC
	stmdb	r7, {sp, lr}^			@ Calling SP, LR
	str	lr, [r7, #0]			@ Save calling PC
	mrs	r6, spsr
	str	r6, [r7, #4]			@ Save CPSR
	str	r0, [r7, #8]			@ Save OLD_R0
	mov	r0, sp
	.endm

	.macro	irq_restore_user_regs
	ldmia	sp, {r0 - lr}^			@ Calling r0 - lr
	mov	r0, r0
	ldr	lr, [sp, #S_PC]			@ Get PC
	add	sp, sp, #S_FRAME_SIZE
	/* return & move spsr_svc into cpsr */
	subs	pc, lr, #4
	.endm

	.macro get_bad_stack
	ldr	r13, IRQ_STACK_START_IN		@ setup our mode stack

	str	lr, [r13]			@ save caller lr / spsr
	mrs	lr, spsr
	str	lr, [r13, #4]

	mov	r13, #MODE_SVC			@ prepare SVC-Mode
	@ msr	spsr_c, r13
	msr	spsr, r13
	mov	lr, pc
	movs	pc, lr
	.endm

	.macro get_irq_stack			@ setup IRQ stack
	ldr	sp, IRQ_STACK_START
	.endm

	.macro get_fiq_stack			@ setup FIQ stack
	ldr	sp, FIQ_STACK_START
	.endm

/*
 * exception handlers
 */
	.align  5
undefined_instruction:
	get_bad_stack
	bad_save_user_regs
	bl	do_undefined_instruction

	.align	5
software_interrupt:
	get_bad_stack
	bad_save_user_regs
	bl	do_software_interrupt

	.align	5
prefetch_abort:
	get_bad_stack
	bad_save_user_regs
	bl	do_prefetch_abort

	.align	5
data_abort:
	get_bad_stack
	bad_save_user_regs
	bl	do_data_abort

	.align	5
not_used:
	get_bad_stack
	bad_save_user_regs
	bl	do_not_used

#ifdef CONFIG_USE_IRQ

	.align	5
irq:
	get_irq_stack
	irq_save_user_regs
	bl	do_irq
	irq_restore_user_regs

	.align	5
fiq:
	get_fiq_stack
	/* someone ought to write a more effiction fiq_save_user_regs */
	irq_save_user_regs
	bl	do_fiq
	irq_restore_user_regs

#else

	.align	5
irq:
	get_bad_stack
	bad_save_user_regs
	bl	do_irq

	.align	5
fiq:
	get_bad_stack
	bad_save_user_regs
	bl	do_fiq

#endif



