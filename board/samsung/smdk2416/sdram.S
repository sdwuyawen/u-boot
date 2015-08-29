///////////////////////////////////////////////////////////////
// 本程序只供学习使用，未经本公司许可，不得用于其它任何商业用途
// 适用开发板型号:Tiny2416、Mini2451、Tiny2451
// 技术论坛:www.arm9home.net
// 修改日期:2013/7/1
// 版权所有，盗版必究。
// Copyright(C) 广州友善之臂计算机科技有限公司
// All rights reserved							
///////////////////////////////////////////////////////////////

#define ELFIN_MEMCTL_BASE		0x48000000
#define BANKCFG_OFFSET			0x00
#define BANKCON1_OFFSET			0x04
#define BANKCON2_OFFSET			0x08
#define BANKCON3_OFFSET			0x0c
#define REFRESH_OFFSET			0x10
#define TIMEOUT_OFFSET			0x14

#define INIT_NORMAL				0x0
#define INIT_PALL				0x1
#define INIT_MRS				0x2
#define INIT_EMRS				0x3
#define INIT_MASK				0x3

#define PHYS_SDRAM_1			0x30000000 /* SDRAM Bank #1 */
#define PHYS_SDRAM_1_SIZE		0x04000000 /* 64 MB */
#define CFG_BANK_CFG_VAL_DDR2	0x00049253
#define CFG_BANK_CON2_VAL_DDR2	0x006E0035

/* SDRAM配置 */
#define	CFG_BANK_CFG_VAL			0x0004920d
#define	CFG_BANK_CON1_VAL		0x04000040
#define	CFG_BANK_CON2_VAL		0x0057003a
#define	CFG_BANK_CON3_VAL		0x80000030
#define	CFG_BANK_REFRESH_VAL		0x00000313

	
sdram_bank_set_val:
	.word	CFG_BANK_CFG_VAL
	.word	CFG_BANK_CON1_VAL
	.word	CFG_BANK_CON2_VAL
	.word	CFG_BANK_CON3_VAL
	.word	CFG_BANK_REFRESH_VAL


.global sdr_ctrl_asm_init
sdr_ctrl_asm_init:

	push {lr}
	
	adr r0, sdram_bank_set_val		/* 当前地址 */
	bl putinthex
	ldr r0, =0x12345678		/* 当前地址 */
	bl putinthex
	ldr r0, sdram_bank_set_val		/* 当前地址 */
		
	mov r12,#2

	/* Set GPK port when using x32 bus width. */
	ldr	r2,=0x560000e0
	ldr r2,[r2]
	ldr	r1,=0xaaaaaaaa	@ set Sdata[31:16]
	str	r1, [r2]

	/* read setting value from structure */
	ldr	r4, =ELFIN_MEMCTL_BASE
	ldmia	r0!, {r5-r11}
	stmia	r4!, {r5-r9}

1000:
	ldr	r4, =ELFIN_MEMCTL_BASE
	ldr	r1, [r4, #BANKCON1_OFFSET]
	ldr	r2, =0x40000000			/* DDR DSQInDLL Value Setting */
	orr	r1, r1, r2
	bic	r1, r1, #INIT_MASK

	/* Step 1: issue PALL */
	orr	r2, r1, #INIT_PALL
	str	r2, [r4, #BANKCON1_OFFSET]

	/* Step 2: write 0xff into the refresh timer */
	mov	r3, #0xff
	str	r3, [r4, #REFRESH_OFFSET]

	/* Step 3: wait more than 120 clk */
	mov	r3, #0x100
1:	subs	r3, r3, #1
	bne	1b

	/* Step 4: issue MRS */
	orr	r2, r1, #INIT_MRS
	str	r2, [r4, #BANKCON1_OFFSET]

	/* Step 5: nornal operation value into the refresh timer */
	str	r9, [r4, #REFRESH_OFFSET]

	/* Step 6: issue EMRS */
	orr	r2, r1, #INIT_EMRS
	str	r2, [r4, #BANKCON1_OFFSET]

	/* Step 7: Normal Mode */
	orr	r2, r1, #INIT_NORMAL
	str	r2, [r4, #BANKCON1_OFFSET]

	ldr	r6, =(PHYS_SDRAM_1+0x4)
	ldr	r7, =0x24564236
	swp	r8, r7, [r6]
	swp	r5, r8, [r6]
	cmp	r7, r5
	beq	1001f

	sub	r12, r12, #1
	cmp	r12, #0
	beq	1004f

1002:	stmia	r4!, {r10-r11}
	b	1000b

/* boyko : Memory Type DDR2 */
1004:	ldr	r4, =ELFIN_MEMCTL_BASE

	/* Step 1: BANKCFG Setting */
	ldr	r2, =CFG_BANK_CFG_VAL_DDR2
	str	r2, [r4, #BANKCFG_OFFSET]

	ldr	r1, =0x44000040
	str	r1, [r4, #BANKCON1_OFFSET]

	/* Step 2: BANKCON2 Setting */
	ldr	r2, =CFG_BANK_CON2_VAL_DDR2
	str	r2, [r4, #BANKCON2_OFFSET]

	/* Step 3: issue PALL */
	orr	r2, r1, #INIT_PALL
	str	r2, [r4, #BANKCON1_OFFSET]

	/* Step 4: Issue a EMRS2 command */
	ldr	r2, =0x80000000
	str	r2, [r4, #BANKCON3_OFFSET]

	orr	r2, r1, #INIT_EMRS
	str	r2, [r4, #BANKCON1_OFFSET]

	/* Step 5: Issue a EMRS3 command */
	ldr	r2, =0xc0000000
	str	r2, [r4, #BANKCON3_OFFSET]

	orr	r2, r1, #INIT_EMRS
	str	r2, [r4, #BANKCON1_OFFSET]

	/* Step 6: Issue a EMRS1 command */
	ldr	r2, =0x44000000
	str	r2, [r4, #BANKCON3_OFFSET]

	orr	r2, r1, #INIT_EMRS
	str	r2, [r4, #BANKCON1_OFFSET]

	/* Step 7: issue MRS */
	ldr	r2, =0x44000130
	str	r2, [r4, #BANKCON3_OFFSET]

	orr	r2, r1, #INIT_MRS
	str	r2, [r4, #BANKCON1_OFFSET]

	/* Step 8: issue PALL */
	orr	r2, r1, #INIT_PALL
	str	r2, [r4, #BANKCON1_OFFSET]

	/* Step 9: write 0xff into the refresh timer */
	mov	r3, #0xff
	str	r3, [r4, #REFRESH_OFFSET]

	/* Step 10: wait more than 120 clk */
	mov	r3, #0x200
10:	subs	r3, r3, #1
	bne	10b

	/* Step 11: issue MRS */
	ldr	r2, =0x44000030
	str	r2, [r4, #BANKCON3_OFFSET]

	orr	r2, r1, #INIT_MRS
	str	r2, [r4, #BANKCON1_OFFSET]

	/* Step 12: Issue a EMRS1 command */
	ldr	r2, =0x47800030
	str	r2, [r4, #BANKCON3_OFFSET]

	orr	r2, r1, #INIT_EMRS
	str	r2, [r4, #BANKCON1_OFFSET]

	ldr	r2, =0x44000030
	str	r2, [r4, #BANKCON3_OFFSET]

	orr	r2, r1, #INIT_EMRS
	str	r2, [r4, #BANKCON1_OFFSET]

	/* Step 13: write 0x400 into the refresh timer */
	mov	r3, #0x400
	str	r3, [r4, #REFRESH_OFFSET]

	/* Step 14: Normal Mode */
	orr	r2, r1, #INIT_NORMAL
	str	r2, [r4, #BANKCON1_OFFSET]
/* boyko : END - Memory Type DDR2 */

	mov r0, #3
	bl put_start_info

	mov r0, #4
	bl put_start_info

	mov r0, #6
	bl put_start_info
	
	pop {lr}
	
1001:	mov	pc, lr




//DRAM controller base address
.equ	BANKCFG,	0x48000000
.equ	BANKCON1,	0x48000004
.equ	BANKCON2,	0x48000008
.equ	BANKCON3,	0x4800000C
.equ	REFRESH,		0x48000010
.equ	TIMEOUT,	0x48000014
		
//.text
.global  SDRAM_Init
// K4T51163QJ-BCE79(DDR2//400M 5-5-5),64MB,Raw Addr A0~A12,Column Addr A0~A9
// 设置DDR0 13位行地址，10位列地址，DDR2接口，16位总线
// DDR命令根据nRAS,nCAS,nWE,nCS控制总线分辨
// Active命令,打开行及bank地址
// Read命令,在Active后,打开列地址读
// Write命令,在Active后,打开列地址写
// Precharge命令,关闭bank,根据A[10]确定关闭指定或所有bank
// AUTO REFRESH or SELF REFRESH命令,刷新命令
// LOAD MODE REGISTER命令,写模式寄存器

SDRAM_Init:
		LDR		R0, =BANKCFG
		LDR		R1, =(2<<17)+(2<<11)+(0<<6)+(1<<1)+(1<<0)
		STR		R1, [R0]
// DQS delay 3,Write buffer,Auto pre-charge,bank address 在高位 		
		LDR		R0, =BANKCON1
		LDR		R1, =(3<<28)+(1<<26)+(1<<8)+(0<<7)+ \
							 (1<<6)+(0<<5)+(1<<4)
		STR		R1, [R0]		
				
// s3c2416 ddr2寄存器的clk设置值是相对HCLK的
// RAS [23:20] Row active time 45ns HCLK=133M DDR2=266M 6clock
// Active命令到Precharge命令的最小时间45ns
// ARFC [19:16] Row cycle time tRFC=105ns 14clock
// 指令刷新时间105ns
// CAS Latency [5:4] CAS latency control 12.5ns 2clock
// Read/Write命令发出后经过5tCK=12.5ns数据才有效
// tRCD [3:2] RAS to CAS delay 12.5ns 2clock
// Active命令需经5tCK=12.5ns后才发出Read/Write命令
// tRP [1:0] Row pre-charge time 12.5ns 2clock
// Precharge命令到发送Active命令5tCK=12.5ns
// 故两个Active命令所需的最小时间 tRC=tRAS+tRP=57.5ns
		LDR		R0, =BANKCON2
		LDR		R1, =(6<<20)+(13<<16)+(3<<4)+(2<<2)+(2<<0)
		STR		R1, [R0]	

// issue a PALL(pre-charge all) command,即Precharge命令
		LDR		R0, =BANKCON1
		LDR		R1, [R0]
		BIC		R1, R1, #0x03
		ORR		R1, R1, #0x01
		STR		R1, [R0]

// issue an EMRS(extern mode register) command to EMR(2)
		LDR		R0, =BANKCON3
		LDR		R1, =(0x2<<30)+(0<<23)+(0<<19)+(0<<16)
		STR		R1, [R0]
		LDR		R0, =BANKCON1
		LDR		R1, [R0]
		ORR		R1, R1, #0x03				
		STR		R1, [R0]

// issue an EMRS(extern mode register) command to EMR(3)
		LDR		R0, =BANKCON3
		LDR		R1, =(0x3<<30)
		STR		R1, [R0]
		LDR		R0, =BANKCON1
		LDR		R1, [R0]
		ORR		R1, R1, #0x03				
		STR		R1, [R0]
				
// issue an EMRS to enable DLL and RDQS, nDQS, ODT disable
		LDR		R0, =BANKCON3
		LDR		R1, =0xFFFF0000
		LDR		R2, [R0]
		BIC		R2, R2, R1
		LDR		R1, =(0x1<<30)+(0<<28)+(0<<27)+(1<<26)+ \
					 (7<<23)+(0<<19)+(0<<22)+(0<<18)+ \
					 (0x0<<17)+(0<<16)				
		ORR		R1, R1, R2
		STR		R1, [R0]
		LDR		R0, =BANKCON1
		LDR		R1, [R0]
		ORR		R1, R1, #0x03				
		STR		R1, [R0]

// issue a mode register set command for DLL reset 
		LDR		R0, =BANKCON3
		LDR		R1, =0x0000FFFF
		LDR		R2, [R0]
		BIC		R2, R2, R1
		LDR		R1, =(0x1<<9)+(1<<8)+(0<<7)+(3<<4)						
		ORR		R1, R1, R2
		STR		R1, [R0]
		LDR		R0, =BANKCON1
		LDR		R1, [R0]
		BIC		R1, R1, #0x03
		ORR		R1, R1, #0x02				
		STR		R1, [R0]
				
// Issue a PALL(pre-charge all) command	
		LDR		R1, [R0]
		BIC		R1, R1, #0x03
		ORR		R1, R1, #0x01
		STR		R1, [R0]
				
// Issue 2 or more auto-refresh commands
		LDR		R0, =REFRESH
		LDR		R1, =0x20
		STR		R1, [R0]
				

// Issue a MRS command with LOW to A8 to initialize device operation
		LDR		R0, =BANKCON3
		LDR		R1, =0x0000FFFF
		LDR		R2, [R0]
		BIC		R2, R2, R1
		LDR		R1, =(0x1<<9)+(0<<8)+(0<<7)+(3<<4)					
		ORR		R1, R1, R2
		STR		R1, [R0]
		LDR		R0, =BANKCON1
		LDR		R1, [R0]
		BIC		R1, R1, #0x03
		ORR		R1, R1, #0x02				
		STR		R1, [R0]
				
// Wait 200 clock, execute OCD Calibration
		LDR		R1, =200
tmpsub:		
		SUBS	R1, R1, #1
		BNE		tmpsub
				
// Issue a EMRS1 command to over OCD Mode Calibration
		LDR		R0, =BANKCON3
		LDR		R1, =0xFFFF0000
		LDR		R2, [R0]
		BIC		R2, R2, R1
		LDR		R1, =(0x1<<30)+(0<<28)+(0<<27)+(1<<26)+ \
					 (0<<23)+(0<<19)+(0<<22)+(0<<18)+ \
					 (0x0<<17)+(0<<16)				
		ORR		R1, R1, R2
		STR		R1, [R0]
		LDR		R0, =BANKCON1
		LDR		R1, [R0]
		ORR		R1, R1, #0x03				
		STR		R1, [R0]

// Refresh period is 7.8us, HCLK=100M, REFCYC=780
		LDR		R0, =REFRESH
		LDR		R1, =780
		STR		R1, [R0]

// issue a Normal mode
		LDR		R0, =BANKCON1
		LDR		R1, [R0]
		BIC		R1, R1, #0x03
		STR		R1, [R0]
				
		BX		LR
				
				

